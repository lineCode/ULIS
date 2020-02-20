// Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Fill.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Fill entry point functions.
* @copyright    Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Fill/Fill.h"
#include "Base/CPU.h"
#include "Base/Perf.h"
#include "Conv/Conv.h"
#include "Data/Block.h"
#include "Data/Pixel.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"
#include "Thread/ThreadPool.h"
#include <immintrin.h>
#include <memory>

ULIS2_NAMESPACE_BEGIN
#ifdef __AVX2__
void
InvokeFillMTProcessScanline_AX2( tByte* iDst, __m256i iSrc, const tSize iCount, const tSize iStride )
{
    tSize index;
    for( index = 0; index < ( iCount - 32 ); index += iStride )
    {
        _mm256_storeu_si256( (__m256i*)iDst, iSrc );
        iDst += iStride;
    }
    // Remaining unaligned scanline end:
    // avoid concurrent write on 256 bit with avx and perform a memcpy instead
    memcpy( iDst, &iSrc, iCount - index );
}
#endif // __AVX2__

#ifdef __SSE4_2__
void
InvokeFillMTProcessScanline_SSE( tByte* iDst, __m128i iSrc, const tSize iCount, const tSize iStride )
{
    tSize index;
    for( index = 0; index < ( iCount - 16 ); index += iStride )
    {
        _mm_storeu_si128( (__m128i*)iDst, iSrc );
        iDst += iStride;
    }
    // Remaining unaligned scanline end:
    // avoid concurrent write on 128 bit with SSE and perform a memcpy instead
    memcpy( iDst, &iSrc, iCount - index );
}
#endif // __SE4_2__

void
InvokeFillMTProcessScanline_MEM( tByte* iDst, std::shared_ptr< tByte >  iSrc, tSize iCount, tSize iStride )
{
    for( uint32 i = 0; i < iCount; ++i )
    {
        memcpy( iDst, iSrc.get(), iStride );
        iDst += iStride;
    }
}


void
Fill_imp( FThreadPool*              iPool
        , bool                      iBlocking
        , const FPerf&              iPerf
        , const FCPU&               iCPU
        , FBlock*                   iDst
        , std::shared_ptr< tByte >  iSrc
        , const FRect&              iRoi )
{
    const tSize bpc = iDst->BytesPerSample();
    const tSize spp = iDst->SamplesPerPixel();
    const tSize bpp = iDst->BytesPerPixel();
    const tSize w   = iDst->Width();
    const tSize bps = iDst->BytesPerScanLine();
    const tSize dsh = iRoi.x * bpp;
    tByte*      dsb = iDst->DataPtr() + dsh;
    #define DST dsb + ( ( iRoi.y + pLINE ) * bps )

#ifdef __AVX2__
    if( iPerf.UseAVX2() && iCPU.info.HW_AVX2 && bpp <= 32 && bps >= 32 )
    {
        const tSize stride = 32 - ( 32 % bpp );
        tByte* srcb = new tByte[32];
        #ifdef ULIS2_DEBUG
        memset( srcb, 0, 32 );
        #endif // ULIS2_DEBUG
        for( tSize i = 0; i < stride; i+= bpp )
            memcpy( (void*)( ( srcb ) + i ), iSrc.get(), bpp );
        __m256i src = _mm256_lddqu_si256( (const __m256i*)srcb );
        delete [] srcb;
        const tSize count = iRoi.w * bpp;
        ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iRoi.h, InvokeFillMTProcessScanline_AX2, DST, src, count, stride )
    }
    else
#endif // __AVX2__
#ifdef __SSE4_2__
    if( iPerf.UseSSE4_2() && iCPU.info.HW_SSE42 && bpp <= 16 && bps >= 16 )
    {
        const tSize stride = 16 - ( 16 % bpp );
        tByte* srcb = new tByte[16];
        #ifdef ULIS2_DEBUG
        memset( srcb, 0, 16 );
        #endif // ULIS2_DEBUG
        for( tSize i = 0; i < stride; i+= bpp )
            memcpy( (void*)( ( srcb ) + i ), iSrc.get(), bpp );
        __m128i src = _mm_lddqu_si128( (const __m128i*)srcb );
        delete [] srcb;
        const tSize count = iRoi.w * bpp;
        ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iRoi.h, InvokeFillMTProcessScanline_SSE, DST, src, count, stride )
    }
    else
#endif // __SSE4_2__
    {
        ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iRoi.h, InvokeFillMTProcessScanline_MEM, DST, iSrc, iRoi.w, bpp )
    }
}

void
Fill( FThreadPool*  iPool
    , bool          iBlocking
    , const FPerf&  iPerf
    , const FCPU&   iCPU
    , FBlock*       iDst
    , const IPixel& iColor
    , bool          iCallInvalidCB )
{
    FillRect( iPool, iBlocking, iPerf, iCPU, iDst, iColor, iDst->Rect(), iCallInvalidCB );
}


void
FillRect( FThreadPool*  iPool
        , bool          iBlocking
        , const FPerf&  iPerf
        , const FCPU&   iCPU
        , FBlock*       iDst
        , const IPixel& iColor
        , const FRect&  iRect
        , bool          iCallInvalidCB )
{
    ULIS2_ASSERT( iPool,                                    "Bad pool" );
    ULIS2_ASSERT( iDst,                                     "Bad destination" );
    ULIS2_ASSERT( !( (!iBlocking) && (iCallInvalidCB ) ),   "Calling invalid CB on non-blocking operation may induce race condition and undefined behaviours." );
    FPixel color( iDst->Format() );
    Conv( iColor, color );
    std::shared_ptr< tByte > src( new tByte[ color.Depth() ], std::default_delete< tByte[] >() );
    memcpy( src.get(), color.Ptr(), color.Depth() );

    FRect roi = iRect & iDst->Rect();

    if( roi.Area() <= 0 )
        return;

    Fill_imp( iPool, iBlocking, iPerf, iCPU, iDst, src, roi );
    iDst->Invalidate( roi, iCallInvalidCB );
}


ULIS2_NAMESPACE_END

