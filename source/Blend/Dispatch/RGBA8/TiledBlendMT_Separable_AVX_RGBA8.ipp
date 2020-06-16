// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         BlendMT_Separable_AVX_RGBA8.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the RGBA8 Blend entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Blend/Modes.h"
#include "Blend/Dispatch/BlendInfo.h"
#include "Blend/Func/AlphaFuncAVX.ipp"
#include "Blend/Func/SeparableBlendFuncAVXF.ipp"
#include "Maths/Geometry.h"
#include "Thread/ThreadPool.h"

ULIS3_NAMESPACE_BEGIN
void
InvokeTiledBlendMTProcessScanline_Separable_AVX_RGBA8( const tByte* iSrc, tByte* iBdp, int32 iLine, std::shared_ptr< const _FBlendInfoPrivate > iInfo ) {
    const _FBlendInfoPrivate&   info    = *iInfo;
    const FFormatInfo&          fmt     = info.source->FormatInfo();
    const tByte*                src     = iSrc;
    tByte*                      bdp     = iBdp;

    const uint32 len = info.backdropWorkingRect.w / 2;
    for( uint32 i = 0; i < len; ++i ) {
        Vec8f   alpha_bdp   = Vec8f( iBdp[fmt.AID], iBdp[fmt.AID + 4] ) / 255.f;
        Vec8f   alpha_src   = Vec8f( iSrc[fmt.AID], iSrc[fmt.AID + 4] ) / 255.f * info.opacityValue;
        Vec8f   alpha_comp  = AlphaNormalAVXF( alpha_src, alpha_bdp );
        Vec8f   var         = select( alpha_comp == 0.f, 0.f, ( alpha_src / alpha_comp ) );
        Vec8f   alpha_result;
        ULIS3_ASSIGN_ALPHAAVXF( info.alphaMode, alpha_result, alpha_src, alpha_bdp );
        alpha_result *= 255.f;

        Vec8f   src_chan = Vec8f( _mm256_cvtepi32_ps( _mm256_cvtepu8_epi32( _mm_loadu_si64( iSrc ) ) ) ) / 255.f;
        Vec8f   bdp_chan = Vec8f( _mm256_cvtepi32_ps( _mm256_cvtepu8_epi32( _mm_loadu_si64( iBdp ) ) ) ) / 255.f;
        Vec8f   res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = SeparableCompOpAVXF< _BM >( src_chan, bdp_chan, alpha_bdp, var ) * 255.f;
        ULIS3_SWITCH_FOR_ALL_DO( info.blendingMode, ULIS3_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN

        Vec8ui _pack0 = _mm256_cvtps_epi32( res_chan );
        Vec8us _pack1 = compress( _pack0 );
        auto _pack = _mm_packus_epi16( _pack1, _pack1 );
        _mm_storeu_si64( iBdp, _pack );
        iBdp[fmt.AID]      = static_cast< uint8 >( alpha_result[0] );
        iBdp[fmt.AID+4]    = static_cast< uint8 >( alpha_result[4] );

        iSrc += 8;
        iBdp += 8;
    }

    // In case W is odd, process one last pixel.
    if( info.backdropWorkingRect.w % 2 ) {
        Vec8f   alpha_bdp   = Vec8f( iBdp[fmt.AID], 0 ) / 255.f;
        Vec8f   alpha_src   = Vec8f( iSrc[fmt.AID], 0 ) / 255.f * info.opacityValue;
        Vec8f   alpha_comp  = AlphaNormalAVXF( alpha_src, alpha_bdp );
        Vec8f   var         = select( alpha_comp == 0.f, 0.f, ( alpha_src / alpha_comp ) );
        Vec8f   alpha_result;
        ULIS3_ASSIGN_ALPHAAVXF( info.alphaMode, alpha_result, alpha_src, alpha_bdp );
        alpha_result *= 255.f;

        Vec8f   src_chan = Vec8f( _mm256_cvtepi32_ps( _mm256_cvtepu8_epi32( _mm_loadu_si32( iSrc ) ) ) ) / 255.f;
        Vec8f   bdp_chan = Vec8f( _mm256_cvtepi32_ps( _mm256_cvtepu8_epi32( _mm_loadu_si32( iBdp ) ) ) ) / 255.f;
        Vec8f   res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = SeparableCompOpAVXF< _BM >( src_chan, bdp_chan, alpha_bdp, var ) * 255.f;
        ULIS3_SWITCH_FOR_ALL_DO( info.blendingMode, ULIS3_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN

        Vec8ui _pack0 = _mm256_cvtps_epi32( res_chan );
        Vec8us _pack1 = compress( _pack0 );
        auto _pack = _mm_packus_epi16( _pack1, _pack1 );
        _mm_storeu_si32( iBdp, _pack );
        iBdp[fmt.AID] = static_cast< uint8 >( alpha_result[0] );
    }
}

void
TiledBlendMT_Separable_AVX_RGBA8( std::shared_ptr< const _FBlendInfoPrivate > iInfo ) {
    const _FBlendInfoPrivate&   info        = *iInfo;
    const tByte*                src         = info.source->DataPtr();
    tByte*                      bdp         = info.backdrop->DataPtr();
    const tSize                 src_bps     = info.source->BytesPerScanLine();
    const tSize                 bdp_bps     = info.backdrop->BytesPerScanLine();
    const tSize                 src_decal_y = info.shift.y + info.sourceRect.y;
    const tSize                 src_decal_x = ( info.shift.x + info.sourceRect.x )  * info.source->BytesPerPixel();
    const tSize                 bdp_decal_x = ( info.backdropWorkingRect.x )        * info.source->BytesPerPixel();
    ULIS3_MACRO_INLINE_PARALLEL_FOR( info.perfIntent, info.pool, info.blocking
                                , info.backdropWorkingRect.h
                                , InvokeTiledBlendMTProcessScanline_Separable_AVX_RGBA8
                                , src + ( ( src_decal_y + pLINE )                * src_bps ) + src_decal_x
                                , bdp + ( ( info.backdropWorkingRect.y + pLINE ) * bdp_bps ) + bdp_decal_x
                                , pLINE , iInfo );
}

ULIS3_NAMESPACE_END

