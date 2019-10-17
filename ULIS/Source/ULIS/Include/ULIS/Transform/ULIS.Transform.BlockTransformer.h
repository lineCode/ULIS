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
#include "ULIS/Transform/ULIS.Transform.BlockTransformerNearestNeighbour.h"
#include "ULIS/Transform/ULIS.Transform.BlockTransformerLinear.h"

namespace ULIS {
/////////////////////////////////////////////////////
// TBlockTransformer_Default
template< uint32 _SH >
class TBlockTransformer_Default
{
public:
    static void Run( const TBlock< _SH >*        iSrcBlock
                   , TBlock< _SH >*              iDstBlock
                   , const glm::mat3&            iInverseTransform
                   , eResamplingMethod           iResamplingMethod = eResamplingMethod::kBilinear
                   , const FPerformanceOptions&  iPerformanceOptions= FPerformanceOptions() )
    {
        switch( iResamplingMethod )
        {
            case eResamplingMethod::kNearestNeighbour:
            {
                TBlockTransformer_NearestNeighbour< _SH >::Run( iSrcBlock, iDstBlock, iInverseTransform, iPerformanceOptions );
                break;
            }

            case eResamplingMethod::kBilinear:
            {
                TBlockTransformer_Linear< _SH >::Run( iSrcBlock, iDstBlock, iInverseTransform, iPerformanceOptions );
                break;
            }

            default: ULIS_CRASH_DELIBERATE;
        }
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
                          , eResamplingMethod           iResamplingMethod = eResamplingMethod::kBilinear
                          , const FPerformanceOptions&  iPerformanceOptions= FPerformanceOptions() )
    {
        TBlockTransformer_Default< _SH >::Run( iSrcBlock, iDstBlock, iInverseTransform, iResamplingMethod, iPerformanceOptions );
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
                          , eResamplingMethod           iResamplingMethod = eResamplingMethod::kBilinear
                          , const FPerformanceOptions&  iPerformanceOptions= FPerformanceOptions() )
    {
        TBlockTransformer_Imp< _SH >::Run( iSrcBlock, iDstBlock, iInverseTransform, iResamplingMethod, iPerformanceOptions );
    }
};

} // namespace ULIS

