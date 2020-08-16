// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         FRasterContext2D.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FRasterContext2D class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FRasterContext2D
/// @brief      The FRasterContext2D class provides a context for calling image
///             raster and composition functions for a given format.
/// @details    The FRasterContext2D works on FRasterImage2D and is bound to a
///             specific format. It prefetches the dispatched implementation to
///             select the fastest method according to the format, and its
///             specializations if available, and according to the current runtime
///             device and its support for SIMD features or thread support.
///
///             \sa FRasterImage2D
///             \sa FThreadPool
///             \sa FDevice
///             \sa FCommandQueue
class ULIS_API FRasterContext2D
{
public:
    /*! Destructor */
    ~FRasterContext2D();

    /*! Constructor */
    FRasterContext2D();
};

ULIS_NAMESPACE_END

