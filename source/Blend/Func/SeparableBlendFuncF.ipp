// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         SeparableBlendFuncF.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the ufloat Blending functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/Modes.h"
#include "Color/ModelStructs.h"
#include "Maths/Maths.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Compositing
ULIS2_FORCEINLINE ufloat ComposeF( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar, ufloat iCr ) {
    return ( 1.f - iVar ) * iCb + iVar * ( ( 1.f - iAb ) *iCs + iAb * iCr );
}

/////////////////////////////////////////////////////
// Standard Separable Blending Modes
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Normal
ULIS2_FORCEINLINE ufloat BlendNormalF( ufloat iCs, ufloat iCb ) {
    return iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Top
ULIS2_FORCEINLINE ufloat BlendTopF( ufloat iCs, ufloat iCb ) {
    return iCs;
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Back
ULIS2_FORCEINLINE ufloat BlendBackF( ufloat iCs, ufloat iCb ) {
    return iCb;
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Behind
ULIS2_FORCEINLINE ufloat BlendBehindF( ufloat iCs, ufloat iCb ) {
    return iCb;
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Darken
ULIS2_FORCEINLINE ufloat BlendDarkenF( ufloat iCs, ufloat iCb ) {
    return  FMaths::Min( iCb, iCs );
}
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Multiply
ULIS2_FORCEINLINE ufloat BlendMultiplyF( ufloat iCs, ufloat iCb ) {
    return  iCb * iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- ColorBurn
ULIS2_FORCEINLINE ufloat BlendColorBurnF( ufloat iCs, ufloat iCb ) {
    return  iCs == 0.f ? 0.f : 1.f - FMaths::Min( 1.f, ( 1.f - iCb ) / iCs );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Lighten
ULIS2_FORCEINLINE ufloat BlendLightenF( ufloat iCs, ufloat iCb ) {
    return  FMaths::Max( iCb, iCs );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Average
ULIS2_FORCEINLINE ufloat BlendAverageF( ufloat iCs, ufloat iCb ) {
    return  ( iCs + iCb ) / 2.f;
}
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Negation
ULIS2_FORCEINLINE ufloat BlendNegationF( ufloat iCs, ufloat iCb ) {
    return  1.f - fabsf( 1.f - iCs - iCb );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Screen
ULIS2_FORCEINLINE ufloat BlendScreenF( ufloat iCs, ufloat iCb ) {
    return  iCb + iCs - ( iCb * iCs );
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- ColorDodge
ULIS2_FORCEINLINE ufloat BlendColorDodgeF( ufloat iCs, ufloat iCb ) {
    return  iCs == 1.f ? 1.f : FMaths::Min( 1.f, iCb / ( 1.f - iCs ) );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Add
ULIS2_FORCEINLINE ufloat BlendAddF( ufloat iCs, ufloat iCb ) {
    return  FMaths::Min( 1.f, iCs + iCb );
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- LinearDodge
ULIS2_FORCEINLINE ufloat BlendLinearDodgeF( ufloat iCs, ufloat iCb ) {
    return  BlendAddF( iCs, iCb );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- SoftLight
ULIS2_FORCEINLINE ufloat _softlight_D( ufloat iX ) {
    return  iX <= 0.25f ? ( ( 16.f * iX - 12.f ) * iX + 4 ) * iX : sqrtf( iX );
}
ULIS2_FORCEINLINE ufloat BlendSoftLightF( ufloat iCs, ufloat iCb ) {
    //return  iCs <= 0.5f ? iCb - ( 1.f - 2.f * iCs ) * iCb * ( 1.f - iCb ) : iCb + ( 2.f * iCs - 1.f ) * ( _softlight_D( iCb ) - iCb );
    ufloat  q = iCb * iCb;
    ufloat  d = 2 * iCs;
    return  q + d * iCb - d * q;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- LinearBurn
ULIS2_FORCEINLINE ufloat BlendLinearBurnF( ufloat iCs, ufloat iCb ) {
    return  iCs + iCb < 1.f ? 0.f : iCs + iCb - 1.f;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- HardLight
ULIS2_FORCEINLINE ufloat BlendHardLightF( ufloat iCs, ufloat iCb ) {
    return  iCs <= 0.5f ? BlendMultiplyF( iCb, 2.f * iCs ) : BlendScreenF( iCb, 2 * iCs - 1.f );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Overlay
ULIS2_FORCEINLINE ufloat BlendOverlayF( ufloat iCs, ufloat iCb ) {
    return  BlendHardLightF( iCb, iCs );
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- VividLight
ULIS2_FORCEINLINE ufloat BlendVividLightF( ufloat iCs, ufloat iCb ) {
    return  iCs <= 0.5f ? BlendColorBurnF( iCb, 2 * iCs ) : BlendColorDodgeF( iCb, 2 * ( iCs - 0.5f ) );
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- LinearLight
ULIS2_FORCEINLINE ufloat BlendLinearLightF( ufloat iCs, ufloat iCb ) {
    return iCs <= 0.5f ? BlendLinearBurnF( iCb, 2 * iCb ) : BlendLinearDodgeF( iCb, 2 * ( iCs - 0.5f ) );
}
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- PinLight
ULIS2_FORCEINLINE ufloat BlendPinLightF( ufloat iCs, ufloat iCb ) {
    return  iCs <= 0.5f ? BlendDarkenF( iCb, 2 * iCb ) : BlendLightenF( iCb, 2 * ( iCs - 0.5f ) );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ HardMix
ULIS2_FORCEINLINE ufloat BlendHardMixF( ufloat iCs, ufloat iCb ) {
    return  BlendVividLightF( iCs, iCb ) < 0.5f ? 0.f : 1.f;
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Difference
ULIS2_FORCEINLINE ufloat BlendDifferenceF( ufloat iCs, ufloat iCb ) {
    return  abs( iCb - iCs );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Exclusion
ULIS2_FORCEINLINE ufloat BlendExclusionF( ufloat iCs, ufloat iCb ) {
    return  iCb + iCs - 2.f * iCb * iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Substract
ULIS2_FORCEINLINE ufloat BlendSubstractF( ufloat iCs, ufloat iCb ) {
    return  iCb > iCs ? iCb - iCs : 0;
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Divide
ULIS2_FORCEINLINE ufloat BlendDivideF( ufloat iCs, ufloat iCb ) {
    return  iCs == 0.f ? 1.f : FMaths::Min( 1.f, iCb / iCs );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Phoenix
ULIS2_FORCEINLINE ufloat BlendPhoenixF( ufloat iCs, ufloat iCb ) {
    return  1.f - FMaths::Max( iCs, iCb ) + FMaths::Min( iCs, iCb );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Reflect
ULIS2_FORCEINLINE ufloat BlendReflectF( ufloat iCs, ufloat iCb ) {
    return  iCb == 1.f ? 1.f : FMaths::Min( 1.f, iCs * iCs / ( 1.f - iCb ) );
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Glow
ULIS2_FORCEINLINE ufloat BlendGlowF( ufloat iCs, ufloat iCb ) {
    return  BlendReflectF( iCb, iCs );
}


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- TComposeF Template Selector
template< eBlendingMode _BM >
ULIS2_FORCEINLINE ufloat CompOpF( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) {
    ULIS2_ASSERT( false, "Alpha Specialization Not Implemented" );
    return  0.f;
}

template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_NORMAL      >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendNormalF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_BEHIND      >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendBehindF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_DARKEN      >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendDarkenF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_MULTIPY     >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendMultiplyF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_COLORBURN   >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendColorBurnF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_LINEARBURN  >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendLinearBurnF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_LIGHTEN     >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendLightenF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_SCREEN      >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendScreenF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_COLORDODGE  >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendColorDodgeF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_LINEARDODGE >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendLinearDodgeF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_OVERLAY     >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendOverlayF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_SOFTLIGHT   >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendSoftLightF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_HARDLIGHT   >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendHardLightF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_VIVIDLIGHT  >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendVividLightF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_LINEARLIGHT >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendLinearLightF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_PINLIGHT    >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendPinLightF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_HARDMIX     >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendHardMixF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_PHOENIX     >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendPhoenixF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_REFLECT     >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendReflectF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_GLOW        >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendGlowF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_DIFFERENCE  >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendDifferenceF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_EXCLUSION   >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendExclusionF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_ADD         >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendAddF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_SUBSTRACT   >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendSubstractF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_DIVIDE      >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendDivideF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_AVERAGE     >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  ComposeF( iCs, iCb, iAb, iVar, BlendAverageF( iCs, iCb ) ); }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_TOP         >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  iCs; }
template<> ULIS2_FORCEINLINE ufloat CompOpF< BM_BACK        >( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar ) { return  iCb; }

ULIS2_NAMESPACE_END

