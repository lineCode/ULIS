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
#include "Blend/BlendFuncF.h"
#include "Conv/Conv.h"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void BlendMono_NonSeparable_CM_Lab_MEM( const FBlock*  iSource
                                      , FBlock*        iBackdrop
                                      , const FRect&   iSrcRoi
                                      , const FRect&   iDstRoi
                                      , eBlendingMode  iBlendingMode
                                      , eAlphaMode     iAlphaMode
                                      , float          iOpacity )
{
    // Gather Data
    const tSize     bpc = iSource->BytesPerSample();                                                                // Bytes Per Channel
    const tSize     ncc = iSource->NumColorChannels();                                                              // Num Color Channel
    const bool      hea = iSource->HasAlpha();                                                                      // Has Extra Alpha
    const tSize     spp = ncc + hea;                                                                                // Samples Per Pixel
    const tSize     bpp = bpc * spp;                                                                                // Bytes Per Pixel
    const tSize     w   = iSource->Width();                                                                         // Width
    const tSize     bps = bpp * w;                                                                                  // Bytes Per Scanline
    uint8           aid = iSource->AlphaIndex();                                                                    // alpha index
    tByte*          src = const_cast< tByte* >( iSource->DataPtr()   + ( iSrcRoi.y * bps ) + ( iSrcRoi.x * bpp ) ); // Source Pointer in src ROI
    tByte*          bdp = iBackdrop->DataPtr() + ( iDstRoi.y * bps ) + ( iDstRoi.x * bpp );                         // Backdrop Pointer in dst ROI
    const tSize     num = iSrcRoi.w * iSrcRoi.h;                                                                    // Number of operations
    const tFormat   fmt = iSource->Format();                                                                        // Format
    FPixelProxy     src_proxy( src, fmt );                                                                          // Proxy on source
    FPixelProxy     bdp_proxy( bdp, fmt );                                                                          // Proxy on backdrop
    FPixelValue     src_conv( ULIS2_FORMAT_RGBF );                                                                  // conv buffer for hsl source
    FPixelValue     bdp_conv( ULIS2_FORMAT_RGBF );                                                                  // conv buffer for hsl backdrop
    FPixelValue     res_conv( ULIS2_FORMAT_RGBF );                                                                  // conv buffer for hsl result
    FPixelValue     result( fmt );                                                                                  // result buffer in native model format

    for( tSize i = 0; i < num; ++i )
    {
        src_proxy.SetPtr( src );
        bdp_proxy.SetPtr( bdp );
        ConvToRGB< T, ufloat >( src_proxy, src_conv );
        ConvToRGB< T, ufloat >( bdp_proxy, bdp_conv );
        FRGBF src_rgbf = { src_conv.RF(), src_conv.GF(), src_conv.BF() };
        FRGBF bdp_rgbf = { bdp_conv.RF(), bdp_conv.GF(), bdp_conv.BF() };
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
        // Convert back rgb to native model
        res_conv.SetRF( result_rgbf.R );
        res_conv.SetGF( result_rgbf.G );
        res_conv.SetBF( result_rgbf.B );
        ConvT< ufloat, T >( res_conv, result );

        // Compose
        for( tSize j = 0; j < spp; ++j )
            FLOAT2TYPE( bdp, j, ComposeF( TYPE2FLOAT( src_proxy.Ptr(), j ), TYPE2FLOAT( bdp_proxy.Ptr(), j ), alpha_bdp, var, TYPE2FLOAT( result.Ptr(), j ) ) );

        // Assign alpha
        if( hea ) FLOAT2TYPE( bdp, aid, alpha_result );

        // Increment ptrs by one pixel
        src += bpp;
        bdp += bpp;
    }
}

ULIS2_NAMESPACE_END

