// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Geometry.cpp
* @author       Clement Berthaud
* @brief        This file provides geometry class definitions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Maths/Geometry.h"
#include "Maths/Maths.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FRect
FRect::FRect()
    : x( 0 )
    , y( 0 )
    , w( 0 )
    , h( 0 )
{}


FRect::FRect( int iX, int iY, int iW, int iH )
    : x( iX )
    , y( iY )
    , w( iW )
    , h( iH )
{}

//static
FRect
FRect::FromXYWH( int iX, int iY, int iW, int iH )
{
    return  FRect( iX, iY, iW, iH );
}


//static
FRect
FRect::FromMinMax( int iXMin, int iYMin, int iXMax, int iYMax )
{
    return  FRect( iXMin, iYMin, iXMax - iXMin, iYMax - iYMin );
}


FRect
FRect::operator&( const FRect& iOther ) const
{
    int x1 = FMaths::Max( x, iOther.x );
    int y1 = FMaths::Max( y, iOther.y );
    int x2 = FMaths::Min( x + w, iOther.x + iOther.w );
    int y2 = FMaths::Min( y + h, iOther.y + iOther.h );
    return  FromMinMax( x1, y1, x2, y2 );
}


FRect
FRect::operator|( const FRect& iOther ) const
{
    int x1 = FMaths::Min( x, iOther.x );
    int y1 = FMaths::Min( y, iOther.y );
    int x2 = FMaths::Max( x + w, iOther.x + iOther.w );
    int y2 = FMaths::Max( y + h, iOther.y + iOther.h );
    return  FromMinMax( x1, y1, x2, y2 );
}
    
bool
FRect::operator==( const FRect& iOther ) const
{
    return  ( x == iOther.x && y == iOther.y && w == iOther.w && h == iOther.h );
}


int
FRect::Area() const
{
    return  w * h;
}

ULIS2_NAMESPACE_END

