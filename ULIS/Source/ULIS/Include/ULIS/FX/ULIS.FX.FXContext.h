/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.FX.FXContext.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/
#pragma once
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerformanceOptions.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/FX/Noise/ULIS.FX.Noise.h"

namespace ULIS {
/////////////////////////////////////////////////////
// TFXContext
template< uint32 _SH >
class TFXContext
{
public:
    template< uint32 _SH >
    static void ValueNoise( TBlock< _SH >* iBlock, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions() )
    {
        assert( iBlock );
        TValueNoiseGenerator< _SH >::Run( iBlock, iPerformanceOptions );
    }

};

} // namespace ULIS

