// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Geometry.h
* @author       Clement Berthaud
* @brief        This file provides geometry class declarations.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include <cmath>

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FRect
struct ULIS3_API FRect
{
    int x;
    int y;
    int w;
    int h;

    FRect();
    FRect( int ix, int iy, int iW, int iH );
    static FRect FromXYWH( int ix, int iy, int iW, int iH );
    static FRect FromMinMax( int ixMin, int iyMin, int ixMax, int iyMax );

    template< class T >
    bool HitTest( const TVec2< T >& iV ) {
        return  iV.x >= static_cast< T >( x )
            &&  iV.x <  static_cast< T >( x + h )
            &&  iV.y >= static_cast< T >( y )
            &&  iV.y <  static_cast< T >( y + h );
    }

    template< class T >
    bool InVerticalRange( T iV ) {
        return  iV >= static_cast< T >( y )
            &&  iV <  static_cast< T >( y + h );
    }

    template< class T >
    bool InHorizontalRange( T iV ) {
        return  iV >= static_cast< T >( x )
            &&  iV <  static_cast< T >( x + w );
    }

    FRect operator&( const FRect& iOther ) const;
    FRect operator|( const FRect& iOther ) const;
    FRect operator-( const FRect& iOther ) const;
    FRect UnionLeaveEmpty( const FRect& iOther ) const;
    bool operator==( const FRect& iOther ) const;
    int Area() const;
    void Sanitize();
    FRect Sanitized();
    void TransformAffine( const FTransform2D& iTransform );
    void TransformPerspective( const FTransform2D& iTransform );
    FRect TransformedAffine( const FTransform2D& iTransform ) const;
    FRect TransformedPerspective( const FTransform2D& iTransform ) const;
    void FitInPositiveRange();
    void Shift( const FVec2I& iVec );
    FVec2I GetShift() const;
};

ULIS3_NAMESPACE_END

