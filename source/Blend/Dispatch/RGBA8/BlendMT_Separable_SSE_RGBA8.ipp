// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMT_Separable_SSE_RGBA8.ipp
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
#include "Blend/Func/SeparableBlendFuncSSEF.ipp"
#include "Blend/Modes.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"

ULIS2_NAMESPACE_BEGIN
void
InvokeBlendMTProcessScanline_Separable_SSE_RGBA8_Subpixel( int32              iLINE
                                                         , const tByte*       iSRC
                                                         , tByte*             iBDP
                                                         , uint8*             iXIDT
                                                         , uint8              iBPC
                                                         , uint8              iNCC
                                                         , uint8              iHEA
                                                         , uint8              iSPP
                                                         , uint8              iBPP
                                                         , uint8              iAID
                                                         , tSize              iSRC_BPS
                                                         , const FRect&       iSrcROI
                                                         , const FRect&       iBdpROI
                                                         , const glm::vec2&   iSubpixelComponent
                                                         , eBlendingMode      iBlendingMode
                                                         , eAlphaMode         iAlphaMode
                                                         , ufloat             iOpacity )
{
}

void
BlendMT_Separable_SSE_RGBA8_Subpixel( FThreadPool*        iPool
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
}

void
InvokeBlendMTProcessScanline_Separable_SSE_RGBA8( const tByte*          iSrc
                                                , tByte*                iBdp
                                                , int                   iW
                                                , const uint8           iAid
                                                , const eBlendingMode   iBlendingMode
                                                , const eAlphaMode      iAlphaMode
                                                , float                 iOpacity )
{
    while( iW-- ) {
        ufloat alpha_bdp    = *( iBdp + iAid ) / 255.f;
        ufloat alpha_src    = ( *( iSrc + iAid ) / 255.f ) * iOpacity;
        ufloat alpha_comp   = AlphaNormalF( alpha_src, alpha_bdp );
        ufloat var          = alpha_comp == 0.f ? 0.f : alpha_src / alpha_comp;
        ufloat alpha_result;
        ULIS2_ASSIGN_ALPHAF( iAlphaMode, alpha_result, alpha_src, alpha_bdp );
        Vec4f src_chan = Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iSrc ) ) ) ) ) / 255.f;
        Vec4f bdp_chan = Vec4f( _mm_cvtepi32_ps( _mm_cvtepu8_epi32( _mm_loadu_si128( (const __m128i*)( iBdp ) ) ) ) ) / 255.f;
        Vec4f res_chan;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) res_chan = SeparableCompOpSSEF< _BM >( src_chan, bdp_chan, alpha_bdp, var ) * 255.f;
        ULIS2_SWITCH_FOR_ALL_DO( iBlendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        auto _pack = _mm_cvtps_epi32( res_chan );
        _pack = _mm_packus_epi32( _pack, _pack );
        _pack = _mm_packus_epi16( _pack, _pack );
        *( uint32* )iBdp = static_cast< uint32 >( _mm_cvtsi128_si32( _pack ) );
        *( iBdp + iAid ) = uint8( alpha_result * 0xFF );
        iSrc += 4;
        iBdp += 4;
    }
}

void
BlendMT_Separable_SSE_RGBA8( FThreadPool*     iPool
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
    // bpc = 1;
    // ncc = 3;
    // hea = true;
    // spp = 4;
    // bpp = 4;
    tFormat fmt = iSource->Format();
    uint8   aid = ( ( ( ~( ( ULIS2_R_RS( fmt ) + 0x1 ) & 0x2 ) ) & 0x2 ) >> 1 ) * 3;

    tSize   src_bps = 4 * iSource->Width();
    tSize   bdp_bps = 4 * iBackdrop->Width();
    ParallelFor( *iPool
               , iBlocking
               , iPerf
               , iBdpROI.h
               , ULIS2_PF_CALL {
                    InvokeBlendMTProcessScanline_Separable_SSE_RGBA8( iSource->DataPtr()    + ( ( iSrcROI.y + iLine ) * src_bps ) + ( iSrcROI.x * 4 )
                                                                    , iBackdrop->DataPtr()  + ( ( iBdpROI.y + iLine ) * bdp_bps ) + ( iBdpROI.x * 4 )
                                                                    , iBdpROI.w, aid, iBlendingMode, iAlphaMode, iOpacity );
               } );
}

ULIS2_NAMESPACE_END

