// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMono_Separable_MEM_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Maths/Geometry.h"
#include "Blend/Modes.h"
#include "Blend/BlendFuncF.h"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void BlendMono_Separable_MEM( const FBlock* iSource
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
    const tSize     num = iSrcRoi.w * iSrcRoi.h;                                            // Nulber of operations

    for( tSize i = 0; i < num; ++i )
    {
        const float alpha_bdp       = hea ? TYPE2FLOAT( bdp, aid ) : 1.f;
        const float alpha_src       = hea ? TYPE2FLOAT( src, aid ) * iOpacity : iOpacity;
        const float alpha_comp      = ( alpha_bdp + alpha_src ) - ( alpha_bdp * alpha_src );
        const float alpha_result    = 1.0f;
        const float var             = alpha_comp == 0 ? 0 : alpha_src / alpha_comp;
        for( tSize j = 0; j < spp; ++j ) {
            float srcvf = TYPE2FLOAT( src, j );
            float bdpvf = TYPE2FLOAT( bdp, j );
            switch( iBlendingMode ) {
            #define COMPOSE( i ) FLOAT2TYPE( bdp, j, ComposeF( srcvf, bdpvf, alpha_bdp, var, i( srcvf, bdpvf ) ) ); break;
                case BM_NORMAL          :   COMPOSE( BlendNormalF       ); break;
                case BM_TOP             :   FLOAT2TYPE( bdp, j, srcvf   ); break;
                case BM_BACK            :   FLOAT2TYPE( bdp, j, bdpvf   ); break;
                case BM_BEHIND          :   COMPOSE( BlendBehindF       ); break;
                case BM_DARKEN          :   COMPOSE( BlendDarkenF       ); break;
                case BM_MULTIPY         :   COMPOSE( BlendMultiplyF     ); break;
                case BM_COLORBURN       :   COMPOSE( BlendColorBurnF    ); break;
                case BM_LINEARBURN      :   COMPOSE( BlendLinearBurnF   ); break;
                case BM_LIGHTEN         :   COMPOSE( BlendLightenF      ); break;
                case BM_SCREEN          :   COMPOSE( BlendScreenF       ); break;
                case BM_COLORDODGE      :   COMPOSE( BlendColorDodgeF   ); break;
                case BM_LINEARDODGE     :   COMPOSE( BlendLinearDodgeF  ); break;
                case BM_OVERLAY         :   COMPOSE( BlendOverlayF      ); break;
                case BM_SOFTLIGHT       :   COMPOSE( BlendSoftLightF    ); break;
                case BM_HARDLIGHT       :   COMPOSE( BlendHardLightF    ); break;
                case BM_VIVIDLIGHT      :   COMPOSE( BlendVividLightF   ); break;
                case BM_LINEARLIGHT     :   COMPOSE( BlendLinearLightF  ); break;
                case BM_PINLIGHT        :   COMPOSE( BlendPinLightF     ); break;
                case BM_HARDMIX         :   COMPOSE( BlendHardMixF      ); break;
                case BM_PHOENIX         :   COMPOSE( BlendPhoenixF      ); break;
                case BM_REFLECT         :   COMPOSE( BlendReflectF      ); break;
                case BM_GLOW            :   COMPOSE( BlendGlowF         ); break;
                case BM_DIFFERENCE      :   COMPOSE( BlendDifferenceF   ); break;
                case BM_EXCLUSION       :   COMPOSE( BlendExclusionF    ); break;
                case BM_ADD             :   COMPOSE( BlendAddF          ); break;
                case BM_SUBSTRACT       :   COMPOSE( BlendSubstractF    ); break;
                case BM_DIVIDE          :   COMPOSE( BlendDivideF       ); break;
                case BM_AVERAGE         :   COMPOSE( BlendAverageF      ); break;
                default                 :   ULIS2_ASSERT( false, "Bad Blending Mode" );
            #undef COMPOSE
            }
        }
        // Assign alpha
        if( hea ) FLOAT2TYPE( bdp, aid, alpha_result );

        // Increment ptrs by one pixel
        src += bpp;
        bdp += bpp;
    }
}

ULIS2_NAMESPACE_END

