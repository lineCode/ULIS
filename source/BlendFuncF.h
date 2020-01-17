// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         BlendFunF.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the ufloat Blending functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include "Modes.h"
#include "Maths.h"
#include "ModelStructs.h"

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
    return  iCs <= 0.5f ? iCb - ( 1.f - 2.f * iCs ) * iCb * ( 1.f - iCb ) : iCb + ( 2.f * iCs - 1.f ) * ( _softlight_D( iCb ) - iCb );
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
/////////////////////////////////////////////////////
// Non Separable HSL Blending Modes
// We assume they are RGB, no check is done, beware.
static ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL LumF( const FRGBF& iC ) {
    return  0.3f * iC.R + 0.59f * iC.G + 0.11f * iC.B;
}

static ULIS2_FORCEINLINE FRGBF ULIS2_VECTORCALL ClipColorF( FRGBF iC ) {
    ufloat l = LumF( iC );
    ufloat n = FMaths::Min3( iC.R, iC.G, iC.B );
    ufloat x = FMaths::Max3( iC.R, iC.G, iC.B );
    if( n < 0.0f )
    {
        ufloat ln = l - n;
        iC.R = l + ( ( ( iC.R - l ) * l ) / ( ln ) );
        iC.G = l + ( ( ( iC.G - l ) * l ) / ( ln ) );
        iC.B = l + ( ( ( iC.B - l ) * l ) / ( ln ) );
    }

    if( x > 1.0f )
    {
        ufloat xl = x - l;
        ufloat ml = 1.f - l;
        iC.R = l + ( ( ( iC.R - l ) * ( ml ) ) / ( xl ) );
        iC.G = l + ( ( ( iC.G - l ) * ( ml ) ) / ( xl ) );
        iC.B = l + ( ( ( iC.B - l ) * ( ml ) ) / ( xl ) );
    }

    return  iC;
}

static ULIS2_FORCEINLINE FRGBF ULIS2_VECTORCALL SetLumF( const FRGBF& iC, ufloat iL ) {
    ufloat d = iL - LumF( iC );
    FRGBF C;
    C.R = iC.R + d;
    C.G = iC.G + d;
    C.B = iC.B + d;
    return  ClipColorF( C );
}

static ULIS2_FORCEINLINE ufloat ULIS2_VECTORCALL SatF( const FRGBF& iC ) {
    return  FMaths::Max3( iC.R, iC.G, iC.B ) - FMaths::Min3( iC.R, iC.G, iC.B );
}

static ULIS2_FORCEINLINE FRGBF ULIS2_VECTORCALL SetSatF( const FRGBF& iC, ufloat iS ) {
    uint8 maxIndex = iC.R > iC.G ? ( iC.R > iC.B ? 0 : 2 ) : ( iC.G > iC.B ? 1 : 2 );
    uint8 minIndex = iC.R < iC.G ? ( iC.R < iC.B ? 0 : 2 ) : ( iC.G < iC.B ? 1 : 2 );
    uint8 midIndex = 3 - maxIndex - minIndex;
    ufloat Cmax = *( ( (ufloat*)( &iC ) ) + maxIndex );
    ufloat Cmin = *( ( (ufloat*)( &iC ) ) + minIndex );
    ufloat Cmid = *( ( (ufloat*)( &iC ) ) + midIndex );
    if( Cmax > Cmin )
    {
        Cmid = ( ( ( Cmid - Cmin ) * iS ) / ( Cmax - Cmin ) );
        Cmax = iS;
    }
    else
    {
        Cmid = Cmax = 0.f;
    }
    Cmin = 0.f;
    FRGBF ret;
    *( ( (ufloat*)( &ret ) ) + maxIndex ) = Cmax;
    *( ( (ufloat*)( &ret ) ) + minIndex ) = Cmin;
    *( ( (ufloat*)( &ret ) ) + midIndex ) = Cmid;
    return  ret;
}

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- DarkerColor
ULIS2_FORCEINLINE FRGBF BlendDarkerColorF( const FRGBF& iCs, const FRGBF& iCb ) {
    return  LumF( iCb ) < LumF( iCs ) ? iCb : iCs;
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------- LighterColor
ULIS2_FORCEINLINE FRGBF BlendLighterColorF( const FRGBF& iCs, const FRGBF& iCb ) {
    return  LumF( iCb ) > LumF( iCs ) ? iCb : iCs;
}
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- Hue
ULIS2_FORCEINLINE FRGBF BlendHueF( const FRGBF& iCs, const FRGBF& iCb ) {
    return  SetLumF( SetSatF( iCs, SatF( iCb ) ), LumF( iCb ) );
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Saturation
ULIS2_FORCEINLINE FRGBF BlendSaturationF( const FRGBF& iCs, const FRGBF& iCb ) {
    return  SetLumF( SetSatF( iCb, SatF( iCs ) ), LumF( iCb ) );
}
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Color
ULIS2_FORCEINLINE FRGBF BlendColorF( const FRGBF& iCs, const FRGBF& iCb ) {
    return  SetLumF( iCs, LumF( iCb ) );
}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Luminosity
ULIS2_FORCEINLINE FRGBF BlendLuminosityF( const FRGBF& iCs, const FRGBF& iCb ) {
    return  SetLumF( iCb, LumF( iCs ) );
}

ULIS2_NAMESPACE_END

