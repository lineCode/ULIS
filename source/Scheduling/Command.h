// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Command.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FCommand class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Scheduling/SchedulePolicy.h"
#include "Scheduling/TaskEvent.h"
#include "Scheduling/CommandArgs.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FCommand
/// @brief      The FCommand class provides a way to store awaiting commands in
///             a command queue, with all informations needed for scheduling and
///             arguments about the operation.
/// @details    The FCommand is used by FCommandQueue and stores information about
///             a command which status is read through a FTaskEvent, which
///             scheduling information is stored in a FSchedulePolicy, and
///             which operation arguments are stored in a ICommandArgs child class.
///
///             \sa FCommandQueue
class FCommand {
public:
    /*! Destructor */
    ~FCommand();

    /*! Constructor */
    FCommand();

private:
    ICommandArgs*   mArgs;
    FTaskEvent      mEvent;
    FSchedulePolicy mPolicy;
};

ULIS_NAMESPACE_END

