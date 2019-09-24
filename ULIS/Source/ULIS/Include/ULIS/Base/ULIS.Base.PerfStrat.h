/**
*
*   ULIS
*__________________
*
* @file     ULIS.Base.PerfStrat.h
* @author   Clement Berthaud
* @brief    This file provides the definition for the FPerfStart struct.
*/
#pragma once
#include <thread>

namespace ULIS {
/////////////////////////////////////////////////////
/// @struct     FPerfStrat
/// @brief      The FPerfStrat struct is user for holding performance options.
/// @details    Used for specification and forwarding of options in multi threaded / SSE pipelines.
///             These flags are juste hints, they can be overriden in some pipelines.
struct FPerfStrat
{
public:
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------- Construction
    /// @fn         FPerfStrat()
    /// @brief      Default Constructor.
    /// @details    Initializes members with default values
    FPerfStrat()
        : use_sse_if_available  ( false                               )
        , use_mem_if_available  ( true                                )
        , desired_workers       ( std::thread::hardware_concurrency() )
    {}

public:
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------- Public Data Members
    const bool          use_sse_if_available;   ///< boolean flag specifying if sse optimisations should be used if available.
    const bool          use_mem_if_available;   ///< boolean flag specifying if memory optimisations should be used if available.
    const unsigned int  desired_workers;        ///< integer representing the desired worker counts for multithreaded processing.
};

} // namespace ULIS

