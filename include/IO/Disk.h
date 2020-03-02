// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Disk.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the disk IO entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Base/Perf.h"

ULIS2_NAMESPACE_BEGIN

enum eImageFormat {
      IM_PNG
    , IM_BMP
    , IM_TGA
    , IM_JPG
    , IM_HDR
};

static const char* kwImageFormat[] = {
      "png"
    , "bmp"
    , "tga"
    , "jpg"
    , "hdr"
};

struct ULIS2_API FXLoadFromFileInfo {
    std::string     path;
    tFormat         desiredFormat;
    FPerfInfo       perfInfo;
};

struct ULIS2_API FSaveToFileInfo {
    const FBlock*   source;
    std::string     path;
    eImageFormat    imageFormat;
    int             quality;
    FPerfInfo       perfInfo;
};

ULIS2_API FBlock* XLoadFromFile( const FXLoadFromFileInfo& );
ULIS2_API void SaveToFile( const FSaveToFileInfo& );

ULIS2_NAMESPACE_END

