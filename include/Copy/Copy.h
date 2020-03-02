// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Copy.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Copy entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Base/Perf.h"
#include "Maths/Geometry.h"
#include <glm/vec2.hpp>

ULIS2_NAMESPACE_BEGIN

struct ULIS2_API FCopyInfo {
    const FBlock*   source;
    FBlock*         destination;
    FRect           area;
    FVec2I          pos;
    FPerfInfo       perfInfo;
};

ULIS2_API void CopyRect( const FCopyInfo& );
ULIS2_API void CopyRaw( const FBlock* iSrc, FBlock* iDst, bool iCallInvalidCB );

ULIS2_NAMESPACE_END

