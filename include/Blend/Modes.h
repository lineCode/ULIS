// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Blend.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Blend and Alpha modes enums and related info.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// eBlendingMode
enum eBlendingMode
{
      BM_NORMAL
    , BM_TOP
    , BM_BACK
    , BM_BEHIND
    , BM_DISSOLVE
    , BM_DARKEN
    , BM_MULTIPY
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
    , BM_HUE
    , BM_SATURATION
    , BM_COLOR
    , BM_LUMINOSITY
    , NUM_BLENDING_MODES
};


static const char* kwBlendingMode[] =
{
      "Normal"
    , "Top"
    , "Back"
    , "Behind"
    , "Dissolve"
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
    , "Hue"
    , "Saturation"
    , "Color"
    , "Luminosity"
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
    , AM_INVMAX
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
    , "InvMax"
    , "Invalid"
};


enum eBlendingModeQualifier
{
      BMQ_SEPARABLE
    , BMQ_NONSEPARABLE
    , BMQ_MISC
};


static
inline
constexpr
eBlendingModeQualifier
BlendingModeQualifier( eBlendingMode iBlendingMode )
{
    switch( iBlendingMode ) {
        case BM_DISSOLVE        :   return  BMQ_MISC;
        case BM_DARKERCOLOR     :   return  BMQ_NONSEPARABLE;
        case BM_LIGHTERCOLOR    :   return  BMQ_NONSEPARABLE;
        case BM_HUE             :   return  BMQ_NONSEPARABLE;
        case BM_SATURATION      :   return  BMQ_NONSEPARABLE;
        case BM_COLOR           :   return  BMQ_NONSEPARABLE;
        case BM_LUMINOSITY      :   return  BMQ_NONSEPARABLE;
        default                 :   return  BMQ_SEPARABLE;
    }
}

ULIS2_NAMESPACE_END

