// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Text.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Text entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Base/Perf.h"
#include "Maths/Geometry.h"
#include "Maths/Transform2D.h"

#include <ft2build.h>
#include FT_FREETYPE_H

ULIS2_NAMESPACE_BEGIN

struct ULIS2_API FTextInfo {
    FBlock*             destination;
    std::wstring        text;
    const FFont*        font;
    int                 size;
    const IPixel*       color;
    const FTransform2D* transform;
    bool                antialiasingFlag;
    FPerfInfo           perfInfo;
};

struct ULIS2_API FTextMetricsInfo {
    std::string         text;
    const FFont*        font;
    int                 size;
    const FTransform2D* transform;
};

struct ULIS2_API _FPrivateTextInfo {
    FBlock*             destination;
    std::wstring        text;
    const FFont*        font;
    int                 size;
    const tByte*        color;
    FT_Matrix*          matrix;
    FVec2I              position;
    bool                antialiasingFlag;
    FPerfInfo           perfInfo;
};

ULIS2_API void RenderText( const FTextInfo& );
ULIS2_API FRect TextMetrics( const FTextMetricsInfo& );

// Dispatch Typedefs ( implemented in dispatch.ipp but available from public API )
typedef void (*fpDispatchedTextFunc)( const _FPrivateTextInfo& );
ULIS2_API fpDispatchedTextFunc QueryDispatchedTextFunctionForParameters( const FTextInfo&  );

ULIS2_NAMESPACE_END

