/**
*
*   ULIS
*__________________
*
* @file     ULIS.Base.PerformanceOptions.h
* @author   Clement Berthaud
* @brief    This file provides the definition for the FPerfStart struct.
*/
#pragma once
#include <thread>

namespace ULIS {
/////////////////////////////////////////////////////
/// @struct     FPerformanceOptions
/// @brief      The FPerformanceOptionsstruct is user for holding performance options.
/// @details    Used for specification and forwarding of options in multi threaded / SSE pipelines.
///             These flags are juste hints, they can be overriden in some pipelines.
struct FPerformanceOptions
{
public:
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------- Construction
    /// @fn         FPerformanceOptions()
    /// @brief      Default Constructor.
    /// @details    Initializes members with default values
    FPerformanceOptions()
        : use_sse_if_available  ( false                               )
        , use_mem_if_available  ( true                                )
        , desired_workers       ( std::thread::hardware_concurrency() )
    {}

public:
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------- Public Data Members
    bool          use_sse_if_available;   ///< boolean flag specifying if sse optimisations should be used if available.
    bool          use_mem_if_available;   ///< boolean flag specifying if memory optimisations should be used if available.
    unsigned int  desired_workers;        ///< integer representing the desired worker counts for multithreaded processing.
};

} // namespace ULIS

