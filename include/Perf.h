// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
 * @file        FCPU.h
 * @author      Clement Berthaud
 * @copyright   Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
 * @license     Please refer to LICENSE.md
 * @brief       This file provides the definition for the FPerf struct.
 */
#pragma once
#include "Core.h"
#include <thread>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @struct     FPerf
/// @brief      The FPerf struct is used for holding performance options.
/// @details    Used for specification and forwarding of options in multi threaded / SSE pipelines.
///             These flags are juste hints, they can be overriden in some pipelines.
struct ULIS2_API FPerf
{
public:
    // Construction
    /// @fn         FPerf()
    /// @brief      Default Constructor.
    /// @details    Initializes members with default values
    FPerf()
        : use_sse_if_available  ( false                               )
        , use_mem_if_available  ( true                                )
        , desired_workers       ( std::thread::hardware_concurrency() )
    {}

public:
    // Public Data Members
    bool          use_sse_if_available;   ///< boolean flag specifying if sse optimisations should be used if available.
    bool          use_mem_if_available;   ///< boolean flag specifying if memory optimisations should be used if available.
    unsigned int  desired_workers;        ///< integer representing the desired worker counts for multithreaded processing.
};

ULIS2_NAMESPACE_END

