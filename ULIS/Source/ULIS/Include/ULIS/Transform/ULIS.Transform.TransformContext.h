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
#include "ULIS/ULIS.Config.h"
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerformanceOptions.h"
#include "ULIS/Transform/ULIS.Transform.ResamplingMethods.h"
#include "ULIS/Transform/ULIS.Transform.BlockTransformer.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Make/ULIS.Make.MakeContext.h"
#include "ULIS/Maths/ULIS.Maths.Geometry.h"
#include "ULIS/Maths/ULIS.Maths.Utility.h"
#include <glm/matrix.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <assert.h>

namespace ULIS {
/////////////////////////////////////////////////////
// TTransformContext
class TTransformContext
{
public:
    template< uint32 _SH >
    static  TBlock< _SH >*  GetTransformedBlock( const TBlock< _SH >* iSrc, const  glm::mat3& iMat, eResamplingMethod iResamplingMethod = eResamplingMethod::kLinear, const FPerformanceOptions& iPerformanceOptions = FPerformanceOptions() )
    {
        // TEST
        {
            FTransformOBB obb( 0, 0, iSrc->Width(), iSrc->Height() );
            obb.Transform( iMat );
            FTransformAABB aabb( obb );
            glm::vec2 shift = aabb.GetShift();
            obb.Shift( shift );
            glm::mat3 translatedTransformMatrix = glm::translate( glm::identity< glm::mat3 >(), glm::vec2( shift ) ) * iMat;
            glm::mat3 inverseTransform = glm::inverse( translatedTransformMatrix );
            TBlock< _SH >* dst = new TBlock< _SH >( FMath::Ceil( aabb.Width() ), FMath::Ceil( aabb.Height() ) );
            std::vector< glm::vec2 > points;
            std::vector< glm::vec2 > pointsLeft;
            std::vector< glm::vec2 > pointsRight;
            points.reserve( 4 );
            pointsLeft.reserve( 3 );
            pointsRight.reserve( 3 );
            obb.GetPoints( &points );
            sort( points.begin(), points.end(), SortCompareLesserX );
            pointsLeft.push_back( points[0] );
            pointsLeft.push_back( points[1] );
            pointsRight.push_back( points[2] );
            pointsRight.push_back( points[3] );
            sort( pointsLeft.begin(), pointsLeft.end(), SortCompareLesserY );
            sort( pointsRight.begin(), pointsRight.end(), SortCompareLesserY );
            if( pointsLeft[0].y > pointsRight[0].y ) pointsLeft.push_back( pointsRight[0] );
            if( pointsLeft[1].y < pointsRight[1].y ) pointsLeft.push_back( pointsRight[1] );
            if( pointsRight[0].y > pointsLeft[0].y ) pointsRight.push_back( pointsLeft[0] );
            if( pointsRight[1].y < pointsLeft[1].y ) pointsRight.push_back( pointsLeft[1] );
            sort( pointsLeft.begin(), pointsLeft.end(), SortCompareLesserY );
            sort( pointsRight.begin(), pointsRight.end(), SortCompareLesserY );

            std::vector< FLinef > linesLeft;
            for( int i = 0; i < pointsLeft.size() - 1; ++i )
            {
                float dx = ( pointsLeft[i+1].x - pointsLeft[i].x );
                float slope, add;
                if( dx == 0 )
                {
                    slope = 0;
                    add = pointsLeft[i].x;
                }
                else
                {
                    float dy = ( pointsLeft[i+1].y - pointsLeft[i].y );
                    slope = dx / dy;
                    add = pointsLeft[i].x - ( slope * pointsLeft[i].y );
                }
                linesLeft.push_back( FLinef( slope, add ) );
            }

            std::vector< FLinef > linesRight;
            for( int i = 0; i < pointsRight.size() - 1; ++i )
            {
                float dx = ( pointsRight[i+1].x - pointsRight[i].x );
                float slope, add;
                if( dx == 0 )
                {
                    slope = 0;
                    add = pointsRight[i].x;
                }
                else
                {
                    float dy = ( pointsRight[i+1].y - pointsRight[i].y );
                    slope = dx / dy;
                    add = pointsRight[i].x - ( slope * pointsRight[i].y );
                }
                linesRight.push_back( FLinef( slope, add ) );
            }

            auto dummy = 0;
        }

        FTransformAABB aabb( 0, 0, iSrc->Width(), iSrc->Height() );
        aabb.Transform( iMat );
        glm::vec2 shift( -aabb.x1, -aabb.y1 );
        aabb.Shift( shift );
        glm::mat3 translated = glm::translate( glm::identity< glm::mat3 >(), glm::vec2( shift ) ) * iMat;
        TBlock< _SH >* dst = new TBlock< _SH >( aabb.Width(), aabb.Height() );
        glm::mat3 inverseTransform = glm::inverse( translated );

        TBlockTransformer< _SH >::Run( iSrc, dst, inverseTransform, iResamplingMethod, iPerformanceOptions );
        return  dst;
    }

    template< uint32 _SH >
    static  void  TransformBlockInto( const TBlock< _SH >* iSrc, TBlock< _SH >* iDst, const  glm::mat3& iMat, eResamplingMethod iResamplingMethod = eResamplingMethod::kLinear , const FPerformanceOptions& iPerformanceOptions = FPerformanceOptions() )
    {
        FTransformAABB aabb( 0, 0, iSrc->Width(), iSrc->Height() );
        aabb.Transform( iMat );
        glm::vec2 shift( -aabb.x1, -aabb.y1 );
        aabb.Shift( shift );
        glm::mat3 translated = glm::translate( glm::identity< glm::mat3 >(), glm::vec2( shift ) ) * iMat;
        glm::mat3 inverseTransform = glm::inverse( translated );

        TBlockTransformer< _SH >::Run( iSrc, iDst, inverseTransform, iResamplingMethod, iPerformanceOptions );
    }
};


} // namespace ULIS

