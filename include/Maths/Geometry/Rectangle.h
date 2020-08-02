// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Rect.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TRectangle class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry/Vector.h"
#include "Maths/Geometry/Vector.h"
#include "Maths/Maths.h"
#include <cmath>

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TRectangle
/// @brief      The TRectangle class provides a simple 2D rectangle class for box
///             geometry applications.
/// @details    The TRectangle class is a template class that provides basic 2D
///             rectangle functionnalities, it can be used with any numeric
///             types, ranging from integer values to floating point values.
///
///             The rectangle representation is stored as x, y, w, h.
template< typename T >
struct TRectangle
{
    /*! The x coordinate of the rectangle. */
    T x;
    /*! The y coordinate of the rectangle. */
    T y;
    /*! The width of the rectangle. */
    T w;
    /*! The height of the rectangle. */
    T h;

    /*! Default constructor, initializes values to zero. */
    TRectangle()
        : x( 0 )
        , y( 0 )
        , w( 0 )
        , h( 0 )
    {}

    /*! Constructor, from input values. */
    TRectangle( T iX, T iY, T iW, T iH )
        : x( iX )
        , y( iY )
        , w( iW )
        , h( iH )
    {}

    /*! Static named maker from input values. */
    static TRectangle FromXYWH( T iX, T iY, T iW, T iH ) {
        return  TRectangle( iX, iY, iW, iH );
    }

    /*! Static named maker from min max input values. */
    static TRectangle FromMinMax( T iXMin, T iYMin, T iXMax, T iYMax ) {
        return  TRectangle( iXMin, iYMin, iXMax - iXMin, iYMax - iYMin );
    }

    /*! Collision test with TVector2. */
    bool HitTest( const TVector2< T >& iV ) {
        return  iV.x >= x
            &&  iV.y >= y
            &&  iV.x <  (x + h )
            &&  iV.y <  ( y + h );
    }

    /*! Vertical collision test with y coordinate value. */
    template< class T >
    bool InVerticalRange( T iV ) {
        return  iV >= y
            &&  iV <  ( y + h );
    }

    /*! Horizontal collision test with x coordinate value. */
    template< class T >
    bool InHorizontalRange( T iV ) {
        return  iV >= x
            &&  iV <  ( x + w );
    }

    /*! Compute intersection of this Rect with input Rect and return result Rect. */
    TRectangle operator&( const TRectangle& iOther ) const {
        T x1 = FMaths::Max( x, iOther.x );
        T y1 = FMaths::Max( y, iOther.y );
        T x2 = FMaths::Min( x + w, iOther.x + iOther.w );
        T y2 = FMaths::Min( y + h, iOther.y + iOther.h );
        return  FromMinMax( x1, y1, x2, y2 );
    }

    /*! Compute union of this Rect with input Rect and return result Rect. */
    TRectangle operator|( const TRectangle& iOther ) const {
        T x1 = FMaths::Min( x, iOther.x );
        T y1 = FMaths::Min( y, iOther.y );
        T x2 = FMaths::Max( x + w, iOther.x + iOther.w );
        T y2 = FMaths::Max( y + h, iOther.y + iOther.h );
        return  FromMinMax( x1, y1, x2, y2 );
    }

    /*! Compute exclude of this Rect with input Rect and return result Rect. */
    TRectangle operator-( const TRectangle& iOther ) const {
        TRectangle inter = *this & iOther;
        if( inter.Area() == 0 )
            return  *this;

        if( inter == *this )
            return  TRectangle();

        T x1  = x;
        T y1  = y;
        T x2  = x + w;
        T y2  = y + h;
        T ux1 = inter.x;
        T uy1 = inter.y;
        T ux2 = inter.x + inter.w;
        T uy2 = inter.y + inter.h;

        TRectangle sides[4] = { FromMinMax( ux1, y1, ux2, uy1 )      // top
                         , FromMinMax( x1, uy1, ux1, uy2 )      // left
                         , FromMinMax( ux2, uy1, x2, uy2 )      // right
                         , FromMinMax( ux1, uy2, ux2, y2 ) };   // bot

        std::vector< TRectangle* > vec;
        for( int i = 0; i < 4; ++i )
            if( sides[i].Area() )
                vec.push_back( &sides[i] );

        TRectangle res = *vec[0];
        for( int i = 1; i < vec.size(); ++i )
            res = res | *vec[i];

        return  res;
    }

    /*! Compute union of this Rect with input Rect and return result Rect, with safeguards for empty rects */
    TRectangle UnionLeaveEmpty( const TRectangle& iOther ) const {
        if( Area() == 0 )
            return iOther;

        if( iOther.Area() == 0 )
            return  *this;

        return  *this | iOther;
    }

    /*! Strict equality comparison. */
    bool operator==( const TRectangle& iOther ) const {
        return  ( x == iOther.x && y == iOther.y && w == iOther.w && h == iOther.h );
    }

    /*! Return the area of the rect. */
    T Area() const {
        return  w * h;
    }

    /*! Sanitize the Rect by setting negative sizes to zero. */
    void Sanitize() {
        if( h < 0 )
            h = 0;

        if( w < 0 )
            w = 0;
    }

    /*! Return the sanitized version of this rect. */
    TRectangle Sanitized() {
        TRectangle ret = *this;
        ret.Sanitize();
        return  ret;
    }

    /*! Affine transform this rect by input transform ( AABB ). */
    void TransformAffine( const FTransform2D& iTransform ) {
        float src_x2 = static_cast< float >( x + w );
        float src_y2 = static_cast< float >( y + h );
        const FMat3F& mat = iTransform.Matrix();
        FVec3F m00 = mat * FVec3F( x, y, 1 );
        FVec3F m10 = mat * FVec3F( src_x2, y, 1 );
        FVec3F m11 = mat * FVec3F( src_x2, src_y2, 1 );
        FVec3F m01 = mat * FVec3F( x, src_y2, 1 );
        x = static_cast< T >( FMaths::RoundToNegativeInfinity( FMaths::Min4( m00.x, m10.x, m11.x, m01.x ) ) );
        y = static_cast< T >( FMaths::RoundToNegativeInfinity( FMaths::Min4( m00.y, m10.y, m11.y, m01.y ) ) );
        w = static_cast< T >( FMaths::RoundToPositiveInfinity( FMaths::Max4( m00.x, m10.x, m11.x, m01.x ) ) ) - x;
        h = static_cast< T >( FMaths::RoundToPositiveInfinity( FMaths::Max4( m00.y, m10.y, m11.y, m01.y ) ) ) - y;
    }

    /*! Perspective transform this rect by input transform ( AABB ). */
    void TransformPerspective( const FTransform2D& iTransform ) {
        float x1 = static_cast< float >( x );
        float y1 = static_cast< float >( y );
        float x2 = static_cast< float >( x + w );
        float y2 = static_cast< float >( y + h );
        const FMat3F& mat = iTransform.Matrix();
        FVec2F A = HomographyTransform( FVec2F( x1, y1 ), mat );
        FVec2F B = HomographyTransform( FVec2F( x2, y1 ), mat );
        FVec2F C = HomographyTransform( FVec2F( x2, y2 ), mat );
        FVec2F D = HomographyTransform( FVec2F( x1, y2 ), mat );
        x = static_cast< T >( FMaths::RoundToNegativeInfinity( FMaths::Min4( A.x, B.x, C.x, D.x ) ) );
        y = static_cast< T >( FMaths::RoundToNegativeInfinity( FMaths::Min4( A.y, B.y, C.y, D.y ) ) );
        w = static_cast< T >( FMaths::RoundToPositiveInfinity( FMaths::Max4( A.x, B.x, C.x, D.x ) ) ) - x;
        h = static_cast< T >( FMaths::RoundToPositiveInfinity( FMaths::Max4( A.y, B.y, C.y, D.y ) ) ) - y;
    }

    /*! Return the affine transformed version of this rect ( AABB ). */
    TRectangle TransformedAffine( const FTransform2D& iTransform ) const {
        TRectangle result = *this;
        result.TransformAffine( iTransform );
        return  ret;
    }

    /*! Return the perspective transformed version of this rect ( AABB ). */
    TRectangle TransformedPerspective( const FTransform2D& iTransform ) const {
        TRectangle result = *this;
        result.TransformPerspective( iTransform );
        return  ret;
    }

    /*! Shift x and y coordinates by input vector. */
    void Shift( const TVector2< T >& iVec ) {
        x += iVec.x;
        y += iVec.y;
    }

    /*! Get x and y coordinates as vector. */
    TVector2< T > GetShift() const {
        return  TVector2< T >( x, y );
    }
};

ULIS_NAMESPACE_END

