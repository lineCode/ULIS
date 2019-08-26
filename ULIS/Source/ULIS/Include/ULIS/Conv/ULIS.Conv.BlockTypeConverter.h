/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Conv.BlockTypeConverter.h
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
// TBlockTypeConverter_ScanLine
template< uint32 _SHSrc, uint32 _SHDst >
class TBlockTypeConverter_ScanLine
{
public:
    static void ProcessScanLine( const TBlock< _SHSrc >* iBlockSrc, TBlock< _SHDst >* iBlockDst, int iLine, int iX1, int iX2 )
    {
        using tPixelProxySrc = TBlock< _SHSrc >::tPixelProxy;
        using tPixelProxyDst = TBlock< _SHDst >::tPixelProxy;
        using src_info = TBlockInfo< _SHSrc >;
        using dst_info = TBlockInfo< _SHDst >;

        for( int x = iX1; x < iX2; ++x )
        {
            tPixelProxySrc srcProxy = iBlockSrc->PixelProxy( x, iLine );
            tPixelProxyDst dstProxy = iBlockDst->PixelProxy( x, iLine );

            for( int i = 0; i < src_info::_nf._nc; ++i )
                dstProxy.SetComponent( i, ConvType< tPixelProxySrc::tPixelType, tPixelProxyDst::tPixelType >( srcProxy.GetComponent( i ) ) );

            dstProxy.SetAlpha( ConvType< tPixelProxySrc::tPixelType, tPixelProxyDst::tPixelType >( srcProxy.GetAlpha() ) );
        }
    }

    static void Run( const TBlock< _SHSrc >* iBlockSrc, TBlock< _SHDst >* iBlockDst )
    {
        const int x1 = 0;
        const int y1 = 0;
        const int x2 = iBlockSrc->Width();
        const int y2 = iBlockSrc->Height();
        FThreadPool& global_pool = FGlobalThreadPool::Get();
        for( int y = y1; y < y2; ++y )
            global_pool.ScheduleJob( ProcessScanLine, iBlockSrc, iBlockDst, y, x1, x2 );

        global_pool.WaitForCompletion();
    }
};

/////////////////////////////////////////////////////
// TBlockTypeConverter_MonoThread
template< uint32 _SHSrc, uint32 _SHDst >
class TBlockTypeConverter_MonoThread
{
public:
    static void Run( const TBlock< _SHSrc >* iBlockSrc, TBlock< _SHDst >* iBlockDst )
    {
        using tPixelProxySrc = TBlock< _SHSrc >::tPixelProxy;
        using tPixelProxyDst = TBlock< _SHDst >::tPixelProxy;
        using src_info = TBlockInfo< _SHSrc >;
        using dst_info = TBlockInfo< _SHDst >;

        for( int y = 0; y < iBlockSrc->Height(); ++y )
        {
            for( int x = 0; x < iBlockSrc->Width(); ++x )
            {
                tPixelProxySrc srcProxy = iBlockSrc->PixelProxy( x, y );
                tPixelProxyDst dstProxy = iBlockDst->PixelProxy( x, y );
                for( int i = 0; i < src_info::_nf._nc; ++i )
                    dstProxy.SetComponent( i, ConvType< tPixelProxySrc::tPixelType, tPixelProxyDst::tPixelType >( srcProxy.GetComponent( i ) ) );
                dstProxy.SetAlpha( ConvType< tPixelProxySrc::tPixelType, tPixelProxyDst::tPixelType >( srcProxy.GetAlpha() ) );
            }
        }
    }
};


/////////////////////////////////////////////////////
// TBlockTypeConverter_Imp
template< uint32 _SHSrc, uint32 _SHDst >
class TBlockTypeConverter_Imp
{
public:
    static inline void Run( const TBlock< _SHSrc >* iBlockSrc, TBlock< _SHDst >* iBlockDst, const FPerfStrat& iPerfStrat = FPerfStrat() )
    {
        if( iPerfStrat.desired_workers > 1 )
        {
            TBlockTypeConverter_ScanLine< _SHSrc, _SHDst >::Run( iBlockSrc, iBlockDst );
        }
        else
        {
            TBlockTypeConverter_MonoThread< _SHSrc, _SHDst >::Run( iBlockSrc, iBlockDst );
        }
    }
};


/////////////////////////////////////////////////////
// TBlockTypeConverter
template< uint32 _SHSrc, uint32 _SHDst, int _MODEL_DIFF >
class TBlockTypeConverter
{
public:
    static inline void Run( const TBlock< _SHSrc >* iBlockSrc, TBlock< _SHDst >* iBlockDst, const FPerfStrat& iPerfStrat = FPerfStrat() )
    {
    }
};

/////////////////////////////////////////////////////
// TBlockTypeConverter
template< uint32 _SHSrc, uint32 _SHDst >
class TBlockTypeConverter< _SHSrc, _SHDst, 0 >
{
public:
    static inline void Run( const TBlock< _SHSrc >* iBlockSrc, TBlock< _SHDst >* iBlockDst, const FPerfStrat& iPerfStrat = FPerfStrat() )
    {
        TBlockTypeConverter_Imp< _SHSrc, _SHDst >::Run( iBlockSrc, iBlockDst, iPerfStrat );
    }
};


} // namespace ULIS

