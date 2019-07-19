/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Make.MakerContext.h
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
// TMakerContext
template< uint32 _SH >
class TMakerContext
{
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS