// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Clipboard_MacOSPlatform.ipp
* @author       Clement Berthaud
* @brief        This file provides the definition for the clipboard IO entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "IO/Clipboard.h"

ULIS_NAMESPACE_BEGIN
FRasterImage2D* XLoadFromClipboard( FThreadPool*            iThreadPool
                          , bool                    iBlocking
                          , uint32                  iPerfIntent
                          , const FHostDeviceInfo&  iHostDeviceInfo
                          , bool                    iCallCB
                          , eFormat                 iDesiredFormat )
{
    return  nullptr;
}

void SaveToClipboard( FThreadPool*              iThreadPool
                    , bool                      iBlocking
                    , uint32                    iPerfIntent
                    , const FHostDeviceInfo&    iHostDeviceInfo
                    , bool                      iCallCB
                    , const FRasterImage2D*             iSource )
{
    return  void();
}

bool ClipboardHasImageData_MacOSPlatform() {
    return  false;
}

ULIS_NAMESPACE_END

