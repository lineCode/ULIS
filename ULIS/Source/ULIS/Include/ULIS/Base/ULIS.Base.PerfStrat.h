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
        : use_sse_if_available  ( true                                  )
        , desired_workers       ( std::thread::hardware_concurrency()   )
    {}

    FPerfStrat( bool iSSE, unsigned int iWorkers = std::thread::hardware_concurrency() )
        : use_sse_if_available  ( iSSE                                  )
        , desired_workers       ( iWorkers                              )
    {}

    const bool          use_sse_if_available;
    const unsigned int  desired_workers;
};

} // namespace ULIS
