// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMT_NonSeparable_AVX_RGBA8.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the RGBA8 Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/Blend.h"
#include "Base/Helpers.ipp"
#include "Base/Perf.h"
#include "Blend/Modes.h"
#include "Maths/Geometry.h"
#include "Blend/Func/AlphaFuncAVX.ipp"
#include "Blend/Func/SeparableBlendFuncAVXF.ipp"
#include "Blend/Func/NonSeparableBlendFuncSSEF.ipp"
#include "Thread/ParallelFor.h"
#include "Thread/ThreadPool.h"
ULIS2_NAMESPACE_BEGIN
void
InvokeBlendMTProcessScanline_NonSeparable_AVX_RGBA8_Subpixel( const int32               iLine
                                                            , const tByte*              iSrc
                                                            , tByte*                    iBdp
                                                            , const uint32              iW
                                                            , const Vec4i&              iIDT
                                                            , const _FBMTPSSAVXRGBA8SP& iParams )
{
}

void
BlendMT_NonSeparable_AVX_RGBA8_Subpixel( FThreadPool*     iPool
                                       , bool             iBlocking
                                       , const FPerf&     iPerf
                                       , const FBlock*    iSource
                                       , FBlock*          iBackdrop
                                       , const FRect&     iSrcROI
                                       , const FRect&     iBdpROI
                                       , const glm::vec2& iSubpixelComponent
                                       , eBlendingMode    iBlendingMode
                                       , eAlphaMode       iAlphaMode
                                       , ufloat           iOpacity )
{
    tFormat fmt = iSource->Format();
    Vec4i idt;
    uint8 aid;
    BuildRGBA8IndexTable( fmt, &idt, &aid );
    const tByte*    src     = iSource->DataPtr();
    tByte*          bdp     = iBackdrop->DataPtr();
    tSize           src_bps = 4 * iSource->Width();
    tSize           bdp_bps = 4 * iBackdrop->Width();

    Vec8f   TX( iSubpixelComponent.x ); Vec8f TY( iSubpixelComponent.y );
    Vec8f   UX = 1.f - TX;              Vec8f UY = 1.f - TY;

    _FBMTPSSAVXRGBA8SP params { iSrcROI.w, iSrcROI.h, src_bps, aid, TX, TY, UX, UY, iBlendingMode, iAlphaMode, iOpacity };

    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iBdpROI.h, InvokeBlendMTProcessScanline_NonSeparable_AVX_RGBA8_Subpixel, pLINE
                                                                       , src + ( ( iSrcROI.y + pLINE ) * src_bps ) + ( iSrcROI.x * 4 )
                                                                       , bdp + ( ( iBdpROI.y + pLINE ) * bdp_bps ) + ( iBdpROI.x * 4 )
                                                                       , iBdpROI.w, idt, params );
}

void
InvokeBlendMTProcessScanline_NonSeparable_AVX_RGBA8( const tByte*          iSrc
                                                   , tByte*                iBdp
                                                   , const uint32          iW
                                                   , const Vec4i&          iIDT
                                                   , const uint8           iAid
                                                   , const eBlendingMode   iBlendingMode
                                                   , const eAlphaMode      iAlphaMode
                                                   , const ufloat          iOpacity )
{
    //  Blending Two Pixels at a time:
    //  R0 G0 B0 A0     R1 G1 B1 A1
    //  -------------------------
    //  | m00 | m10 | m20 | m30 |
    //  |_____|_____|_____|_____|
    //  | m00 | m10 | m20 | m30 |
    //  |_____|_____|_____|_____|
    // The implementation is thread safe, there is no thread concurrency
    // no read / write overlap, even the sse loads do not overflow the bounding
    // rect, because of memcpy load.
    const uint32 len = iW/2;
    for( uint32 i = 0; i < len; ++i ) {
        Vec8f   alpha_bdp   = Vec8f( iBdp[iAid], iBdp[iAid + 4] ) / 255.f;
        Vec8f   alpha_src   = Vec8f( iSrc[iAid], iSrc[iAid + 4] ) / 255.f * iOpacity;
        Vec8f   alpha_comp  = AlphaNormalAVXF( alpha_src, alpha_bdp );
        Vec8f   var         = select( alpha_comp == 0.f, 0.f, ( alpha_src / alpha_bdp ) );
        Vec8f   alpha_result;
        ULIS2_ASSIGN_ALPHAAVXF( iAlphaMode, alpha_result, alpha_src, alpha_bdp );
        alpha_result *= 255.f;

        Vec8f   src_chan = Vec8f( _mm256_cvtepi32_ps( _mm256_cvtepu8_epi32( _mm_loadu_si64( iSrc ) ) ) ) / 255.f;
        Vec8f   bdp_chan = Vec8f( _mm256_cvtepi32_ps( _mm256_cvtepu8_epi32( _mm_loadu_si64( iBdp ) ) ) ) / 255.f;
        Vec4f   s0 = lookup4( iIDT, src_chan.get_low()  );
        Vec4f   s1 = lookup4( iIDT, src_chan.get_high() );
        Vec4f   b0 = lookup4( iIDT, bdp_chan.get_low()  );
        Vec4f   b1 = lookup4( iIDT, bdp_chan.get_high() );
        s0.insert( 3, 0.f );
        s1.insert( 3, 0.f );
        b0.insert( 3, 0.f );
        b1.insert( 3, 0.f );

        Vec8f res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 )                                                \
            auto _mr0 = NonSeparableOpF< _BM >( s0, b0 );                                       \
            auto _mr1 = NonSeparableOpF< _BM >( s1, b1 );                                       \
            res_chan = Vec8f( _mr0, _mr1 );                                                     \
            res_chan = ComposeAVXF( src_chan, bdp_chan, alpha_bdp, var, res_chan );
        ULIS2_SWITCH_FOR_ALL_DO( iBlendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN

        Vec8ui _pack0 = _mm256_cvtps_epi32( res_chan );
        Vec8us _pack1 = compress( _pack0 );
        auto _pack = _mm_packus_epi16( _pack1, _pack1 );
        _mm_storeu_si64( iBdp, _pack );
        iBdp[iAid]      = static_cast< uint8 >( alpha_result[0] );
        iBdp[iAid+4]    = static_cast< uint8 >( alpha_result[4] );

        iSrc += 8;
        iBdp += 8;
    }

    // In case W is odd, process one last pixel.
    if( iW%2 ) {
        Vec8f   alpha_bdp   = Vec8f( iBdp[iAid], 0 ) / 255.f;
        Vec8f   alpha_src   = Vec8f( iSrc[iAid], 0 ) / 255.f * iOpacity;
        Vec8f   alpha_comp  = AlphaNormalAVXF( alpha_src, alpha_bdp );
        Vec8f   var         = select( alpha_comp == 0.f, 0.f, ( alpha_src / alpha_bdp ) );
        Vec8f   alpha_result;
        ULIS2_ASSIGN_ALPHAAVXF( iAlphaMode, alpha_result, alpha_src, alpha_bdp );
        alpha_result *= 255.f;

        Vec8f   src_chan = Vec8f( _mm256_cvtepi32_ps( _mm256_cvtepu8_epi32( _mm_loadu_si32( iSrc ) ) ) ) / 255.f;
        Vec8f   bdp_chan = Vec8f( _mm256_cvtepi32_ps( _mm256_cvtepu8_epi32( _mm_loadu_si32( iBdp ) ) ) ) / 255.f;
        Vec4f   s0 = lookup4( iIDT, src_chan.get_low()  );
        Vec4f   b0 = lookup4( iIDT, bdp_chan.get_low()  );
        s0.insert( 3, 0.f );
        b0.insert( 3, 0.f );
        Vec8f res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 )                                                \
            auto _mr0 = NonSeparableOpF< _BM >( s0, b0 );                                       \
            res_chan = Vec8f( _mr0, 0.f );                                                      \
            res_chan = ComposeAVXF( src_chan, bdp_chan, alpha_bdp, var, res_chan );
        ULIS2_SWITCH_FOR_ALL_DO( iBlendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN

        Vec8ui _pack0 = _mm256_cvtps_epi32( res_chan );
        Vec8us _pack1 = compress( _pack0 );
        auto _pack = _mm_packus_epi16( _pack1, _pack1 );
        _mm_storeu_si32( iBdp, _pack );
        iBdp[iAid] = static_cast< uint8 >( alpha_result[0] );
    }
}

void
BlendMT_NonSeparable_AVX_RGBA8( FThreadPool*      iPool
                              , bool              iBlocking
                              , const FPerf&      iPerf
                              , const FBlock*     iSource
                              , FBlock*           iBackdrop
                              , const FRect&      iSrcROI
                              , const FRect&      iBdpROI
                              , const glm::vec2&  iSubpixelComponent
                              , eBlendingMode     iBlendingMode
                              , eAlphaMode        iAlphaMode
                              , ufloat            iOpacity )
{
    tFormat fmt = iSource->Format();
    Vec4i idt;
    uint8 aid;
    BuildRGBA8IndexTable( fmt, &idt, &aid );
    const tByte*    src     = iSource->DataPtr();
    tByte*          bdp     = iBackdrop->DataPtr();
    tSize           src_bps = 4 * iSource->Width();
    tSize           bdp_bps = 4 * iBackdrop->Width();

    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iBdpROI.h, InvokeBlendMTProcessScanline_NonSeparable_AVX_RGBA8
                                                                       , src + ( ( iSrcROI.y + pLINE ) * src_bps ) + ( iSrcROI.x * 4 )
                                                                       , bdp + ( ( iBdpROI.y + pLINE ) * bdp_bps ) + ( iBdpROI.x * 4 )
                                                                       , iBdpROI.w, idt, aid, iBlendingMode, iAlphaMode, iOpacity );
}

ULIS2_NAMESPACE_END

