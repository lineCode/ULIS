// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Blend.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Base/Perf.h"
#include "Blend/BlendingPRNGSeed.h"
#include "Blend/Modes.h"
#include "Maths/Geometry.h"

ULIS2_NAMESPACE_BEGIN

struct ULIS2_API FBlendInfo {
    const FBlock*   source;
    FBlock*         backdrop;
    FRect           sourceRect;
    FVec2F          backdropPosition;
    bool            subpixelFlag;
    eBlendingMode   blendingMode;
    eAlphaMode      alphaMode;
    float           opacityValue;
    FPerfInfo       perfInfo;

    // Internal
    FVec2I          _shift;
    FVec2I          _backdropCoverage;
    FRect           _backdropWorkingRect;
    FVec2F          _buspixelComponent;
};


ULIS2_API void Blend( const FBlendInfo& );

typedef void (*fpDispatchedBlendFunc)( const FFormatInfo& iFormatInfo, std::shared_ptr< const FBlendInfo > iBlendParams );
ULIS2_API fpDispatchedBlendFunc QueryDispatchedBlendFunctionForParameters( const FFormatInfo& iFormatInfo, const FBlendInfo& iBlendParams );

ULIS2_NAMESPACE_END

