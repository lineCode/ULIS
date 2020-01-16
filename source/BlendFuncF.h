// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendFunF.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the float Blending functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include "Modes.h"
#include "Maths.h"

ULIS2_NAMESPACE_BEGIN

//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Normal
ULIS2_FORCEINLINE float BlendNormalF( float iCs, float iCb ) {
    return iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Top
ULIS2_FORCEINLINE float BlendTopF( float iCs, float iCb ) {
    return iCs;
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Back
ULIS2_FORCEINLINE float BlendBackF( float iCs, float iCb ) {
    return iCb;
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Behind
ULIS2_FORCEINLINE float BlendBehindF( float iCs, float iCb ) {
    return iCb;
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Darken
ULIS2_FORCEINLINE float BlendDarkenF( float iCs, float iCb ) {
    return  FMaths::Min( iCb, iCs );
}
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Multiply
ULIS2_FORCEINLINE float BlendMultiplyF( float iCs, float iCb ) {
    return  iCb * iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- ColorBurn
ULIS2_FORCEINLINE float BlendColorBurnF( float iCs, float iCb ) {
    return  iCs == 0.f ? 0.f : 1.f - FMaths::Min( 1.f, ( 1.f - iCb ) / iCs );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Lighten
ULIS2_FORCEINLINE float BlendLightenF( float iCs, float iCb ) {
    return  FMaths::Max( iCb, iCs );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Average
ULIS2_FORCEINLINE float BlendAverageF( float iCs, float iCb ) {
    return  ( iCs + iCb ) / 2.f;
}
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Negation
ULIS2_FORCEINLINE float BlendNegationF( float iCs, float iCb ) {
    return  1.f - fabsf( 1.f - iCs - iCb );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Screen
ULIS2_FORCEINLINE float BlendScreenF( float iCs, float iCb ) {
    return  iCb + iCs - ( iCb * iCs );
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- ColorDodge
ULIS2_FORCEINLINE float BlendColorDodgeF( float iCs, float iCb ) {
    return  iCs == 1.f ? 1.f : FMaths::Min( 1.f, iCb / ( 1.f - iCs ) );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Add
ULIS2_FORCEINLINE float BlendAddF( float iCs, float iCb ) {
    return  FMaths::Min( 1.f, iCs + iCb );
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- LinearDodge
ULIS2_FORCEINLINE float BlendLinearDodgeF( float iCs, float iCb ) {
    return  BlendAddF( iCs, iCb );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- SoftLight
ULIS2_FORCEINLINE float _softlight_D( float iX ) {
    return  iX <= 0.25f ? ( ( 16.f * iX - 12.f ) * iX + 4 ) * iX : sqrtf( iX );
}
ULIS2_FORCEINLINE float BlendSoftLightF( float iCs, float iCb ) {
    return  iCs <= 0.5f ? iCb - ( 1.f - 2.f * iCs ) * iCb * ( 1.f - iCb ) : iCb + ( 2.f * iCs - 1.f ) * ( _softlight_D( iCb ) - iCb );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- LinearBurn
ULIS2_FORCEINLINE float BlendLinearBurnF( float iCs, float iCb ) {
    return  iCs + iCb < 1.f ? 0.f : iCs + iCb - 1.f;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- HardLight
ULIS2_FORCEINLINE float BlendHardLightF( float iCs, float iCb ) {
    return  iCs <= 0.5f ? BlendMultiplyF( iCb, 2.f * iCs ) : BlendScreenF( iCb, 2 * iCs - 1.f );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Overlay
ULIS2_FORCEINLINE float BlendOverlayF( float iCs, float iCb ) {
    return  BlendHardLightF( iCb, iCs );
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- VividLight
ULIS2_FORCEINLINE float BlendVividLightF( float iCs, float iCb ) {
    return  iCs <= 0.5f ? BlendColorBurnF( iCb, 2 * iCs ) : BlendColorDodgeF( iCb, 2 * ( iCs - 0.5f ) );
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- LinearLight
ULIS2_FORCEINLINE float BlendLinearLightF( float iCs, float iCb ) {
    return iCs <= 0.5f ? BlendLinearBurnF( iCb, 2 * iCb ) : BlendLinearDodgeF( iCb, 2 * ( iCs - 0.5f ) );
}
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- PinLight
ULIS2_FORCEINLINE float BlendPinLightF( float iCs, float iCb ) {
    return  iCs <= 0.5f ? BlendDarkenF( iCb, 2 * iCb ) : BlendLightenF( iCb, 2 * ( iCs - 0.5f ) );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ HardMix
ULIS2_FORCEINLINE float BlendHardMixF( float iCs, float iCb ) {
    return  BlendVividLightF( iCs, iCb ) < 0.5f ? 0.f : 1.f;
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Difference
ULIS2_FORCEINLINE float BlendDifferenceF( float iCs, float iCb ) {
    return  abs( iCb - iCs );
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Exclusion
ULIS2_FORCEINLINE float BlendExclusionF( float iCs, float iCb ) {
    return  iCb + iCs - 2.f * iCb * iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Substract
ULIS2_FORCEINLINE float BlendSubstractF( float iCs, float iCb ) {
    return  iCb > iCs ? iCb - iCs : 0;
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Divide
ULIS2_FORCEINLINE float BlendDivideF( float iCs, float iCb ) {
    return  iCs == 0.f ? 1.f : FMaths::Min( 1.f, iCb / iCs );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Phoenix
ULIS2_FORCEINLINE float BlendPhoenixF( float iCs, float iCb ) {
    return  1.f - FMaths::Max( iCs, iCb ) + FMaths::Min( iCs, iCb );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Reflect
ULIS2_FORCEINLINE float BlendReflectF( float iCs, float iCb ) {
    return  iCb == 1.f ? 1.f : FMaths::Min( 1.f, iCs * iCs / ( 1.f - iCb ) );
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------- Glow
ULIS2_FORCEINLINE float BlendGlowF( float iCs, float iCb ) {
    return  BlendReflectF( iCb, iCs );
}

ULIS2_NAMESPACE_END

