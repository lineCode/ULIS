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

ULIS_NAMESPACE_BEGIN
typedef void (*fpInvalidateFunction)( const FBlock* /* block */, void* /* info */, const FRectI& /* rect */ );
typedef void (*fpCleanupFunction)( uint8* /* data */, void* /* info */ );

ULIS_API void OnCleanup_FreeMemory( uint8* iData, void* iInfo );

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
    ULIS_FORCEINLINE void ExecuteIfBound( Ts ... args ) const {
        if( mFptr )
            mFptr( args ..., mInfo );
    }

    ULIS_FORCEINLINE R Execute( Ts ... args ) const {
        ULIS_ASSERT( mFptr, "Error: Callback not set." );
        return  mFptr( args ..., mInfo );
    }

private:
    tFptr mFptr;
    void* mInfo;
};

typedef TCallback< void, uint8* > FOnCleanup;
typedef TCallback< void, const FBlock*, const FRectI& > FOnInvalid;
template class ULIS_API TCallback< void, uint8* >;
template class ULIS_API TCallback< void, const FBlock*, const FRectI& >;

ULIS_NAMESPACE_END

