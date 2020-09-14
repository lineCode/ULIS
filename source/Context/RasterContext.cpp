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
#include "Scheduling/CommandQueue.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FRasterContext::FContextualDispatchTable
struct FRasterContext::FContextualDispatchTable
{
    friend class FRasterContext;

public:
    /*! Constructor */
    FContextualDispatchTable( const FDevice& iDevice, eFormat iFormat )
        : mScheduleBlendSeparable(              TDispatcher< FDispatchedBlendSeparableInvocationSchedulerSelector >             ::Query( iDevice, iFormat ) )
        , mScheduleBlendNonSeparable(           TDispatcher< FDispatchedBlendNonSeparableInvocationSchedulerSelector >          ::Query( iDevice, iFormat ) )
        , mScheduleBlendMisc(                   TDispatcher< FDispatchedBlendMiscInvocationSchedulerSelector >                  ::Query( iDevice, iFormat ) )
        , mScheduleBlendSeparableSubpixel(      TDispatcher< FDispatchedBlendSeparableSubpixelInvocationSchedulerSelector >     ::Query( iDevice, iFormat ) )
        , mScheduleBlendNonSeparableSubpixel(   TDispatcher< FDispatchedBlendNonSeparableSubpixelInvocationSchedulerSelector >  ::Query( iDevice, iFormat ) )
        , mScheduleBlendMiscSubpixel(           TDispatcher< FDispatchedBlendMiscSubpixelInvocationSchedulerSelector >          ::Query( iDevice, iFormat ) )
    {
        ULIS_ASSERT( mScheduleBlendSeparable,               "Error: No dispatch found." );
        ULIS_ASSERT( mScheduleBlendNonSeparable,            "Error: No dispatch found." );
        ULIS_ASSERT( mScheduleBlendMisc,                    "Error: No dispatch found." );
        ULIS_ASSERT( mScheduleBlendSeparableSubpixel,       "Error: No dispatch found." );
        ULIS_ASSERT( mScheduleBlendNonSeparableSubpixel,    "Error: No dispatch found." );
        ULIS_ASSERT( mScheduleBlendMiscSubpixel,            "Error: No dispatch found." );
    }

    /*! Destructor */
    ~FContextualDispatchTable()
    {}

private:
    fpBlendInvocationScheduler mScheduleBlendSeparable;
    fpBlendInvocationScheduler mScheduleBlendNonSeparable;
    fpBlendInvocationScheduler mScheduleBlendMisc;
    fpBlendInvocationScheduler mScheduleBlendSeparableSubpixel;
    fpBlendInvocationScheduler mScheduleBlendNonSeparableSubpixel;
    fpBlendInvocationScheduler mScheduleBlendMiscSubpixel;
};

/////////////////////////////////////////////////////
// FRasterContext: Construction / Destruction
FRasterContext::~FRasterContext()
{
    delete  mContextualDispatchTable;
}

FRasterContext::FRasterContext(
      const FCommandQueue& iQueue
    , const FDevice& iDevice
    , eFormat iFormat
)
    : mContextualDispatchTable( nullptr )
    , mQueue( iQueue )
    , mDevice( iDevice )
    , mFormat( iFormat )
{
    mContextualDispatchTable = new  FContextualDispatchTable( iDevice, iFormat );
}

/////////////////////////////////////////////////////
// FRasterContext: Blend
void
FRasterContext::Blend(
      const FBlock& iSource
    , FBlock& iBackdrop
    , const FRectI& iSourceRect
    , const FVec2I& iPosition
    , eBlendMode iBlendingMode
    , eAlphaMode iAlphaMode
    , ufloat iOpacity
    , const FSchedulePolicy& iPolicy
    , uint32 iNumWait
    , const FTaskEvent* iWaitList
    , FTaskEvent* iEvent
)
{
    fpBlendInvocationScheduler run = nullptr;
    switch( BlendingModeQualifier( iBlendingMode ) ) {
        case BlendQualifier_Misc            : run = mContextualDispatchTable->mScheduleBlendMisc;
        case BlendQualifier_Separable       : run = mContextualDispatchTable->mScheduleBlendSeparable;
        case BlendQualifier_NonSeparable    : run = mContextualDispatchTable->mScheduleBlendNonSeparable;
    }
    ULIS_ASSERT( run, "Error: No dispatch found." );
}

void
FRasterContext::BlendAA(
      const FBlock& iSource
    , FBlock& iBackdrop
    , const FRectI& iSourceRect
    , const FVec2F& iPosition
    , eBlendMode iBlendingMode
    , eAlphaMode iAlphaMode
    , ufloat iOpacity
    , const FSchedulePolicy& iPolicy
    , uint32 iNumWait
    , const FTaskEvent* iWaitList
    , FTaskEvent* iEvent
)
{
    fpBlendInvocationScheduler run = nullptr;
    switch( BlendingModeQualifier( iBlendingMode ) ) {
        case BlendQualifier_Misc            : run = mContextualDispatchTable->mScheduleBlendMiscSubpixel;
        case BlendQualifier_Separable       : run = mContextualDispatchTable->mScheduleBlendSeparableSubpixel;
        case BlendQualifier_NonSeparable    : run = mContextualDispatchTable->mScheduleBlendNonSeparableSubpixel;
    }
    ULIS_ASSERT( run, "Error: No dispatch found." );
}

ULIS_NAMESPACE_END

