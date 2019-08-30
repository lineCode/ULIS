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
        {
            memcpy( iDst.Ptr(), iSrc.Ptr(), src_info::_nf._pd );
            iDst.AssignColorProfile( iSrc.ColorProfile() );
        }
        else
        {
            TPixelTypeConverter< _SHSrc, _SHDst, ( (int)src_info::_nf._cm - (int)dst_info::_nf._cm ) >::Apply( iSrc, iDst );
        }
    }

    struct FConversionDiagnosis
    {
        bool bSameFormat;
        bool bSameType;
        bool bSameModel;
        bool bSameLayout;
        bool bSameProfile;
    };

    template< uint32 _SHSrc, uint32 _SHDst >
    static void Convert( const TPixelBase< _SHSrc >& iSrc, TPixelBase< _SHDst >& iDst )
    {
        using src_info = TBlockInfo< _SHSrc >;
        using dst_info = TBlockInfo< _SHDst >;

        FConversionDiagnosis diag;
        diag.bSameFormat    = src_info::_nf._sh == dst_info::_nf._sh;
        diag.bSameType      = src_info::_nf._tp == dst_info::_nf._tp;
        diag.bSameModel     = src_info::_nf._cm == dst_info::_nf._cm;
        diag.bSameLayout    = src_info::_nf._lh == dst_info::_nf._lh;
        diag.bSameProfile   = iSrc.ColorProfile() == iDst.ColorProfile();

        if( diag.bSameFormat && diag.bSameProfile )
        {
            memcpy( iDst.Ptr(), iSrc.Ptr(), src_info::_nf._pd );
            iDst.AssignColorProfile( iSrc.ColorProfile() );
            return;
        }

        constexpr uint32 srcDefaultModel = TDefaultModelFormat< src_info::_nf._cm >();
        constexpr uint32 dstDefaultModel = TDefaultModelFormat< dst_info::_nf._cm >();
        TPixelValue< srcDefaultModel > srcFallback;
        TPixelValue< dstDefaultModel > dstFallback;
        ConvertTypeAndLayoutInto< _SHSrc, srcDefaultModel >( iSrc, srcFallback );
        //ConvertTypeAndLayoutInto< iSrc, dstDefaultModel >( iSrc, dstFallback );
        //TPixelTypeConverter< _SHSrc, _SHDst, ( (int)src_info::_nf._cm - (int)dst_info::_nf._cm ) >::Apply( iSrc, iDst );
    }
};


} // namespace ULIS

