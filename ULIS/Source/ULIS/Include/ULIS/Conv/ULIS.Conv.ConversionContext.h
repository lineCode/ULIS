/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Conv.ConversionContext.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerfStrat.h"
#include "ULIS/Data/ULIS.Data.Block.h"

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >

/////////////////////////////////////////////////////
// TConversionContext
class TConversionContext
{
    template< uint32 _SHA, uint32 _SHB >
    static void Convert( TBlock< _SHA >* iBlockA, TBlock< _SHB >* iBlockB, const FPerfStrat& iPerfStrat = FPerfStrat() )
    {
        assert( iBlockA & iBlockB );
    }
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS