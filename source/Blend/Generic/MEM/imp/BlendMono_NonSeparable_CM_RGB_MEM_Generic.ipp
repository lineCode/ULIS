// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMono_NonSeparable_CM_RGB_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Maths/Geometry.h"
#include "Blend/Modes.h"
#include "Base/Perf.h"
#include "Color/ModelStructs.h"
#include "Blend/Func/NonSeparableBlendFuncRGBF.ipp"
#include "Blend/BlendHelpers.h"
#include "Conv/Conv.h"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void BlendMono_NonSeparable_CM_RGB_MEM( const FBlock*       iSource
                                      , FBlock*             iBackdrop
                                      , const FRect&        iSrcRoi
                                      , const FRect&        iDstRoi
                                      , const eBlendingMode iBlendingMode
                                      , const eAlphaMode    iAlphaMode
                                      , const float         iOpacity )
{
    uint8 bpc, ncc, hea, spp, bpp, aid;
    tSize bps, num;
    uint8* idt;
    BuildBlendParams( &bpc, &ncc, &hea, &spp, &bpp, &bps, &num, &aid, &idt, iSource->Format(), iSrcRoi );
    const tByte* src = iSource->DataPtr()   + ( iSrcRoi.y * bps ) + ( iSrcRoi.x * bpp );
    tByte*       bdp = iBackdrop->DataPtr() + ( iDstRoi.y * bps ) + ( iDstRoi.x * bpp );

    for( tSize i = 0; i < num; ++i ) {
        FRGBF src_rgbf = { TYPE2FLOAT( src, idt[0] ), TYPE2FLOAT( src, idt[1] ), TYPE2FLOAT( src, idt[2] ) };
        FRGBF bdp_rgbf = { TYPE2FLOAT( bdp, idt[0] ), TYPE2FLOAT( bdp, idt[1] ), TYPE2FLOAT( bdp, idt[2] ) };
        FRGBF result_rgbf;

        const float alpha_bdp       = hea ? TYPE2FLOAT( bdp, aid ) : 1.f;
        const float alpha_src       = hea ? TYPE2FLOAT( src, aid ) * iOpacity : iOpacity;
        const float alpha_comp      = ( alpha_bdp + alpha_src ) - ( alpha_bdp * alpha_src );
        const float alpha_result    = 1.0f;
        const float var             = alpha_comp == 0 ? 0 : alpha_src / alpha_comp;

        switch( iBlendingMode ) {
            case BM_DARKERCOLOR     :   result_rgbf = BlendDarkerColorF(  src_rgbf, bdp_rgbf ); break;
            case BM_LIGHTERCOLOR    :   result_rgbf = BlendLighterColorF( src_rgbf, bdp_rgbf ); break;
            case BM_HUE             :   result_rgbf = BlendHueF(          src_rgbf, bdp_rgbf ); break;
            case BM_SATURATION      :   result_rgbf = BlendSaturationF(   src_rgbf, bdp_rgbf ); break;
            case BM_COLOR           :   result_rgbf = BlendColorF(        src_rgbf, bdp_rgbf ); break;
            case BM_LUMINOSITY      :   result_rgbf = BlendLuminosityF(   src_rgbf, bdp_rgbf ); break;
            default                 :   ULIS2_ASSERT( false, "Bad Blending Mode" );
        }
        // Compose

        for( tSize j = 0; j < ncc; ++j )
            FLOAT2TYPE( bdp, idt[j], ComposeF( *( (float*)(&src_rgbf) + j ), *( (float*)(&bdp_rgbf) + j ), alpha_bdp, var, *( (float*)(&result_rgbf) + j ) ) );

        // Assign alpha
        if( hea ) FLOAT2TYPE( bdp, aid, alpha_result );

        // Increment ptrs by one pixel
        src += bpp;
        bdp += bpp;
    }

    // delete temp
    delete [] idt;
}

ULIS2_NAMESPACE_END

