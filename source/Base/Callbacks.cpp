// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Callbacks.cpp
* @author       Clement Berthaud
* @brief        This file provides definitions for the image callbacks.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Base/Callbacks.h"

ULIS3_NAMESPACE_BEGIN
void OnCleanup_FreeMemory( tByte* iData, void* iInfo )
{
    delete [] iData;
}

void OnCleanup_DoNothing( tByte* iData, void* iInfo )
{
}

ULIS3_NAMESPACE_END

