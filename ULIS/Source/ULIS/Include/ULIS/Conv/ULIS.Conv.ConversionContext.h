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
#include "ULIS/Conv/ULIS.Conv.BlockTypeConverter.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Make/ULIS.Make.MakeContext.h"

namespace ULIS {
/////////////////////////////////////////////////////
// TConversionContext
class TConversionContext
{
public:
    template< uint32 _SHSrc, uint32 _SHDst >
    static void ConvertTypeAndLayoutInto( const TBlock< _SHSrc >* iBlockSrc, TBlock< _SHDst >* iBlockDst, const FPerfStrat& iPerfStrat = FPerfStrat() )
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
        if( _SHSrc == _SHDst )
            TMakeContext< _SHSrc >::CopyBlockInto( (const TBlock< _SHSrc >*)iBlockSrc, (TBlock< _SHSrc >*)iBlockDst, iPerfStrat );
        else
            TBlockTypeConverter< _SHSrc, _SHDst, ( (int)src_info::_nf._cm - (int)dst_info::_nf._cm ) >::Run( iBlockSrc, iBlockDst, iPerfStrat );
    }

    template< uint32 _SHSrc, uint32 _SHDst >
    static void ConvertTypeAndLayoutInto( const TPixelBase< _SHSrc >& iSrc, TPixelBase< _SHDst >& iDst )
    {
        using src_info = TBlockInfo< _SHSrc >;
        using dst_info = TBlockInfo< _SHDst >;
        assert( src_info::_nf._cm == dst_info::_nf._cm ); // Color Model
        if( _SHSrc == _SHDst )
            iDst = iSrc;
        else
            TPixelTypeConverter< _SHSrc, _SHDst, ( (int)src_info::_nf._cm - (int)dst_info::_nf._cm ) >::Apply( iSrc, iDst );
    }
};


} // namespace ULIS

