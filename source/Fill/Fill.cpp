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
#include "Data/Block.h"
#include "Data/Pixel.h"
#include "Conv/Conv.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"
#include <immintrin.h>

ULIS2_NAMESPACE_BEGIN
void
InvokeFillMTProcessScanline_AX2( tByte* iDst, __m256i& iSrc, const tSize iCount, const tSize iStride )
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


void
InvokeFillMTProcessScanline_SSE( tByte* iDst, __m128i& iSrc, const tSize iCount, const tSize iStride )
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


void
InvokeFillMTProcessScanline_MEM( tByte* iDst, const tByte* iSrc, tSize iCount, tSize iStride )
{
    for( uint32 i = 0; i < iCount; ++i )
    {
        memcpy( iDst, iSrc, iStride );
        iDst += iStride;
    }
}


void
FillMT( FThreadPool*   iPool
      , FBlock*        iDst
      , const tByte*   iSrc
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
    if( iPerf.UseAVX2() && bpp <= 32 )
    {
        const tSize stride = 32 - ( 32 % bpp );
        tByte* srcb = new tByte[32];
        #ifdef ULIS2_DEBUG
        memset( srcb, 0, 32 );
        #endif // ULIS2_DEBUG
        for( tSize i = 0; i < stride; i+= bpp )
            memcpy( (void*)( ( srcb ) + i ), iSrc, bpp );
        __m256i src = _mm256_lddqu_si256( (const __m256i*)srcb );
        delete [] srcb;
        const tSize count = iRoi.w * bpp;
        ParallelFor( *iPool, iRoi.h, iPerf, ULIS2_PF_CALL { InvokeFillMTProcessScanline_AX2( DST, src, count, stride ); } );
    }
    else if( iPerf.UseSSE4_2() && bpp <= 16 )
    {
        const tSize stride = 16 - ( 16 % bpp );
        tByte* srcb = new tByte[16];
        #ifdef ULIS2_DEBUG
        memset( srcb, 0, 16 );
        #endif // ULIS2_DEBUG
        for( tSize i = 0; i < stride; i+= bpp )
            memcpy( (void*)( ( srcb ) + i ), iSrc, bpp );
        __m128i src = _mm_lddqu_si128( (const __m128i*)srcb );
        delete [] srcb;
        const tSize count = iRoi.w * bpp;
        ParallelFor( *iPool, iRoi.h, iPerf, ULIS2_PF_CALL { InvokeFillMTProcessScanline_SSE( DST, src, count, stride ); } );
    }
    else
    {
        ParallelFor( *iPool, iRoi.h, iPerf, ULIS2_PF_CALL { InvokeFillMTProcessScanline_MEM( DST, iSrc, iRoi.w, bpp ); } );
    }
}


void
FillMono( FBlock*      iDst
        , const tByte* iSrc
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
        memcpy( dst, iSrc, bpp );
        dst += bpp;
    }
}


void
Fill( FThreadPool*     iPool
    , FBlock*          iDst
    , const IPixel&    iColor
    , const FPerf&     iPerf
    , bool             iCallInvalidCB )
{
    FillRect( iPool, iDst, iColor, iDst->Rect(), iPerf, iCallInvalidCB );
}


void
FillRect( FThreadPool*     iPool
        , FBlock*          iDst
        , const IPixel&    iColor
        , const FRect&     iRect
        , const FPerf&     iPerf
        , bool             iCallInvalidCB )
{
    ULIS2_ASSERT( iDst, "Bad destination" );
    FPixel color( iDst->Format() );
    Conv( iColor, color );
    const tByte* src = color.Ptr();
    FRect roi = iRect & iDst->Rect();

    if( roi.Area() <= 0 )
        return;

    if( iPerf.UseMT() )
        FillMT( iPool, iDst, src, roi, iPerf );
    else
        FillMono( iDst, src, roi );

    iDst->Invalidate( roi, iCallInvalidCB );
}


ULIS2_NAMESPACE_END

