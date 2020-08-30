// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Modes.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Blend and Alpha modes enums and related info.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// eBlendMode
enum eBlendMode
{
      Blend_NORMAL
    , Blend_TOP
    , Blend_BACK
    , Blend_BEHIND
    , Blend_DISSOLVE
    , Blend_BAYERDITHER8x8
    , Blend_DARKEN
    , Blend_MULTIPLY
    , Blend_COLORBURN
    , Blend_LINEARBURN
    , Blend_DARKERCOLOR
    , Blend_LIGHTEN
    , Blend_SCREEN
    , Blend_COLORDODGE
    , Blend_LINEARDODGE
    , Blend_LIGHTERCOLOR
    , Blend_OVERLAY
    , Blend_SOFTLIGHT
    , Blend_HARDLIGHT
    , Blend_VIVIDLIGHT
    , Blend_LINEARLIGHT
    , Blend_PINLIGHT
    , Blend_HARDMIX
    , Blend_PHOENIX
    , Blend_REFLECT
    , Blend_GLOW
    , Blend_DIFFERENCE
    , Blend_EXCLUSION
    , Blend_ADD
    , Blend_SUBSTRACT
    , Blend_DIVIDE
    , Blend_AVERAGE
    , Blend_NEGATION
    , Blend_HUE
    , Blend_SATURATION
    , Blend_COLOR
    , Blend_LUMINOSITY
    , Blend_PARTIALDERIVATIVE
    , Blend_WHITEOUT
    , Blend_ANGLECORRECTED
    , NumBlendingModes
};


static const char* kwBlendMode[] =
{
      "Normal"
    , "Top"
    , "Back"
    , "Behind"
    , "Dissolve"
    , "Dither"
    , "Darken"
    , "Multiply"
    , "ColorBurn"
    , "LinearBurn"
    , "DarkerColor"
    , "Lighten"
    , "Screen"
    , "ColorDodge"
    , "LinearDodge"
    , "LighterColor"
    , "Overlay"
    , "SoftLight"
    , "HardLight"
    , "VividLight"
    , "LinearLight"
    , "PinLight"
    , "HardMix"
    , "Phoenix"
    , "Reflect"
    , "Glow"
    , "Difference"
    , "Exclusion"
    , "Add"
    , "Substract"
    , "Divide"
    , "Average"
    , "Negation"
    , "Hue"
    , "Saturation"
    , "Color"
    , "Luminosity"
    , "PartialDerivative"
    , "Whiteout"
    , "AngleCorrected"
    , "Invalid"
};


/////////////////////////////////////////////////////
// eAlphaMode
enum eAlphaMode
{
      AM_NORMAL
    , AM_ERASE
    , AM_TOP
    , AM_BACK
    , AM_SUB
    , AM_ADD
    , AM_MUL
    , AM_MIN
    , AM_MAX
    , NumAlphaModes
};


static const char* kwAlphaMode[] =
{
      "Normal"
    , "Erase"
    , "Top"
    , "Back"
    , "Sub"
    , "Add"
    , "Mul"
    , "Min"
    , "Max"
    , "Invalid"
};

/////////////////////////////////////////////////////
// eBlendQualifier
enum eBlendQualifier
{
      BlendQualifier_Separable
    , BlendQualifier_NonSeparable
    , BlendQualifier_Misc
};

static
inline
constexpr
eBlendQualifier
BlendingModeQualifier( eBlendMode iBlendingMode )
{
    switch( iBlendingMode ) {
        case Blend_DISSOLVE            :   return  BlendQualifier_Misc;
        case Blend_BAYERDITHER8x8      :   return  BlendQualifier_Misc;
        case Blend_DARKERCOLOR         :   return  BlendQualifier_NonSeparable;
        case Blend_LIGHTERCOLOR        :   return  BlendQualifier_NonSeparable;
        case Blend_HUE                 :   return  BlendQualifier_NonSeparable;
        case Blend_SATURATION          :   return  BlendQualifier_NonSeparable;
        case Blend_COLOR               :   return  BlendQualifier_NonSeparable;
        case Blend_LUMINOSITY          :   return  BlendQualifier_NonSeparable;
        case Blend_PARTIALDERIVATIVE   :   return  BlendQualifier_NonSeparable;
        case Blend_WHITEOUT            :   return  BlendQualifier_NonSeparable;
        case Blend_ANGLECORRECTED      :   return  BlendQualifier_NonSeparable;
        default                     :   return  BlendQualifier_Separable;
    }
}

/////////////////////////////////////////////////////
// Macros
#define ULIS_FOR_ALL_SEPARABLE_BM_DO( X, _E0, _E1, _E2, _E3 )   \
    X( Blend_NORMAL            , _E0, _E1, _E2, _E3 )              \
    X( Blend_TOP               , _E0, _E1, _E2, _E3 )              \
    X( Blend_BACK              , _E0, _E1, _E2, _E3 )              \
    X( Blend_BEHIND            , _E0, _E1, _E2, _E3 )              \
    X( Blend_DARKEN            , _E0, _E1, _E2, _E3 )              \
    X( Blend_MULTIPLY          , _E0, _E1, _E2, _E3 )              \
    X( Blend_COLORBURN         , _E0, _E1, _E2, _E3 )              \
    X( Blend_LINEARBURN        , _E0, _E1, _E2, _E3 )              \
    X( Blend_LIGHTEN           , _E0, _E1, _E2, _E3 )              \
    X( Blend_SCREEN            , _E0, _E1, _E2, _E3 )              \
    X( Blend_COLORDODGE        , _E0, _E1, _E2, _E3 )              \
    X( Blend_LINEARDODGE       , _E0, _E1, _E2, _E3 )              \
    X( Blend_OVERLAY           , _E0, _E1, _E2, _E3 )              \
    X( Blend_SOFTLIGHT         , _E0, _E1, _E2, _E3 )              \
    X( Blend_HARDLIGHT         , _E0, _E1, _E2, _E3 )              \
    X( Blend_VIVIDLIGHT        , _E0, _E1, _E2, _E3 )              \
    X( Blend_LINEARLIGHT       , _E0, _E1, _E2, _E3 )              \
    X( Blend_PINLIGHT          , _E0, _E1, _E2, _E3 )              \
    X( Blend_HARDMIX           , _E0, _E1, _E2, _E3 )              \
    X( Blend_PHOENIX           , _E0, _E1, _E2, _E3 )              \
    X( Blend_REFLECT           , _E0, _E1, _E2, _E3 )              \
    X( Blend_GLOW              , _E0, _E1, _E2, _E3 )              \
    X( Blend_DIFFERENCE        , _E0, _E1, _E2, _E3 )              \
    X( Blend_EXCLUSION         , _E0, _E1, _E2, _E3 )              \
    X( Blend_ADD               , _E0, _E1, _E2, _E3 )              \
    X( Blend_SUBSTRACT         , _E0, _E1, _E2, _E3 )              \
    X( Blend_DIVIDE            , _E0, _E1, _E2, _E3 )              \
    X( Blend_AVERAGE           , _E0, _E1, _E2, _E3 )              \
    X( Blend_NEGATION          , _E0, _E1, _E2, _E3 )

#define ULIS_FOR_ALL_NONSEPARABLE_BM_DO( X, _E0, _E1, _E2, _E3 )    \
    X( Blend_DARKERCOLOR       , _E0, _E1, _E2, _E3 )                  \
    X( Blend_LIGHTERCOLOR      , _E0, _E1, _E2, _E3 )                  \
    X( Blend_HUE               , _E0, _E1, _E2, _E3 )                  \
    X( Blend_SATURATION        , _E0, _E1, _E2, _E3 )                  \
    X( Blend_COLOR             , _E0, _E1, _E2, _E3 )                  \
    X( Blend_LUMINOSITY        , _E0, _E1, _E2, _E3 )                  \
    X( Blend_PARTIALDERIVATIVE , _E0, _E1, _E2, _E3 )                  \
    X( Blend_WHITEOUT          , _E0, _E1, _E2, _E3 )                  \
    X( Blend_ANGLECORRECTED    , _E0, _E1, _E2, _E3 )

#define ULIS_FOR_ALL_MISC_BM_DO( X, _E0, _E1, _E2, _E3 )    \
    X( Blend_DISSOLVE          , _E0, _E1, _E2, _E3 )          \
    X( Blend_BAYERDITHER8x8    , _E0, _E1, _E2, _E3 )

#define ULIS_FOR_ALL_BM_DO( X, _E0, _E1, _E2, _E3 )             \
    ULIS_FOR_ALL_SEPARABLE_BM_DO(      X, _E0, _E1, _E2, _E3 )  \
    ULIS_FOR_ALL_NONSEPARABLE_BM_DO(   X, _E0, _E1, _E2, _E3 )  \
    ULIS_FOR_ALL_MISC_BM_DO(           X, _E0, _E1, _E2, _E3 )

#define ULIS_FOR_ALL_AM_DO( X, _E0, _E1, _E2, _E3 )     \
    X( AM_NORMAL        , _E0, _E1, _E2, _E3 )          \
    X( AM_ERASE         , _E0, _E1, _E2, _E3 )          \
    X( AM_TOP           , _E0, _E1, _E2, _E3 )          \
    X( AM_BACK          , _E0, _E1, _E2, _E3 )          \
    X( AM_SUB           , _E0, _E1, _E2, _E3 )          \
    X( AM_ADD           , _E0, _E1, _E2, _E3 )          \
    X( AM_MUL           , _E0, _E1, _E2, _E3 )          \
    X( AM_MIN           , _E0, _E1, _E2, _E3 )          \
    X( AM_MAX           , _E0, _E1, _E2, _E3 )

ULIS_NAMESPACE_END

