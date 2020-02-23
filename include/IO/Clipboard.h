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
#include "Base/Core.h"
#include "Base/Perf.h"

ULIS2_NAMESPACE_BEGIN

ULIS2_API struct FXLoadFromClipboard {
    FPerfInfo       perfInfo;
};

ULIS2_API struct FSaveToClipboard {
    FPerfInfo       perfInfo;
};

ULIS2_API FBlock* XLoadFromClipboard( const FXLoadFromClipboard& );
ULIS2_API void SaveToClipboard( const FSaveToClipboard& );
ULIS2_API bool ClipboardHasImageData();

ULIS2_NAMESPACE_END

