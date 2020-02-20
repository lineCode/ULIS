// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMT_NonSeparable_CM_Lab_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Base/Helpers.ipp"
#include "Blend/Modes.h"
#include "Blend/Func/AlphaFuncF.ipp"
#include "Blend/Func/NonSeparableBlendFuncF.ipp"
#include "Color/ModelStructs.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void
InvokeBlendMTProcessScanline_NonSeparable_CM_Lab_MEM_Generic_Subpixel( int32            iLINE
                                                                     , const tByte*     iSRC
                                                                     , tByte*           iBDP
                                                                     , uint8*           iXIDT
                                                                     , uint8            iBPC
                                                                     , uint8            iNCC
                                                                     , uint8            iHEA
                                                                     , uint8            iSPP
                                                                     , uint8            iBPP
                                                                     , uint8            iAID
                                                                     , tSize             iSRC_BPS
                                                                     , const FRect&     iSrcROI
                                                                     , const FRect&     iBdpROI
                                                                     , const glm::vec2& iSubpixelComponent
                                                                     , eBlendingMode    iBlendingMode
                                                                     , eAlphaMode       iAlphaMode
                                                                     , ufloat           iOpacity )
{
    const tByte*        src = iSRC;
    tByte*              bdp = iBDP;
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
        SampleSubpixelAlphaOpt< T >( src, iHEA, iAID, iBPP, iSRC_BPS, x, iLINE, 0000, 0000, iSrcROI.w, iSrcROI.h, sub, bus, vv0, &m11, &m10, &vv1, &res );
        const float alpha_bdp       = iHEA ? TYPE2FLOAT( bdp, iAID ) : 1.f;
        const float alpha_src       = res * iOpacity;
        const float alpha_comp      = AlphaNormalF( alpha_src, alpha_bdp );
        const float var             = alpha_comp == 0.f ? 0.f : alpha_src / alpha_comp;
        float alpha_result;
        ULIS2_ASSIGN_ALPHAF( iAlphaMode, alpha_result, alpha_src, alpha_bdp );

        float subpixel_L = SampleSubpixelChannelPremult< T >( src, iXIDT[0], iBPP, iSRC_BPS, x, iLINE, 0000, 0000, iSrcROI.w, iSrcROI.h, sub, bus, m11, m01, m10, m00, res );
        float subpixel_a = SampleSubpixelChannelPremult< T >( src, iXIDT[1], iBPP, iSRC_BPS, x, iLINE, 0000, 0000, iSrcROI.w, iSrcROI.h, sub, bus, m11, m01, m10, m00, res );
        float subpixel_b = SampleSubpixelChannelPremult< T >( src, iXIDT[2], iBPP, iSRC_BPS, x, iLINE, 0000, 0000, iSrcROI.w, iSrcROI.h, sub, bus, m11, m01, m10, m00, res );
        FLabF src_lab = { subpixel_L, subpixel_a, subpixel_b };
        FLabF bdp_lab = { TYPE2FLOAT( bdp, iXIDT[0] ), TYPE2FLOAT( bdp, iXIDT[1] ), TYPE2FLOAT( bdp, iXIDT[2] ) };
        FLChF src_lch = LabToLCh( src_lab );
        FLChF bdp_lch = LabToLCh( bdp_lab );
        FLChF result_lch;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) result_lch = NonSeparableOpF< _BM >( src_lch, bdp_lch );
        ULIS2_SWITCH_FOR_ALL_DO( iBlendingMode, ULIS2_FOR_ALL_NONSEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN
        FLabF result_lab = LChToLab( result_lch );

        // Compose
        for( uint8 j = 0; j < iNCC; ++j )
            FLOAT2TYPE( bdp, iXIDT[j], ComposeF( *( &(src_lab.L) + j ), *( &(bdp_lab.L) + j ), alpha_bdp, var, *( &(result_lab.L) + j ) ) );

        // Assign alpha
        if( iHEA ) FLOAT2TYPE( bdp, iAID, alpha_result );

        // Increment ptrs by one pixel
        src += iBPP;
        bdp += iBPP;
    }
}

template< typename T >
void
BlendMT_NonSeparable_CM_Lab_MEM_Generic_Subpixel( FThreadPool*      iPool
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
    uint8* xidt;
    uint8 bpc, ncc, hea, spp, bpp, aid;
    tSize roi_w, roi_h, src_bps, bdp_bps, src_jmp, bdp_jmp;
    BuildBlendParams( iBdpROI, iSource, iBackdrop, &bpc, &ncc, &hea, &spp, &bpp, &aid, &xidt, &roi_w, &roi_h, &src_bps, &bdp_bps, &src_jmp, &bdp_jmp );
    const tByte*    src = iSource->DataPtr();
    tByte*          bdp = iBackdrop->DataPtr();
    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iBdpROI.h, InvokeBlendMTProcessScanline_NonSeparable_CM_Lab_MEM_Generic_Subpixel< T >, pLINE
                                                                       , src + ( ( iSrcROI.y + pLINE ) * src_bps ) + ( iSrcROI.x * bpp )
                                                                       , bdp + ( ( iBdpROI.y + pLINE ) * bdp_bps ) + ( iBdpROI.x * bpp )
                                                                       , xidt, bpc, ncc, hea, spp, bpp, aid, src_bps, iSrcROI, iBdpROI
                                                                       , iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity );
}

template< typename T >
void
InvokeBlendMTProcessScanline_NonSeparable_CM_Lab_MEM_Generic( int32             iLINE
                                                            , const tByte*      iSRC
                                                            , tByte*            iBDP
                                                            , uint8*            iXIDT
                                                            , uint8             iBPC
                                                            , uint8             iNCC
                                                            , uint8             iHEA
                                                            , uint8             iSPP
                                                            , uint8             iBPP
                                                            , uint8             iAID
                                                            , tSize             iSRC_BPS
                                                            , const FRect&      iSrcROI
                                                            , const FRect&      iBdpROI
                                                            , const glm::vec2&  iSubpixelComponent
                                                            , eBlendingMode     iBlendingMode
                                                            , eAlphaMode        iAlphaMode
                                                            , ufloat            iOpacity )
{
    const tByte*    src = iSRC;
    tByte*          bdp = iBDP;

    for( int x = 0; x < iBdpROI.w; ++x ) {
        // Compose Alpha
        const float alpha_bdp       = iHEA ? TYPE2FLOAT( bdp, iAID ) : 1.f;
        const float alpha_src       = iHEA ? TYPE2FLOAT( src, iAID ) * iOpacity : iOpacity;
        const float alpha_comp      = AlphaNormalF( alpha_src, alpha_bdp );
        const float var             = alpha_comp == 0.f ? 0.f : alpha_src / alpha_comp;
        float alpha_result;
        ULIS2_ASSIGN_ALPHAF( iAlphaMode, alpha_result, alpha_src, alpha_bdp );

        FLabF src_lab = { TYPE2FLOAT( src, iXIDT[0] ), TYPE2FLOAT( src, iXIDT[1] ), TYPE2FLOAT( src, iXIDT[2] ) };
        FLabF bdp_lab = { TYPE2FLOAT( bdp, iXIDT[0] ), TYPE2FLOAT( bdp, iXIDT[1] ), TYPE2FLOAT( bdp, iXIDT[2] ) };
        FLChF src_lch = LabToLCh( src_lab );
        FLChF bdp_lch = LabToLCh( bdp_lab );
        FLChF result_lch;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) result_lch = NonSeparableOpF< _BM >( src_lch, bdp_lch );
        ULIS2_SWITCH_FOR_ALL_DO( iBlendingMode, ULIS2_FOR_ALL_NONSEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN
        FLabF result_lab = LChToLab( result_lch );

        // Compose
        for( uint8 j = 0; j < iNCC; ++j )
            FLOAT2TYPE( bdp, iXIDT[j], ComposeF( *( &(src_lab.L) + j ), *( &(bdp_lab.L) + j ), alpha_bdp, var, *( &(result_lab.L) + j ) ) );

        // Assign alpha
        if( iHEA ) FLOAT2TYPE( bdp, iAID, alpha_result );

        // Increment ptrs by one pixel
        src += iBPP;
        bdp += iBPP;
    }
}

template< typename T >
void
BlendMT_NonSeparable_CM_Lab_MEM_Generic( FThreadPool*       iPool
                                       , bool               iBlocking
                                       , const FPerf&       iPerf
                                       , const FBlock*      iSource
                                       , FBlock*            iBackdrop
                                       , const FRect&       iSrcROI
                                       , const FRect&       iBdpROI
                                       , const glm::vec2&   iSubpixelComponent
                                       , eBlendingMode      iBlendingMode
                                       , eAlphaMode         iAlphaMode
                                       , ufloat             iOpacity )
{
    uint8* xidt;
    uint8 bpc, ncc, hea, spp, bpp, aid;
    tSize roi_w, roi_h, src_bps, bdp_bps, src_jmp, bdp_jmp;
    BuildBlendParams( iBdpROI, iSource, iBackdrop, &bpc, &ncc, &hea, &spp, &bpp, &aid, &xidt, &roi_w, &roi_h, &src_bps, &bdp_bps, &src_jmp, &bdp_jmp );
    const tByte*    src = iSource->DataPtr();
    tByte*          bdp = iBackdrop->DataPtr();
    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, iBdpROI.h, InvokeBlendMTProcessScanline_NonSeparable_CM_Lab_MEM_Generic< T >, pLINE
                                                                       , src + ( ( iSrcROI.y + pLINE ) * src_bps ) + ( iSrcROI.x * bpp )
                                                                       , bdp + ( ( iBdpROI.y + pLINE ) * bdp_bps ) + ( iBdpROI.x * bpp )
                                                                       , xidt, bpc, ncc, hea, spp, bpp, aid, src_bps, iSrcROI, iBdpROI
                                                                       , iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity );
}

ULIS2_NAMESPACE_END

