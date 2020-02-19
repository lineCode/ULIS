// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMT_Separable_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/Blend.h"
#include "Base/Helpers.ipp"
#include "Blend/Modes.h"
#include "Blend/Func/SeparableBlendFuncF.ipp"
#include "Blend/Func/AlphaFuncF.ipp"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void
InvokeBlendMTProcessScanline_Separable_MEM_Generic_Subpixel( int32              iLINE
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
    const tByte* src = iSRC;
    tByte*       bdp = iBDP;
    const glm::vec2&    sub = iSubpixelComponent;
    glm::vec2           bus = glm::vec2( 1.f ) - iSubpixelComponent;

    //  -------------
    //  | m00 | m10 |
    //  |_____|_____|___
    //  | m01 | m11 |
    //  |_____|_____|
    //     |  |  |
    //    vv0 | vv1  -> res
    float m11, m01, m10, m00, vv0, vv1, res;
    m11 = m10 = vv1 = 0.f;
    for( int x = 0; x < iBdpROI.w; ++x ) {
        m00 = m10;
        m01 = m11;
        vv0 = vv1;
        SampleSubpixelAlphaOpt< T >( src, iHEA, iAID, iBPP, iSRC_BPS, x, iLINE, iSrcROI.w, iSrcROI.h, sub, bus, vv0, &m11, &m10, &vv1, &res );
        const float alpha_bdp       = iHEA ? TYPE2FLOAT( bdp, iAID ) : 1.f;
        const float alpha_src       = res * iOpacity;
        const float alpha_comp      = AlphaNormalF( alpha_src, alpha_bdp );
        const float var             = alpha_comp == 0.f ? 0.f : alpha_src / alpha_comp;
        float alpha_result;
        ULIS2_ASSIGN_ALPHAF( iAlphaMode, alpha_result, alpha_src, alpha_bdp );

        for( uint8 j = 0; j < iNCC; ++j )
        {
            uint8 r = iXIDT[j];
            float srcvf = SampleSubpixelChannelPremult< T >( src, r, iBPP, iSRC_BPS, x, iLINE, iSrcROI.w, iSrcROI.h, sub, bus, m11, m01, m10, m00, res );
            float bdpvf = TYPE2FLOAT( bdp, r );
            #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) FLOAT2TYPE( bdp, r, SeparableCompOpF< _BM >( srcvf, bdpvf, alpha_bdp, var ) );
            ULIS2_SWITCH_FOR_ALL_DO( iBlendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
            #undef TMP_ASSIGN
        }

        // Assign alpha
        if( iHEA ) FLOAT2TYPE( bdp, iAID, alpha_result );

        // Increment ptrs by one pixel
        src += iBPP;
        bdp += iBPP;
    }
}

template< typename T >
void
BlendMT_Separable_MEM_Generic_Subpixel( FThreadPool*        iPool
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
    uint8* xidt;
    uint8 bpc, ncc, hea, spp, bpp, aid;
    tSize roi_w, roi_h, src_bps, bdp_bps, src_jmp, bdp_jmp;
    BuildBlendParams( iBdpROI, iSource, iBackdrop, &bpc, &ncc, &hea, &spp, &bpp, &aid, &xidt, &roi_w, &roi_h, &src_bps, &bdp_bps, &src_jmp, &bdp_jmp );
    const tByte*    src = iSource->DataPtr();
    tByte*          bdp = iBackdrop->DataPtr();
    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iBdpROI.h, InvokeBlendMTProcessScanline_Separable_MEM_Generic_Subpixel< T >, pLINE
                                                                       , src + ( ( iSrcROI.y + pLINE ) * src_bps ) + ( iSrcROI.x * bpp )
                                                                       , bdp + ( ( iBdpROI.y + pLINE ) * bdp_bps ) + ( iBdpROI.x * bpp )
                                                                       , xidt, bpc, ncc, hea, spp, bpp, aid, src_bps, iSrcROI, iBdpROI
                                                                       , iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity );
}

template< typename T >
void
InvokeBlendMTProcessScanline_Separable_MEM_Generic( int32               iLINE
                                                  , const tByte*        iSRC
                                                  , tByte*              iBDP
                                                  , uint8*              iXIDT
                                                  , uint8               iBCP
                                                  , uint8               iNCC
                                                  , uint8               iHEA
                                                  , uint8               iSPP
                                                  , uint8               iBPP
                                                  , uint8               iAID
                                                  , tSize               iSRC_BPS
                                                  , const FRect&        iSrcROI
                                                  , const FRect&        iBdpROI
                                                  , const glm::vec2&    iSubpixelComponent
                                                  , eBlendingMode       iBlendingMode
                                                  , eAlphaMode          iAlphaMode
                                                  , ufloat              iOpacity )
{
    const tByte* src = iSRC;
    tByte*       bdp = iBDP;

    for( int x = 0; x < iBdpROI.w; ++x ) {
        // Compose Alpha
        const float alpha_bdp       = iHEA ? TYPE2FLOAT( bdp, iAID ) : 1.f;
        const float alpha_src       = iHEA ? TYPE2FLOAT( src, iAID ) * iOpacity : iOpacity;
        const float alpha_comp      = AlphaNormalF( alpha_src, alpha_bdp );
        const float var             = alpha_comp == 0.f ? 0.f : alpha_src / alpha_comp;
        float alpha_result;
        ULIS2_ASSIGN_ALPHAF( iAlphaMode, alpha_result, alpha_src, alpha_bdp );

        // Compose Channels
        for( uint8 j = 0; j < iNCC; ++j )
        {
            uint8 r = iXIDT[j];
            float srcvf = TYPE2FLOAT( src, r );
            float bdpvf = TYPE2FLOAT( bdp, r );
            #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) FLOAT2TYPE( bdp, r, SeparableCompOpF< _BM >( srcvf, bdpvf, alpha_bdp, var ) );
            ULIS2_SWITCH_FOR_ALL_DO( iBlendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
            #undef TMP_ASSIGN
        }

        // Assign alpha
        if( iHEA ) FLOAT2TYPE( bdp, iAID, alpha_result );

        // Increment ptrs by one pixel
        src += iBPP;
        bdp += iBPP;
    }
}

template< typename T >
void
BlendMT_Separable_MEM_Generic( FThreadPool*     iPool
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
    uint8* xidt;
    uint8 bpc, ncc, hea, spp, bpp, aid;
    tSize roi_w, roi_h, src_bps, bdp_bps, src_jmp, bdp_jmp;
    BuildBlendParams( iBdpROI, iSource, iBackdrop, &bpc, &ncc, &hea, &spp, &bpp, &aid, &xidt, &roi_w, &roi_h, &src_bps, &bdp_bps, &src_jmp, &bdp_jmp );
    const tByte*    src = iSource->DataPtr();
    tByte*          bdp = iBackdrop->DataPtr();
    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iBdpROI.h, InvokeBlendMTProcessScanline_Separable_MEM_Generic< T >, pLINE
                                                                       , src + ( ( iSrcROI.y + pLINE ) * src_bps ) + ( iSrcROI.x * bpp )
                                                                       , bdp + ( ( iBdpROI.y + pLINE ) * bdp_bps ) + ( iBdpROI.x * bpp )
                                                                       , xidt, bpc, ncc, hea, spp, bpp, aid, src_bps, iSrcROI, iBdpROI
                                                                       , iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity );
}

ULIS2_NAMESPACE_END

