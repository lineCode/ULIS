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
#include "Base/CPU.h"
#include "Base/Perf.h"
#include "Data/Block.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"
#include <immintrin.h>

ULIS2_NAMESPACE_BEGIN
#ifdef __AVX2__
void
InvokeFillMTProcessScanline_AX2( tByte* iDst, const tSize iCount, const tSize iStride )
{
    int64 index;
    for( index = 0; index < int64( iCount ) - 32; index += iStride )
    {
        _mm256_storeu_si256( (__m256i*)iDst, _mm256_setzero_si256() );
        iDst += iStride;
    }
    // Remaining unaligned scanline end:
    // avoid concurrent write on 256 bit with avx and perform a memset instead
    memset( iDst, 0, iCount - index );
}
#endif // __AVX2__

#ifdef __SSE4_2__
void
InvokeFillMTProcessScanline_SSE4_2( tByte* iDst, const tSize iCount, const tSize iStride )
{
    int64 index;
    for( index = 0; index < int64( iCount ) - 16; index += iStride )
    {
        _mm_storeu_si128( (__m128i*)iDst, _mm_setzero_si128() );
        iDst += iStride;
    }
    // Remaining unaligned scanline end:
    // avoid concurrent write on 128 bit with SSE and perform a memset instead
    memset( iDst, 0, iCount - index );
}
#endif // __SE4_2__

void
InvokeFillMTProcessScanline_MEM( tByte* iDst, tSize iCount, tSize iStride )
{
    memset( iDst, 0, iCount );
}


void
Clear_imp( FThreadPool* iPool
         , bool         iBlocking
         , const FPerf& iPerf
         , const FCPU&  iCPU
         , FBlock*      iDst
         , const FRect& iRoi )
{
    const tSize bpc = iDst->BytesPerSample();
    const tSize spp = iDst->SamplesPerPixel();
    const tSize bpp = iDst->BytesPerPixel();
    const tSize w   = iDst->Width();
    const tSize bps = iDst->BytesPerScanLine();
    const tSize dsh = iRoi.x * bpp;
    tByte*      dsb = iDst->DataPtr() + dsh;
    #define DST dsb + ( ( iRoi.y + iLine ) * bps )

    #ifdef __AVX2__
    if( iPerf.UseAVX2() && iCPU.info.HW_AVX2 && bps >= 32 )
    {
        const tSize stride = 32;
        const tSize count = iRoi.w * bpp;
        ParallelFor( *iPool, iBlocking, iPerf, iRoi.h, ULIS2_PF_CALL { InvokeFillMTProcessScanline_AX2( DST, count, stride ); } );
    }
    else
    #endif // __AVX2__
    #ifdef __SSE4_2__
    if( iPerf.UseSSE4_2() && iCPU.info.HW_SSE42 && bps >= 16 )
    {
        const tSize stride = 16;
        const tSize count = iRoi.w * bpp;
        ParallelFor( *iPool, iBlocking, iPerf, iRoi.h, ULIS2_PF_CALL { InvokeFillMTProcessScanline_SSE4_2( DST, count, stride ); } );
    }
    else
    #endif // __SSE4_2__
    {
        ParallelFor( *iPool, iBlocking , iPerf, iRoi.h, ULIS2_PF_CALL { InvokeFillMTProcessScanline_MEM( DST, iRoi.w, bpp ); } );
    }
}

void
Clear( FThreadPool* iPool
     , bool         iBlocking
     , const FPerf& iPerf
     , const FCPU&  iCPU
     , FBlock*      iDst
     , bool         iCallInvalidCB )
{
    ClearRect( iPool, iBlocking, iPerf, iCPU, iDst, iDst->Rect(), iCallInvalidCB );
}


void
ClearRect( FThreadPool* iPool
         , bool         iBlocking
         , const FPerf& iPerf
         , const FCPU&  iCPU
         , FBlock*      iDst
         , const FRect& iRect
         , bool         iCallInvalidCB )
{
    ULIS2_ASSERT( iPool,                                    "Bad pool" );
    ULIS2_ASSERT( iDst,                                     "Bad destination" );
    ULIS2_ASSERT( !( (!iBlocking) && (iCallInvalidCB ) ),   "Calling invalid CB on non-blocking operation may induce race condition and undefined behaviours." );
    FRect roi = iRect & iDst->Rect();

    if( roi.Area() <= 0 )
        return;

    Clear_imp( iPool, iBlocking, iPerf, iCPU, iDst, roi );
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

