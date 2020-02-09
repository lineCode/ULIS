// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         IO.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the disk IO entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
enum eImageFormat {
      IM_PNG
    , IM_BMP
    , IM_TGA
    , IM_JPG
    , IM_HDR
};

static const char* kwImageFormat[] =
{
      "PNG"
    , "BMP"
    , "TGA"
    , "JPG"
    , "HDR"
};

ULIS2_API FBlock* XLoad( FThreadPool*       iPool
                       , bool               iBlocking
                       , const FPerf&       iPerf
                       , const FCPU&        iCPU
                       , const std::string& iPath
                       , tFormat            iDesiredFormat = 0 );

ULIS2_API void Save( FThreadPool*       iPool
                   , bool               iBlocking
                   , const FPerf&       iPerf
                   , const FCPU&        iCPU
                   , const FBlock*      iSource
                   , const std::string& iPath
                   , eImageFormat       iImageFormat );
ULIS2_NAMESPACE_END

