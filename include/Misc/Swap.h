// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Swap.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Swap entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS2_NAMESPACE_BEGIN

struct ULIS2_API FSwapInfo {
    FBlock*     destination;
    uint8       channel1;
    uint8       channel2;
    FPerfInfo   perfInfo;
};

ULIS2_API void Swap( const FSwapInfo& );

ULIS2_NAMESPACE_END

