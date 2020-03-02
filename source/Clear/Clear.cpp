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

ULIS2_NAMESPACE_BEGIN
#ifdef __AVX2__
void InvokeFillMTProcessScanline_AX2( tByte* iDst, const tSize iCount, const tSize iStride ) {
    int64 index;
    for( index = 0; index < int64( iCount ) - 32; index += iStride ) {
        _mm256_storeu_si256( (__m256i*)iDst, _mm256_setzero_si256() );
        iDst += iStride;
    }
    // Remaining unaligned scanline end: avoid concurrent write on 256 bit with avx and perform a memset instead
    memset( iDst, 0, iCount - index );
}
#endif // __AVX2__

#ifdef __SSE4_2__
void InvokeFillMTProcessScanline_SSE4_2( tByte* iDst, const tSize iCount, const tSize iStride ) {
    int64 index;
    for( index = 0; index < int64( iCount ) - 16; index += iStride ) {
        _mm_storeu_si128( (__m128i*)iDst, _mm_setzero_si128() );
        iDst += iStride;
    }
    // Remaining unaligned scanline end: avoid concurrent write on 128 bit with SSE and perform a memset instead
    memset( iDst, 0, iCount - index );
}
#endif // __SE4_2__

void InvokeFillMTProcessScanline_MEM( tByte* iDst, tSize iCount, tSize iStride ) {
    memset( iDst, 0, iCount );
}

void Clear_imp( const FClearInfo& iClearParams ) {
    const FFormatInfo& fmtInfo = iClearParams.destination->FormatInfo();
    const tSize bpp = fmtInfo.BPP;
    const tSize w   = iClearParams.destination->Width();
    const tSize bps = iClearParams.destination->BytesPerScanLine();
    const tSize dsh = iClearParams.area.x * bpp;
    tByte*      dsb = iClearParams.destination->DataPtr() + dsh;
    #define DST dsb + ( ( iClearParams.area.y + static_cast< int64 >( pLINE ) ) * static_cast< int64 >( bps ) )

    #ifdef __AVX2__
    if( iClearParams.perfInfo.intent.UseAVX2() && gCpuInfo.info.HW_AVX2 && bps >= 32 ) {
        const tSize stride = 32;
        const tSize count = iClearParams.area.w * bpp;
        ULIS2_MACRO_INLINE_PARALLEL_FOR( iClearParams.perfInfo.intent, iClearParams.perfInfo.pool, iClearParams.perfInfo.blocking
                                       , iClearParams.area.h
                                       , InvokeFillMTProcessScanline_AX2, DST, count, stride )
    } else
    #endif
    #ifdef __SSE4_2__
    if( iClearParams.perfInfo.intent.UseSSE4_2() && gCpuInfo.info.HW_SSE42 && bps >= 16 ) {
        const tSize stride = 16;
        const tSize count = iClearParams.area.w * bpp;
        ULIS2_MACRO_INLINE_PARALLEL_FOR( iClearParams.perfInfo.intent, iClearParams.perfInfo.pool, iClearParams.perfInfo.blocking
                                       , iClearParams.area.h
                                       , InvokeFillMTProcessScanline_SSE4_2, DST, count, stride )
    } else
    #endif
    {
        ULIS2_MACRO_INLINE_PARALLEL_FOR( iClearParams.perfInfo.intent, iClearParams.perfInfo.pool, iClearParams.perfInfo.blocking
                                       , iClearParams.area.h
                                       , InvokeFillMTProcessScanline_MEM, DST, iClearParams.area.w, bpp )
    }
}

void Clear( const FClearInfo& iClearParams ) {
    // Assertions
    ULIS2_ASSERT( iClearParams.destination,                                             "Bad source."                                                       );
    ULIS2_ASSERT( !iClearParams.perfInfo.intent.UseMT() || iClearParams.perfInfo.pool,  "Multithreading flag is specified but no thread pool is provided."  );
    ULIS2_ASSERT( !iClearParams.perfInfo.callCB || iClearParams.perfInfo.blocking,      "Callback flag is specified on non-blocking operation."             );

    // Fit region of interest
    FRect roi = iClearParams.area & iClearParams.destination->Rect();

    // Check no-op
    if( roi.Area() <= 0 )
        return;

    FClearInfo forwardClearInfo = iClearParams;
    forwardClearInfo.area = roi;

    // Call
    Clear_imp( forwardClearInfo );

    // Invalid
    iClearParams.destination->Invalidate( roi, iClearParams.perfInfo.callCB );
}

void ClearRaw( FBlock* iDst, bool iCallInvalidCB ) {
    ULIS2_ASSERT( iDst, "Bad destination" );
    // One call, supposedly more efficient for small block.
    memset( iDst->DataPtr(), 0, iDst->BytesTotal() );
}

ULIS2_NAMESPACE_END

