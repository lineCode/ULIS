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
#include "Maths/Transform2D.h"

#include <immintrin.h>
#include <glm/mat2x2.hpp>
#include <glm/vec2.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include FT_GLYPH_H

#include "Text/Dispatch/Dispatch.ipp"


ULIS2_NAMESPACE_BEGIN
void
RenderText( const FTextInfo& iTextParams ) {
    // Assertions
    ULIS2_ASSERT( iTextParams.destination,                                              "Bad source."                                                       );
    ULIS2_ASSERT( !iTextParams.perfInfo.intent.UseMT() || iTextParams.perfInfo.pool,    "Multithreading flag is specified but no thread pool is provided."  );
    ULIS2_ASSERT( !iTextParams.perfInfo.callCB || iTextParams.perfInfo.blocking,        "Callback flag is specified on non-blocking operation."             );

    // Bake color param in destination model
    FPixelValue nativeColor( iTextParams.destination->Format() );
    Conv( *iTextParams.color, nativeColor );
    const tByte* colorBytes = nativeColor.Ptr();

    // Translate Matrix param
    const glm::mat3& _mat = iTextParams.transform->Matrix();
    FT_Matrix matrix;
    matrix.xx = (FT_Fixed)( _mat[0].x * 0x10000L );
    matrix.xy = (FT_Fixed)( _mat[0].y * 0x10000L );
    matrix.yx = (FT_Fixed)( _mat[1].x * 0x10000L );
    matrix.yy = (FT_Fixed)( _mat[1].y * 0x10000L );
    int dx = static_cast< int >( _mat[2].x );
    int dy = static_cast< int >( _mat[2].y );

    // Bake forward params
    _FPrivateTextInfo forwardParams = {};
    forwardParams.destination       = iTextParams.destination;
    forwardParams.text              = iTextParams.text;
    forwardParams.font              = iTextParams.font;
    forwardParams.size              = iTextParams.size;
    forwardParams.color             = colorBytes;
    forwardParams.matrix            = &matrix;
    forwardParams.position          = FVec2I( dx, dy );
    forwardParams.antialiasingFlag  = iTextParams.antialiasingFlag;
    forwardParams.perfInfo          = iTextParams.perfInfo;

    // Query
    fpDispatchedTextFunc fptr = QueryDispatchedTextFunctionForParameters( iTextParams );

    // Call
    if( fptr )
        fptr( forwardParams );

    // Invalidate
    iTextParams.destination->Invalidate( iTextParams.perfInfo.callCB );
}


FRect
TextMetrics( const FTextMetricsInfo& iTextMetricsParams ) {
    const glm::mat3& _mat = iTextMetricsParams.transform->Matrix();
    FT_Matrix matrix;
    matrix.xx = (FT_Fixed)( _mat[0].x * 0x10000L );
    matrix.xy = (FT_Fixed)( _mat[0].y * 0x10000L );
    matrix.yx = (FT_Fixed)( _mat[1].x * 0x10000L );
    matrix.yy = (FT_Fixed)( _mat[1].y * 0x10000L );
    int dx = static_cast< int >( _mat[2].x );
    int dy = static_cast< int >( _mat[2].y );

    FRect result;
    result.x = static_cast< int >( dx );
    result.y = static_cast< int >( dy );
    result.w = 1;
    result.h = 1;

    const char* str = iTextMetricsParams.text.c_str();
    int len = (int)iTextMetricsParams.text.size();

    FT_GlyphSlot  slot;
    FT_Vector     pen;

    FT_Error error = 0;
    FT_Face face = iTextMetricsParams.font->Handle();
    error = FT_Set_Pixel_Sizes( face, 0, iTextMetricsParams.size );
    ULIS2_ERROR( !error, "Error setting face size" );

    slot = face->glyph;
    pen.x = 0;
    pen.y = 0;
    int autobaseline = (int)( iTextMetricsParams.size * 0.7 );

    for( int n = 0; n < len; ++n ) {
        FT_Set_Transform( face, &matrix, &pen );
        FT_UInt glyph_index = FT_Get_Char_Index( face, str[n] );
        error = FT_Load_Glyph( face, glyph_index, FT_LOAD_BITMAP_METRICS_ONLY );
        ULIS2_ERROR( !error, "Error loading glyph" );

        FRect box = FRect::FromXYWH( dx + slot->bitmap_left, dy + ( autobaseline - slot->bitmap_top ), slot->bitmap.width, slot->bitmap.rows );
        result = result | box;

        pen.x += slot->advance.x;
        pen.y += slot->advance.y;
    }

    return  result;
}

ULIS2_NAMESPACE_END

