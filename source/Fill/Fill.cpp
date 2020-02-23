// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Fill.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Fill entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Fill/Fill.h"
#include "Base/CPU.h"
#include "Conv/Conv.h"
#include "Data/Block.h"
#include "Data/Pixel.h"
#include "Thread/ParallelFor.h"
#include <immintrin.h>

ULIS2_NAMESPACE_BEGIN
#ifdef __AVX2__
void
InvokeFillMTProcessScanline_AX2( tByte* iDst, __m256i iSrc, const tSize iCount, const tSize iStride ) {
    tSize index = 0;
    for( index = 0; index < ( iCount - 32 ); index += iStride ) {
        _mm256_storeu_si256( (__m256i*)iDst, iSrc );
        iDst += iStride;
    }

    // Remaining unaligned scanline end: avoid concurrent write on 256 bit with avx and perform a memcpy instead
    memcpy( iDst, &iSrc, iCount - index );
}
#endif // __AVX2__

#ifdef __SSE4_2__
void
InvokeFillMTProcessScanline_SSE( tByte* iDst, __m128i iSrc, const tSize iCount, const tSize iStride ) {
    tSize index;
    for( index = 0; index < ( iCount - 16 ); index += iStride ) {
        _mm_storeu_si128( (__m128i*)iDst, iSrc );
        iDst += iStride;
    }
    // Remaining unaligned scanline end: avoid concurrent write on 128 bit with SSE and perform a memcpy instead
    memcpy( iDst, &iSrc, iCount - index );
}
#endif // __SE4_2__

void
InvokeFillMTProcessScanline_MEM( tByte* iDst, std::shared_ptr< const FPixelValue > iSrc, tSize iCount, tSize iStride ) {
    const tByte* src = iSrc->Ptr();
    for( uint32 i = 0; i < iCount; ++i ) {
        memcpy( iDst, src, iStride );
        iDst += iStride;
    }
}

void
Fill_imp( const FFormatInfo& iFmtInfo, const FFillInfo& iFillParams, std::shared_ptr< const FPixelValue > iColor ) {
    // Bake Params
    const tSize bpp     = iFmtInfo.BPP;
    const tSize bps     = iFillParams.destination->BytesPerScanLine();
    const tSize dsh     = iFillParams.area.x * bpp;
    tByte*      dsb     = iFillParams.destination->DataPtr() + dsh;
    const tByte* src    = iColor->Ptr();
    #define DST dsb + ( ( iFillParams.area.y + pLINE ) * bps )

#ifdef __AVX2__
    if( iFillParams.perfInfo.intent.UseAVX2() && gCpuInfo.info.HW_AVX2 && bpp <= 32 && bps >= 32 ) {
        tSize   count   = iFillParams.area.w * bpp;
        tSize   stride  = 32 - ( 32 % bpp );
        tByte*  srcb    = new tByte[32];

        for( tSize i = 0; i < stride; i+= bpp )
            memcpy( (void*)( ( srcb ) + i ), src, bpp );

        __m256i src = _mm256_lddqu_si256( (const __m256i*)srcb );

        delete [] srcb;

        ULIS2_MACRO_INLINE_PARALLEL_FOR( iFillParams.perfInfo.intent, iFillParams.perfInfo.pool, iFillParams.perfInfo.blocking
                                       , iFillParams.area.h
                                       , InvokeFillMTProcessScanline_AX2, DST, src, count, stride )
    } else
#endif
#ifdef __SSE4_2__
    if( iFillParams.perfInfo.intent.UseSSE4_2() && gCpuInfo.info.HW_SSE42 && bpp <= 16 && bps >= 16 ) {
        tSize   count   = iFillParams.area.w * bpp;
        tSize   stride  = 16 - ( 16 % bpp );
        tByte*  srcb    = new tByte[16];

        for( tSize i = 0; i < stride; i+= bpp )
            memcpy( (void*)( ( srcb ) + i ), src, bpp );

        __m128i src = _mm_lddqu_si128( (const __m128i*)srcb );

        delete [] srcb;

        ULIS2_MACRO_INLINE_PARALLEL_FOR( iFillParams.perfInfo.intent, iFillParams.perfInfo.pool, iFillParams.perfInfo.blocking
                                       , iFillParams.area.h
                                       , InvokeFillMTProcessScanline_SSE, DST, src, count, stride )
    } else
#endif
    {
        ULIS2_MACRO_INLINE_PARALLEL_FOR( iFillParams.perfInfo.intent, iFillParams.perfInfo.pool, iFillParams.perfInfo.blocking
                                       , iFillParams.area.h
                                       , InvokeFillMTProcessScanline_MEM, DST, iColor, iFillParams.area.w, bpp )
    }
}

void
Fill( const FFillInfo& iFillParams ) {
    // Assertions
    ULIS2_ASSERT( iFillParams.destination,                                              "Bad source."                                                       );
    ULIS2_ASSERT( !iFillParams.perfInfo.intent.UseMT() || iFillParams.perfInfo.pool,    "Multithreading flag is specified but no thread pool is provided."  );
    ULIS2_ASSERT( !iFillParams.perfInfo.callCB || iFillParams.perfInfo.blocking,        "Callback flag is specified on non-blocking operation."             );

    // Fit region of interest
    FRect roi = iFillParams.area & iFillParams.destination->Rect();

    // Check no-op
    if( roi.Area() <= 0 )
        return;

    // Bake color param, shared Ptr for thread safety and scope life time extension in non blocking multithreaded processing
    std::shared_ptr< FPixelValue > color = std::make_shared< FPixelValue >( iFillParams.destination->Format() );
    Conv( *iFillParams.color, *color );

    // Bake forward param
    FFillInfo forwardFillInfo = iFillParams;
    forwardFillInfo.area = roi;

    // Call
    Fill_imp( iFillParams.destination->FormatInfo(), forwardFillInfo, color );

    // Invalid
    iFillParams.destination->Invalidate( roi, iFillParams.perfInfo.callCB );
}

ULIS2_NAMESPACE_END

