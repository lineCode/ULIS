/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Conv.Connection.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Data/ULIS.Data.Block.h"

namespace ULIS {
/////////////////////////////////////////////////////
// TForwardConnector
template< uint32 _SH, e_cm _CM >
struct TForwardConnector
{
    static TPixelValue< TModelConnectionFormat< _CM >() > ConnectionModelFormat( const TPixelValue< _SH >& iValue )
    {
        return  TPixelValue< TModelConnectionFormat< _CM >() >();
    }
};
/////////////////////////////////////////////////////
// TForwardConnector Specialization


} // namespace ULIS

