// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Callbacks.h
* @author       Clement Berthaud
* @brief        This file provides declarations for the generic callbacks mechanisms.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS3_NAMESPACE_BEGIN
typedef void (*fpInvalidateFunction)( const FBlock* /* block */, void* /* info */, const FRect& /* rect */ );
typedef void (*fpCleanupFunction)( tByte* /* data */, void* /* info */ );

ULIS3_API void OnCleanup_FreeMemory( tByte* iData, void* iInfo );

template< typename R, typename ... Ts >
class TCallback
{
public:
    typedef R (*tFptr)( Ts ..., void* );
    TCallback()
        : mFptr( nullptr )
        , mInfo( nullptr )
    {}

    TCallback( tFptr iFptr, void* iInfo = nullptr )
        : mFptr( iFptr )
        , mInfo( iInfo )
    {}

    // No return value because we can't ensure a generic default return value if not bound.
    ULIS3_FORCEINLINE void ExecuteIfBound( Ts ... args ) const {
        if( mFptr )
            mFptr( args ..., mInfo );
    }

    ULIS3_FORCEINLINE R Execute( Ts ... args ) const {
        ULIS3_ASSERT( mFptr, "Error: Callback not set." );
        return  mFptr( args ..., mInfo );
    }

private:
    tFptr mFptr;
    void* mInfo;
};

typedef TCallback< void, tByte* > FOnCleanup;
typedef TCallback< void, const FBlock*, const FRect& > FOnInvalid;

ULIS3_NAMESPACE_END

