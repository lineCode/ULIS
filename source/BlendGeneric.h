// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendGeneric.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include "Geometry.h"
#include "Modes.h"
#include "Perf.h"
#include "BlendFuncF.h"
#include "Conv.h"

ULIS2_NAMESPACE_BEGIN
#define TYPE_TO_FLOAT( i ) ConvType< T, float >( *( (T*)( i ) ) )
template< typename T >
void BlendMono_MEM_Standard( const FBlock* iSource
                           , FBlock*       iBackdrop
                           , const FRect&  iSrcRoi
                           , const FRect&  iDstRoi
                           , eBlendingMode iBlendingMode
                           , eAlphaMode    iAlphaMode
                           , float         iOpacity )
{

    // Gather Data
    const tSize     bpc = iSource->BytesPerSample();                                        // Bytes Per Channel
    const tSize     ncc = iSource->NumColorChannels();                                      // Num Color Channel
    const bool      hea = iSource->HasAlpha();                                              // Has Extra Alpha
    const tSize     spp = ncc + hea;                                                        // Samples Per Pixel
    const tSize     bpp = bpc * spp;                                                        // Bytes Per Pixel
    const tSize     w   = iSource->Width();                                                 // Width
    const tSize     bps = bpp * w;                                                          // Bytes Per Scanline
    uint8           aid = iSource->AlphaIndex();                                            // alpha index
    const tByte*    src = iSource->DataPtr()   + ( iSrcRoi.y * bps ) + ( iSrcRoi.x * bpp ); // Source Pointer in src ROI
    tByte*          bdp = iBackdrop->DataPtr() + ( iDstRoi.y * bps ) + ( iDstRoi.x * bpp ); // Backdrop Pointer in dst ROI
    // Process
    const tSize count = iSrcRoi.w * iSrcRoi.h;
    for( tSize i = 0; i < count; ++i )
    {
        // Precomp
        const float alpha_bdp       = hea ? TYPE_TO_FLOAT( bdp + aid ) : 1.f;
        const float alpha_src       = hea ? TYPE_TO_FLOAT( src + aid ) * iOpacity : iOpacity;
        const float alpha_comp      = ( alpha_bdp + alpha_src ) - ( alpha_bdp * alpha_src );
        const float alpha_result    = 1.0f;
        const float var             = alpha_comp == 0 ? 0 : alpha_src / alpha_comp;
        // Compute Separable Channels in float
        for( tSize j = 0; j < spp; ++j ) {
            float srcvf = TYPE_TO_FLOAT( src + j );
            float bdpvf = TYPE_TO_FLOAT( bdp + j );
            switch( iBlendingMode ) {
                case BM_NORMAL          :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendNormalF(        srcvf, bdpvf ) ) ); break;
                case BM_TOP             :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendTopF(           srcvf, bdpvf ) ) ); break;
                case BM_BACK            :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendBackF(          srcvf, bdpvf ) ) ); break;
                case BM_BEHIND          :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendBehindF(        srcvf, bdpvf ) ) ); break;
                case BM_DARKEN          :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendDarkenF(        srcvf, bdpvf ) ) ); break;
                case BM_MULTIPY         :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendMultiplyF(      srcvf, bdpvf ) ) ); break;
                case BM_COLORBURN       :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendColorBurnF(     srcvf, bdpvf ) ) ); break;
                case BM_LINEARBURN      :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendLinearBurnF(    srcvf, bdpvf ) ) ); break;
                case BM_LIGHTEN         :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendLightenF(       srcvf, bdpvf ) ) ); break;
                case BM_SCREEN          :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendScreenF(        srcvf, bdpvf ) ) ); break;
                case BM_COLORDODGE      :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendColorDodgeF(    srcvf, bdpvf ) ) ); break;
                case BM_LINEARDODGE     :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendLinearDodgeF(   srcvf, bdpvf ) ) ); break;
                case BM_OVERLAY         :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendOverlayF(       srcvf, bdpvf ) ) ); break;
                case BM_SOFTLIGHT       :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendSoftLightF(     srcvf, bdpvf ) ) ); break;
                case BM_HARDLIGHT       :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendHardLightF(     srcvf, bdpvf ) ) ); break;
                case BM_VIVIDLIGHT      :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendVividLightF(    srcvf, bdpvf ) ) ); break;
                case BM_LINEARLIGHT     :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendLinearLightF(   srcvf, bdpvf ) ) ); break;
                case BM_PINLIGHT        :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendPinLightF(      srcvf, bdpvf ) ) ); break;
                case BM_HARDMIX         :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendHardMixF(       srcvf, bdpvf ) ) ); break;
                case BM_PHOENIX         :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendPhoenixF(       srcvf, bdpvf ) ) ); break;
                case BM_REFLECT         :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendReflectF(       srcvf, bdpvf ) ) ); break;
                case BM_GLOW            :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendGlowF(          srcvf, bdpvf ) ) ); break;
                case BM_DIFFERENCE      :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendDifferenceF(    srcvf, bdpvf ) ) ); break;
                case BM_EXCLUSION       :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendExclusionF(     srcvf, bdpvf ) ) ); break;
                case BM_ADD             :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendAddF(           srcvf, bdpvf ) ) ); break;
                case BM_SUBSTRACT       :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendSubstractF(     srcvf, bdpvf ) ) ); break;
                case BM_DIVIDE          :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendDivideF(        srcvf, bdpvf ) ) ); break;
                case BM_AVERAGE         :   *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( srcvf, bdpvf, alpha_bdp, var, BlendAverageF(       srcvf, bdpvf ) ) ); break;
                default                 :   ULIS2_ASSERT( false, "Bad Blending Mode" );
            }
        }
        // Assign alpha
        if( hea )
            *( (T*)( bdp + aid ) ) = ConvType< float, T >( alpha_result );

        // Increment ptrs by one pixel
        src += bpp;
        bdp += bpp;
    }
}

template< typename T >
void BlendMono_MEM_HSL( const FBlock*  iSource
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

    const tFormat   fmt = iSource->Format();
    FPixelValue srchslf( ULIS2_FORMAT_HSLF );
    FPixelValue bdphslf( ULIS2_FORMAT_HSLF );
    FPixelValue reshslf( ULIS2_FORMAT_HSLF );
    FPixelValue resnat( fmt );
    FPixelProxy srcproxy( src, fmt );
    FPixelProxy bdpproxy( bdp, fmt );
    // Process
    const tSize count = iSrcRoi.w * iSrcRoi.h;
    for( tSize i = 0; i < count; ++i )
    {
        // Convert forward any model forward to hsl
        srcproxy.SetPtr( src );
        bdpproxy.SetPtr( bdp );
        Conv( srcproxy, srchslf );
        Conv( bdpproxy, bdphslf );

        // Precomp
        const float alpha_bdp       = hea ? TYPE_TO_FLOAT( bdp + aid ) : 1.f;
        const float alpha_src       = hea ? TYPE_TO_FLOAT( src + aid ) * iOpacity : iOpacity;
        const float alpha_comp      = ( alpha_bdp + alpha_src ) - ( alpha_bdp * alpha_src );
        const float alpha_result    = 1.0f;
        const float var             = alpha_comp == 0 ? 0 : alpha_src / alpha_comp;

        switch( iBlendingMode ) {
            case BM_DARKERCOLOR     :   BlendDarkerColorHSLF(   &srchslf, &bdphslf, &reshslf ); break;
            case BM_LIGHTERCOLOR    :   BlendLighterColorHSLF(  &srchslf, &bdphslf, &reshslf ); break;
            case BM_HUE             :   BlendHueHSLF(           &srchslf, &bdphslf, &reshslf ); break;
            case BM_SATURATION      :   BlendSaturationHSLF(    &srchslf, &bdphslf, &reshslf ); break;
            case BM_COLOR           :   BlendColorHSLF(         &srchslf, &bdphslf, &reshslf ); break;
            case BM_LUMINOSITY      :   BlendLuminosityHSLF(    &srchslf, &bdphslf, &reshslf ); break;
            default                 :   ULIS2_ASSERT( false, "Bad Blending Mode" );
        }
        // Convert back hsl to native model
        Conv( reshslf, resnat );

        // Compose
        for( tSize j = 0; j < spp; ++j )
            *( (T*)( bdp + j ) ) = ConvType< float, T >( ComposeF( TYPE_TO_FLOAT( srcproxy.Ptr() + j ), TYPE_TO_FLOAT( bdpproxy.Ptr() + j ), alpha_bdp, var, TYPE_TO_FLOAT( resnat.Ptr() + j ) ) );

        // Assign alpha
        if( hea )
            *( (T*)( bdp + aid ) ) = ConvType< float, T >( alpha_result );

        // Increment ptrs by one pixel
        src += bpp;
        bdp += bpp;
    }
}

template< typename T >
void BlendMono_MEM_Misc( const FBlock*   iSource
                       , FBlock*         iBackdrop
                       , const FRect&    iSrcRoi
                       , const FRect&    iDstRoi
                       , eBlendingMode   iBlendingMode
                       , eAlphaMode      iAlphaMode
                       , float           iOpacity )
{
}

#undef TYPE_TO_FLOAT
ULIS2_NAMESPACE_END

