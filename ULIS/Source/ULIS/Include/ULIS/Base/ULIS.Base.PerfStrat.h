/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.PerfStrat.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include <thread>

namespace ULIS {
/////////////////////////////////////////////////////
// FPerfStrat
struct FPerfStrat
{
    FPerfStrat()
        : use_sse_if_available  ( false                               )
        , use_mem_if_available  ( true                                )
        , desired_workers       ( std::thread::hardware_concurrency() )
    {}

    const bool          use_sse_if_available;
    const bool          use_mem_if_available;
    const unsigned int  desired_workers;
};

} // namespace ULIS
