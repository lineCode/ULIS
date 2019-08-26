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
#include "ULIS/Make/ULIS.Make.MakeContext.h"

namespace ULIS {
/////////////////////////////////////////////////////
// TConversionContext
class TConversionContext
{
public:
    template< uint32 _SHSrc, uint32 _SHDst >
    static void ConvertTypeInto( const TBlock< _SHSrc >* iBlockSrc, TBlock< _SHDst >* iBlockDst, const FPerfStrat& iPerfStrat = FPerfStrat() )
    {
        // For:
        // Any Types
        // Any Layout
        // Profile Agnostic
        // Same Model
        assert( iBlockSrc );
        assert( iBlockDst );
        assert( iBlockSrc->Width() == iBlockDst->Width() );
        assert( iBlockSrc->Height() == iBlockDst->Height() );
        using src_info = TBlockInfo< _SHSrc >;
        using dst_info = TBlockInfo< _SHDst >;
        assert( src_info::_nf._cm == dst_info::_nf._cm ); // Color Model
    }
};


} // namespace ULIS

