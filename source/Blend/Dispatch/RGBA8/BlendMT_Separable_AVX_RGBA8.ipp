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
                                                         , const int32                  iW
                                                         , const _FBMTPSSAVXRGBA8SP&    iParams )
{
    const bool firstLine    = iLine < 1;
    const bool lastLine     = iLine >= iParams.mCoverageY;
    //   The gain is not huge compared to SSE
    //   _X_ | _X_ | _X_ | _X_ | _X_ | ...
    //  _____|_____|_____|_____|_____|_
    //   _X_ | m00 | m10 | m20 | m30 | ...
    //  _____|_____|_____|_____|_____|_
    //   _X_ | m01 | m11 | m21 | m31 | ...
    //  _____|_____|_____|_____|_____|_
    //        \     \   /     /
    //         \     \ /     /
    //          \     X     /
    //           \   / \   /
    //            \ /   \ /
    //             |     |
    //          vv0vv1 vv1vv2 -> res
    Vec8f alpha_m00m10, alpha_m10m20, alpha_m01m11, alpha_m11m21, alpha_vv0, alpha_vv1, alpha_smp;
    Vec8f smpch_m00m10, smpch_m10m20, smpch_m01m11, smpch_m11m21, smpch_vv0, smpch_vv1, smpch_smp;

    alpha_m10m20 = alpha_m11m21 = alpha_vv1 = 0.f;
    smpch_m10m20 = smpch_m11m21 = smpch_vv1 = 0.f;

    const tByte* p00 = iSrc - iParams.mSrcBps;
    const tByte* p10 = iSrc - iParams.mSrcBps + 4;
    const tByte* p01 = iSrc;
    const tByte* p11 = iSrc + 4;

    for( int32 x = 0; x < iW; x+=2 ) {
        const bool condA = x     >= iParams.mCoverageX || firstLine   ;
        const bool condB = x+1   >= iParams.mCoverageX || firstLine   ;
        const bool condC = x     >= iParams.mCoverageX || lastLine    ;
        const bool condD = x+1   >= iParams.mCoverageX || lastLine    ;

        // Load Alpha
        Vec4f la00 = condA ? 0.f : p00[iParams.mAid] / 255.f;
        Vec4f la10 = condB ? 0.f : p10[iParams.mAid] / 255.f;
        Vec4f la01 = condC ? 0.f : p01[iParams.mAid] / 255.f;
        Vec4f la11 = condD ? 0.f : p11[iParams.mAid] / 255.f;
        alpha_m00m10 = Vec8f( alpha_m10m20.get_high(), la00 );
        alpha_m01m11 = Vec8f( alpha_m11m21.get_high(), la01 );
        alpha_m10m20 = Vec8f( la00, la10 );
        alpha_m11m21 = Vec8f( la01, la11 );
        alpha_vv0 = alpha_m00m10 * iParams.mTY + alpha_m01m11 * iParams.mUY;
        alpha_vv1 = alpha_m10m20 * iParams.mTY + alpha_m11m21 * iParams.mUY;
        alpha_smp = alpha_vv0 * iParams.mTX + alpha_vv1 * iParams.mUX;

        // Load Channels
        Vec4f fc00 = condA ? 0.f : Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si32( p00 ) ) ) ) / 255.f;
        Vec4f fc10 = condB ? 0.f : Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si32( p10 ) ) ) ) / 255.f;
        Vec4f fc01 = condC ? 0.f : Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si32( p01 ) ) ) ) / 255.f;
        Vec4f fc11 = condD ? 0.f : Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si32( p11 ) ) ) ) / 255.f;

        smpch_m00m10 = Vec8f( smpch_m10m20.get_high(), fc00 );
        smpch_m01m11 = Vec8f( smpch_m11m21.get_high(), fc01 );
        smpch_m10m20 = Vec8f( fc00, fc10 );
        smpch_m11m21 = Vec8f( fc01, fc11 );
        smpch_vv0 = ( smpch_m00m10 * alpha_m00m10 ) * iParams.mTY + ( smpch_m01m11 * alpha_m01m11 )  * iParams.mUY;
        smpch_vv1 = ( smpch_m10m20 * alpha_m10m20 ) * iParams.mTY + ( smpch_m11m21 * alpha_m11m21 )  * iParams.mUY;
        smpch_smp = select( alpha_smp == 0.f, 0.f, ( smpch_vv0 * iParams.mTX + smpch_vv1 * iParams.mUX ) / alpha_smp );

        // Comp Alpha
        Vec8f alpha_bdp     = *( iBdp + iParams.mAid ) / 255.f;
        Vec8f alpha_src     = alpha_smp * iParams.mOpacity;
        Vec8f alpha_comp    = AlphaNormalAVXF( alpha_src, alpha_bdp );
        Vec8f var           = select( alpha_comp == 0.f, 0.f, alpha_src / alpha_comp );
        Vec8f alpha_result;
        ULIS2_ASSIGN_ALPHAAVXF( iParams.mAlphaMode, alpha_result, alpha_src, alpha_bdp );
        alpha_result *= 255.f;

        // Comp Channels
        __m128i bdp128 = _mm_setzero_si128();
        memcpy( &bdp128, iBdp, 8 );
        Vec8f   bdp_chan = Vec8f( _mm256_cvtepi32_ps( _mm256_cvtepu8_epi32( bdp128 ) ) ) / 255.f;
        Vec8f   res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = SeparableCompOpAVXF< _BM >( smpch_smp, bdp_chan, alpha_bdp, var ) * 255.f;
        ULIS2_SWITCH_FOR_ALL_DO( iParams.mBlendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN

        Vec8ui _pack0 = _mm256_cvtps_epi32( res_chan );
        Vec8us _pack1 = compress( _pack0 );
        auto _pack = _mm_packus_epi16( _pack1, _pack1 );
        _mm_storeu_si64( iBdp, _pack );
        iBdp[iParams.mAid]      = static_cast< uint8 >( alpha_result[0] );
        iBdp[iParams.mAid+4]    = static_cast< uint8 >( alpha_result[4] );

        iBdp += 8;
        p00 += 8;
        p10 += 8;
        p01 += 8;
        p11 += 8;
    }
}

void
BlendMT_Separable_AVX_RGBA8_Subpixel( const FFormatInfo& iFormatInfo, const FPerfInfo& iPerfParams, std::shared_ptr< const FBlendInfo > iBlendParams ) {
    /*
    tFormat fmt = iSource->Format();
    uint8   aid = ( ( ( ~( ( ULIS2_R_RS( fmt ) + 0x1 ) & 0x2 ) ) & 0x2 ) >> 1 ) * 3;
    const tByte* src    = iSource->DataPtr();
    tByte*       bdp    = iBackdrop->DataPtr();
    tSize       src_bps = 4 * iSource->Width();
    tSize       bdp_bps = 4 * iBackdrop->Width();
    Vec8f   TX( iSubpixelComponent.x ); Vec8f TY( iSubpixelComponent.y );
    Vec8f   UX = 1.f - TX;              Vec8f UY = 1.f - TY;
    _FBMTPSSAVXRGBA8SP params { iSrcROI.w, iSrcROI.h, src_bps, aid, TX, TY, UX, UY, iBlendingMode, iAlphaMode, iOpacity };

    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iBdpROI.h, InvokeBlendMTProcessScanline_Separable_AVX_RGBA8_Subpixel, pLINE
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
        Vec8f   res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = SeparableCompOpAVXF< _BM >( src_chan, bdp_chan, alpha_bdp, var ) * 255.f;
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
        Vec8f   res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = SeparableCompOpAVXF< _BM >( src_chan, bdp_chan, alpha_bdp, var ) * 255.f;
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
BlendMT_Separable_AVX_RGBA8( const FFormatInfo& iFormatInfo, const FPerfInfo& iPerfParams, std::shared_ptr< const FBlendInfo > iBlendParams ) {
/*
    tFormat fmt = iSource->Format();
    uint8   aid = ( ( ( ~( ( ULIS2_R_RS( fmt ) + 0x1 ) & 0x2 ) ) & 0x2 ) >> 1 ) * 3;
    const tByte*    src     = iSource->DataPtr();
    tByte*          bdp     = iBackdrop->DataPtr();
    tSize           src_bps = 4 * iSource->Width();
    tSize           bdp_bps = 4 * iBackdrop->Width();

    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iBdpROI.h, InvokeBlendMTProcessScanline_Separable_AVX_RGBA8
                                                                       , src + ( ( iSrcROI.y + pLINE ) * src_bps ) + ( iSrcROI.x * 4 )
                                                                       , bdp + ( ( iBdpROI.y + pLINE ) * bdp_bps ) + ( iBdpROI.x * 4 )
                                                                       , iBdpROI.w, aid, iBlendingMode, iAlphaMode, iOpacity );
                                                                       */
}

ULIS2_NAMESPACE_END

