// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         CommandQueue.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FCommandQueue class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Scheduling/CommandQueue.h"
#include "Thread/ThreadPool.h"

ULIS_NAMESPACE_BEGIN
FCommandQueue::~FCommandQueue()
{
}

FCommandQueue::FCommandQueue( FThreadPool* iPool )
    : mPool( iPool )
{
}

void
FCommandQueue::Push( FCommand* iCommand )
{
    mQueue.Push( iCommand );
}

ULIS_NAMESPACE_END

