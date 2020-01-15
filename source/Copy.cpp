// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Copy.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Copy entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Copy.h"
#include "Block.h"
#include "ParallelFor.h"

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
CopyMT( FThreadPool&    iPool
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
    if( iPerf.useAVX2 )
    {
        const tSize stride = 32 - ( 32 % bpp );
        const tSize count = iSrcRoi.w * bpp;
        ParallelFor( iPool, iSrcRoi.h, iPerf, ULIS2_PF_CALL { InvokeCopyMTProcessScanline_AX2( DST, SRC, count, stride ); } );
    }
    else if( iPerf.useSSE4_2 )
    {
        const tSize stride = 16 - ( 16 % bpp );
        const tSize count = iSrcRoi.w * bpp;
        ParallelFor( iPool, iSrcRoi.h, iPerf, ULIS2_PF_CALL { InvokeCopyMTProcessScanline_SSE( DST, SRC, count, stride ); } );
    }
    else
    {
        const tSize count = iSrcRoi.w * bpp;
        ParallelFor( iPool, iSrcRoi.h, iPerf, ULIS2_PF_CALL { InvokeCopyMTProcessScanline_MEM( DST, SRC, iSrcRoi.w ); } );
    }
}


void
CopyMono( const FBlock* iSrc
        , FBlock*       iDst
        , const FRect&  iSrcRoi
        , const FRect&  iDstRoi )
{
    const tSize  bpc = iDst->BytesPerSample();
    const tSize  spp = iDst->SamplesPerPixel();
    const tSize  bpp = bpc * spp;
    const tSize  w   = iDst->Width();
    const tSize  bps = bpp * w;
    const tByte* src = iSrc->DataPtr() + ( iSrcRoi.y * bps ) + ( iSrcRoi.x * bpp );
    tByte*       dst = iDst->DataPtr() + ( iDstRoi.y * bps ) + ( iDstRoi.x * bpp );
    const tSize  num = iSrcRoi.w * bpp;
    for( uint32 i = 0; i < (uint32)iSrcRoi.h; ++i )
    {
        memcpy( dst, src, num );
        src += bps;
        dst += bps;
    }
}


void
Copy( FThreadPool&  iPool
    , const FBlock* iSrc
    , FBlock*       iDst
    , const FPoint& iDstPos
    , const FPerf&  iPerf
    , bool          iCallInvalidCB )
{
    CopyRect( iPool, iSrc, iDst, iSrc->Rect(), FPoint(), iPerf, iCallInvalidCB );
}


void
CopyRect( FThreadPool&  iPool
        , const FBlock* iSrc
        , FBlock*       iDst
        , const FRect&  iSrcRect
        , const FPoint& iDstPos
        , const FPerf&  iPerf
        , bool          iCallInvalidCB )
{
    ULIS2_ASSERT( iSrc->Model() == iDst->Model(),                       "Models do not match" );
    ULIS2_ASSERT( iSrc->Type() == iDst->Type(),                         "Types do not match" );
    ULIS2_ASSERT( iSrc->SamplesPerPixel() == iDst->SamplesPerPixel(),   "Samples do not match" );
    ULIS2_ASSERT( iSrc,                                                 "Bad source" );
    ULIS2_ASSERT( iDst,                                                 "Bad destination" );
    ULIS2_ASSERT( iSrc != iDst,                                         "Destination and source cannot be the same" );

    // Gather src rect and shift to destination
    FRect target_rect = iSrcRect & iSrc->Rect();
    target_rect.x = iDstPos.x;
    target_rect.y = iDstPos.y;
    // Gather dst rect
    // Interset target with dst, target may be out of range
    FRect dst_roi = target_rect & iDst->Rect();
    // Gather src rect and fit size to fix overflow
    FRect src_roi = dst_roi;
    src_roi.x = iSrcRect.x;
    src_roi.y = iSrcRect.y;

    // Check if this is a no-op
    if( src_roi.Area() <= 0 )
        return;

    // Select invocation based on performance preferences
    if( iPerf.useMT )
        CopyMT( iPool, iSrc, iDst, src_roi, dst_roi, iPerf );
    else
        CopyMono( iSrc, iDst, src_roi, dst_roi );

    // Invalidate dst region of interest
    iDst->Invalidate( dst_roi, iCallInvalidCB );
}


void
CopyRaw( const FBlock* iSrc
       , FBlock*       iDst
       , bool          iCallInvalidCB )
{
    ULIS2_ASSERT( iSrc->Model() == iDst->Model(),                       "Models do not match" );
    ULIS2_ASSERT( iSrc->Type() == iDst->Type(),                         "Types do not match" );
    ULIS2_ASSERT( iSrc->SamplesPerPixel() == iDst->SamplesPerPixel(),   "Samples do not match" );
    ULIS2_ASSERT( iSrc->BytesTotal() == iDst->BytesTotal(),             "Sizes do not match" );
    ULIS2_ASSERT( iSrc,                                                 "Bad source" );
    ULIS2_ASSERT( iDst,                                                 "Bad destination" );
    ULIS2_ASSERT( iSrc != iDst,                                         "Destination and source cannot be the same" );
    // One call, supposedly more efficient for small block.
    memcpy( iDst->DataPtr(), iSrc->DataPtr(), iSrc->BytesTotal() );
}


ULIS2_NAMESPACE_END

