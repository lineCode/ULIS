/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Transform.TransformContext.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerformanceOptions.h"
#include "ULIS/Transform/ULIS.Transform.BlockTransformer.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Make/ULIS.Make.MakeContext.h"

namespace ULIS {
/////////////////////////////////////////////////////
// TTransformContext
class TTransformContext
{
public:
    template< uint32 _SH >
    static void ConvertTypeAndLayoutInto( const TBlock< _SH >* iBlock, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions() )
    {
    }
};


} // namespace ULIS

