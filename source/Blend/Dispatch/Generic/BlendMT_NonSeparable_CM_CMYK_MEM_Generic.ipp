// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMT_NonSeparable_CM_CMYK_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/Func/BlendHelpers.ipp"
#include "Blend/Modes.h"
#include "Blend/Func/AlphaFuncF.ipp"
#include "Blend/Func/NonSeparableBlendFuncF.ipp"
#include "Color/ModelStructs.h"
#include "Maths/Geometry.h"
#include "Thread/ParallelFor.h"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void
InvokeBlendMTProcessScanline_NonSeparable_CM_CMYK_MEM_Generic_Subpixel( int32               iLINE
                                                                      , const tByte*        iSRC
                                                                      , tByte*              iBDP
                                                                      , uint8*              iXIDT
                                                                      , uint8               iBPC
                                                                      , uint8               iNCC
                                                                      , uint8               iHEA
                                                                      , uint8               iSPP
                                                                      , uint8               iBPP
                                                                      , uint8               iAID
                                                                      , tSize                iSRC_BPS
                                                                      , const FRect&        iSrcROI
                                                                      , const FRect&        iBdpROI
                                                                      , const glm::vec2&    iSubpixelComponent
                                                                      , eBlendingMode       iBlendingMode
                                                                      , eAlphaMode          iAlphaMode
                                                                      , ufloat              iOpacity )
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
        SampleSubpixelAlphaOpt< T >( src, iHEA, iAID, iBPP, iSRC_BPS, x, iLINE, iSrcROI.w, iSrcROI.h, sub, bus, vv0, &m11, &m10, &vv1, &res );
        const float alpha_bdp       = iHEA ? TYPE2FLOAT( bdp, iAID ) : 1.f;
        const float alpha_src       = res * iOpacity;
        const float alpha_comp      = AlphaNormalF( alpha_src, alpha_bdp );
        const float var             = alpha_comp == 0.f ? 0.f : alpha_src / alpha_comp;
        float alpha_result;
        ULIS2_ASSIGN_ALPHAF( iAlphaMode, alpha_result, alpha_src, alpha_bdp );

        float subpixel_C = SampleSubpixelChannelPremult< T >( src, iXIDT[0], iBPP, iSRC_BPS, x, iLINE, iSrcROI.w, iSrcROI.h, sub, bus, m11, m01, m10, m00, res );
        float subpixel_M = SampleSubpixelChannelPremult< T >( src, iXIDT[1], iBPP, iSRC_BPS, x, iLINE, iSrcROI.w, iSrcROI.h, sub, bus, m11, m01, m10, m00, res );
        float subpixel_Y = SampleSubpixelChannelPremult< T >( src, iXIDT[2], iBPP, iSRC_BPS, x, iLINE, iSrcROI.w, iSrcROI.h, sub, bus, m11, m01, m10, m00, res );
        float subpixel_K = SampleSubpixelChannelPremult< T >( src, iXIDT[2], iBPP, iSRC_BPS, x, iLINE, iSrcROI.w, iSrcROI.h, sub, bus, m11, m01, m10, m00, res );
        FCMYKF  src_cmykf = { subpixel_C, subpixel_M, subpixel_Y, subpixel_K };
        FCMYKF  bdp_cmykf = { TYPE2FLOAT( bdp, iXIDT[0] ), TYPE2FLOAT( bdp, iXIDT[1] ), TYPE2FLOAT( bdp, iXIDT[2] ), TYPE2FLOAT( bdp, iXIDT[3] ) };
        FRGBF   src_rgbf = CMYKToRGB( src_cmykf );
        FRGBF   bdp_rgbf = CMYKToRGB( bdp_cmykf );
        FRGBF result_rgbf;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) result_rgbf = NonSeparableOpF< _BM >( src_rgbf, bdp_rgbf );
        ULIS2_SWITCH_FOR_ALL_DO( iBlendingMode, ULIS2_FOR_ALL_NONSEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN
        FCMYKF  result_cmykf = RGBToCMYK( result_rgbf );

        // Compose
        for( uint8 j = 0; j < iNCC; ++j )
            FLOAT2TYPE( bdp, iXIDT[j], ComposeF( *( &(src_rgbf.R) + j ), *( &(bdp_rgbf.R) + j ), alpha_bdp, var, *( &(result_rgbf.R) + j ) ) );

        // Assign alpha
        if( iHEA ) FLOAT2TYPE( bdp, iAID, alpha_result );

        // Increment ptrs by one pixel
        src += iBPP;
        bdp += iBPP;
    }
}

template< typename T >
void
BlendMT_NonSeparable_CM_CMYK_MEM_Generic_Subpixel( FThreadPool*     iPool
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
    XBuildBlendParams( iBdpROI, iSource, iBackdrop, &bpc, &ncc, &hea, &spp, &bpp, &aid, &xidt, &roi_w, &roi_h, &src_bps, &bdp_bps, &src_jmp, &bdp_jmp );
    ParallelFor( *iPool
               , iBlocking
               , iPerf
               , iBdpROI.h
               , ULIS2_PF_CALL {
                    InvokeBlendMTProcessScanline_NonSeparable_CM_CMYK_MEM_Generic_Subpixel< T >( iLine
                                                                                               , iSource->DataPtr()   + ( ( iSrcROI.y + iLine ) * src_bps ) + ( iSrcROI.x * bpp )
                                                                                               , iBackdrop->DataPtr() + ( ( iBdpROI.y + iLine ) * bdp_bps ) + ( iBdpROI.x * bpp )
                                                                                               , xidt, bpc, ncc, hea, spp, bpp, aid, src_bps, iSrcROI, iBdpROI
                                                                                               , iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity );
               } );
    delete [] xidt;
}

template< typename T >
void
InvokeBlendMTProcessScanline_NonSeparable_CM_CMYK_MEM_Generic( int32            iLINE
                                                             , const tByte*     iSRC
                                                             , tByte*           iBDP
                                                             , uint8*           iXIDT
                                                             , uint8            iBPC
                                                             , uint8            iNCC
                                                             , uint8            iHEA
                                                             , uint8            iSPP
                                                             , uint8            iBPP
                                                             , uint8            iAID
                                                             , tSize            iSRC_BPS
                                                             , const FRect&     iSrcROI
                                                             , const FRect&     iBdpROI
                                                             , const glm::vec2& iSubpixelComponent
                                                             , eBlendingMode    iBlendingMode
                                                             , eAlphaMode       iAlphaMode
                                                             , ufloat           iOpacity )
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

        FCMYKF  src_cmykf = { TYPE2FLOAT( src, iXIDT[0] ), TYPE2FLOAT( src, iXIDT[1] ), TYPE2FLOAT( src, iXIDT[2] ), TYPE2FLOAT( src, iXIDT[3] ) };
        FCMYKF  bdp_cmykf = { TYPE2FLOAT( bdp, iXIDT[0] ), TYPE2FLOAT( bdp, iXIDT[1] ), TYPE2FLOAT( bdp, iXIDT[2] ), TYPE2FLOAT( bdp, iXIDT[3] ) };
        FRGBF   src_rgbf = CMYKToRGB( src_cmykf );
        FRGBF   bdp_rgbf = CMYKToRGB( bdp_cmykf );
        FRGBF   result_rgbf;
        #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) result_rgbf = NonSeparableOpF< _BM >( src_rgbf, bdp_rgbf );
        ULIS2_SWITCH_FOR_ALL_DO( iBlendingMode, ULIS2_FOR_ALL_NONSEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
        #undef TMP_ASSIGN
        FCMYKF  result_cmykf = RGBToCMYK( result_rgbf );

        // Compose
        for( uint8 j = 0; j < iNCC; ++j )
            FLOAT2TYPE( bdp, iXIDT[j], ComposeF( *( &(src_cmykf.C) + j ), *( &(bdp_cmykf.C) + j ), alpha_bdp, var, *( &(result_cmykf.C) + j ) ) );

        // Assign alpha
        if( iHEA ) FLOAT2TYPE( bdp, iAID, alpha_result );

        // Increment ptrs by one pixel
        src += iBPP;
        bdp += iBPP;
    }
}

template< typename T >
void
BlendMT_NonSeparable_CM_CMYK_MEM_Generic( FThreadPool*      iPool
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
    XBuildBlendParams( iBdpROI, iSource, iBackdrop, &bpc, &ncc, &hea, &spp, &bpp, &aid, &xidt, &roi_w, &roi_h, &src_bps, &bdp_bps, &src_jmp, &bdp_jmp );
    ParallelFor( *iPool
               , iBlocking
               , iPerf
               , iBdpROI.h
               , ULIS2_PF_CALL {
                    InvokeBlendMTProcessScanline_NonSeparable_CM_CMYK_MEM_Generic< T >( iLine
                                                                                      , iSource->DataPtr()   + ( ( iSrcROI.y + iLine ) * src_bps ) + ( iSrcROI.x * bpp )
                                                                                      , iBackdrop->DataPtr() + ( ( iBdpROI.y + iLine ) * bdp_bps ) + ( iBdpROI.x * bpp )
                                                                                      , xidt, bpc, ncc, hea, spp, bpp, aid, src_bps, iSrcROI, iBdpROI
                                                                                      , iSubpixelComponent, iBlendingMode, iAlphaMode, iOpacity );
               } );
    delete [] xidt;
}

ULIS2_NAMESPACE_END

