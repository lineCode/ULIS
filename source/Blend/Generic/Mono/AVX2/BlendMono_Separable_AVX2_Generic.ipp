// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendMono_Separable_AVX2_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/BlendHelpers.h"
#include "Blend/Modes.h"
#include "Blend/Func/SeparableBlendFuncF.ipp"
#include "Blend/Func/AlphaFuncF.ipp"
#include "Maths/Geometry.h"

ULIS2_NAMESPACE_BEGIN
template< typename T >
void BlendMono_Separable_AVX2( const FBlock*         iSource
                             , FBlock*               iBackdrop
                             , const FRect&          iSrcRoi
                             , const FRect&          iDstRoi
                             , const eBlendingMode   iBlendingMode
                             , const eAlphaMode      iAlphaMode
                             , const float           iOpacity )
{
    uint8 bpc, ncc, hea, spp, bpp, aid;
    tSize bps, num;
    uint8* idt;
    BuildBlendParams( &bpc, &ncc, &hea, &spp, &bpp, &bps, &num, &aid, &idt, iSource->Format(), iSrcRoi );
    const tByte* src = iSource->DataPtr()   + ( iSrcRoi.y * bps ) + ( iSrcRoi.x * bpp );
    tByte*       bdp = iBackdrop->DataPtr() + ( iDstRoi.y * bps ) + ( iDstRoi.x * bpp );

    for( tSize i = 0; i < num; ++i ) {
        const float alpha_bdp       = hea ? TYPE2FLOAT( bdp, aid ) : 1.f;
        const float alpha_src       = hea ? TYPE2FLOAT( src, aid ) * iOpacity : iOpacity;
        const float alpha_comp      = AlphaNormalF( alpha_src, alpha_bdp );
        const float var             = alpha_comp == 0 ? 0 : alpha_src / alpha_comp;
        float alpha_result;
        switch( iAlphaMode ) {
            case AM_NORMAL  : alpha_result = AlphaNormalF(  alpha_src, alpha_bdp );
            case AM_ERASE   : alpha_result = AlphaEraseF(   alpha_src, alpha_bdp );
            case AM_TOP     : alpha_result = AlphaTopF(     alpha_src, alpha_bdp );
            case AM_BACK    : alpha_result = AlphaBackF(    alpha_src, alpha_bdp );
            case AM_SUB     : alpha_result = AlphaSubF(     alpha_src, alpha_bdp );
            case AM_ADD     : alpha_result = AlphaAddF(     alpha_src, alpha_bdp );
            case AM_MUL     : alpha_result = AlphaMulF(     alpha_src, alpha_bdp );
            case AM_MIN     : alpha_result = AlphaMinF(     alpha_src, alpha_bdp );
            case AM_MAX     : alpha_result = AlphaMaxF(     alpha_src, alpha_bdp );
            case AM_INVMAX  : alpha_result = AlphaInvMaxF(  alpha_src, alpha_bdp );
        }

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

    delete [] idt;
}

ULIS2_NAMESPACE_END

