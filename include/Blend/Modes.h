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
      BM_NORMAL
    , BM_TOP
    , BM_BACK
    , BM_BEHIND
    , BM_DISSOLVE
    , BM_BAYERDITHER8x8
    , BM_DARKEN
    , BM_MULTIPLY
    , BM_COLORBURN
    , BM_LINEARBURN
    , BM_DARKERCOLOR
    , BM_LIGHTEN
    , BM_SCREEN
    , BM_COLORDODGE
    , BM_LINEARDODGE
    , BM_LIGHTERCOLOR
    , BM_OVERLAY
    , BM_SOFTLIGHT
    , BM_HARDLIGHT
    , BM_VIVIDLIGHT
    , BM_LINEARLIGHT
    , BM_PINLIGHT
    , BM_HARDMIX
    , BM_PHOENIX
    , BM_REFLECT
    , BM_GLOW
    , BM_DIFFERENCE
    , BM_EXCLUSION
    , BM_ADD
    , BM_SUBSTRACT
    , BM_DIVIDE
    , BM_AVERAGE
    , BM_NEGATION
    , BM_HUE
    , BM_SATURATION
    , BM_COLOR
    , BM_LUMINOSITY
    , BM_PARTIALDERIVATIVE
    , BM_WHITEOUT
    , BM_ANGLECORRECTED
    , NUM_BLENDING_MODES
};


static const char* kwBlendingMode[] =
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
    , NUM_ALPHA_MODES
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
        case BM_DISSOLVE            :   return  BlendQualifier_Misc;
        case BM_BAYERDITHER8x8      :   return  BlendQualifier_Misc;
        case BM_DARKERCOLOR         :   return  BlendQualifier_NonSeparable;
        case BM_LIGHTERCOLOR        :   return  BlendQualifier_NonSeparable;
        case BM_HUE                 :   return  BlendQualifier_NonSeparable;
        case BM_SATURATION          :   return  BlendQualifier_NonSeparable;
        case BM_COLOR               :   return  BlendQualifier_NonSeparable;
        case BM_LUMINOSITY          :   return  BlendQualifier_NonSeparable;
        case BM_PARTIALDERIVATIVE   :   return  BlendQualifier_NonSeparable;
        case BM_WHITEOUT            :   return  BlendQualifier_NonSeparable;
        case BM_ANGLECORRECTED      :   return  BlendQualifier_NonSeparable;
        default                     :   return  BlendQualifier_Separable;
    }
}

/////////////////////////////////////////////////////
// Macros
#define ULIS_FOR_ALL_SEPARABLE_BM_DO( X, _E0, _E1, _E2, _E3 )   \
    X( BM_NORMAL            , _E0, _E1, _E2, _E3 )              \
    X( BM_TOP               , _E0, _E1, _E2, _E3 )              \
    X( BM_BACK              , _E0, _E1, _E2, _E3 )              \
    X( BM_BEHIND            , _E0, _E1, _E2, _E3 )              \
    X( BM_DARKEN            , _E0, _E1, _E2, _E3 )              \
    X( BM_MULTIPLY          , _E0, _E1, _E2, _E3 )              \
    X( BM_COLORBURN         , _E0, _E1, _E2, _E3 )              \
    X( BM_LINEARBURN        , _E0, _E1, _E2, _E3 )              \
    X( BM_LIGHTEN           , _E0, _E1, _E2, _E3 )              \
    X( BM_SCREEN            , _E0, _E1, _E2, _E3 )              \
    X( BM_COLORDODGE        , _E0, _E1, _E2, _E3 )              \
    X( BM_LINEARDODGE       , _E0, _E1, _E2, _E3 )              \
    X( BM_OVERLAY           , _E0, _E1, _E2, _E3 )              \
    X( BM_SOFTLIGHT         , _E0, _E1, _E2, _E3 )              \
    X( BM_HARDLIGHT         , _E0, _E1, _E2, _E3 )              \
    X( BM_VIVIDLIGHT        , _E0, _E1, _E2, _E3 )              \
    X( BM_LINEARLIGHT       , _E0, _E1, _E2, _E3 )              \
    X( BM_PINLIGHT          , _E0, _E1, _E2, _E3 )              \
    X( BM_HARDMIX           , _E0, _E1, _E2, _E3 )              \
    X( BM_PHOENIX           , _E0, _E1, _E2, _E3 )              \
    X( BM_REFLECT           , _E0, _E1, _E2, _E3 )              \
    X( BM_GLOW              , _E0, _E1, _E2, _E3 )              \
    X( BM_DIFFERENCE        , _E0, _E1, _E2, _E3 )              \
    X( BM_EXCLUSION         , _E0, _E1, _E2, _E3 )              \
    X( BM_ADD               , _E0, _E1, _E2, _E3 )              \
    X( BM_SUBSTRACT         , _E0, _E1, _E2, _E3 )              \
    X( BM_DIVIDE            , _E0, _E1, _E2, _E3 )              \
    X( BM_AVERAGE           , _E0, _E1, _E2, _E3 )              \
    X( BM_NEGATION          , _E0, _E1, _E2, _E3 )

#define ULIS_FOR_ALL_NONSEPARABLE_BM_DO( X, _E0, _E1, _E2, _E3 )    \
    X( BM_DARKERCOLOR       , _E0, _E1, _E2, _E3 )                  \
    X( BM_LIGHTERCOLOR      , _E0, _E1, _E2, _E3 )                  \
    X( BM_HUE               , _E0, _E1, _E2, _E3 )                  \
    X( BM_SATURATION        , _E0, _E1, _E2, _E3 )                  \
    X( BM_COLOR             , _E0, _E1, _E2, _E3 )                  \
    X( BM_LUMINOSITY        , _E0, _E1, _E2, _E3 )                  \
    X( BM_PARTIALDERIVATIVE , _E0, _E1, _E2, _E3 )                  \
    X( BM_WHITEOUT          , _E0, _E1, _E2, _E3 )                  \
    X( BM_ANGLECORRECTED    , _E0, _E1, _E2, _E3 )

#define ULIS_FOR_ALL_MISC_BM_DO( X, _E0, _E1, _E2, _E3 )    \
    X( BM_DISSOLVE          , _E0, _E1, _E2, _E3 )          \
    X( BM_BAYERDITHER8x8    , _E0, _E1, _E2, _E3 )

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

