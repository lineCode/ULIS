// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Extract.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Swap entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Base/Perf.h"
#include <vector>

ULIS2_NAMESPACE_BEGIN

struct ULIS2_API FExtractInfo {
    FBlock*     source;
    FBlock*     destination;
    bool        sourceRawIndicesFlag;
    bool        destinationRawIndicesFlag;
    uint8       sourceExtractMask;
    uint8       destinationExtractMask;
    FPerfInfo   perfInfo;
};

struct ULIS2_API FXExtractInfo {
    FBlock*     source;
    tFormat     destinationFormat;
    bool        sourceRawIndicesFlag;
    bool        destinationRawIndicesFlag;
    uint8       sourceExtractMask;
    uint8       destinationExtractMask;
    FPerfInfo   perfInfo;
};

ULIS2_API void Extract( const FExtractInfo& );
ULIS2_API FBlock* XExtract( const FXExtractInfo& );

ULIS2_NAMESPACE_END

