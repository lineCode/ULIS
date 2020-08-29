// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         FRasterContext.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FRasterContext class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Context/RasterContext.h"
#include "Blend/BlendDispatch.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FRasterContext::FContextualDispatchTable
struct FRasterContext::FContextualDispatchTable
{
    friend class FRasterContext;

public:
    /*! Constructor */
    FContextualDispatchTable( const FDevice& iDevice, eFormat iFormat )
        : mScheduleBlendSeparable(      TDispatcher< FDispatchedBlendSeparableInvocationSchedulerSelector >     ::Query( iDevice, iFormat ) )
        , mScheduleBlendNonSeparable(   TDispatcher< FDispatchedBlendNonSeparableInvocationSchedulerSelector >  ::Query( iDevice, iFormat ) )
        , mScheduleBlendMisc(           TDispatcher< FDispatchedBlendMiscInvocationSchedulerSelector >          ::Query( iDevice, iFormat ) )
    {
        ULIS_ASSERT( mScheduleBlendSeparable,       "Bad bad bad !" );
        ULIS_ASSERT( mScheduleBlendNonSeparable,    "Bad bad bad !" );
        ULIS_ASSERT( mScheduleBlendMisc,            "Bad bad bad !" );
    }

    /*! Destructor */
    ~FContextualDispatchTable()
    {}

private:
    fpBlendInvocationScheduler mScheduleBlendSeparable;
    fpBlendInvocationScheduler mScheduleBlendNonSeparable;
    fpBlendInvocationScheduler mScheduleBlendMisc;
};

/////////////////////////////////////////////////////
// FRasterContext
FRasterContext::~FRasterContext()
{
    delete  mContextualDispatchTable;
}

FRasterContext::FRasterContext( const FDevice& iDevice, eFormat iFormat )
    : mContextualDispatchTable( nullptr )
    , mDevice( iDevice )
    , mFormat( iFormat )
{
    mContextualDispatchTable = new  FContextualDispatchTable( iDevice, iFormat );
}

ULIS_NAMESPACE_END

