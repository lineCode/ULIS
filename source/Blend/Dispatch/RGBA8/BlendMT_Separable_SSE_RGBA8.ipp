// Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMT_Separable_SSE_RGBA8.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the RGBA8 Blend entry point functions.
* @copyright    Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Blend/Modes.h"
#include "Blend/Dispatch/BlendInfo.h"
#include "Blend/Func/AlphaFuncF.ipp"
#include "Blend/Func/AlphaFuncSSEF.ipp"
#include "Blend/Func/SeparableBlendFuncSSEF.ipp"
#include "Maths/Geometry.h"
#include "Thread/ThreadPool.h"

ULIS2_NAMESPACE_BEGIN
void
InvokeBlendMTProcessScanline_Separable_SSE_RGBA8_Subpixel( const tByte* iSrc, tByte* iBdp, int32 iLine, const tSize iSrcBps, std::shared_ptr< const _FBlendInfoPrivate > iInfo ) {
    const _FBlendInfoPrivate&   info    = *iInfo;
    const FFormatInfo&          fmt     = info.source->FormatInfo();
    const tByte*                src     = iSrc;
    tByte*                      bdp     = iBdp;
    const bool notLastLine  = iLine < info.backdropCoverage.y;
    const bool notFirstLine = iLine > 0;
    const bool onLeftBorder = info.backdropWorkingRect.x == 0;
    const bool hasLeftData  = info.sourceRect.x + info.shift.x > 0;
    const bool hasTopData   = info.sourceRect.y + info.shift.y > 0;

    Vec4f   TX( info.subpixelComponent.x );
    Vec4f   TY( info.subpixelComponent.y );
    Vec4f   UX( info.buspixelComponent.x );
    Vec4f   UY( info.buspixelComponent.y );

    Vec4f alpha_m11, alpha_m01, alpha_m10, alpha_m00, alpha_vv0, alpha_vv1, alpha_smp;
    Vec4f smpch_m11, smpch_m01, smpch_m10, smpch_m00, smpch_vv0, smpch_vv1, smpch_smp;
    alpha_m11 = ( notLastLine && onLeftBorder && hasLeftData )      ? *( iSrc - fmt.BPP + fmt.AID           ) / 255.f : 0.f;
    alpha_m10 = ( hasLeftData && ( notFirstLine || hasTopData ) )   ? *( iSrc - fmt.BPP + fmt.AID - iSrcBps ) / 255.f : 0.f;
    alpha_vv1 = alpha_m10 * TY + alpha_m11 * UY;
    smpch_m11 = ( notLastLine && onLeftBorder && hasLeftData )      ? Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc - fmt.BPP            ) ) ) ) ) / 255.f : 0.f;
    smpch_m10 = ( hasLeftData && ( notFirstLine || hasTopData ) )   ? Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc - fmt.BPP - iSrcBps  ) ) ) ) ) / 255.f : 0.f;
    smpch_vv1 = ( smpch_m10 * alpha_m10 ) * TY + ( smpch_m11 * alpha_m11 )  * UY;

    for( int x = 0; x < info.backdropWorkingRect.w; ++x ) {
        const bool notLastCol = x < info.backdropCoverage.x;
        alpha_m00 = alpha_m10;
        alpha_m01 = alpha_m11;
        alpha_vv0 = alpha_vv1;
        smpch_m00 = smpch_m10;
        smpch_m01 = smpch_m11;
        smpch_vv0 = smpch_vv1;
        alpha_m11 = ( notLastCol && notLastLine )                     ? *( iSrc + fmt.AID             ) / 255.f : 0.f;
        alpha_m10 = ( notLastCol && ( notFirstLine || hasTopData ) )  ? *( iSrc + fmt.AID - iSrcBps   ) / 255.f : 0.f;
        alpha_vv1 = alpha_m10 * TY + alpha_m11 * UY;
        alpha_smp = alpha_vv0 * TX + alpha_vv1 * UX;
        smpch_m11 = ( notLastCol && notLastLine )                     ? Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc              ) ) ) ) ) / 255.f : 0.f;
        smpch_m10 = ( notLastCol && ( notFirstLine || hasTopData ) )  ? Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc - iSrcBps    ) ) ) ) ) / 255.f : 0.f;
        smpch_vv1 = ( smpch_m10 * alpha_m10 ) * TY + ( smpch_m11 * alpha_m11 )  * UY;
        smpch_smp = select( alpha_smp == 0.f, 0.f, ( smpch_vv0 * TX + smpch_vv1 * UX ) / alpha_smp );

        Vec4f alpha_bdp     = *( iBdp + fmt.AID ) / 255.f;
        Vec4f alpha_src     = alpha_smp * info.opacityValue;
        Vec4f alpha_comp    = AlphaNormalSSEF( alpha_src, alpha_bdp );
        Vec4f var           = select( alpha_comp == 0.f, 0.f, alpha_src / alpha_comp );
        Vec4f alpha_result;
        ULIS2_ASSIGN_ALPHASSEF( info.alphaMode, alpha_result, alpha_src, alpha_bdp );

        Vec4f bdp_chan = Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iBdp ) ) ) ) ) / 255.f;
        Vec4f res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = SeparableCompOpSSEF< _BM >( smpch_smp, bdp_chan, alpha_bdp, var ) * 255.f;
        ULIS2_SWITCH_FOR_ALL_COMP_OP_DO( info.blendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN

        auto _pack = _mm_cvtps_epi32( res_chan );
        _pack = _mm_packus_epi32( _pack, _pack );
        _pack = _mm_packus_epi16( _pack, _pack );
        *( uint32* )iBdp = static_cast< uint32 >( _mm_cvtsi128_si32( _pack ) );
        *( iBdp + fmt.AID ) = uint8( alpha_result[0] * 0xFF );
        iSrc += 4;
        iBdp += 4;
    }
}

void
BlendMT_Separable_SSE_RGBA8_Subpixel( std::shared_ptr< const _FBlendInfoPrivate > iInfo ) {
    const _FBlendInfoPrivate&   info        = *iInfo;
    const tByte*                src         = info.source->DataPtr();
    tByte*                      bdp         = info.backdrop->DataPtr();
    const tSize                 src_bps     = info.source->BytesPerScanLine();
    const tSize                 bdp_bps     = info.backdrop->BytesPerScanLine();
    const tSize                 src_decal_y = info.shift.y + info.sourceRect.y;
    const tSize                 src_decal_x = ( info.shift.x + info.sourceRect.x )  * info.source->BytesPerPixel();
    const tSize                 bdp_decal_x = ( info.backdropWorkingRect.x )        * info.source->BytesPerPixel();
    ULIS2_MACRO_INLINE_PARALLEL_FOR( info.perfIntent, info.pool, info.blocking
                                   , info.backdropWorkingRect.h
                                   , InvokeBlendMTProcessScanline_Separable_SSE_RGBA8_Subpixel
                                   , src + ( ( src_decal_y + pLINE )                * src_bps ) + src_decal_x
                                   , bdp + ( ( info.backdropWorkingRect.y + pLINE ) * bdp_bps ) + bdp_decal_x
                                   , pLINE , src_bps, iInfo );
}

void
InvokeBlendMTProcessScanline_Separable_SSE_RGBA8( const tByte* iSrc, tByte* iBdp, int32 iLine, std::shared_ptr< const _FBlendInfoPrivate > iInfo ) {
    const _FBlendInfoPrivate&   info    = *iInfo;
    const FFormatInfo&          fmt     = info.source->FormatInfo();
    const tByte*                src     = iSrc;
    tByte*                      bdp     = iBdp;

    for( int x = 0; x < info.backdropWorkingRect.w; ++x ) {
        ufloat alpha_bdp    = bdp[fmt.AID] / 255.f;
        ufloat alpha_src    = ( src[fmt.AID] / 255.f ) * info.opacityValue;
        ufloat alpha_comp   = AlphaNormalF( alpha_src, alpha_bdp );
        ufloat var          = alpha_comp == 0.f ? 0.f : alpha_src / alpha_comp;
        ufloat alpha_result;
        ULIS2_ASSIGN_ALPHAF( info.alphaMode, alpha_result, alpha_src, alpha_bdp );
        Vec4f src_chan = Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( reinterpret_cast< const __m128i* >( src ) ) ) ) ) / 255.f;
        Vec4f bdp_chan = Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( reinterpret_cast< const __m128i* >( bdp ) ) ) ) ) / 255.f;
        Vec4f res_chan;

        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = SeparableCompOpSSEF< _BM >( src_chan, bdp_chan, alpha_bdp, var ) * 255.f;
        ULIS2_SWITCH_FOR_ALL_COMP_OP_DO( info.blendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN

        auto _pack = _mm_cvtps_epi32( res_chan );
        _pack = _mm_packus_epi32( _pack, _pack );
        _pack = _mm_packus_epi16( _pack, _pack );
        *( uint32* )bdp = static_cast< uint32 >( _mm_cvtsi128_si32( _pack ) );
        bdp[fmt.AID] = static_cast< uint8 >( alpha_result * 0xFF );

        src += 4;
        bdp += 4;
    }
}

void
BlendMT_Separable_SSE_RGBA8( std::shared_ptr< const _FBlendInfoPrivate > iInfo ) {
    const _FBlendInfoPrivate&   info        = *iInfo;
    const tByte*                src         = info.source->DataPtr();
    tByte*                      bdp         = info.backdrop->DataPtr();
    const tSize                 src_bps     = info.source->BytesPerScanLine();
    const tSize                 bdp_bps     = info.backdrop->BytesPerScanLine();
    const tSize                 src_decal_y = info.shift.y + info.sourceRect.y;
    const tSize                 src_decal_x = ( info.shift.x + info.sourceRect.x )  * info.source->BytesPerPixel();
    const tSize                 bdp_decal_x = ( info.backdropWorkingRect.x )        * info.source->BytesPerPixel();
    ULIS2_MACRO_INLINE_PARALLEL_FOR( info.perfIntent, info.pool, info.blocking
                                , info.backdropWorkingRect.h
                                , InvokeBlendMTProcessScanline_Separable_SSE_RGBA8
                                , src + ( ( src_decal_y + pLINE )                * src_bps ) + src_decal_x
                                , bdp + ( ( info.backdropWorkingRect.y + pLINE ) * bdp_bps ) + bdp_decal_x
                                , pLINE , iInfo );
}

ULIS2_NAMESPACE_END

