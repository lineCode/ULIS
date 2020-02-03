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

ULIS2_NAMESPACE_BEGIN
void
TraceText( FThreadPool*         iPool
         , bool                 iBlocking
         , const FPerf&         iPerf
         , const FCPU&          iCPU
         , bool                 iAntialiasing
         , FBlock*              iDst
         , const std::string&   iText
         , const FFont&         iFont
         , int                  iSize
         , const IPixel&        iColor
         , const glm::vec2&     iPos
         , const glm::mat2&     iTransform
         , bool                 iCallInvalidCB )
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

ULIS2_NAMESPACE_END

