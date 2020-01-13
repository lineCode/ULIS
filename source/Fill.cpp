// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Fill.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Fill entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Fill.h"
#include "Block.h"
#include "Pixel.h"
#include "Conv.h"
#include "Geometry.h"
#include "ParallelFor.h"

ULIS2_NAMESPACE_BEGIN
void Fill_mtd_mem_imp( FBlock*      iDst
                 , const tByte*     iSrc
                 , int32            iLine )
{
    const tSize bpp = iDst->BytesPerPixel();
    const tSize w   = iDst->Width();
    const tSize bps = bpp * w;
    tByte*      dst = iDst->DataPtr() + iLine * bps;
    for( uint32 i = 0; i < w; ++i )
    {
        memcpy( dst, iSrc, bpp );
        dst += bpp;
    }
}


void Fill_mono_mem_imp( FBlock*     iDst
                 , const tByte*     iSrc )
{
    const tSize bpp = iDst->BytesPerPixel();
    const tSize w   = iDst->Width();
    const tSize h   = iDst->Height();
    const tSize num = w * h;
    tByte* dst      = iDst->DataPtr();
    for( uint32 i = 0; i < num; ++i )
    {
        memcpy( dst, iSrc, bpp );
        dst += bpp;
    }
}


void Fill( FBlock*          iDst
         , const IPixel&    iColor
         , FThreadPool&     iPool
         , const FPerf&     iPerf
         , bool             iCallInvalidCB )
{
    FillRect( iDst, iColor, iDst->Rect(), iPool, iPerf, iCallInvalidCB );
}


void FillRect( FBlock*          iDst
             , const IPixel&    iColor
             , const FRect&     iRect
             , FThreadPool&     iPool
             , const FPerf&     iPerf
             , bool             iCallInvalidCB )
{
    ULIS2_ASSERT( iDst, "Bad destination" );
    FPixel color( iDst->Format() );
    Conv( iColor, color );
    const tByte* src = color.Ptr();
    FRect area = iRect & iDst->Rect();
    if( iPerf.mtd )
        ParallelFor( iPool, area.h, iPerf, ULIS2_PF_CALL { Fill_mtd_mem_imp( iDst, src, iLine ); } );
    else
        Fill_mono_mem_imp( iDst, src );

    iDst->Invalidate( area, iCallInvalidCB );
}


ULIS2_NAMESPACE_END

