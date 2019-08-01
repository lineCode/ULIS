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
#include <cmath>

namespace ULIS {


/////////////////////////////////////////////////////
// FRect
struct FRect
{
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

    int x;
    int y;
    int w;
    int h;

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
    FPoint()
        : x( 0 )
        , y( 0 )
    {}

    FPoint( int iX, int iY )
        : x( iX )
        , y( iY )
    {}
    
    FPoint RotateAround( FPoint pivotPoint, float radianRotation)
    {
        //Trigonometric direction
        double sin = -std::sin(radianRotation);
        double cos = -std::cos(radianRotation);
        
        x -= pivotPoint.x;
        y -= pivotPoint.y;
        
        return FPoint( ( x * cos - y * sin ) + pivotPoint.x, ( x * sin + y * cos ) + pivotPoint.y );
    }

    int x;
    int y;
};

} // namespace ULIS

