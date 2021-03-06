// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Command.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FCommand class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Scheduling/Command.h"

ULIS_NAMESPACE_BEGIN

FCommand::~FCommand()
{
    if( mArgs )
        delete  mArgs;
}

FCommand::FCommand(
      ICommandArgs* iArgs
    , const FSchedulePolicy& iPolicy
    , FTaskEvent* iEvent
    , fpCommandScheduler iSched
)
    : mArgs( iArgs )
    , mPolicy( iPolicy )
    , mEvent( iEvent )
    , mSched( iSched )
{
}

ULIS_NAMESPACE_END

