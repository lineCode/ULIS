// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         SchedulePolicy.h
* @author       Clement Berthaud
* @brief        This file provides declaration for the FSchedulePolicy class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FSchedulePolicy
/// @brief      The FSchedulePolicy class provides a way to control how a task
///             is dispatched and scheduled on a multithreaded system, in
///             coordination with a FThreadPool and a FCommandQueue.
/// @details    The FSchedulePolicy specifies wether a task should be
///             multithreaded or not, and if so which policy should be applied.
///             Wether the scheduling is done on a chunk basis, or on a scanline
///             approach, for example.
///
///             \sa FRasterContext
///             \sa FThreadPool
///             \sa FDevice
///             \sa FCommandQueue
class ULIS_API FSchedulePolicy
{
};

ULIS_NAMESPACE_END

