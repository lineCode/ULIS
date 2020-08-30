// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         SchedulePolicy.cpp
* @author       Clement Berthaud
* @brief        This file provides definition for the FSchedulePolicy class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Scheduling/SchedulePolicy.h"

ULIS_NAMESPACE_BEGIN
FSchedulePolicy::~FSchedulePolicy()
{
    // Nothing ATM
}

FSchedulePolicy::FSchedulePolicy(
      eScheduleRunPolicy iRun
    , eScheduleFlowPolicy iFlow
    , eScheduleModePolicy iMode
    , eScheduleParameterPolicy iParam
    , uint32 iValue
)
    : mRun( iRun )
    , mFlow( iFlow )
    , mMode( iMode )
    , mParameter( iParam )
    , mValue( iValue )
{
}

eScheduleRunPolicy
FSchedulePolicy::RunPolicy() const
{
    return  mRun;
}

eScheduleFlowPolicy
FSchedulePolicy::FlowPolicy() const
{
    return  mFlow;
}

eScheduleModePolicy
FSchedulePolicy::ModePolicy() const
{
    return  mMode;
}

eScheduleParameterPolicy
FSchedulePolicy::ParameterPolicy() const
{
    return  mParameter;
}

uint32
FSchedulePolicy::Value() const
{
    return  mValue;
}

ULIS_NAMESPACE_END

