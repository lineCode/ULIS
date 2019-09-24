
/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Conv.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerformanceOptions.h"

namespace ULIS { class IBlock; }

namespace ULIS {
/////////////////////////////////////////////////////
// FConversionContext
class FConversionContext
{
public:
    static void ConvTypeAndLayoutInto( const IBlock* iBlockSrc, IBlock* iBlockDst, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions() );
};

} // namespace ULIS

