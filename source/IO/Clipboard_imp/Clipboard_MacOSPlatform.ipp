// Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Clipboard_MacOSPlatform.ipp
* @author       Clement Berthaud
* @brief        This file provides the definition for the clipboard IO entry point functions.
* @copyright    Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "IO/Clipboard.h"

ULIS2_NAMESPACE_BEGIN
FBlock* XLoadFromClipboard_MacOSPlatform( const FXLoadFromClipboardInfo& iLoadParams ) {
    return  nullptr;
}


void SaveToClipboard_MacOSPlatform( const FSaveToClipboardInfo& iSaveParams ) {
    return  void();
}

bool ClipboardHasImageData_MacOSPlatform() {
    return  false;
}

ULIS2_NAMESPACE_END

