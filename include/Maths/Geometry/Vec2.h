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
    T x;
    T y;

    TVec2()
        : x( 0 )
        , y( 0 )
    {}

    TVec2( T iValue )
        : x( iValue )
        , y( iValue )
    {}

    TVec2( T iX, T iY )
        : x( iX )
        , y( iY )
    {}

    template< typename U >
    TVec2( U iX, U iY )
        : x( static_cast< T >( iX ) )
        , y( static_cast< T >( iY ) )
    {}

    template< typename U >
    TVec2( const TVec2< U >& iOther )
        : x( static_cast< T >( iOther.x ) )
        , y( static_cast< T >( iOther.y ) )
    {}

    ULIS3_FORCEINLINE T Distance() const {
        return  sqrt( x * x + y *y );
    }

    ULIS3_FORCEINLINE T DistanceSquared() const {
        return  x * x + y * y;
    }

    ULIS3_FORCEINLINE T ManhattanDistance() const {
        return  x + y;
    }

    ULIS3_FORCEINLINE T DotProduct( const TVec2& iOther ) {
        return  x * iOther.x + y * iOther.y;
    }

    ULIS3_FORCEINLINE T operator|( const TVec2& iOther ) const {
        return  ( *this | iOther );
    }

    ULIS3_FORCEINLINE TVec2 operator+( const TVec2& iOther ) const {
        return  TVec2( x + iOther.x, y + iOther.y );
    }

    ULIS3_FORCEINLINE TVec2 operator-(const TVec2& iOther ) const {
        return  TVec2( x - iOther.x, y - iOther.y );
    }

    ULIS3_FORCEINLINE TVec2 operator-( T iValue ) const {
        return  TVec2( x - iValue, y - iValue );
    }

    ULIS3_FORCEINLINE TVec2 operator+( T iValue ) const {
        return  TVec2( x + iValue, y + iValue );
    }

    ULIS3_FORCEINLINE TVec2 operator*( T iValue ) const {
        return  TVec2( x * iValue, y * iValue );
    }

    ULIS3_FORCEINLINE TVec2 operator/( T iValue ) const {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        return  TVec2( x / iValue, y / iValue );
    }

    ULIS3_FORCEINLINE TVec2 operator%( T iValue ) const {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        return  TVec2( x % iValue, y % iValue );
    }

    ULIS3_FORCEINLINE TVec2 operator*(const TVec2& iOther ) const {
        return  TVec2( x * iOther.x, y * iOther.y );
    }

    ULIS3_FORCEINLINE TVec2 operator/(const TVec2& iOther ) const {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        return  TVec2( x / iOther.x, y / iOther.y );
    }

    ULIS3_FORCEINLINE TVec2 operator%(const TVec2& iOther ) const {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        return  TVec2( x % iOther.x, y % iOther.y );
    }

    ULIS3_FORCEINLINE bool operator==(const TVec2& iOther ) const {
        return  x == iOther.x && y == iOther.y;
    }

    ULIS3_FORCEINLINE bool operator!=(const TVec2& iOther ) const {
        return  x != iOther.x || y != iOther.y;
    }

    ULIS3_FORCEINLINE TVec2 operator-() const {
        return  TVec2( -x, -y );
    }

    ULIS3_FORCEINLINE TVec2 operator+=(const TVec2& iOther ) {
        x += iOther.x;
        y += iOther.y;
        return  *this;
    }

    ULIS3_FORCEINLINE TVec2 operator-=(const TVec2& iOther ) {
        x -= iOther.x;
        y -= iOther.y;
        return  *this;
    }

    ULIS3_FORCEINLINE TVec2 operator*=(T iValue) {
        x *= iValue;
        y *= iValue;
        return  *this;
    }

    ULIS3_FORCEINLINE TVec2 operator/=(T iValue ) {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        x /= iValue;
        y /= iValue;
        return  *this;
    }

    ULIS3_FORCEINLINE TVec2 operator%=(T iValue ) {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        x %= iValue;
        y %= iValue;
        return  *this;
    }

    ULIS3_FORCEINLINE TVec2 operator*=(const TVec2& iOther ) { 
        x *= iOther.x; y *= iOther.y;
        return  *this;
    }

    ULIS3_FORCEINLINE TVec2 operator/=(const TVec2& iOther ) { 
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        x /= iOther.x;
        y /= iOther.y;
        return  *this;
    }

    ULIS3_FORCEINLINE TVec2 operator%=(const TVec2& iOther ) { 
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        x %= iOther.x;
        y %= iOther.y;
        return  *this;
    }

    ULIS3_FORCEINLINE T& operator[](int32 iIndex ) {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < 2, "Bad Index" );
        return  ( &x )[ iIndex ];
    }

    ULIS3_FORCEINLINE T operator[]( int32 iIndex) const {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < 2, "Bad Index" );
        return  ( &x )[ iIndex ];
    }

    ULIS3_FORCEINLINE void Normalize() {
        T dist = Distance();
        ULIS3_ASSERT( dist != static_cast< T >( 0 ), "Division by zero" );
        x /= dist;
        y /= dist;
    }
};

ULIS3_NAMESPACE_END

