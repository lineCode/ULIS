// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMono_NonSeparable_CM_Lab_MEM_Generic.ipp
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
#include "color/ModelStructs.h"
#include "Blend/Func/NonSeparableBlendFuncRGBF.ipp"
#include "Conv/Conv.h"
#include "lcms2.h"


ULIS2_NAMESPACE_BEGIN
template< typename T >
void BlendMono_NonSeparable_CM_Lab_MEM( const FBlock*       iSource
                                      , FBlock*             iBackdrop
                                      , const FRect&        iSrcRoi
                                      , const FRect&        iDstRoi
                                      , const eBlendingMode iBlendingMode
                                      , const eAlphaMode    iAlphaMode
                                      , const float         iOpacity )
{
    // Gather Data
    const tSize     bpc = iSource->BytesPerSample();                                                                // Bytes Per Channel
    const tSize     ncc = iSource->NumColorChannels();                                                              // Num Color Channel
    const bool      hea = iSource->HasAlpha();                                                                      // Has Extra Alpha
    const tSize     spp = ncc + hea;                                                                                // Samples Per Pixel
    const tSize     bpp = bpc * spp;                                                                                // Bytes Per Pixel
    const tSize     w   = iSource->Width();                                                                         // Width
    const tSize     bps = bpp * w;                                                                                  // Bytes Per Scanline
    const uint8     aid = iSource->AlphaIndex();                                                                    // alpha index
    tByte*          src = const_cast< tByte* >( iSource->DataPtr()   + ( iSrcRoi.y * bps ) + ( iSrcRoi.x * bpp ) ); // Source Pointer in src ROI
    tByte*          bdp = iBackdrop->DataPtr() + ( iDstRoi.y * bps ) + ( iDstRoi.x * bpp );                         // Backdrop Pointer in dst ROI
    const tSize     num = iSrcRoi.w * iSrcRoi.h;                                                                    // Number of operations
    const tFormat   fmt = iSource->Format();                                                                        // Format
    const uint8     cod = ULIS2_R_RS( fmt );                                                                        // Layout ( Reverse Swapped )
    uint8*          idt = new uint8[ bpp ];                                                                         // Index table
    BuildIndexTable( cod, spp, idt );

    for( tSize i = 0; i < num; ++i ) {
        FLabF src_lab = { TYPE2FLOAT( src, idt[0] ), TYPE2FLOAT( src, idt[1] ), TYPE2FLOAT( src, idt[2] ) };
        FLabF bdp_lab = { TYPE2FLOAT( bdp, idt[0] ), TYPE2FLOAT( bdp, idt[1] ), TYPE2FLOAT( bdp, idt[2] ) };
        FLChF src_lch = LabToLCh( src_lab );
        FLChF bdp_lch = LabToLCh( bdp_lab );
        FLChF result_lch;
        FLabF result_lab;

        const float alpha_bdp       = hea ? TYPE2FLOAT( bdp, aid ) : 1.f;
        const float alpha_src       = hea ? TYPE2FLOAT( src, aid ) * iOpacity : iOpacity;
        const float alpha_comp      = ( alpha_bdp + alpha_src ) - ( alpha_bdp * alpha_src );
        const float alpha_result    = 1.0f;
        const float var             = alpha_comp == 0 ? 0 : alpha_src / alpha_comp;

        switch( iBlendingMode ) {
            case BM_DARKERCOLOR     :   result_lch = BlendDarkerColorF(  src_lch, bdp_lch ); break;
            case BM_LIGHTERCOLOR    :   result_lch = BlendLighterColorF( src_lch, bdp_lch ); break;
            case BM_HUE             :   result_lch = BlendHueF(          src_lch, bdp_lch ); break;
            case BM_SATURATION      :   result_lch = BlendSaturationF(   src_lch, bdp_lch ); break;
            case BM_COLOR           :   result_lch = BlendColorF(        src_lch, bdp_lch ); break;
            case BM_LUMINOSITY      :   result_lch = BlendLuminosityF(   src_lch, bdp_lch ); break;
            default                 :   ULIS2_ASSERT( false, "Bad Blending Mode" );
        }

        result_lab = LChToLab( result_lch );

        // Compose
        for( tSize j = 0; j < ncc; ++j )
            FLOAT2TYPE( bdp, idt[j], ComposeF( *( (float*)(&src_lab) + j ), *( (float*)(&bdp_lab) + j ), alpha_bdp, var, *( (float*)(&result_lab) + j ) ) );

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

