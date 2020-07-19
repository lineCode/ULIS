// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Vec2.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TVec2 class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include <cmath>

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// TVec2
template< typename T >
struct TVec2
{
    /*! The x component of the 2D vector. */
    T x;
    /*! The y component of the 2D vector. */
    T y;

    /*! Construct the vector with default zero values. */
    TVec2()
        : x( 0 )
        , y( 0 )
    {}

    /*! Construct the vector from input value ( both x and y will have value iValue ) */
    TVec2( T iValue )
        : x( iValue )
        , y( iValue )
    {}

    /*! Construct the vector from input values. */
    TVec2( T iX, T iY )
        : x( iX )
        , y( iY )
    {}

    /*! Construct the vector from input vector of any convertible type. */
    template< typename U >
    TVec2( const TVec2< U >& iOther )
        : x( static_cast< T >( iOther.x ) )
        , y( static_cast< T >( iOther.y ) )
    {}

    /*! Return the euclidean distance of the vector. */
    ULIS3_FORCEINLINE T Distance() const {
        return  sqrt( x * x + y *y );
    }

    /*!
    Return the squared euclidean distance of the vector.
    This can be useful for testing against another squared distance, thus
    saving a square root calculation.
    */
    ULIS3_FORCEINLINE T DistanceSquared() const {
        return  x * x + y * y;
    }

    /*! Return the manhattan distance of the vector. ( abs( x ) + abs( y ) ) */
    ULIS3_FORCEINLINE T ManhattanDistance() const {
        return  abs( x ) + abs( y );
    }

    /*! Return the dot product of the vector */
    ULIS3_FORCEINLINE T DotProduct( const TVec2& iOther ) const {
        return  x * iOther.x + y * iOther.y;
    }

    /*! Alias for the dot product of the vector */
    ULIS3_FORCEINLINE T operator|( const TVec2& iOther ) const {
        return  DotProduct( iOther );
    }

    /*! Add the input vector to this vector and return the summed vector */
    ULIS3_FORCEINLINE TVec2 operator+( const TVec2& iOther ) const {
        return  TVec2( x + iOther.x, y + iOther.y );
    }

    /*! Substract the input vector to this vector and return the difference vector */
    ULIS3_FORCEINLINE TVec2 operator-(const TVec2& iOther ) const {
        return  TVec2( x - iOther.x, y - iOther.y );
    }

    /*! Substract the input value to this vector and return the difference vector */
    ULIS3_FORCEINLINE TVec2 operator-( T iValue ) const {
        return  TVec2( x - iValue, y - iValue );
    }

    /*! Add the input value to this vector and return the summed vector */
    ULIS3_FORCEINLINE TVec2 operator+( T iValue ) const {
        return  TVec2( x + iValue, y + iValue );
    }

    /*! Multiply this vector by the input value and return the result vector */
    ULIS3_FORCEINLINE TVec2 operator*( T iValue ) const {
        return  TVec2( x * iValue, y * iValue );
    }

    /*! Divide this vector by the input value and return the result vector */
    ULIS3_FORCEINLINE TVec2 operator/( T iValue ) const {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        return  TVec2( x / iValue, y / iValue );
    }

    /*! Compute modulo of this vector by the input value and return the result vector */
    ULIS3_FORCEINLINE TVec2 operator%( T iValue ) const {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        return  TVec2( x % iValue, y % iValue );
    }

    /*! Multiply this vector by the input vector and return the result vector */
    ULIS3_FORCEINLINE TVec2 operator*(const TVec2& iOther ) const {
        return  TVec2( x * iOther.x, y * iOther.y );
    }

    /*! Divide this vector by the input vector and return the result vector */
    ULIS3_FORCEINLINE TVec2 operator/(const TVec2& iOther ) const {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        return  TVec2( x / iOther.x, y / iOther.y );
    }

    /*! Compute modulo of this vector by the input vector and return the result vector */
    ULIS3_FORCEINLINE TVec2 operator%(const TVec2& iOther ) const {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        return  TVec2( x % iOther.x, y % iOther.y );
    }

    /*! Compare this vector to the other vector for strict equality. */
    ULIS3_FORCEINLINE bool operator==(const TVec2& iOther ) const {
        return  x == iOther.x && y == iOther.y;
    }

    /*! Compare this vector to the other vector for strict inequality. */
    ULIS3_FORCEINLINE bool operator!=(const TVec2& iOther ) const {
        return  x != iOther.x || y != iOther.y;
    }

    /*! Return the unary negative version of this vector. */
    ULIS3_FORCEINLINE TVec2 operator-() const {
        return  TVec2( -x, -y );
    }

    /*! Add the input to this vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec2& operator+=(const TVec2& iOther ) {
        x += iOther.x;
        y += iOther.y;
        return  *this;
    }

    /*! Substract the input to this vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec2& operator-=(const TVec2& iOther ) {
        x -= iOther.x;
        y -= iOther.y;
        return  *this;
    }

    /*! Multiply this vector by the input value and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec2& operator*=(T iValue) {
        x *= iValue;
        y *= iValue;
        return  *this;
    }

    /*! Divide this vector by the input value and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec2& operator/=(T iValue ) {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        x /= iValue;
        y /= iValue;
        return  *this;
    }

    /*! Compute modulo of this vector by the input value and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec2& operator%=(T iValue ) {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        x %= iValue;
        y %= iValue;
        return  *this;
    }

    /*! Multiply this vector by the input vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec2& operator*=(const TVec2& iOther ) { 
        x *= iOther.x; y *= iOther.y;
        return  *this;
    }

    /*! Divide this vector by the input vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec2& operator/=(const TVec2& iOther ) {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        x /= iOther.x;
        y /= iOther.y;
        return  *this;
    }

    /*! Compute modulo of this vector by the input vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec2& operator%=(const TVec2& iOther ) {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        x %= iOther.x;
        y %= iOther.y;
        return  *this;
    }

    /*! Access component x or y by index, return a reference to the component. */
    ULIS3_FORCEINLINE T& operator[](int32 iIndex ) {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < 2, "Bad Index" );
        return  ( &x )[ iIndex ];
    }

    /*! Access component x or y by index, return a const reference to the component. */
    ULIS3_FORCEINLINE const T& operator[]( int32 iIndex) const {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < 2, "Bad Index" );
        return  ( &x )[ iIndex ];
    }

    /*! Normalize this vector. */
    ULIS3_FORCEINLINE void Normalize() {
        T dist = Distance();
        ULIS3_ASSERT( dist != static_cast< T >( 0 ), "Division by zero" );
        x /= dist;
        y /= dist;
    }

    /*! Return the normalized version of this vector. */
    ULIS3_FORCEINLINE TVec2 Normalized() const {
        TVec2 r = *this;
        r.Normalize();
        return  r;
    }
};

ULIS3_NAMESPACE_END

