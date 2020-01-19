// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         SeparableBlendFuncF.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the ufloat Blending functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/Modes.h"
#include "Maths/Maths.h"
#include "Color/ModelStructs.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Compositing
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL ComposeF( ufloat iCs, ufloat iCb, ufloat iAb, ufloat iVar, ufloat iCr ) {
    return ( 1.f - iVar ) * iCb + iVar * ( ( 1.f - iAb ) *iCs + iAb * iCr );
}

/////////////////////////////////////////////////////
// Standard Separable Blending Modes
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Normal
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendNormalF( ufloat iCs, ufloat iCb ) {
    return iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Top
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendTopF( ufloat iCs, ufloat iCb ) {
    return iCs;
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Back
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendBackF( ufloat iCs, ufloat iCb ) {
    return iCb;
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Behind
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendBehindF( ufloat iCs, ufloat iCb ) {
    return iCb;
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Darken
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendDarkenF( ufloat iCs, ufloat iCb ) {
    return  FMaths::Min( iCb, iCs );
}
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Multiply
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendMultiplyF( ufloat iCs, ufloat iCb ) {
    return  iCb * iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- ColorBurn
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendColorBurnF( ufloat iCs, ufloat iCb ) {
    return  iCs == 0.f ? 0.f : 1.f - FMaths::Min( 1.f, ( 1.f - iCb ) / iCs );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Lighten
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendLightenF( ufloat iCs, ufloat iCb ) {
    return  FMaths::Max( iCb, iCs );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Average
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendAverageF( ufloat iCs, ufloat iCb ) {
    return  ( iCs + iCb ) / 2.f;
}
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Negation
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendNegationF( ufloat iCs, ufloat iCb ) {
    return  1.f - fabsf( 1.f - iCs - iCb );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Screen
ULIS2_FORCEINLINE ufloat BlendScreenF( ufloat iCs, ufloat iCb ) {
    return  iCb + iCs - ( iCb * iCs );
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- ColorDodge
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendColorDodgeF( ufloat iCs, ufloat iCb ) {
    return  iCs == 1.f ? 1.f : FMaths::Min( 1.f, iCb / ( 1.f - iCs ) );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Add
ULIS2_FORCEINLINE ufloat BlendAddF( ufloat iCs, ufloat iCb ) {
    return  FMaths::Min( 1.f, iCs + iCb );
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- LinearDodge
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendLinearDodgeF( ufloat iCs, ufloat iCb ) {
    return  BlendAddF( iCs, iCb );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- SoftLight
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL _softlight_D( ufloat iX ) {
    return  iX <= 0.25f ? ( ( 16.f * iX - 12.f ) * iX + 4 ) * iX : sqrtf( iX );
}
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendSoftLightF( ufloat iCs, ufloat iCb ) {
    //return  iCs <= 0.5f ? iCb - ( 1.f - 2.f * iCs ) * iCb * ( 1.f - iCb ) : iCb + ( 2.f * iCs - 1.f ) * ( _softlight_D( iCb ) - iCb );
    ufloat q = iCb * iCb;
    ufloat d = 2 * iCs;
    return  q + d * iCb - d * q;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- LinearBurn
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendLinearBurnF( ufloat iCs, ufloat iCb ) {
    return  iCs + iCb < 1.f ? 0.f : iCs + iCb - 1.f;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- HardLight
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendHardLightF( ufloat iCs, ufloat iCb ) {
    return  iCs <= 0.5f ? BlendMultiplyF( iCb, 2.f * iCs ) : BlendScreenF( iCb, 2 * iCs - 1.f );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Overlay
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendOverlayF( ufloat iCs, ufloat iCb ) {
    return  BlendHardLightF( iCb, iCs );
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- VividLight
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendVividLightF( ufloat iCs, ufloat iCb ) {
    return  iCs <= 0.5f ? BlendColorBurnF( iCb, 2 * iCs ) : BlendColorDodgeF( iCb, 2 * ( iCs - 0.5f ) );
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- LinearLight
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendLinearLightF( ufloat iCs, ufloat iCb ) {
    return iCs <= 0.5f ? BlendLinearBurnF( iCb, 2 * iCb ) : BlendLinearDodgeF( iCb, 2 * ( iCs - 0.5f ) );
}
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- PinLight
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendPinLightF( ufloat iCs, ufloat iCb ) {
    return  iCs <= 0.5f ? BlendDarkenF( iCb, 2 * iCb ) : BlendLightenF( iCb, 2 * ( iCs - 0.5f ) );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ HardMix
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendHardMixF( ufloat iCs, ufloat iCb ) {
    return  BlendVividLightF( iCs, iCb ) < 0.5f ? 0.f : 1.f;
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Difference
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendDifferenceF( ufloat iCs, ufloat iCb ) {
    return  abs( iCb - iCs );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Exclusion
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendExclusionF( ufloat iCs, ufloat iCb ) {
    return  iCb + iCs - 2.f * iCb * iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Substract
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendSubstractF( ufloat iCs, ufloat iCb ) {
    return  iCb > iCs ? iCb - iCs : 0;
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Divide
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendDivideF( ufloat iCs, ufloat iCb ) {
    return  iCs == 0.f ? 1.f : FMaths::Min( 1.f, iCb / iCs );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Phoenix
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendPhoenixF( ufloat iCs, ufloat iCb ) {
    return  1.f - FMaths::Max( iCs, iCb ) + FMaths::Min( iCs, iCb );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Reflect
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendReflectF( ufloat iCs, ufloat iCb ) {
    return  iCb == 1.f ? 1.f : FMaths::Min( 1.f, iCs * iCs / ( 1.f - iCb ) );
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Glow
ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL BlendGlowF( ufloat iCs, ufloat iCb ) {
    return  BlendReflectF( iCb, iCs );
}
ULIS2_NAMESPACE_END

