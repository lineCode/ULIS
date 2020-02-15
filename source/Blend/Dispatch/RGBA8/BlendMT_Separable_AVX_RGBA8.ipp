// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMT_Separable_AVX_RGBA8.ipp
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
#include "Thread/ParallelFor.h"
#include "Thread/ThreadPool.h"

ULIS2_NAMESPACE_BEGIN
void
InvokeBlendMTProcessScanline_Separable_AVX_RGBA8_Subpixel( const int32                  iLine
                                                         , const tByte*                 iSrc
                                                         , tByte*                       iBdp
                                                         , const uint32                 iW
                                                         , const _FBMTPSSSSERGBA8SP&    iParams )
{
    /*
    //  -------------
    //  | m00 | m10 |
    //  |_____|_____|___
    //  | m01 | m11 |
    //  |_____|_____|
    //     |  |  |
    //    vv0 | vv1  -> res
    Vec4f alpha_m11, alpha_m01, alpha_m10, alpha_m00, alpha_vv0, alpha_vv1, alpha_smp;
    Vec4f smpch_m11, smpch_m01, smpch_m10, smpch_m00, smpch_vv0, smpch_vv1, smpch_smp;
    alpha_m11 = alpha_m10 = alpha_vv1 = 0.f;
    smpch_m11 = smpch_m10 = smpch_vv1 = 0.f;
    int x = 0;
    for( uint32 i = 0; i < iW; ++i ) {
        alpha_m00 = alpha_m10;
        alpha_m01 = alpha_m11;
        alpha_vv0 = alpha_vv1;
        smpch_m00 = smpch_m10;
        smpch_m01 = smpch_m11;
        smpch_vv0 = smpch_vv1;
        alpha_m11 = x >= iParams.mCoverageX || iLine >= iParams.mCoverageY ? 0.f : *( iSrc + iParams.mAid ) / 255.f;
        alpha_m10 = x >= iParams.mCoverageX || iLine < 1 ? 0.f : *( ( iSrc - iParams.mSrcBps ) + iParams.mAid ) / 255.f;
        alpha_vv1 = alpha_m10 * iParams.mTY + alpha_m11 * iParams.mUY;
        alpha_smp = alpha_vv0 * iParams.mTX + alpha_vv1 * iParams.mUX;
        smpch_m11 = x >= iParams.mCoverageX || iLine >= iParams.mCoverageY ? 0.f : Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc ) ) ) ) ) / 255.f;
        smpch_m10 = x >= iParams.mCoverageX || iLine < 1 ? 0.f : Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc - iParams.mSrcBps ) ) ) ) ) / 255.f;
        smpch_vv1 = ( smpch_m10 * alpha_m10 ) * iParams.mTY + ( smpch_m11 * alpha_m11 )  * iParams.mUY;
        smpch_smp = select( alpha_smp == 0.f, 0.f, ( smpch_vv0 * iParams.mTX + smpch_vv1 * iParams.mUX ) / alpha_smp );
        Vec4f alpha_bdp     = *( iBdp + iParams.mAid ) / 255.f;
        Vec4f alpha_src     = alpha_smp * iParams.mOpacity;
        Vec4f alpha_comp    = AlphaNormalSSEF( alpha_src, alpha_bdp );
        Vec4f var           = select( alpha_comp == 0.f, 0.f, alpha_src / alpha_comp );
        Vec4f alpha_result;
        ULIS2_ASSIGN_ALPHASSEF( iParams.mAlphaMode, alpha_result, alpha_src, alpha_bdp );
        Vec4f bdp_chan = Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iBdp ) ) ) ) ) / 255.f;
        Vec4f res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = SeparableCompOpSSEF< _BM >( smpch_smp, bdp_chan, alpha_bdp, var ) * 255.f;
        ULIS2_SWITCH_FOR_ALL_DO( iParams.mBlendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN
        auto _pack = _mm_cvtps_epi32( res_chan );
        _pack = _mm_packus_epi32( _pack, _pack );
        _pack = _mm_packus_epi16( _pack, _pack );
        *( uint32* )iBdp = static_cast< uint32 >( _mm_cvtsi128_si32( _pack ) );
        *( iBdp + iParams.mAid ) = uint8( alpha_result[0] * 0xFF );
        iSrc += 4;
        iBdp += 4;
        ++x;
    }
    */
}

void
BlendMT_Separable_AVX_RGBA8_Subpixel( FThreadPool*        iPool
                                    , bool                iBlocking
                                    , const FPerf&        iPerf
                                    , const FBlock*       iSource
                                    , FBlock*             iBackdrop
                                    , const FRect&        iSrcROI
                                    , const FRect&        iBdpROI
                                    , const glm::vec2&    iSubpixelComponent
                                    , eBlendingMode       iBlendingMode
                                    , eAlphaMode          iAlphaMode
                                    , ufloat              iOpacity )
{
    /*
    tFormat fmt = iSource->Format();
    uint8   aid = ( ( ( ~( ( ULIS2_R_RS( fmt ) + 0x1 ) & 0x2 ) ) & 0x2 ) >> 1 ) * 3;
    const tByte* src    = iSource->DataPtr();
    tByte*       bdp    = iBackdrop->DataPtr();
    tSize       src_bps = 4 * iSource->Width();
    tSize       bdp_bps = 4 * iBackdrop->Width();
    Vec4f   TX( iSubpixelComponent.x ); Vec4f TY( iSubpixelComponent.y );
    Vec4f   UX = 1.f - TX;              Vec4f UY = 1.f - TY;
    _FBMTPSSSSERGBA8SP params { iSrcROI.w, iSrcROI.h, src_bps, aid, TX, TY, UX, UY, iBlendingMode, iAlphaMode, iOpacity };

    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iBdpROI.h, InvokeBlendMTProcessScanline_Separable_SSE_RGBA8_Subpixel, pLINE
                                                                       , src + ( ( iSrcROI.y + pLINE ) * src_bps ) + ( iSrcROI.x * 4 )
                                                                       , bdp + ( ( iBdpROI.y + pLINE ) * bdp_bps ) + ( iBdpROI.x * 4 )
                                                                       , iBdpROI.w, params );
    */
}

void
InvokeBlendMTProcessScanline_Separable_AVX_RGBA8( const tByte*          iSrc
                                                , tByte*                iBdp
                                                , const uint32          iW
                                                , const uint8           iAid
                                                , const eBlendingMode   iBlendingMode
                                                , const eAlphaMode      iAlphaMode
                                                , const ufloat          iOpacity )
{
    //  Blending Two Pixels at a time:
    //  R0 G0 B0 A0     R0 G0 B0 A0
    //  -------------
    //  | m00 | m10 |
    //  |_____|_____|

    for( uint32 i = 0; i < iW; ++i ) {
        Vec8f   alpha_bdp   = Vec8f( iBdp[iAid], iBdp[iAid + 4] ) / 255.f;
        Vec8f   alpha_src   = ( Vec8f( iSrc[iAid], iSrc[iAid + 4] ) / 255.f ) * iOpacity;
        Vec8f   alpha_comp  = AlphaNormalAVXF( alpha_src, alpha_bdp );
        Vec8f   var         = select( alpha_comp == 0.f, 0.f, ( alpha_src / alpha_bdp ) );
        Vec8f   alpha_result;
        ULIS2_ASSIGN_ALPHAAVXF( iAlphaMode, alpha_result, alpha_src, alpha_bdp );
        _mm256_loadu_si256( reinterpret_cast< const __m256i* >( iSrc ) );
        Vec8f   src_chan = Vec8f( _mm256_cvtepi32_ps( _mm256_cvtepu8_epi32( _mm_loadu_si128( reinterpret_cast< const __m128i* >( iSrc ) ) ) ) ) / 255.f;
        Vec8f   bdp_chan = Vec8f( _mm256_cvtepi32_ps( _mm256_cvtepu8_epi32( _mm_loadu_si128( reinterpret_cast< const __m128i* >( iBdp ) ) ) ) ) / 255.f;
        Vec8f   res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = SeparableCompOpAVXF< _BM >( src_chan, bdp_chan, alpha_bdp, var ) * 255.f;
        ULIS2_SWITCH_FOR_ALL_DO( iBlendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN

        auto _pack = _mm256_cvtps_epi32( res_chan );
        _pack = _mm256_packus_epi32( _pack, _pack );
        _pack = _mm256_packus_epi16( _pack, _pack );
        memcpy( iBdp, &_pack, 8 );
        *( iBdp + iAid )        = uint8( alpha_result[0] * 0xFF );
        *( iBdp + iAid + 4 )    = uint8( alpha_result[4] * 0xFF );

        iSrc += 8;
        iBdp += 8;
    }
}

void
BlendMT_Separable_AVX_RGBA8( FThreadPool*     iPool
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
    uint8   aid = ( ( ( ~( ( ULIS2_R_RS( fmt ) + 0x1 ) & 0x2 ) ) & 0x2 ) >> 1 ) * 3;
    const tByte*    src     = iSource->DataPtr();
    tByte*          bdp     = iBackdrop->DataPtr();
    tSize           src_bps = 4 * iSource->Width();
    tSize           bdp_bps = 4 * iBackdrop->Width();

    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iBdpROI.h, InvokeBlendMTProcessScanline_Separable_AVX_RGBA8
                                                                       , src + ( ( iSrcROI.y + pLINE ) * src_bps ) + ( iSrcROI.x * 4 )
                                                                       , bdp + ( ( iBdpROI.y + pLINE ) * bdp_bps ) + ( iBdpROI.x * 4 )
                                                                       , iBdpROI.w / 2, aid, iBlendingMode, iAlphaMode, iOpacity );
}

ULIS2_NAMESPACE_END

