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
        ULIS_ASSERT( mScheduleBlendSeparable,       "Error: No dispatch found." );
        ULIS_ASSERT( mScheduleBlendNonSeparable,    "Error: No dispatch found." );
        ULIS_ASSERT( mScheduleBlendMisc,            "Error: No dispatch found." );
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
// FRasterContext: Construction / Destruction
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

/////////////////////////////////////////////////////
// FRasterContext: Blend
void
FRasterContext::Blend(
      const FBlock& iSource
    , FBlock& iBackdrop
    , const FRectI& iSourceRect
    , const FVec2I& iPosition
    , eBlendingMode iBlendingMode
    , eAlphaMode iAlphaMode
    , ufloat iOpacity )
{
    ULIS_ASSERT( mContextualDispatchTable.mScheduleBlendSeparable,      "Error: No dispatch found." );
    ULIS_ASSERT( mContextualDispatchTable.mScheduleBlendNonSeparable,   "Error: No dispatch found." );
    ULIS_ASSERT( mContextualDispatchTable.mScheduleBlendMisc,           "Error: No dispatch found." );
    switch( BlendingModeQualifier( iBlendingMode ) ) {
        case BMQ_MISC           : return;
        case BMQ_SEPARABLE      : return;
        case BMQ_NONSEPARABLE   : return;
        default                 : ULIS_ASSERT( false, "Error: Implementation path is not hooked for qualifier." ); return;
    }
}


ULIS_NAMESPACE_END

