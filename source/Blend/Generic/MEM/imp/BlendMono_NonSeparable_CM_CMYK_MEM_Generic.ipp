// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMono_NonSeparable_CM_CMYK_MEM_Generic.ipp
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

ULIS2_NAMESPACE_BEGIN
template< typename T >
void BlendMono_NonSeparable_CM_CMYK_MEM( const FBlock*      iSource
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
        FCMYKF  src_cmykf = { TYPE2FLOAT( src, idt[0] ), TYPE2FLOAT( src, idt[1] ), TYPE2FLOAT( src, idt[2] ), TYPE2FLOAT( src, idt[3] ) };
        FCMYKF  bdp_cmykf = { TYPE2FLOAT( bdp, idt[0] ), TYPE2FLOAT( bdp, idt[1] ), TYPE2FLOAT( bdp, idt[2] ), TYPE2FLOAT( bdp, idt[3] ) };
        FRGBF   src_rgbf = CMYKToRGB( src_cmykf );
        FRGBF   bdp_rgbf = CMYKToRGB( bdp_cmykf );
        FRGBF   result_rgbf;
        FCMYKF  result_cmykf;

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

        result_cmykf = RGBToCMYK( result_rgbf );

        // Compose
        for( tSize j = 0; j < ncc; ++j )
            FLOAT2TYPE( bdp, idt[j], ComposeF( *( (float*)(&src_cmykf) + j ), *( (float*)(&bdp_cmykf) + j ), alpha_bdp, var, *( (float*)(&result_cmykf) + j ) ) );

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

