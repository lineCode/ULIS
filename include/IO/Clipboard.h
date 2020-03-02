// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Clipboard.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the clipboard IO entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS2_NAMESPACE_BEGIN

struct ULIS2_API FXLoadFromClipboardInfo {
    tFormat         desiredFormat;
    FPerfInfo       perfInfo;
};

struct ULIS2_API FSaveToClipboardInfo {
    const FBlock*   source;
    FPerfInfo       perfInfo;
};

ULIS2_API FBlock* XLoadFromClipboard( const FXLoadFromClipboardInfo& );
ULIS2_API void SaveToClipboard( const FSaveToClipboardInfo& );
ULIS2_API bool ClipboardHasImageData();

ULIS2_NAMESPACE_END

