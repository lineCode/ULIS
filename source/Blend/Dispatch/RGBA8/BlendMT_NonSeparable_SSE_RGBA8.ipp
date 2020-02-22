// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMT_NonSeparable_SSE_RGBA8.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the RGBA8 Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/Blend.h"
#include "Base/Helpers.ipp"
#include "Blend/Func/AlphaFuncSSEF.ipp"
#include "Blend/Func/CompositingHelpers.ipp"
#include "Blend/Func/NonSeparableBlendFuncSSEF.ipp"
#include "Blend/Modes.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"
ULIS2_NAMESPACE_BEGIN
void
InvokeBlendMTProcessScanline_NonSeparable_SSE_RGBA8_Subpixel( const tByte* iSrc, tByte* iBdp, int32 iLine, const tSize iSrcBps, const FFormatInfo* iFmtInfo, std::shared_ptr< const FBlendInfo > iBlendParams, const Vec4i iIDT ) {
    const FBlendInfo&   blendInfo       = *iBlendParams;
    const tByte*        src             = iSrc;
    tByte*              bdp             = iBdp;
    const bool          notLastLine     = iLine < blendInfo._backdropCoverage.y;
    const bool          notFirstLine    = iLine > 0;
    const bool          onLeftBorder    = blendInfo._backdropWorkingRect.x == 0;
    const bool          hasLeftData     = blendInfo.sourceRect.x + blendInfo._shift.x > 0;
    const bool          hasTopData      = blendInfo.sourceRect.y + blendInfo._shift.y > 0;

    Vec4f   TX( blendInfo.backdropPosition.x );
    Vec4f   TY( blendInfo.backdropPosition.y );
    Vec4f   UX( blendInfo._buspixelComponent.x );
    Vec4f   UY( blendInfo._buspixelComponent.y );

    Vec4f alpha_m11, alpha_m01, alpha_m10, alpha_m00, alpha_vv0, alpha_vv1, alpha_smp;
    Vec4f smpch_m11, smpch_m01, smpch_m10, smpch_m00, smpch_vv0, smpch_vv1, smpch_smp;
    alpha_m11 = alpha_m10 = alpha_vv1 = 0.f;
    smpch_m11 = smpch_m10 = smpch_vv1 = 0.f;

    alpha_m11 =( notLastLine && onLeftBorder && hasLeftData )       ? *( iSrc - iFmtInfo->BPP + iFmtInfo->AID           ) / 255.f : 0.f;
    alpha_m10 = ( hasLeftData && ( notFirstLine || hasTopData ) )   ? *( iSrc - iFmtInfo->BPP + iFmtInfo->AID - iSrcBps ) / 255.f : 0.f;
    alpha_vv1 = alpha_m10 * TY + alpha_m11 * UY;

    smpch_m11 =( notLastLine && onLeftBorder && hasLeftData )       ? Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc - iFmtInfo->BPP            ) ) ) ) ) / 255.f : 0.f;
    smpch_m10 = ( hasLeftData && ( notFirstLine || hasTopData ) )   ? Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc - iFmtInfo->BPP - iSrcBps  ) ) ) ) ) / 255.f : 0.f;
    smpch_vv1 = ( smpch_m10 * alpha_m10 ) * TY + ( smpch_m11 * alpha_m11 )  * UY;

    for( int x = 0; x < blendInfo._backdropWorkingRect.w; ++x ) {
        const bool notLastCol = x < blendInfo._backdropCoverage.x;
        alpha_m00 = alpha_m10;
        alpha_m01 = alpha_m11;
        alpha_vv0 = alpha_vv1;
        smpch_m00 = smpch_m10;
        smpch_m01 = smpch_m11;
        smpch_vv0 = smpch_vv1;
        alpha_m11 = ( notLastCol && notLastLine )                     ? *( iSrc + iFmtInfo->AID             ) / 255.f : 0.f;
        alpha_m10 = ( notLastCol && ( notFirstLine || hasTopData ) )  ? *( iSrc + iFmtInfo->AID - iSrcBps   ) / 255.f : 0.f;
        alpha_vv1 = alpha_m10 * TY + alpha_m11 * UY;
        alpha_smp = alpha_vv0 * TX + alpha_vv1 * UX;
        smpch_m11 = ( notLastCol && notLastLine )                     ? Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc              ) ) ) ) ) / 255.f : 0.f;
        smpch_m10 = ( notLastCol && ( notFirstLine || hasTopData ) )  ? Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc - iSrcBps    ) ) ) ) ) / 255.f : 0.f;
        smpch_vv1 = ( smpch_m10 * alpha_m10 ) * TY + ( smpch_m11 * alpha_m11 )  * UY;
        smpch_smp = lookup4( iIDT, select( alpha_smp == 0.f, 0.f, ( smpch_vv0 * TX + smpch_vv1 * UX ) / alpha_smp ) );

        Vec4f alpha_bdp     = *( iBdp + iFmtInfo->AID ) / 255.f;
        Vec4f alpha_src     = alpha_smp * blendInfo.opacityValue;
        Vec4f alpha_comp    = AlphaNormalSSEF( alpha_src, alpha_bdp );
        Vec4f var           = select( alpha_comp == 0.f, 0.f, alpha_src / alpha_comp );
        Vec4f alpha_result;
        ULIS2_ASSIGN_ALPHASSEF( blendInfo.alphaMode, alpha_result, alpha_src, alpha_bdp );

        Vec4f bdp_chan = lookup4( iIDT, Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iBdp ) ) ) ) ) / 255.f );
        smpch_smp.insert( 3, 0.f );
        bdp_chan.insert( 3, 0.f );
        Vec4f res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = NonSeparableCompOpSSEF< _BM >( smpch_smp, bdp_chan, alpha_bdp, var ) * 255.f;
        ULIS2_SWITCH_FOR_ALL_DO( blendInfo.blendingMode, ULIS2_FOR_ALL_NONSEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN

        res_chan = lookup4( iIDT, res_chan );
        auto _pack = _mm_cvtps_epi32( res_chan );
        _pack = _mm_packus_epi32( _pack, _pack );
        _pack = _mm_packus_epi16( _pack, _pack );
        *( uint32* )iBdp = static_cast< uint32 >( _mm_cvtsi128_si32( _pack ) );
        *( iBdp + iFmtInfo->AID ) = uint8( alpha_result[0] * 0xFF );
        iSrc += 4;
        iBdp += 4;
    }
}

void
BlendMT_NonSeparable_SSE_RGBA8_Subpixel( const FFormatInfo& iFormatInfo, std::shared_ptr< const FBlendInfo > iBlendParams ) {
    Vec4i idt;
    BuildRGBA8IndexTable( iFormatInfo.COD, &idt );
    const FBlendInfo&   blendInfo   = *iBlendParams;
    const tByte*        src         = iBlendParams->source->DataPtr();
    tByte*              bdp         = iBlendParams->backdrop->DataPtr();
    const tSize         src_bps     = iBlendParams->source->BytesPerScanLine();
    const tSize         bdp_bps     = iBlendParams->backdrop->BytesPerScanLine();
    const tSize         src_decal_x = blendInfo.sourceRect.x            * iFormatInfo.BPP;
    const tSize         bdp_decal_x = blendInfo._backdropWorkingRect.x  * iFormatInfo.BPP;
    ULIS2_MACRO_INLINE_PARALLEL_FOR( blendInfo.perfInfo.intent, blendInfo.perfInfo.pool, blendInfo.perfInfo.blocking
                                   , blendInfo._backdropWorkingRect.h
                                   , InvokeBlendMTProcessScanline_NonSeparable_SSE_RGBA8_Subpixel
                                   , src + ( ( blendInfo.sourceRect.y           + pLINE ) * src_bps ) + src_decal_x
                                   , bdp + ( ( blendInfo._backdropWorkingRect.y + pLINE ) * bdp_bps ) + bdp_decal_x
                                   , pLINE, src_bps, &iFormatInfo, iBlendParams, idt );
}

void
InvokeBlendMTProcessScanline_NonSeparable_SSE_RGBA8( const tByte* iSrc, tByte* iBdp, int32 iLine, const FFormatInfo* iFmtInfo, std::shared_ptr< const FBlendInfo > iBlendParams, const Vec4i iIDT ) {
    const FBlendInfo&   blendInfo   = *iBlendParams;
    const tByte*        src         = iSrc;
    tByte*              bdp         = iBdp;

    for( int x = 0; x < blendInfo._backdropWorkingRect.w; ++x ) {
        ufloat alpha_bdp    = bdp[iFmtInfo->AID] / 255.f;
        ufloat alpha_src    = ( src[iFmtInfo->AID] / 255.f ) * blendInfo.opacityValue;
        ufloat alpha_comp   = AlphaNormalF( alpha_src, alpha_bdp );
        ufloat var          = alpha_comp == 0.f ? 0.f : alpha_src / alpha_comp;
        ufloat alpha_result;
        ULIS2_ASSIGN_ALPHAF( blendInfo.alphaMode, alpha_result, alpha_src, alpha_bdp );

        Vec4f src_chan = lookup4( iIDT, Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc ) ) ) ) ) / 255.f );
        Vec4f bdp_chan = lookup4( iIDT, Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iBdp ) ) ) ) ) / 255.f );
        src_chan.insert( 3, 0.f );
        bdp_chan.insert( 3, 0.f );
        Vec4f res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = NonSeparableCompOpSSEF< _BM >( src_chan, bdp_chan, alpha_bdp, var ) * 255.f;
        ULIS2_SWITCH_FOR_ALL_DO( blendInfo.blendingMode, ULIS2_FOR_ALL_NONSEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN

        res_chan = lookup4( iIDT, res_chan );
        auto _pack = _mm_cvtps_epi32( res_chan );
        _pack = _mm_packus_epi32( _pack, _pack );
        _pack = _mm_packus_epi16( _pack, _pack );
        *( uint32* )iBdp = static_cast< uint32 >( _mm_cvtsi128_si32( _pack ) );
        *( iBdp + iFmtInfo->AID ) = uint8( alpha_result * 0xFF );
        iSrc += 4;
        iBdp += 4;
    }
}

void
BlendMT_NonSeparable_SSE_RGBA8( const FFormatInfo& iFormatInfo, std::shared_ptr< const FBlendInfo > iBlendParams ) {
    Vec4i idt;
    BuildRGBA8IndexTable( iFormatInfo.COD, &idt );
    const FBlendInfo&   blendInfo   = *iBlendParams;
    const tByte*        src         = iBlendParams->source->DataPtr();
    tByte*              bdp         = iBlendParams->backdrop->DataPtr();
    const tSize         src_bps     = iBlendParams->source->BytesPerScanLine();
    const tSize         bdp_bps     = iBlendParams->backdrop->BytesPerScanLine();
    const tSize         src_decal_x = blendInfo.sourceRect.x            * iFormatInfo.BPP;
    const tSize         bdp_decal_x = blendInfo._backdropWorkingRect.x  * iFormatInfo.BPP;
    ULIS2_MACRO_INLINE_PARALLEL_FOR( blendInfo.perfInfo.intent, blendInfo.perfInfo.pool, blendInfo.perfInfo.blocking
                                   , blendInfo._backdropWorkingRect.h
                                   , InvokeBlendMTProcessScanline_NonSeparable_SSE_RGBA8
                                   , src + ( ( blendInfo.sourceRect.y           + pLINE ) * src_bps ) + src_decal_x
                                   , bdp + ( ( blendInfo._backdropWorkingRect.y + pLINE ) * bdp_bps ) + bdp_decal_x
                                   , pLINE , &iFormatInfo, iBlendParams, idt );
}

ULIS2_NAMESPACE_END

