// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Geometry.h
* @author       Clement Berthaud
* @brief        This file provides geometry class declarations.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// TVec2
template< typename T >
struct ULIS2_API TVec2
{
    T x;
    T y;

    TVec2() : x( 0 ), y( 0 ) {}
    TVec2( T iX, T iY ) : x( iX ), y( iY ) {};
};

/////////////////////////////////////////////////////
// FRect
struct ULIS2_API FRect
{
    int x;
    int y;
    int w;
    int h;

    FRect();
    FRect( int iX, int iY, int iW, int iH );
    static FRect FromXYWH( int iX, int iY, int iW, int iH );
    static FRect FromMinMax( int iXMin, int iYMin, int iXMax, int iYMax );
    FRect operator&( const FRect& iOther ) const;
    FRect operator|( const FRect& iOther ) const;
    bool operator==( const FRect& iOther ) const;
    int Area() const;
    void TransformAffine( const FTransform2D& iTransform );
    void TransformPerspective( const FTransform2D& iTransform );
    FRect TransformedAffine( const FTransform2D& iTransform ) const;
    FRect TransformedPerspective( const FTransform2D& iTransform ) const;
    void FitInPositiveRange();
    void Shift( const FVec2I& iVec );
    FVec2I GetShift() const;
};

ULIS2_NAMESPACE_END

