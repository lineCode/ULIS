// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Callbacks.h
* @author       Clement Berthaud
* @brief        This file provides declarations for the image callbacks.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN

// Callback Typedefs
typedef void (*fpInvalidateFunction)( const FBlock* /* block */, void* /* info */, const FRect& /* rect */ );
typedef void (*fpCleanupFunction)( tByte* /* data */, void* /* info */ );

// Default Callbacks
ULIS2_API void OnCleanup_FreeMemory( tByte* iData, void* iInfo );
ULIS2_API void OnCleanup_DoNothing(  tByte* iData, void* iInfo );

/////////////////////////////////////////////////////
/// @class      FOnInvalid
/// @brief      The FOnInvalid struct provides a mean of storing and executing an Invalid callback with extra info.
struct ULIS2_API FOnInvalid
{
    FOnInvalid();
    FOnInvalid( fpInvalidateFunction iInvalidateFunction, void* iInvalidateInfo = nullptr );
    void ExecuteIfBound( const FBlock* iBlock, const FRect& iRect ) const;

private:
    fpInvalidateFunction    execute;
    void*                   info;
};


/////////////////////////////////////////////////////
/// @class      FOnCleanup
/// @brief      The FOnCleanup struct provides a mean of storing and executing a Cleanup callback with extra info.
struct ULIS2_API FOnCleanup
{
    FOnCleanup();
    FOnCleanup( fpCleanupFunction iCleanupFunction, void* iCleanupInfo = nullptr );
    void ExecuteIfBound( tByte* iData ) const;

private:
    fpCleanupFunction       execute;
    void*                   info;
};

ULIS2_NAMESPACE_END

