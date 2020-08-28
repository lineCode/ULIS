// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         FRasterContext.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FRasterContext class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FRasterContext
/// @brief      The FRasterContext class provides a context for calling image
///             raster and composition functions for a given format.
/// @details    The FRasterContext works on FBlock and is bound to a
///             specific format. It prefetches the dispatched implementation to
///             select the fastest method according to the format, and its
///             specializations if available, and according to the current runtime
///             device and its support for SIMD features or thread support.
///
///             \sa FBlock
///             \sa FThreadPool
///             \sa FDevice
///             \sa FCommandQueue
class ULIS_API FRasterContext
{
private:
    struct FContextualDispatchTable;

public:
    /*! Destructor */
    ~FRasterContext();

    /*! Constructor */
    FRasterContext( const FDevice& iDevice, eFormat iFormat );

private:
    FContextualDispatchTable* mContextualDispatchTable;
    const FDevice& mDevice;
    eFormat mFormat;
};

ULIS_NAMESPACE_END

