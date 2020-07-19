// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Spline.h
* @author       Clement Berthaud
* @brief        This file provides basic Spline tools.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry/Rect.h"
#include "Maths/Geometry/Vec2.h"

ULIS3_NAMESPACE_BEGIN
struct FParametricSplineSample {
    FVec2F point;
    float length;
    float param;
};

struct FLinearSplineSample {
    FVec2F point;
    float length;
    float param;
};
ULIS3_NAMESPACE_END

