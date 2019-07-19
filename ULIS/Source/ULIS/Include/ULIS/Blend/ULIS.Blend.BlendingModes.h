/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Blend.BlendingModes.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

namespace ULIS {
/////////////////////////////////////////////////////
// eBlendingMode
enum class eBlendingMode : uint8
{
      kNormal
    , kBehind
    , kDissolve

    , kDarken
    , kMultiply
    , kColorBurn
    , kLinearBurn
    , kDarkerColor

    , kLighten
    , kScreen
    , kColorDodge
    , kLinearDodge
    , kLighterColor

    , kOverlay
    , kSoftLight
    , kHardLight
    , kVividLight
    , kLinearLight
    , kPinLight
    , kHardMix

    , kDifference
    , kExclusion
    , kSubstract
    , kDivide

    , kHue
    , kSaturation
    , kColor
    , kLuminosity

    , kNumBlendingModes
};

static const char* kwBlendingMode[] =
{
      "Normal"
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

    , "Difference"
    , "Exclusion"
    , "Substract"
    , "Divide"

    , "Hue"
    , "Saturation"
    , "Color"
    , "Luminosity"

    , "Invalid"
};

#define ULIS_FOR_ALL_BLENDING_MODES_DO( iMode, X )                              \
    switch( iMode ) {                                                           \
        case eBlendingMode::kNormal:   X( eBlendingMode::kNormal );     break;  \
        case eBlendingMode::kMultiply: X( eBlendingMode::kMultiply );   break;  \
    }
} // namespace ULIS