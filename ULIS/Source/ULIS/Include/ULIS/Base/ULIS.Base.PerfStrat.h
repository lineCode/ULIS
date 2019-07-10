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
        : initialized( false )
        , use_sse_if_available( false )
        , use_mt_if_available( false )
        , desired_workers( std::thread::hardware_concurrency() )
    {}

    FPerfStrat( bool iSSE, bool iMT, unsigned int iWorkers = std::thread::hardware_concurrency() )
        : initialized( true )
        , use_sse_if_available( iSSE )
        , use_mt_if_available( iMT )
        , desired_workers( iWorkers )
    {}

    const bool initialized;
    const bool use_sse_if_available;
    const bool use_mt_if_available;
    const unsigned int desired_workers;
};

} // namespace ULIS
