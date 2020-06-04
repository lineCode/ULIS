// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         Modes.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Blend and Alpha modes enums and related info.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// eBlendingMode
enum eBlendingMode
{
      BM_NORMAL
    , BM_TOP
    , BM_BACK
    , BM_BEHIND
    , BM_DISSOLVE
    , BM_BAYERDITHER8x8
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

ULIS3_NAMESPACE_END

