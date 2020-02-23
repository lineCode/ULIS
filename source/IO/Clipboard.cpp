// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Clipboard.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the clipboard IO entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "IO/Clipboard.h"
#include "Data/Block.h"
#include "base/CPU.h"
#include "Conv/Conv.h"

// CLIP
#include <clip.h>

ULIS2_NAMESPACE_BEGIN
FBlock* XLoadFromClipboard( const FXLoadFromClipboard& ) {
    return  nullptr;
}


void SaveToClipboard( const FSaveToClipboard& ) {
    return  void();
}

bool ClipboardHasImageData() {
    return  false;
}

ULIS2_NAMESPACE_END

