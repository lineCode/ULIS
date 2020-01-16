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

ULIS2_NAMESPACE_BEGIN

template< typename T >
void BlendMono_MEM_Separable( const FBlock* iSource
                            , FBlock*       iBackdrop
                            , const FRect&  iSrcRoi
                            , const FRect&  iDstRoi
                            , eBlendingMode iBlendingMode
                            , eAlphaMode    iAlphaMode
                            , float         iOpacity )
{

    // Gather Data
    const tFormat   fmt = iSource->Format();                                                // Format
    const tSize     bpc = iSource->BytesPerSample();                                        // Bytes Per Channel
    const tSize     ncc = iSource->NumColorChannels();                                      // Num Color Channel
    const bool      hea = iSource->HasAlpha();                                              // Has Extra Alpha
    const tSize     spp = ncc + hea;                                                        // Samples Per Pixel
    const tSize     bpp = bpc * spp;                                                        // Bytes Per Pixel
    const tSize     w   = iSource->Width();                                                 // Width
    const tSize     bps = bpp * w;                                                          // Bytes Per Scanline
    uint8           msp = spp - 1;                                                          // Max Sample
    uint8           cod = ULIS2_R_RS( fmt );                                                // Reverse-Swap code
    const tByte*    src = iSource->DataPtr()   + ( iSrcRoi.y * bps ) + ( iSrcRoi.x * bpp ); // Source Pointer in src ROI
    tByte*          bdp = iBackdrop->DataPtr() + ( iDstRoi.y * bps ) + ( iDstRoi.x * bpp ); // Backdrop Pointer in dst ROI

    // Build Redirection Tables
    uint8* index_table  = new uint8[ spp ];
    uint8 alpha_index   = 0;
    switch( cod ) {
        case 1:  for( tSize i = 0; i < spp; ++i ) index_table[i] = ( msp - i );                                     alpha_index = 0;    break;
        case 2:  for( tSize i = 0; i < spp; ++i ) index_table[i] = ( i + 1 ) > msp ? 0 : i + 1;                     alpha_index = 0;    break;
        case 3:  for( tSize i = 0; i < spp; ++i ) index_table[i] = ( msp - i ) - 1 < 0 ? msp : ( msp - i ) - 1;     alpha_index = msp;  break;
        default: for( tSize i = 0; i < spp; ++i ) index_table[i] = i;                                               alpha_index = msp;  break;
    }

    // Data Holders to abstract away the Alpha.
    float*  srcd = new  float[ ncc + 1 ];
    float*  bdpd = new  float[ ncc + 1 ];
    for( tSize i = 0; i < ncc + 1; ++i )
    { srcd[i] = 1.f;    bdpd[i] = 1.f; }

    // Process
    const tSize count = iSrcRoi.w * iSrcRoi.h;
    for( tSize i = 0; i < count; ++i )
    {
        for( tSize j = 0; j < ( spp ); ++j )
        {
            uint8 r = index_table[j];
            srcd[ r ] = ConvType< T, float >( *( (T*)( src + r ) ) );
            bdpd[ r ] = ConvType< T, float >( *( (T*)( bdp + r ) ) );
        }

        // Precomp
        const float alpha_bdp       = bdpd[ alpha_index ];
        const float alpha_src       = srcd[ alpha_index ] * iOpacity;
        const float alpha_comp      = ( alpha_bdp + alpha_src ) - ( alpha_bdp * alpha_src );
        const float alpha_result    = 1.0f;
        const float var             = alpha_comp == 0 ? 0 : alpha_src / alpha_comp;
        // Compute Separable Channels in float
        for( tSize j = 0; j < ncc; ++j )
        {
            uint8 r = index_table[j];
            switch( iBlendingMode ) {
                case BM_NORMAL          :   bdpd[ index_table[ j ] ] = BlendNormalF( srcd[r], bdpd[r] ); break;
                case BM_TOP             :   bdpd[ index_table[ j ] ] = BlendTopF( srcd[r], bdpd[r] ); break;
                case BM_BACK            :   bdpd[ index_table[ j ] ] = BlendBackF( srcd[r], bdpd[r] ); break;
                case BM_BEHIND          :   bdpd[ index_table[ j ] ] = BlendBehindF( srcd[r], bdpd[r] ); break;
                case BM_DARKEN          :   bdpd[ index_table[ j ] ] = BlendDarkenF( srcd[r], bdpd[r] ); break;
                case BM_MULTIPY         :   bdpd[ index_table[ j ] ] = BlendMultiplyF( srcd[r], bdpd[r] ); break;
                case BM_COLORBURN       :   bdpd[ index_table[ j ] ] = BlendColorBurnF( srcd[r], bdpd[r] ); break;
                case BM_LINEARBURN      :   bdpd[ index_table[ j ] ] = BlendLinearBurnF( srcd[r], bdpd[r] ); break;
                case BM_LIGHTEN         :   bdpd[ index_table[ j ] ] = BlendLightenF( srcd[r], bdpd[r] ); break;
                case BM_SCREEN          :   bdpd[ index_table[ j ] ] = BlendScreenF( srcd[r], bdpd[r] ); break;
                case BM_COLORDODGE      :   bdpd[ index_table[ j ] ] = BlendColorDodgeF( srcd[r], bdpd[r] ); break;
                case BM_LINEARDODGE     :   bdpd[ index_table[ j ] ] = BlendLinearDodgeF( srcd[r], bdpd[r] ); break;
                case BM_OVERLAY         :   bdpd[ index_table[ j ] ] = BlendOverlayF( srcd[r], bdpd[r] ); break;
                case BM_SOFTLIGHT       :   bdpd[ index_table[ j ] ] = BlendSoftLightF( srcd[r], bdpd[r] ); break;
                case BM_HARDLIGHT       :   bdpd[ index_table[ j ] ] = BlendHardLightF( srcd[r], bdpd[r] ); break;
                case BM_VIVIDLIGHT      :   bdpd[ index_table[ j ] ] = BlendVividLightF( srcd[r], bdpd[r] ); break;
                case BM_LINEARLIGHT     :   bdpd[ index_table[ j ] ] = BlendLinearLightF( srcd[r], bdpd[r] ); break;
                case BM_PINLIGHT        :   bdpd[ index_table[ j ] ] = BlendPinLightF( srcd[r], bdpd[r] ); break;
                case BM_HARDMIX         :   bdpd[ index_table[ j ] ] = BlendHardMixF( srcd[r], bdpd[r] ); break;
                case BM_PHOENIX         :   bdpd[ index_table[ j ] ] = BlendPhoenixF( srcd[r], bdpd[r] ); break;
                case BM_REFLECT         :   bdpd[ index_table[ j ] ] = BlendReflectF( srcd[r], bdpd[r] ); break;
                case BM_GLOW            :   bdpd[ index_table[ j ] ] = BlendGlowF( srcd[r], bdpd[r] ); break;
                case BM_DIFFERENCE      :   bdpd[ index_table[ j ] ] = BlendDifferenceF( srcd[r], bdpd[r] ); break;
                case BM_EXCLUSION       :   bdpd[ index_table[ j ] ] = BlendExclusionF( srcd[r], bdpd[r] ); break;
                case BM_ADD             :   bdpd[ index_table[ j ] ] = BlendAddF( srcd[r], bdpd[r] ); break;
                case BM_SUBSTRACT       :   bdpd[ index_table[ j ] ] = BlendSubstractF( srcd[r], bdpd[r] ); break;
                case BM_DIVIDE          :   bdpd[ index_table[ j ] ] = BlendDivideF( srcd[r], bdpd[r] ); break;
                case BM_AVERAGE         :   bdpd[ index_table[ j ] ] = BlendAverageF( srcd[r], bdpd[r] ); break;
            }
        }

        bdpd[ alpha_index ] = alpha_result;

        // Emplace result
        for( tSize j = 0; j < spp; ++j )
            *( (T*)( bdp + index_table[ j ] ) ) = ConvType< float, T >( bdpd[ index_table[ j ] ] );

        // Increment ptrs by one pixel
        src += bpp;
        bdp += bpp;
    }

    // Delete temporary data
    delete [] index_table;
    delete [] srcd;
    delete [] bdpd;
}

template< typename T >
void BlendMono_MEM_NonSeparable( const FBlock*  iSource
                               , FBlock*        iBackdrop
                               , const FRect&   iSrcRoi
                               , const FRect&   iDstRoi
                               , eBlendingMode  iBlendingMode
                               , eAlphaMode     iAlphaMode
                               , float          iOpacity )
{
}

template< typename T >
void BlendMono_MEM_Unusual( const FBlock*   iSource
                          , FBlock*         iBackdrop
                          , const FRect&    iSrcRoi
                          , const FRect&    iDstRoi
                          , eBlendingMode   iBlendingMode
                          , eAlphaMode      iAlphaMode
                          , float           iOpacity )
{
}

ULIS2_NAMESPACE_END

