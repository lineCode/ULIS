// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         BlendMT_NonSeparable_SSE_RGBA8.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the RGBA8 Blend entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Blend/Modes.h"
#include "Blend/Dispatch/BlendInfo.h"
#include "Blend/Func/AlphaFuncSSEF.ipp"
#include "Blend/Func/CompositingHelpers.ipp"
#include "Blend/Func/NonSeparableBlendFuncSSEF.ipp"
#include "Maths/Geometry.h"
#include "Thread/ThreadPool.h"

ULIS3_NAMESPACE_BEGIN
void
InvokeTiledBlendMTProcessScanline_NonSeparable_SSE_RGBA8( const tByte* iSrc, tByte* iBdp, int32 iLine, std::shared_ptr< const _FBlendInfoPrivate > iInfo, const Vec4i iIDT ) {
    const _FBlendInfoPrivate&   info    = *iInfo;
    const FFormatInfo&          fmt     = info.source->FormatInfo();

    for( int x = 0; x < info.backdropWorkingRect.w; ++x ) {
        ufloat alpha_bdp    = iBdp[fmt.AID] / 255.f;
        ufloat alpha_src    = ( iSrc[fmt.AID] / 255.f ) * info.opacityValue;
        ufloat alpha_comp   = AlphaNormalF( alpha_src, alpha_bdp );
        ufloat var          = alpha_comp == 0.f ? 0.f : alpha_src / alpha_comp;
        ufloat alpha_result;
        ULIS3_ASSIGN_ALPHAF( info.alphaMode, alpha_result, alpha_src, alpha_bdp );

        Vec4f src_chan = lookup4( iIDT, Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc ) ) ) ) ) / 255.f );
        Vec4f bdp_chan = lookup4( iIDT, Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iBdp ) ) ) ) ) / 255.f );
        src_chan.insert( 3, 0.f );
        bdp_chan.insert( 3, 0.f );
        Vec4f res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = NonSeparableCompOpSSEF< _BM >( src_chan, bdp_chan, alpha_bdp, var ) * 255.f;
        ULIS3_SWITCH_FOR_ALL_DO( info.blendingMode, ULIS3_FOR_ALL_NONSEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN

        res_chan = lookup4( iIDT, res_chan );
        auto _pack = _mm_cvtps_epi32( res_chan );
        _pack = _mm_packus_epi32( _pack, _pack );
        _pack = _mm_packus_epi16( _pack, _pack );
        *( uint32* )iBdp = static_cast< uint32 >( _mm_cvtsi128_si32( _pack ) );
        *( iBdp + fmt.AID ) = uint8( alpha_result * 0xFF );
        iSrc += 4;
        iBdp += 4;
    }
}

void
TiledBlendMT_NonSeparable_SSE_RGBA8( std::shared_ptr< const _FBlendInfoPrivate > iInfo ) {
    const _FBlendInfoPrivate&   info        = *iInfo;
    const tByte*                src         = info.source->DataPtr();
    tByte*                      bdp         = info.backdrop->DataPtr();
    const tSize                 src_bps     = info.source->BytesPerScanLine();
    const tSize                 bdp_bps     = info.backdrop->BytesPerScanLine();
    const tSize                 src_decal_y = info.shift.y + info.sourceRect.y;
    const tSize                 src_decal_x = ( info.shift.x + info.sourceRect.x )  * info.source->BytesPerPixel();
    const tSize                 bdp_decal_x = ( info.backdropWorkingRect.x )        * info.source->BytesPerPixel();
    Vec4i idt;
    BuildRGBA8IndexTable( info.source->FormatInfo().COD, &idt );
    ULIS3_MACRO_INLINE_PARALLEL_FOR( info.perfIntent, info.pool, info.blocking
                                , info.backdropWorkingRect.h
                                , InvokeTiledBlendMTProcessScanline_NonSeparable_SSE_RGBA8
                                , src + ( ( src_decal_y + pLINE )                * src_bps ) + src_decal_x
                                , bdp + ( ( info.backdropWorkingRect.y + pLINE ) * bdp_bps ) + bdp_decal_x
                                , pLINE , iInfo, idt );
}

ULIS3_NAMESPACE_END

