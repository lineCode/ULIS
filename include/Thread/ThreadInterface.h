// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         ThreadInterface.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the ThreadInterface entry points.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include <thread>

ULIS_NAMESPACE_BEGIN

ULIS_API FThreadPool* XCreateThreadPool( uint32 iCount = std::thread::hardware_concurrency() );
ULIS_API void XDeleteThreadPool( FThreadPool* iThreadPool );
ULIS_API void Fence( FThreadPool& iPool );
ULIS_API void SetNumWorkers( FThreadPool& iPool, uint32 iValue );
ULIS_API uint32 GetProcessed( FThreadPool& iPool );
ULIS_API uint32 GetNumWorkers( FThreadPool& iPool );
ULIS_API uint32 MaxWorkers();

ULIS_NAMESPACE_END

