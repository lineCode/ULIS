// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Clear.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Clear entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Clear/Clear.h"
#include "Data/Block.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"

ULIS2_NAMESPACE_BEGIN
void
InvokeFillMTProcessScanline_AX2( tByte* iDst, const tSize iCount, const tSize iStride )
{
    tSize index;
    for( index = 0; index < ( iCount - 32 ); index += iStride )
    {
        _mm256_storeu_si256( (__m256i*)iDst, _mm256_setzero_si256() );
        iDst += iStride;
    }
    // Remaining unaligned scanline end:
    // avoid concurrent write on 256 bit with avx and perform a memset instead
    memset( iDst, 0, iCount - index );
}


void
InvokeFillMTProcessScanline_SSE( tByte* iDst, const tSize iCount, const tSize iStride )
{
    tSize index;
    for( index = 0; index < ( iCount - 16 ); index += iStride )
    {
        _mm_storeu_si128( (__m128i*)iDst, _mm_setzero_si128() );
        iDst += iStride;
    }
    // Remaining unaligned scanline end:
    // avoid concurrent write on 128 bit with SSE and perform a memset instead
    memset( iDst, 0, iCount - index );
}


void
InvokeFillMTProcessScanline_MEM( tByte* iDst, tSize iCount, tSize iStride )
{
    memset( iDst, 0, iCount );
}


void
ClearMT( FThreadPool&   iPool
       , FBlock*        iDst
       , const FRect&   iRoi
       , const FPerf&   iPerf )
{
    const tSize bpc = iDst->BytesPerSample();
    const tSize spp = iDst->SamplesPerPixel();
    const tSize bpp = bpc * spp;
    const tSize w   = iDst->Width();
    const tSize bps = bpp * w;
    const tSize dsh = iRoi.x * bpp;
    tByte*      dsb = iDst->DataPtr() + dsh;
    #define DST dsb + ( ( iRoi.y + iLine ) * bps )
    if( iPerf.UseAVX2() )
    {
        const tSize stride = 32 - ( 32 % bpp );
        const tSize count = iRoi.w * bpp;
        ParallelFor( iPool, iRoi.h, iPerf, ULIS2_PF_CALL { InvokeFillMTProcessScanline_AX2( DST, count, stride ); } );
    }
    else if( iPerf.UseSSE4_2() )
    {
        const tSize stride = 16 - ( 16 % bpp );
        const tSize count = iRoi.w * bpp;
        ParallelFor( iPool, iRoi.h, iPerf, ULIS2_PF_CALL { InvokeFillMTProcessScanline_SSE( DST, count, stride ); } );
    }
    else
    {
        ParallelFor( iPool, iRoi.h, iPerf, ULIS2_PF_CALL { InvokeFillMTProcessScanline_MEM( DST, iRoi.w, bpp ); } );
    }
}


void
ClearMono( FBlock*      iDst
         , const FRect& iRoi )
{
    const tSize bpc = iDst->BytesPerSample();
    const tSize spp = iDst->SamplesPerPixel();
    const tSize bpp = bpc * spp;
    const tSize w   = iDst->Width();
    const tSize h   = iDst->Height();
    const tSize bps = bpp * w;
    const tSize num = w * h;
    tByte*      dst = iDst->DataPtr() + iRoi.y * bps + iRoi.x * bpp;

    for( uint32 i = 0; i < num; ++i )
    {
        memcpy( dst, 0, bpp );
        dst += bpp;
    }
}


void
Clear( FThreadPool&     iPool
     , FBlock*          iDst
     , const FPerf&     iPerf
     , bool             iCallInvalidCB )
{
    ClearRect( iPool, iDst, iDst->Rect(), iPerf, iCallInvalidCB );
}


void
ClearRect( FThreadPool& iPool
         , FBlock*      iDst
         , const FRect& iRect
         , const FPerf& iPerf
         , bool         iCallInvalidCB )
{
    ULIS2_ASSERT( iDst, "Bad destination" );
    FRect roi = iRect & iDst->Rect();

    if( roi.Area() <= 0 )
        return;

    if( iPerf.UseMT() )
        ClearMT( iPool, iDst, roi, iPerf );
    else
        ClearMono( iDst, roi );

    iDst->Invalidate( roi, iCallInvalidCB );
}


void
ClearRaw( FBlock*   iDst
        , bool      iCallInvalidCB )
{
    ULIS2_ASSERT( iDst, "Bad destination" );
    // One call, supposedly more efficient for small block.
    memset( iDst->DataPtr(), 0, iDst->BytesTotal() );
}

ULIS2_NAMESPACE_END

