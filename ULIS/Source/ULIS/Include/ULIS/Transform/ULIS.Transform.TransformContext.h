/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Transform.TransformContext.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerformanceOptions.h"
#include "ULIS/Transform/ULIS.Transform.BlockTransformer.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Make/ULIS.Make.MakeContext.h"
#include "ULIS/Maths/ULIS.Maths.Geometry.h"
#include "ULIS/Maths/ULIS.Maths.Utility.h"
#include <glm/matrix.hpp>

namespace ULIS {
/////////////////////////////////////////////////////
// TTransformContext
class TTransformContext
{
public:
    template< uint32 _SH >
    static  TBlock< _SH >*  GetTransformedBlock( const TBlock< _SH >* iSrc, const  glm::mat3& iMat, const FPerformanceOptions& iPerformanceOptions = FPerformanceOptions() )
    {
        FTransformBoundingBox aabb( 0, 0, iSrc->Width(), iSrc->Height() );
        aabb.Transform( iMat );
        glm::vec2 shift( -aabb.x1, -aabb.y1 );
        TBlock< _SH >* dst = new TBlock< _SH >( aabb.Width(), aabb.Height() );
        glm::mat3 inverseTransform = glm::inverse( iMat );

        TBlockTransformer< _SH >::Run( iSrc, dst, inverseTransform, shift, iPerformanceOptions );
        return  dst;
    }
};


} // namespace ULIS

