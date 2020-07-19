// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Vec3.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TVec3 class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include <cmath>

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TVec3
/// @brief      The TVec3 class provides a simple 3D vector class for vector
///             geometry applications.
/// @details    The TVec3 class is a template class that provides basic 3D
///             vector functionnalities, it can be used with any numeric types,
///             ranging from integer values to floating point values.
template< typename T >
struct TVec3
{
    /*! The x component of the 3D vector. */
    T x;
    /*! The y component of the 3D vector. */
    T y;
    /*! The z component of the 3D vector. */
    T z;

    /*! Construct the vector with default zero values. */
    TVec3()
        : x( 0 )
        , y( 0 )
        , z( 0 )
    {}

    /*! Construct the vector from input value ( both x and y will have value iValue ) */
    TVec3( T iValue )
        : x( iValue )
        , y( iValue )
        , z( iValue )
    {}

    /*! Construct the vector from input values. */
    TVec3( T iX, T iY, T iZ )
        : x( iX )
        , y( iY )
        , z( iZ )
    {}

    /*! Construct the vector from input vector of any convertible type. */
    template< typename U >
    TVec3( const TVec3< U >& iOther )
        : x( static_cast< T >( iOther.x ) )
        , y( static_cast< T >( iOther.y ) )
        , z( static_cast< T >( iOther.z ) )
    {}

    /*! Return the euclidean distance of the vector. */
    ULIS3_FORCEINLINE T Distance() const {
        return  sqrt( x * x + y *y + z * z );
    }

    /*!
    Return the squared euclidean distance of the vector.
    This can be useful for testing against another squared distance, thus
    saving a square root calculation.
    */
    ULIS3_FORCEINLINE T DistanceSquared() const {
        return  x * x + y * y + z * z;
    }

    /*! Return the manhattan distance of the vector. ( abs( x ) + abs( y ) + abs( z ) ) */
    ULIS3_FORCEINLINE T ManhattanDistance() const {
        return  abs( x ) + abs( y ) + abs( z );
    }

    /*! Return the dot product of the vector */
    ULIS3_FORCEINLINE T DotProduct( const TVec3& iOther ) const {
        return  x * iOther.x + y * iOther.y + z * iOther.z;
    }

    /*! Alias for the dot product of the vector */
    ULIS3_FORCEINLINE T operator|( const TVec3& iOther ) const {
        return  DotProduct( iOther );
    }

    /*! Add the input vector to this vector and return the summed vector */
    ULIS3_FORCEINLINE TVec3 operator+( const TVec3& iOther ) const {
        return  TVec3( x + iOther.x, y + iOther.y, z + iOther.z );
    }

    /*! Substract the input vector to this vector and return the difference vector */
    ULIS3_FORCEINLINE TVec3 operator-(const TVec3& iOther ) const {
        return  TVec3( x - iOther.x, y - iOther.y, z - iOther.z );
    }

    /*! Substract the input value to this vector and return the difference vector */
    ULIS3_FORCEINLINE TVec3 operator-( T iValue ) const {
        return  TVec3( x - iValue, y - iValue, z - iValue );
    }

    /*! Add the input value to this vector and return the summed vector */
    ULIS3_FORCEINLINE TVec3 operator+( T iValue ) const {
        return  TVec3( x + iValue, y + iValue, z + iValue );
    }

    /*! Multiply this vector by the input value and return the result vector */
    ULIS3_FORCEINLINE TVec3 operator*( T iValue ) const {
        return  TVec3( x * iValue, y * iValue, z * iValue );
    }

    /*! Divide this vector by the input value and return the result vector */
    ULIS3_FORCEINLINE TVec3 operator/( T iValue ) const {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        return  TVec3( x / iValue, y / iValue, z / iValue );
    }

    /*! Compute modulo of this vector by the input value and return the result vector */
    ULIS3_FORCEINLINE TVec3 operator%( T iValue ) const {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        return  TVec3( x % iValue, y % iValue, z % iValue );
    }

    /*! Multiply this vector by the input vector and return the result vector */
    ULIS3_FORCEINLINE TVec3 operator*(const TVec3& iOther ) const {
        return  TVec3( x * iOther.x, y * iOther.y, z * iOther.z );
    }

    /*! Divide this vector by the input vector and return the result vector */
    ULIS3_FORCEINLINE TVec3 operator/(const TVec3& iOther ) const {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.z != static_cast< T >( 0 ), "Division by zero" );
        return  TVec3( x / iOther.x, y / iOther.y, z / iOther.z );
    }

    /*! Compute modulo of this vector by the input vector and return the result vector */
    ULIS3_FORCEINLINE TVec3 operator%(const TVec3& iOther ) const {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.z != static_cast< T >( 0 ), "Division by zero" );
        return  TVec3( x % iOther.x, y % iOther.y, z % iOther.z );
    }

    /*! Compare this vector to the other vector for strict equality. */
    ULIS3_FORCEINLINE bool operator==(const TVec3& iOther ) const {
        return  x == iOther.x && y == iOther.y && z == iOther.z;
    }

    /*! Compare this vector to the other vector for strict inequality. */
    ULIS3_FORCEINLINE bool operator!=(const TVec3& iOther ) const {
        return  x != iOther.x || y != iOther.y || z != iOther.z;
    }

    /*! Return the unary negative version of this vector. */
    ULIS3_FORCEINLINE TVec3 operator-() const {
        return  TVec3( -x, -y, -z );
    }

    /*! Add the input to this vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec3& operator+=(const TVec3& iOther ) {
        x += iOther.x;
        y += iOther.y;
        z += iOther.z;
        return  *this;
    }

    /*! Substract the input to this vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec3& operator-=(const TVec3& iOther ) {
        x -= iOther.x;
        y -= iOther.y;
        z -= iOther.z;
        return  *this;
    }

    /*! Multiply this vector by the input value and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec3& operator*=(T iValue) {
        x *= iValue;
        y *= iValue;
        z *= iValue;
        return  *this;
    }

    /*! Divide this vector by the input value and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec3& operator/=(T iValue ) {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        x /= iValue;
        y /= iValue;
        z /= iValue;
        return  *this;
    }

    /*! Compute modulo of this vector by the input value and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec3& operator%=(T iValue ) {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        x %= iValue;
        y %= iValue;
        z %= iValue;
        return  *this;
    }

    /*! Multiply this vector by the input vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec3& operator*=(const TVec3& iOther ) { 
        x *= iOther.x;
        y *= iOther.y;
        z *= iOther.z;
        return  *this;
    }

    /*! Divide this vector by the input vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec3& operator/=(const TVec3& iOther ) {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.z != static_cast< T >( 0 ), "Division by zero" );
        x /= iOther.x;
        y /= iOther.y;
        z /= iOther.z;
        return  *this;
    }

    /*! Compute modulo of this vector by the input vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec3& operator%=(const TVec3& iOther ) {
        ULIS3_ASSERT( iOther.x != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.y != static_cast< T >( 0 ), "Division by zero" );
        ULIS3_ASSERT( iOther.z != static_cast< T >( 0 ), "Division by zero" );
        x %= iOther.x;
        y %= iOther.y;
        z %= iOther.z;
        return  *this;
    }

    /*! Access component x or y by index, return a reference to the component. */
    ULIS3_FORCEINLINE T& operator[](int32 iIndex ) {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < 3, "Bad Index" );
        return  ( &x )[ iIndex ];
    }

    /*! Access component x or y by index, return a const reference to the component. */
    ULIS3_FORCEINLINE const T& operator[]( int32 iIndex) const {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < 3, "Bad Index" );
        return  ( &x )[ iIndex ];
    }

    /*! Normalize this vector. */
    ULIS3_FORCEINLINE const TVec2& Normalize() {
        T dist = Distance();
        ULIS3_ASSERT( dist != static_cast< T >( 0 ), "Division by zero" );
        x /= dist;
        y /= dist;
        z /= dist;
        return  *this
    }

    /*! Return the normalized version of this vector. */
    ULIS3_FORCEINLINE TVec3 Normalized() const {
        TVec3 r = *this;
        r.Normalize();
        return  r;
    }

    /*! Return the cross product of this vector with another vector. */
    ULIS3_FORCEINLINE TVec3 CrossProduct( const TVec3& iOther ) const {
        return  TVec3( y * iOther.z - z * iOther.y
                     , z * iOther.x - x * iOther.z
                     , x * iOther.y - y * iOther.x );
    }

    /*! Alias for the cross product of the vector */
    ULIS3_FORCEINLINE T operator^( const TVec3& iOther ) const {
        return  CrossProduct( iOther );
    }

};

ULIS3_NAMESPACE_END

