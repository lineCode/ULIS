/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Maths.Geometry.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/
#pragma once
#include "ULIS/Maths/ULIS.Maths.Utility.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <vector>

namespace ULIS {
/////////////////////////////////////////////////////
// FRect
struct FRect
{
    int x;
    int y;
    int w;
    int h;


    FRect()
        : x( 0 )
        , y( 0 )
        , w( 0 )
        , h( 0 )
    {}


    FRect( int iX, int iY, int iW, int iH )
        : x( iX )
        , y( iY )
        , w( iW )
        , h( iH )
    {}


    FRect operator&( const FRect& iOther ) const
    {
        int x1 = FMath::Max( x, iOther.x );
        int y1 = FMath::Max( y, iOther.y );
        int x2 = FMath::Min( x + w, iOther.x + iOther.w );
        int y2 = FMath::Min( y + h, iOther.y + iOther.h );
        return  FRect( x1, y1, x2 - x1, y2 - y1 );
    }


    int Area() const
    {
        return  w * h;
    }

};


/////////////////////////////////////////////////////
// FPoint
struct FPoint
{
    int x;
    int y;


    FPoint()
        : x( 0 )
        , y( 0 )
    {}


    FPoint( int iX, int iY )
        : x( iX )
        , y( iY )
    {}


    FPoint RotateAround( FPoint pivotPoint, double radianRotation)
    {
        //Trigonometric direction
        double sin = -std::sin(radianRotation);
        double cos = -std::cos(radianRotation);
        
        x -= pivotPoint.x;
        y -= pivotPoint.y;
        
        return FPoint( ( x * cos - y * sin ) + pivotPoint.x, ( x * sin + y * cos ) + pivotPoint.y );
    }


    //Give the symmetric of the point through the axis of equation ax + b = y
    FPoint AxialSymmetry( float a, float b )
    {
        float d = ( x + ( y - b ) * a ) / ( 1 + a * a );
        return FPoint( 2 * d - x,
                       2 * d * a - y + 2 * b );
    }

};


/////////////////////////////////////////////////////
// FPoint64 bits
struct FPoint64
{
    int64 x;
    int64 y;


    FPoint64()
        : x( 0 )
        , y( 0 )
    {}


    FPoint64( int64 iX, int64 iY )
        : x( iX )
        , y( iY )
    {}


    FPoint64 RotateAround( FPoint pivotPoint, double radianRotation)
    {
        //Trigonometric direction
        double sin = -std::sin(radianRotation);
        double cos = -std::cos(radianRotation);
        
        x -= pivotPoint.x;
        y -= pivotPoint.y;
        
        return FPoint64( ( x * cos - y * sin ) + pivotPoint.x, ( x * sin + y * cos ) + pivotPoint.y );
    }


    //Give the symmetric of the point through the axis of equation ax + b = y
    FPoint64 AxialSymmetry( float a, float b )
    {
        float d = ( x + ( y - b ) * a ) / ( 1 + a * a );
        return FPoint64( 2 * d - x,
                         2 * d * a - y + 2 * b );
    }

};

/////////////////////////////////////////////////////
// FTransformBoundingBox
// A rectangle used to preview the transformation bounding box result
// Used for precomputation and allocation before actual transforms
struct FTransformBoundingBox
{
    FTransformBoundingBox( float iX1, float iY1, float iX2, float iY2 )
        : x1( iX1 )
        , y1( iY1 )
        , x2( iX2 )
        , y2( iY2 )
    {
    }


    FTransformBoundingBox( const  std::vector< glm::vec2 >& iPoints )
    {
        SetPoints( iPoints );
    }


    void GetPoints( std::vector< glm::vec2 >* oPoints ) const
    {
        oPoints->clear();
        oPoints->push_back( glm::vec2( x1, y1 ) );
        oPoints->push_back( glm::vec2( x2, y1 ) );
        oPoints->push_back( glm::vec2( x2, y2 ) );
        oPoints->push_back( glm::vec2( x1, y2 ) );
    }


    void GetPoints( std::vector< glm::vec3 >* opoints ) const
    {
        // For glm mat operations and translation operations, points have to be vec3
        // because we multiply with mat3
        // Z is always 1, this is relevant and very important
        // otherwise translation have no effect
        // Pretty much like homogeneous coordinates
        opoints->clear();
        opoints->push_back( glm::vec3( x1, y1, 1.f ) );
        opoints->push_back( glm::vec3( x2, y1, 1.f ) );
        opoints->push_back( glm::vec3( x2, y2, 1.f ) );
        opoints->push_back( glm::vec3( x1, y2, 1.f ) );
    }


    void SetPoints( const std::vector< glm::vec2 >& points )
    {
        assert( points.size() == 4 );
        x1 = FMath::Min( points[0].x, FMath::Min3( points[1].x, points[2].x, points[3].x ) );
        y1 = FMath::Min( points[0].y, FMath::Min3( points[1].y, points[2].y, points[3].y ) );
        x2 = FMath::Max( points[0].x, FMath::Max3( points[1].x, points[2].x, points[3].x ) );
        y2 = FMath::Max( points[0].y, FMath::Max3( points[1].y, points[2].y, points[3].y ) );
    }


    void SetPoints( const std::vector< glm::vec3 >& points )
    {
        assert( points.size() == 4 );
        x1 = FMath::RoundAwayFromZero( FMath::Min( points[0].x, FMath::Min3( points[1].x, points[2].x, points[3].x ) ) );
        y1 = FMath::RoundAwayFromZero( FMath::Min( points[0].y, FMath::Min3( points[1].y, points[2].y, points[3].y ) ) );
        x2 = FMath::RoundAwayFromZero( FMath::Max( points[0].x, FMath::Max3( points[1].x, points[2].x, points[3].x ) ) );
        y2 = FMath::RoundAwayFromZero( FMath::Max( points[0].y, FMath::Max3( points[1].y, points[2].y, points[3].y ) ) );
    }


    void Transform( const glm::mat3& mat )
    {
        std::vector< glm::vec3 > src_points;
        std::vector< glm::vec3 > dst_points;
        GetPoints( &src_points );
        // We compute result points by multiplicating mat with vec3s
        // It is important that mat is on the left-hand side
        // because glm mats are column major.
        dst_points.push_back( mat * src_points[0] );
        dst_points.push_back( mat * src_points[1] );
        dst_points.push_back( mat * src_points[2] );
        dst_points.push_back( mat * src_points[3] );
        SetPoints( dst_points );
    }

    float Width() const { return x2 - x1; }
    float Height() const { return y2 - y1; }

    void FitInPositiveRange()
    {
        x2 -= x1;
        y2 -= y1;
        x1 = 0;
        y1 = 0;
    }

    float x1, y1, x2, y2;
};

} // namespace ULIS

