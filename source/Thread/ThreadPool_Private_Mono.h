// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         ThreadPool_Private_Mono.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the FThreadPool_private
*               class for systems without actual thread support.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Thread/ThreadPool.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FThreadPool_private
/// @brief      The FThreadPool_Private class provides the private implementation
///             for FThreadPool using the pimpl idiom.
/// @details    This version of the private implementation is for systems
///             without actual multi threading support.
///
///             \sa FThreadPool
class ULIS_API FThreadPool::FThreadPool_private
{
public:
    ~FThreadPool_private();
    FThreadPool_private( uint32 iNumWorkers );
    void ScheduleJob( const FCommand& iCommand );
    void WaitForCompletion();
    void SetNumWorkers( uint32 iNumWorkers );
    uint32 GetProcessed() const;
    uint32 GetNumWorkers() const;
    static uint32 MaxWorkers();

private:
    uint32 mProcessed;
};

FThreadPool::FThreadPool_private::~FThreadPool_private()
{
}

FThreadPool::FThreadPool_private::FThreadPool_private( uint32 iNumWorkers )
    : mProcessed( 0 )
{
}

void
FThreadPool::FThreadPool_private::ScheduleJob( const FCommand& iCommand )
{
    ++mProcessed;
}

void
FThreadPool::FThreadPool_private::WaitForCompletion()
{
}

void
FThreadPool::FThreadPool_private::SetNumWorkers( uint32 iNumWorkers )
{
}

uint32
FThreadPool::FThreadPool_private::GetProcessed() const
{
    return  mProcessed;
}

uint32
FThreadPool::FThreadPool_private::GetNumWorkers() const
{
    return  1;
}

//static
uint32
FThreadPool::FThreadPool_private::MaxWorkers()
{
    return  1;
}

ULIS_NAMESPACE_END

