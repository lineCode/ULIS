
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
#include "ULIS/Base/ULIS.Base.PerfStrat.h"

namespace ULIS { class IBlock; }

namespace ULIS {
/////////////////////////////////////////////////////
// FConvContext
class FConvContext
{
public:
    static void ConvTypeAndLayoutInto( const IBlock* iBlockSrc, IBlock* iBlockDst, const FPerfStrat& iPerfStrat = FPerfStrat() );
};

} // namespace ULIS

