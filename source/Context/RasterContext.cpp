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
public:
    /*! Constructor */
    FContextualDispatchTable()
    {}

    /*! Destructor */
    ~FContextualDispatchTable()
    {}

public:
    fpBlendInvocationScheduler  mScheduleBlendSeparable;
};

/////////////////////////////////////////////////////
// FRasterContext
FRasterContext::~FRasterContext()
{
    delete  mContextualDispatchTable;
}

FRasterContext::FRasterContext()
    : mContextualDispatchTable( nullptr )
{
    mContextualDispatchTable = new  FContextualDispatchTable();
}
ULIS_NAMESPACE_END

