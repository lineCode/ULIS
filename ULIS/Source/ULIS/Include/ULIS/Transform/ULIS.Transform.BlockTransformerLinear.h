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
#include "ULIS/Transform/ULIS.Transform.ResamplingMethods.h"

namespace ULIS {
/////////////////////////////////////////////////////
// TBlockTransformer_Linear_ScanLine
template< uint32 _SH >
class TBlockTransformer_Linear_ScanLine
{
public:
    static void ProcessScanLine( const TBlock< _SH >*   iSrcBlock
                   , TBlock< _SH >*         iDstBlock
                   , const glm::mat3&       iInverseTransform
                   , const int              iLine
                   , const int              iX1
                   , const int              iX2 )
    {
        const int maxx = iSrcBlock->Width();
        const int maxy = iSrcBlock->Height();
        const typename TBlock< _SH >::tPixelValue fallback = typename TBlock< _SH >::tPixelValue();
        for( int x = iX1; x < iX2; ++x )
            {
                glm::vec3 point_in_dst( x, iLine, 1.f );
                glm::vec2 point_in_src = ( iInverseTransform * point_in_dst );
                int src_x = floor( point_in_src.x );
                int src_y = floor( point_in_src.y );
                if( src_x < 0 || src_y < 0 || src_x >= maxx || src_y >= maxy )
                    iDstBlock->SetPixelValue( x, iLine, fallback );
                else
                    iDstBlock->SetPixelProxy( x, iLine, iSrcBlock->PixelProxy( src_x, src_y ) );
            }
    }

    static void Run( const TBlock< _SH >*        iSrcBlock
                   , TBlock< _SH >*              iDstBlock
                   , const glm::mat3&            iInverseTransform )
    {
        const int x1 = 0;
        const int y1 = 0;
        const int x2 = iDstBlock->Width();
        const int y2 = iDstBlock->Height();
        FThreadPool& global_pool = FGlobalThreadPool::Get();
        for( int y = y1; y < y2; ++y )
            global_pool.ScheduleJob( ProcessScanLine, iSrcBlock, iDstBlock, iInverseTransform, y, x1, x2 );
        global_pool.WaitForCompletion();
    }
};


/////////////////////////////////////////////////////
// TBlockTransformer_Linear_MonoThread
template< uint32 _SH >
class TBlockTransformer_Linear_MonoThread
{
public:
    static void Run( const TBlock< _SH >*        iSrcBlock
                   , TBlock< _SH >*              iDstBlock
                   , const glm::mat3&            iInverseTransform )
    {
        const int x1 = 0;
        const int y1 = 0;
        const int x2 = iDstBlock->Width();
        const int y2 = iDstBlock->Height();
        const int maxx = iSrcBlock->Width();
        const int maxy = iSrcBlock->Height();
        const typename TBlock< _SH >::tPixelValue fallback = typename TBlock< _SH >::tPixelValue();
        for( int y = y1; y < y2; ++y )
        {
            for( int x = x1; x < x2; ++x )
            {
                glm::vec3 point_in_dst( x, y, 1.f );
                glm::vec2 point_in_src = ( iInverseTransform * point_in_dst );
                glm::vec2 c00 = point_in_src + glm::vec2( -0.5, -0.5 );
                glm::vec2 c10 = point_in_src + glm::vec2( +0.5, -0.5 );
                glm::vec2 c11 = point_in_src + glm::vec2( +0.5, +0.5 );
                glm::vec2 c01 = point_in_src + glm::vec2( -0.5, +0.5 );

                float src_x     = point_in_src.x;
                float src_y     = point_in_src.y;
                float left_x    = src_x - 0.5f;
                float up_y      = src_y - 0.5f;
                float right_x   = src_x + 0.5f;
                float bot_y     = src_y + 0.5f;
                float tx        = left_x - src_x;
                float ty        = up_y - src_y;
                auto GetSample = [&]( float iX, float iY ) {
                    if( iX < 0 || iY < 0 || iY >= maxx || iY >= maxy )
                        return  (const typename TBlock< _SH >::tPixelValue)fallback;
                    else
                        return  (const typename TBlock< _SH >::tPixelValue)iSrcBlock->PixelProxy( iX, iY );
                };
                auto sample_left    = GetSample( left_x, src_y );
                auto sample_up      = GetSample( src_x, up_y );
                auto sample_right   = GetSample( right_x, src_y );
                auto sample_bot     = GetSample( src_x, bot_y );

                if( src_x < 0 || src_y < 0 || src_x >= maxx || src_y >= maxy )
                {
                    iDstBlock->SetPixelValue( x, y, fallback );
                }
                else
                {
                    iDstBlock->SetPixelProxy( x, y, iSrcBlock->PixelProxy( src_x, src_y ) );
                }
            }
        }
    }
};


/////////////////////////////////////////////////////
// TBlockTransformer_Linear
template< uint32 _SH >
class TBlockTransformer_Linear
{
public:
    static void Run( const TBlock< _SH >*        iSrcBlock
                   , TBlock< _SH >*              iDstBlock
                   , const glm::mat3&            iInverseTransform
                   , const FPerformanceOptions&  iPerformanceOptions= FPerformanceOptions() )
    {
        if( iPerformanceOptions.desired_workers > 1 )
        {
            TBlockTransformer_Linear_ScanLine< _SH >::Run( iSrcBlock, iDstBlock, iInverseTransform );
        }
        else
        {
            TBlockTransformer_Linear_MonoThread< _SH >::Run( iSrcBlock, iDstBlock, iInverseTransform );
        }
    }
};

} // namespace ULIS

