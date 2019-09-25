/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Transform.BlockTransformer.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerformanceOptions.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Global/ULIS.Global.GlobalThreadPool.h"

namespace ULIS {
/////////////////////////////////////////////////////
// TBlockTransformer_Default_ScanLine
template< uint32 _SH >
class TBlockTransformer_Default_ScanLine
{
public:
    static void Run( const TBlock< _SH >*   iSrcBlock
                   , TBlock< _SH >*         iDstBlock
                   , const glm::mat3&       iInverseTransform
                   , const int              iLine
                   , const int              iX1
                   , const int              iX2 )
    {
        ULIS_CRASH_TODO;
    }

    static void Run( const TBlock< _SH >*        iSrcBlock
                   , TBlock< _SH >*              iDstBlock
                   , const glm::mat3&            iInverseTransform )
    {
        ULIS_CRASH_TODO;
        /*
        const int x1 = iROI.x;
        const int y1 = iROI.y;
        const int x2 = x1 + iROI.w;
        const int y2 = y1 + iROI.h;
        FThreadPool& global_pool = FGlobalThreadPool::Get();
        for( int y = y1; y < y2; ++y )
            global_pool.ScheduleJob( ProcessScanLine, iBlockTop, iBlockBack, iOpacity, y, x1, x2, iShift );

        global_pool.WaitForCompletion();
        */
    }
};


/////////////////////////////////////////////////////
// TBlockTransformer_Default_MonoThread
template< uint32 _SH >
class TBlockTransformer_Default_MonoThread
{
public:
    static void Run( const TBlock< _SH >*        iSrcBlock
                   , TBlock< _SH >*              iDstBlock
                   , const glm::mat3&            iInverseTransform
                   , const glm::vec2&            iShift )
    {
        const int x1 = -iShift.x;
        const int y1 = -iShift.y;
        const int x2 = iDstBlock->Width() + x1;
        const int y2 = iDstBlock->Height() + y1;
        const int maxx = iSrcBlock->Width();
        const int maxy = iSrcBlock->Height();
        TBlock< _SH >::tPixelValue fallback = TBlock< _SH >::tPixelValue();
        for( int y = y1; y < y2; ++y )
        {
            for( int x = x1; x < x2; ++x )
            {
                glm::vec3 point_in_dst( x, y, 1.f );
                glm::vec2 point_in_src = ( iInverseTransform * point_in_dst );
                int src_x = point_in_src.x;
                int src_y = point_in_src.y;
                if( src_x < 0 || src_y < 0 || src_x >= maxx || src_y >= maxy )
                    iDstBlock->SetPixelValue( x + iShift.x, y + iShift.y, fallback );
                else
                    iDstBlock->SetPixelProxy( x + iShift.x, y + iShift.y, iSrcBlock->PixelProxy( src_x, src_y ) );
            }
        }
    }
};


/////////////////////////////////////////////////////
// TBlockTransformer_Default
template< uint32 _SH >
class TBlockTransformer_Default
{
public:
    static void Run( const TBlock< _SH >*        iSrcBlock
                   , TBlock< _SH >*              iDstBlock
                   , const glm::mat3&            iInverseTransform
                   , const glm::vec2&            iShift
                   , const FPerformanceOptions&  iPerformanceOptions= FPerformanceOptions() )
    {
        TBlockTransformer_Default_MonoThread< _SH >::Run( iSrcBlock, iDstBlock, iInverseTransform, iShift );
        /*
        if( iPerformanceOptions.desired_workers > 1 )
        {
            TBlockTransformer_Default_ScanLine< _SH >::Run( iSrcBlock, iDstBlock, iInverseTransform );
        }
        else
        {
            TBlockTransformer_Default_MonoThread< _SH >::Run( iSrcBlock, iDstBlock, iInverseTransform );
        }
        */
    }
};


/////////////////////////////////////////////////////
// TBlockTransformer_Imp
template< uint32 _SH >
class TBlockTransformer_Imp
{
public:
    static inline void Run( const TBlock< _SH >*        iSrcBlock
                          , TBlock< _SH >*              iDstBlock
                          , const glm::mat3&            iInverseTransform
                          , const glm::vec2&            iShift
                          , const FPerformanceOptions&  iPerformanceOptions= FPerformanceOptions() )
    {
        TBlockTransformer_Default< _SH >::Run( iSrcBlock, iDstBlock, iInverseTransform, iShift, iPerformanceOptions );
    }
};


/////////////////////////////////////////////////////
// TBlockTransformer
template< uint32 _SH >
class TBlockTransformer
{
public:
    static inline void Run( const TBlock< _SH >*        iSrcBlock
                          , TBlock< _SH >*              iDstBlock
                          , const glm::mat3&            iInverseTransform
                          , const glm::vec2&            iShift
                          , const FPerformanceOptions&  iPerformanceOptions= FPerformanceOptions() )
    {
        TBlockTransformer_Imp< _SH >::Run( iSrcBlock, iDstBlock, iInverseTransform, iShift, iPerformanceOptions );
    }
};

} // namespace ULIS

