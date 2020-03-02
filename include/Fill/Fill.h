// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Fill.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Fill entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Base/Perf.h"
#include "Maths/Geometry.h"

ULIS2_NAMESPACE_BEGIN
struct ULIS2_API FFillInfo {
    FBlock*         destination;
    const IPixel*   color;
    FRect           area;
    FPerfInfo       perfInfo;
};

ULIS2_API void Fill( const FFillInfo& );

ULIS2_NAMESPACE_END

