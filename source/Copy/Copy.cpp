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
#include "Data/Block.h"
#include "Thread/ParallelFor.h"
#include <immintrin.h>

ULIS2_NAMESPACE_BEGIN
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


void InvokeCopyMTProcessScanline_MEM( tByte* iDst, const tByte* iSrc, tSize iCount )
{
    memcpy( iDst, iSrc, iCount );
}


void
Copy_imp( FThreadPool*    iPool
        , const FBlock*   iSrc
        , FBlock*         iDst
        , const FRect&    iSrcRoi
        , const FRect&    iDstRoi
        , const FPerf&    iPerf )
{
    const tSize bpc = iDst->BytesPerSample();
    const tSize spp = iDst->SamplesPerPixel();
    const tSize bpp = bpc * spp;
    const tSize w   = iDst->Width();
    const tSize bps = bpp * w;
    const tSize srh = iSrcRoi.x * bpp;
    const tSize dsh = iDstRoi.x * bpp;
    const tByte*srb = iSrc->DataPtr() + srh;
    tByte*      dsb = iDst->DataPtr() + dsh;
    #define SRC srb + ( ( iSrcRoi.y + iLine ) * bps )
    #define DST dsb + ( ( iDstRoi.y + iLine ) * bps )
    if( iPerf.UseAVX2() )
    {
        const tSize stride = 32;
        const tSize count = iSrcRoi.w * bpp;
        ParallelFor( *iPool, iSrcRoi.h, iPerf, ULIS2_PF_CALL { InvokeCopyMTProcessScanline_AX2( DST, SRC, count, stride ); } );
    }
    else if( iPerf.UseSSE4_2() )
    {
        const tSize stride = 16;
        const tSize count = iSrcRoi.w * bpp;
        ParallelFor( *iPool, iSrcRoi.h, iPerf, ULIS2_PF_CALL { InvokeCopyMTProcessScanline_SSE( DST, SRC, count, stride ); } );
    }
    else
    {
        const tSize count = iSrcRoi.w * bpp;
        ParallelFor( *iPool, iSrcRoi.h, iPerf, ULIS2_PF_CALL { InvokeCopyMTProcessScanline_MEM( DST, SRC, iSrcRoi.w ); } );
    }
}


void
Copy( FThreadPool*      iPool
    , const FBlock*     iSrc
    , FBlock*           iDst
    , const glm::ivec2& iDstPos
    , const FPerf&      iPerf
    , bool              iCallInvalidCB )
{
    CopyRect( iPool, iSrc, iDst, iSrc->Rect(), iDstPos, iPerf, iCallInvalidCB );
}


void
CopyRect( FThreadPool*      iPool
        , const FBlock*     iSrc
        , FBlock*           iDst
        , const FRect&      iSrcRect
        , const glm::ivec2& iDstPos
        , const FPerf&      iPerf
        , bool              iCallInvalidCB )
{
    ULIS2_ASSERT( iPool,                            "Bad pool" );
    ULIS2_ASSERT( iSrc,                             "Bad source" );
    ULIS2_ASSERT( iDst,                             "Bad destination" );
    ULIS2_ASSERT( iSrc->Format() == iDst->Format(), "Formats do not match" );
    ULIS2_WARNING( iSrc != iDst,                    "Copying a block on itself may trigger data race, use at your own risk or ensure written areas do not overlap." );

    // Ensure the selected source rect actually fits in source dimensions.
    FRect src_roi = iSrcRect & iSrc->Rect();

    // Compute coordinates of target rect in destination, with source rect dimension
    int target_xmin = iDstPos.x;
    int target_ymin = iDstPos.y;
    int target_xmax = iDstPos.x + src_roi.w;
    int target_ymax = iDstPos.y + src_roi.h;
    FRect dst_target = FRect::FromMinMax( target_xmin, target_ymin, target_xmax, target_ymax );

    // Ensure the selected target actually fits in destination
    FRect dst_fit = dst_target & iDst->Rect();
    if( dst_fit.Area() <= 0 ) return;

    Copy_imp( iPool, iSrc, iDst, src_roi, dst_fit, iPerf );
    iDst->Invalidate( dst_fit, iCallInvalidCB );
}


void
CopyRaw( const FBlock* iSrc
       , FBlock*       iDst
       , bool          iCallInvalidCB )
{
    ULIS2_ASSERT( iSrc,                             "Bad source" );
    ULIS2_ASSERT( iDst,                             "Bad destination" );
    ULIS2_ASSERT( iSrc != iDst,                     "Destination and source cannot be the same" );
    ULIS2_ASSERT( iSrc->Format() == iDst->Format(), "Formats do not matchs" );
    // One call, supposedly more efficient for small block.
    memcpy( iDst->DataPtr(), iSrc->DataPtr(), iSrc->BytesTotal() );
}


ULIS2_NAMESPACE_END

