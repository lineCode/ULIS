// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMono_Separable_SSE4_2_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/Blend.h"
#include "Blend/BlendHelpers.h"
#include "Blend/Modes.h"
#include "Blend/Func/SeparableBlendFuncSSEF.ipp"
#include "Blend/Func/AlphaFuncSSEF.ipp"
#include "Maths/Geometry.h"

ULIS2_NAMESPACE_BEGIN
ULIS2_BLENDSPEC_TEMPLATE_SIG void BlendMono_Separable_C1A_SSE4_2_Subpixel( ULIS2_BLENDSPEC_PARAMS_SIG ) {
}

ULIS2_BLENDSPEC_TEMPLATE_SIG void BlendMono_Separable_C1A_SSE4_2( ULIS2_BLENDSPEC_PARAMS_SIG ) {
    uint8* xidt;
    uint8 bpc, ncc, hea, spp, bpp, aid;
    tSize roi_w, roi_h, src_bps, bdp_bps, src_jmp, bdp_jmp;
    XBuildBlendParams( iBdpROI, iSource, iBackdrop, &bpc, &ncc, &hea, &spp, &bpp, &aid, &xidt, &roi_w, &roi_h, &src_bps, &bdp_bps, &src_jmp, &bdp_jmp );
    const tByte*        src = iSource->DataPtr()   + ( iSrcROI.y * src_bps ) + ( iSrcROI.x * bpp );
    tByte*              bdp = iBackdrop->DataPtr() + ( iBdpROI.y * bdp_bps ) + ( iBdpROI.x * bpp );
    const tSize stride = 16;
    const tSize count  = roi_w * bpp;
    // fci: First Channel Index, this allows to load 4 floats in case of CMYK
    // sid: second alpha index, this allows to load 2 grey pixels at once
    // alb: alpha base, for samples that are 5 channels, this allows to shift load alpha properly
    // lui: look up indexes, this allows to spread alpha properly.
    uint8 fci = ncc >= 4 ? xidt[0] : 0;
    uint8 sid = aid + spp;
    uint8 alb = ncc >= 4 ? fci ? 0 : 4 : 0;
    Vec4i lui;
    if( spp * 4 < 16 )  lui = Vec4i( aid, aid, sid, sid );
    else                lui = Vec4i( aid - alb );

    for( tSize y = 0; y < roi_w; ++y ) {
        for( tSize x = 0; x < roi_h; ++x ) {
            const Vec4f alpha_bdp = hea ? lookup4( lui, LoadSSEF< T >( bdp, alb ) ) : 1.f;
            const Vec4f alpha_src = hea ? lookup4( lui, LoadSSEF< T >( src, alb ) ) * iOpacity : iOpacity;
            const Vec4f alpha_comp  = AlphaNormalSSEF( alpha_src, alpha_bdp );
            const Vec4f var         = select( alpha_comp == 0, 0.f, alpha_src / alpha_comp );
            Vec4f alpha_result;
            ULIS2_ASSIGN_ALPHASSEF( iAlphaMode, alpha_result, alpha_src, alpha_bdp );

            Vec4f srcvf = LoadSSEF< T >( src, fci );
            Vec4f bdpvf = LoadSSEF< T >( bdp, fci );
            Vec4f resvf;
            #define TMP_ASSIGN( _BM, _E1, _E2, _E3 ) resvf = SeparableCompOpSSEF< _BM >( srcvf, bdpvf, alpha_bdp, var );
            ULIS2_SWITCH_FOR_ALL_DO( iBlendingMode, ULIS2_FOR_ALL_SEPARABLE_BM_DO, TMP_ASSIGN, 0, 0, 0 )
            #undef TMP_ASSIGN

            // Increment ptrs by one pixel
            src += bpp;
            bdp += bpp;
        }
        // Increment ptrs jump one line
        src += src_jmp;
        bdp += bdp_jmp;
    }

    delete [] xidt;
}

ULIS2_NAMESPACE_END

