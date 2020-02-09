// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Text.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Text entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Text/Text.h"
#include "Base/CPU.h"
#include "Base/Perf.h"
#include "Conv/Conv.h"
#include "Data/Block.h"
#include "Data/Pixel.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"
#include "Text/Font.h"
#include <immintrin.h>

#include "Text/Dispatch/Dispatch.ipp"

#include FT_GLYPH_H

ULIS2_NAMESPACE_BEGIN
void
RenderText( FThreadPool*          iPool
    , bool                  iBlocking
    , const FPerf&          iPerf
    , const FCPU&           iCPU
    , bool                  iAntialiasing
    , FBlock*               iDst
    , const std::string&    iText
    , const FFont&          iFont
    , int                   iSize
    , const IPixel&         iColor
    , const glm::vec2&      iPos
    , const glm::mat2&      iTransform
    , bool                  iCallInvalidCB )
{
    ULIS2_ASSERT( iPool,                                    "Bad pool" );
    ULIS2_ASSERT( iDst,                                     "Bad destination" );
    ULIS2_ASSERT( !( (!iBlocking) && (iCallInvalidCB ) ),   "Calling invalid CB on non-blocking operation may induce race condition and undefined behaviours." );

    FPixel nativeColor( iDst->Format() );
    Conv( iColor, nativeColor );
    const tByte* color = nativeColor.Ptr();

    FT_Matrix matrix;
    matrix.xx = (FT_Fixed)( iTransform[0].x * 0x10000L );
    matrix.xy = (FT_Fixed)( iTransform[0].y * 0x10000L );
    matrix.yx = (FT_Fixed)( iTransform[1].x * 0x10000L );
    matrix.yy = (FT_Fixed)( iTransform[1].y * 0x10000L );

    fpDispatchedTextFunc fptr = QueryDispatchedTextFunctionForParameters( iDst->Format(), iAntialiasing, iPerf, iCPU );
    if( fptr ) fptr( iPool, iBlocking, iPerf, iDst, iText, iFont, iSize, color, (int)iPos.x, (int)iPos.y, matrix );

    iDst->Invalidate( iCallInvalidCB );
}


FRect
Metrics( const std::string& iText
       , const FFont&       iFont
       , int                iSize
       , const glm::vec2&   iPos
       , const glm::mat2&   iTransform )
{
    FRect result;
    result.x = static_cast< int >( iPos.x );
    result.y = static_cast< int >( iPos.y );
    result.w = 1;
    result.h = 1;

    FT_Matrix matrix;
    matrix.xx = (FT_Fixed)( iTransform[0].x * 0x10000L );
    matrix.xy = (FT_Fixed)( iTransform[0].y * 0x10000L );
    matrix.yx = (FT_Fixed)( iTransform[1].x * 0x10000L );
    matrix.yy = (FT_Fixed)( iTransform[1].y * 0x10000L );

    const char* str = iText.c_str();
    int len = (int)iText.size();

    FT_GlyphSlot  slot;
    FT_Vector     pen;

    FT_Error error = 0;
    FT_Face face = iFont.Handle();
    error = FT_Set_Pixel_Sizes( face, 0, iSize );
    ULIS2_ERROR( !error, "Error setting face size" );

    slot = face->glyph;
    pen.x = 0;
    pen.y = 0;
    int autobaseline = (int)( iSize * 0.7 );

    for( int n = 0; n < len; ++n ) {
        FT_Set_Transform( face, &matrix, &pen );
        FT_UInt glyph_index = FT_Get_Char_Index( face, str[n] );
        error = FT_Load_Glyph( face, glyph_index, FT_LOAD_BITMAP_METRICS_ONLY );
        ULIS2_ERROR( !error, "Error loading glyph" );

        FRect box = FRect::FromXYWH( (int)iPos.x + slot->bitmap_left, (int)iPos.y + ( autobaseline - slot->bitmap_top ), slot->bitmap.width, slot->bitmap.rows );
        result = result | box;

        pen.x += slot->advance.x;
        pen.y += slot->advance.y;
    }

    return  result;
}

ULIS2_NAMESPACE_END

