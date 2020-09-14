// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         ThreadPool_Private_Mono.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the FThreadPool_Private
*               class for systems without actual thread support.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Thread/ThreadPool.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FThreadPool_Private
/// @brief      The FThreadPool_Private class provides the private implementation
///             for FThreadPool using the pimpl idiom.
/// @details    This version of the private implementation is for systems
///             without actual multi threading support.
///
///             \sa FThreadPool
class ULIS_API FThreadPool::FThreadPool_Private
{
public:
    ~FThreadPool_Private();
    FThreadPool_Private( uint32 iNumWorkers );
    void ScheduleJob( const FCommand& iCommand );
    void WaitForCompletion();
    void SetNumWorkers( uint32 iNumWorkers );
    uint32 GetProcessed() const;
    uint32 GetNumWorkers() const;
    static uint32 MaxWorkers();

private:
    uint32 mProcessed;
};

FThreadPool::FThreadPool_Private::~FThreadPool_Private()
{
}

FThreadPool::FThreadPool_Private::FThreadPool_Private( uint32 iNumWorkers )
    : mProcessed( 0 )
{
}

void
FThreadPool::FThreadPool_Private::ScheduleJob( const FCommand& iCommand )
{
    ++mProcessed;
}

void
FThreadPool::FThreadPool_Private::WaitForCompletion()
{
}

void
FThreadPool::FThreadPool_Private::SetNumWorkers( uint32 iNumWorkers )
{
}

uint32
FThreadPool::FThreadPool_Private::GetProcessed() const
{
    return  mProcessed;
}

uint32
FThreadPool::FThreadPool_Private::GetNumWorkers() const
{
    return  1;
}

//static
uint32
FThreadPool::FThreadPool_Private::MaxWorkers()
{
    return  1;
}

ULIS_NAMESPACE_END

