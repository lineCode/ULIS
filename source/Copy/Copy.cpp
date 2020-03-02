// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Copy.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Copy entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Copy/Copy.h"
#include "Base/CPU.h"
#include "Base/Perf.h"
#include "Data/Block.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"
#include "Thread/ThreadPool.h"
#include <immintrin.h>

ULIS2_NAMESPACE_BEGIN

struct ULIS2_API _FPrivateCopyInfo {
    const FBlock*   source;
    FBlock*         destination;
    FRect           src_roi;
    FRect           dst_roi;
    FPerfInfo       perfInfo;
};


#ifdef __AVX2__
void InvokeCopyMTProcessScanline_AX2( tByte* iDst, const tByte* iSrc, const tSize iCount, const tSize iStride )
{
    tSize index;
    for( index = 0; index < ( iCount - 32 ); index += iStride )
    {
        _mm256_storeu_si256( (__m256i*)iDst, _mm256_loadu_si256( (const __m256i*)iSrc ) );
        iDst += iStride;
    }
    // Remaining unaligned scanline end:
    // avoid concurrent write on 256 bit with AVS and perform a memcpy instead
    memcpy( iDst, &iSrc, iCount - index );
}
#endif // __AVX2__

#ifdef __SSE4_2__
void InvokeCopyMTProcessScanline_SSE( tByte* iDst, const tByte* iSrc, const tSize iCount, const tSize iStride )
{
    tSize index;
    for( index = 0; index < ( iCount - 16 ); index += iStride )
    {
        _mm_storeu_si128( (__m128i*)iDst, _mm_loadu_si128( (const __m128i*)iSrc ) );
        iDst += iStride;
    }
    // Remaining unaligned scanline end:
    // avoid concurrent write on 128 bit with SSE and perform a memcpy instead
    memcpy( iDst, &iSrc, iCount - index );
}
#endif // __SE4_2__

void InvokeCopyMTProcessScanline_MEM( tByte* iDst, const tByte* iSrc, tSize iCount )
{
    memcpy( iDst, iSrc, iCount );
}


void
Copy_imp( std::shared_ptr< const _FPrivateCopyInfo > iCopyParams )
{
    const tSize bpc = iCopyParams->destination->BytesPerSample();
    const tSize spp = iCopyParams->destination->SamplesPerPixel();
    const tSize bpp = iCopyParams->destination->BytesPerPixel();
    const tSize w   = iCopyParams->destination->Width();
    const tSize bps = iCopyParams->destination->BytesPerScanLine();
    const tSize srh = iCopyParams->src_roi.x * bpp;
    const tSize dsh = iCopyParams->dst_roi.x * bpp;
    const tByte*srb = iCopyParams->source->DataPtr() + srh;
    const auto basesrcy = iCopyParams->src_roi.y;
    const auto basedsty = iCopyParams->dst_roi.y;
    tByte*      dsb = iCopyParams->destination->DataPtr() + dsh;
    #define SRC srb + ( ( basesrcy + pLINE ) * bps )
    #define DST dsb + ( ( basedsty + pLINE ) * bps )
    #ifdef __AVX2__
    if( iCopyParams->perfInfo.intent.UseAVX2() && gCpuInfo.info.HW_AVX2 && bpp <= 32 && bps >= 32 )
    {
        const tSize stride = 32;
        const tSize count = iCopyParams->src_roi.w;

        ULIS2_MACRO_INLINE_PARALLEL_FOR( iCopyParams->perfInfo.intent, iCopyParams->perfInfo.pool, iCopyParams->perfInfo.blocking
                                       , iCopyParams->src_roi.h
                                       , InvokeCopyMTProcessScanline_AX2, DST, SRC, count, stride )
    }
    else
    #endif // __AVX2__
    #ifdef __SSE4_2__
    if( iCopyParams->perfInfo.intent.UseSSE4_2() && gCpuInfo.info.HW_SSE42 && bpp <= 16 && bps >= 16 )
    {
        const tSize stride = 16;
        const tSize count = iCopyParams->src_roi.w;

        ULIS2_MACRO_INLINE_PARALLEL_FOR( iCopyParams->perfInfo.intent, iCopyParams->perfInfo.pool, iCopyParams->perfInfo.blocking
                                       , iCopyParams->src_roi.h
                                       , InvokeCopyMTProcessScanline_SSE, DST, SRC, count, stride )
    }
    else
    #endif // __SSE4_2__
    {
        ULIS2_MACRO_INLINE_PARALLEL_FOR( iCopyParams->perfInfo.intent, iCopyParams->perfInfo.pool, iCopyParams->perfInfo.blocking
                                       , iCopyParams->src_roi.h
                                       , InvokeCopyMTProcessScanline_MEM, DST, SRC, iCopyParams->src_roi.w )
    }
}


void CopyRect( const FCopyInfo& iCopyParams ) {
    // Assertions
    ULIS2_ASSERT( iCopyParams.source,                                                   "Bad source."                                                       );
    ULIS2_ASSERT( iCopyParams.destination,                                              "Bad destination."                                                  );
    ULIS2_ASSERT( !iCopyParams.perfInfo.intent.UseMT() || iCopyParams.perfInfo.pool,    "Multithreading flag is specified but no thread pool is provided."  );
    ULIS2_ASSERT( !iCopyParams.perfInfo.callCB || iCopyParams.perfInfo.blocking,        "Callback flag is specified on non-blocking operation."             );
    ULIS2_ASSERT( iCopyParams.source->Format() == iCopyParams.destination->Format(),    "Formats do not match"                                              );
    ULIS2_WARNING( iCopyParams.source != iCopyParams.destination,                       "Copying a block on itself is dangerous."                           );

    // Ensure the selected source rect actually fits in source dimensions.
    FRect src_roi = iCopyParams.area & iCopyParams.source->Rect();

    // Compute coordinates of target rect in destination, with source rect dimension
    int target_xmin = iCopyParams.pos.x;
    int target_ymin = iCopyParams.pos.y;
    int target_xmax = target_xmin + src_roi.w;
    int target_ymax = target_ymin + src_roi.h;
    FRect dst_target = FRect::FromMinMax( target_xmin, target_ymin, target_xmax, target_ymax );

    // Ensure the selected target actually fits in destination
    FRect dst_fit = dst_target & iCopyParams.destination->Rect();
    if( dst_fit.Area() <= 0 ) return;

    // Forward
    std::shared_ptr< _FPrivateCopyInfo > forwardCopyInfo = std::make_shared< _FPrivateCopyInfo >();
    forwardCopyInfo->source         = iCopyParams.source;
    forwardCopyInfo->destination    = iCopyParams.destination;
    forwardCopyInfo->src_roi        = src_roi;
    forwardCopyInfo->dst_roi        = dst_fit;
    forwardCopyInfo->perfInfo       = iCopyParams.perfInfo;

    // Call
    Copy_imp( forwardCopyInfo );

    // Invalidate
    iCopyParams.destination->Invalidate( dst_fit, iCopyParams.perfInfo.callCB );
}


void
CopyRaw( const FBlock* iSrc, FBlock* iDst, bool iCallInvalidCB ) {
    // Assertions
    ULIS2_ASSERT( iSrc,                             "Bad source"                                );
    ULIS2_ASSERT( iDst,                             "Bad destination"                           );
    ULIS2_ASSERT( iSrc != iDst,                     "Destination and source cannot be the same" );
    ULIS2_ASSERT( iSrc->Format() == iDst->Format(), "Formats do not matchs"                     );

    // One call, supposedly more efficient for small block.
    memcpy( iDst->DataPtr(), iSrc->DataPtr(), iSrc->BytesTotal() );

    // Invalid
    iDst->Invalidate( iCallInvalidCB );
}


ULIS2_NAMESPACE_END

