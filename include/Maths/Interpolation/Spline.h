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
#include "Maths/Geometry/Rectangle.h"
#include "Maths/Geometry/Vector.h"

ULIS_NAMESPACE_BEGIN
struct FSplineParametricSample {
    FVec2F point;
    float length;
    float param;
};

struct FSplineLinearSample {
    FVec2F point;
    float length;
    float param;
};
ULIS_NAMESPACE_END

