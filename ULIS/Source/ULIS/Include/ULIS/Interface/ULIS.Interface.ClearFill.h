/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.ClearFill.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerfStrat.h"
#include "ULIS/Color/ULIS.Color.CColor.h"
#include "ULIS/Maths/ULIS.Maths.Geometry.h"

namespace ULIS { class IBlock; }

namespace ULIS {
/////////////////////////////////////////////////////
// FClearFillContext
class FClearFillContext
{
public:
    static void Fill( IBlock* iBlock, const CColor& iColor, const FPerfStrat& iPerfStrat = FPerfStrat(), bool callInvalidCB = true );
    static void FillRect( IBlock* iBlock, const CColor& iColor, const FRect& iRect, const FPerfStrat& iPerfStrat = FPerfStrat(), bool callInvalidCB = true );
    static void Clear( IBlock* iBlock, const FPerfStrat& iPerfStrat = FPerfStrat(), bool callInvalidCB = true );
    static void ClearRect( IBlock* iBlock, const FRect& iRect, const FPerfStrat& iPerfStrat = FPerfStrat(), bool callInvalidCB = true );
};

} // namespace ULIS

