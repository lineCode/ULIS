// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
 * @file        FPerf.h
 * @author      Clement Berthaud
 * @copyright   Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
 * @license     Please refer to LICENSE.md
 * @brief       This file provides the definition for the FPerf struct.
 */
#pragma once
#include "Core.h"

ULIS2_NAMESPACE_BEGIN
enum eOpt
{
      kMem
    , kSSE
};

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
        : opt( true )
        , mtd( true )
    {}

public:
    // Public Data Members
    uint    opt; ///< uint flag specifying the optimisation level that should be used if available.
    bool    mtd; ///< boolean flag specifying if multithreaded optimisations should be used if available.
};

ULIS2_NAMESPACE_END

