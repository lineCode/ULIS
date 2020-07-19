// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Vec4.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TVec4 class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry/Vec3.h"
#include <cmath>

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TVec4
/// @brief      The TVec4 class provides a simple 4D vector class for vector
///             geometry applications.
/// @details    The TVec4 class is a template class that provides basic 4D
///             vector functionnalities, it can be used with any numeric types,
///             ranging from integer values to floating point values.
template< typename T >
struct TVec4
{
    /*! The x component of the 4D vector. */
    T x;
    /*! The y component of the 4D vector. */
    T y;
    /*! The z component of the 4D vector. */
    T z;
    /*! The z component of the 4D vector. */
    T w;

    /*! Construct the vector with default zero values. */
    TVec4()
        : x( 0 )
        , y( 0 )
        , z( 0 )
        , w( 0 )
    {}

    /*! Construct the vector from input value ( both x and y will have value iValue ) */
    TVec4( T iValue )
        : x( iValue )
        , y( iValue )
        , z( iValue )
        , w( iValue )
    {}

    /*! Construct the vector from input values. */
    TVec4( T iX, T iY = 0, T iZ = 0, T iW = 0 )
        : x( iX )
        , y( iY )
        , z( iZ )
        , w( iW )
    {}

    /*! Construct the vector from TVec2. */
    TVec4( const TVec2< T >& iVec, T iZ = 0, T iW = 0 );

    /*! Construct the vector from TVec3. */
    TVec4( const TVec3< T >& iVec, T iW = 0 );

    /*! Construct the vector from input vector of any convertible type. */
    template< typename U >
    TVec4( const TVec4< U >& iOther )
        : x( static_cast< T >( iOther.x ) )
        , y( static_cast< T >( iOther.y ) )
        , z( static_cast< T >( iOther.z ) )
        , w( static_cast< T >( iOther.w ) )
    {}

    /*! Return the euclidean distance of the vector. */
    ULIS3_FORCEINLINE T Distance() const {
        return  sqrt( x * x + y *y + z * z + w * w );
    }

    /*!
    Return the squared euclidean distance of the vector.
    This can be useful for testing against another squared distance, thus
    saving a square root calculation.
    */
    ULIS3_FORCEINLINE T DistanceSquared() const {
        return  x * x + y * y + z * z + w * w;
    }

    /*! Return the manhattan distance of the vector. ( abs( x ) + abs( y ) + abs( z ) ) */
    ULIS3_FORCEINLINE T ManhattanDistance() const {
        return  abs( x ) + abs( y ) + abs( z ) + abs( w );
    }

    /*! Return the dot product of the vector */
    ULIS3_FORCEINLINE T DotProduct( const TVec4& iOther ) const {
        return  x * iOther.x + y * iOther.y + z * iOther.z + w * iOther.w;
    }

    /*! Alias for the dot product of the vector */
    ULIS3_FORCEINLINE T operator|( const TVec4& iOther ) const {
        return  DotProduct( iOther );
    }

    /*! Add the input vector to this vector and return the summed vector */
    ULIS3_FORCEINLINE TVec4 operator+( const TVec4& iOther ) const {
        return  TVec4( x + iOther.x, y + iOther.y, z + iOther.z, w + iOther.w );
    }

    /*! Substract the input vector to this vector and return the difference vector */
    ULIS3_FORCEINLINE TVec4 operator-(const TVec4& iOther ) const {
        return  TVec4( x - iOther.x, y - iOther.y, z - iOther.z, w - iOther.w );
    }

    /*! Substract the input value to this vector and return the difference vector */
    ULIS3_FORCEINLINE TVec4 operator-( T iValue ) const {
        return  TVec4( x - iValue, y - iValue, z - iValue, w - iValue );
    }

    /*! Add the input value to this vector and return the summed vector */
    ULIS3_FORCEINLINE TVec4 operator+( T iValue ) const {
        return  TVec4( x + iValue, y + iValue, z + iValue, w + iValue );
    }

    /*! Multiply this vector by the input value and return the result vector */
    ULIS3_FORCEINLINE TVec4 operator*( T iValue ) const {
        return  TVec4( x * iValue, y * iValue, z * iValue, w * iValue );
    }

    /*! Divide this vector by the input value and return the result vector */
    ULIS3_FORCEINLINE TVec4 operator/( T iValue ) const {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        return  TVec4( x / iValue, y / iValue, z / iValue, w / iValue );
    }

    /*! Compute modulo of this vector by the input value and return the result vector */
    ULIS3_FORCEINLINE TVec4 operator%( T iValue ) const {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        return  TVec4( x % iValue, y % iValue, z % iValue, w % iValue );
    }

    /*! Multiply this vector by the input vector and return the result vector */
    ULIS3_FORCEINLINE TVec4 operator*(const TVec4& iOther ) const {
        return  TVec4( x * iOther.x, y * iOther.y, z * iOther.z, w * iOther.w );
    }

    /*! Divide this vector by the input vector and return the result vector */
    ULIS3_FORCEINLINE TVec4 operator/(const TVec4& iOther ) const {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.z != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.w != static_cast< T >( 0 ), "Division by zero" );
        return  TVec4( x / iOther.x, y / iOther.y, z / iOther.z, w / iOther.w );
    }

    /*! Compute modulo of this vector by the input vector and return the result vector */
    ULIS3_FORCEINLINE TVec4 operator%(const TVec4& iOther ) const {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.z != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.w != static_cast< T >( 0 ), "Division by zero" );
        return  TVec4( x % iOther.x, y % iOther.y, z % iOther.z, w % iOther.w );
    }

    /*! Compare this vector to the other vector for strict equality. */
    ULIS3_FORCEINLINE bool operator==(const TVec4& iOther ) const {
        return  x == iOther.x && y == iOther.y && z == iOther.z && w == iOther.w;
    }

    /*! Compare this vector to the other vector for strict inequality. */
    ULIS3_FORCEINLINE bool operator!=(const TVec4& iOther ) const {
        return  x != iOther.x || y != iOther.y || z != iOther.z || w != iOther.w;
    }

    /*! Return the unary negative version of this vector. */
    ULIS3_FORCEINLINE TVec4 operator-() const {
        return  TVec4( -x, -y, -z, -w );
    }

    /*! Add the input to this vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec4& operator+=(const TVec4& iOther ) {
        x += iOther.x;
        y += iOther.y;
        z += iOther.z;
        w += iOther.w;
        return  *this;
    }

    /*! Substract the input to this vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec4& operator-=(const TVec4& iOther ) {
        x -= iOther.x;
        y -= iOther.y;
        z -= iOther.z;
        w -= iOther.w;
        return  *this;
    }

    /*! Multiply this vector by the input value and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec4& operator*=(T iValue) {
        x *= iValue;
        y *= iValue;
        z *= iValue;
        w *= iValue;
        return  *this;
    }

    /*! Divide this vector by the input value and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec4& operator/=(T iValue ) {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        x /= iValue;
        y /= iValue;
        z /= iValue;
        w /= iValue;
        return  *this;
    }

    /*! Compute modulo of this vector by the input value and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec4& operator%=(T iValue ) {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        x %= iValue;
        y %= iValue;
        z %= iValue;
        w %= iValue;
        return  *this;
    }

    /*! Multiply this vector by the input vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec4& operator*=(const TVec4& iOther ) { 
        x *= iOther.x;
        y *= iOther.y;
        z *= iOther.z;
        w *= iOther.w;
        return  *this;
    }

    /*! Divide this vector by the input vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec4& operator/=(const TVec4& iOther ) {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.z != static_cast< T >( 0 ), "Division by zero" );
        x /= iOther.x;
        y /= iOther.y;
        z /= iOther.z;
        w /= iOther.w;
        return  *this;
    }

    /*! Compute modulo of this vector by the input vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec4& operator%=(const TVec4& iOther ) {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.z != static_cast< T >( 0 ), "Division by zero" );
        x %= iOther.x;
        y %= iOther.y;
        z %= iOther.z;
        w %= iOther.w;
        return  *this;
    }

    /*! Access component x or y by index, return a reference to the component. */
    ULIS3_FORCEINLINE T& operator[](int32 iIndex ) {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < 4, "Bad Index" );
        return  ( &x )[ iIndex ];
    }

    /*! Access component x or y by index, return a const reference to the component. */
    ULIS3_FORCEINLINE const T& operator[]( int32 iIndex) const {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < 4, "Bad Index" );
        return  ( &x )[ iIndex ];
    }

    /*! Normalize this vector. */
    ULIS3_FORCEINLINE const TVec2& Normalize() {
        T dist = Distance();
        ULIS3_ASSERT( dist != static_cast< T >( 0 ), "Division by zero" );
        x /= dist;
        y /= dist;
        z /= dist;
        w /= dist;
        return  *this
    }

    /*! Return the normalized version of this vector. */
    ULIS3_FORCEINLINE TVec4 Normalized() const {
        TVec4 r = *this;
        r.Normalize();
        return  r;
    }
};

ULIS3_NAMESPACE_END

