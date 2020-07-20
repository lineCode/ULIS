// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Vec8.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TVec8 class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry/Vec3.h"
#include "Maths/Geometry/VecSwizzle.h"
#include <cmath>

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TVec8
/// @brief      The TVec8 class provides a simple 8D vector class for vector
///             geometry applications.
/// @details    The TVec8 class is a template class that provides basic 8D
///             vector functionnalities, it can be used with any numeric types,
///             ranging from integer values to floating point values.
template< typename T >
struct TVec8
{
    /*! The x component of the 8D vector. */
    T data[8];

    /*! Construct the vector with default zero values. */
    TVec8()
        : data{ 0, 0, 0, 0, 0, 0, 0, 0 }
    {}

    /*! Construct the vector from input value ( both x and y will have value iValue ) */
    TVec8( T iValue )
        : data{ iValue, iValue, iValue, iValue, iValue, iValue, iValue, iValue }
    {}

    /*! Construct the vector from input value ( both x and y will have value iValue ) */
    TVec8( T i0, T i1, T i2 = 0, T i3 = 0, T i4 = 0, T i5 = 0, T i6 = 0, T i7 = 0 )
        : data{ i0, i1, i2, i3, i4, i5, i6, i7 }
    {}

    /*! Construct the vector from input vector of any convertible type. */
    template< typename U >
    TVec8( const TVec8< U >& iOther )
        : data{ iOther.data[0], iOther.data[1], iOther.data[2], iOther.data[3], iOther.data[4], iOther.data[5], iOther.data[6], iOther.data[7], iOther.data[8] }
    {}

    /*! Return the euclidean distance of the vector. */
    ULIS3_FORCEINLINE T Distance() const {
        return  sqrt( DistanceSquared() );
    }

    /*!
    Return the squared euclidean distance of the vector.
    This can be useful for testing against another squared distance, thus
    saving a square root calculation.
    */
    ULIS3_FORCEINLINE T DistanceSquared() const {
        T sum = 0;
        for( int i = 0; i < 8; ++i )
            sum += data[i] * data[i];

        return  sum;
    }

    /*! Return the manhattan distance of the vector. ( abs( x ) + abs( y ) + abs( z ) ) */
    ULIS3_FORCEINLINE T ManhattanDistance() const {
        T sum = 0;
        for( int i = 0; i < 8; ++i )
            sum += abs( data[i] );

        return  sum;
    }

    /*! Return the dot product of the vector */
    ULIS3_FORCEINLINE T DotProduct( const TVec8& iOther ) const {
        T sum = 0;
        for( int i = 0; i < 8; ++i )
            sum += data[i] * iOther.data[i];

        return  sum;
    }

    /*! Alias for the dot product of the vector */
    ULIS3_FORCEINLINE T operator|( const TVec8& iOther ) const {
        return  DotProduct( iOther );
    }

    /*! Add the input vector to this vector and return the summed vector */
    ULIS3_FORCEINLINE TVec8 operator+( const TVec8& iOther ) const {
        TVec8 ret;
        for( int i = 0; i < 8; ++i )
            ret.data[i] = data[i] + iOther.data[i];

        return  ret;
    }

    /*! Substract the input vector to this vector and return the difference vector */
    ULIS3_FORCEINLINE TVec8 operator-(const TVec8& iOther ) const {
        TVec8 ret;
        for( int i = 0; i < 8; ++i )
            ret.data[i] = data[i] - iOther.data[i];

        return  ret;
    }

    /*! Substract the input value to this vector and return the difference vector */
    ULIS3_FORCEINLINE TVec8 operator-( T iValue ) const {
        TVec8 ret;
        for( int i = 0; i < 8; ++i )
            ret.data[i] = data[i] - iValue

        return  ret;
    }

    /*! Add the input value to this vector and return the summed vector */
    ULIS3_FORCEINLINE TVec8 operator+( T iValue ) const {
        TVec8 ret;
        for( int i = 0; i < 8; ++i )
            ret.data[i] = data[i] + iValue;

        return  ret;
    }

    /*! Multiply this vector by the input value and return the result vector */
    ULIS3_FORCEINLINE TVec8 operator*( T iValue ) const {
        return  TVec8( x * iValue, y * iValue, z * iValue, w * iValue );
    }

    /*! Divide this vector by the input value and return the result vector */
    ULIS3_FORCEINLINE TVec8 operator/( T iValue ) const {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        TVec8 ret;
        for( int i = 0; i < 8; ++i )
            ret.data[i] = data[i] / iValue;

        return  ret;
    }

    /*! Compute modulo of this vector by the input value and return the result vector */
    ULIS3_FORCEINLINE TVec8 operator%( T iValue ) const {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        TVec8 ret;
        for( int i = 0; i < 8; ++i )
            ret.data[i] = data[i] % iValue;

        return  ret;
    }

    /*! Multiply this vector by the input vector and return the result vector */
    ULIS3_FORCEINLINE TVec8 operator*(const TVec8& iOther ) const {
        TVec8 ret;
        for( int i = 0; i < 8; ++i )
            ret.data[i] = data[i] * iOther.data[i];

        return  ret;
    }

    /*! Divide this vector by the input vector and return the result vector */
    ULIS3_FORCEINLINE TVec8 operator/(const TVec8& iOther ) const {
        for( int i = 0; i < 8; ++i )
            ULIS3_ASSERT( iOther.data[i] != static_cast< T >( 0 ), "Division by zero" );

        TVec8 ret;
        for( int i = 0; i < 8; ++i )
            ret.data[i] = data[i] / iOther.data[i];

        return  ret;
    }

    /*! Compute modulo of this vector by the input vector and return the result vector */
    ULIS3_FORCEINLINE TVec8 operator%(const TVec8& iOther ) const {
        for( int i = 0; i < 8; ++i )
            ULIS3_ASSERT( iOther.data[i] != static_cast< T >( 0 ), "Division by zero" );

        TVec8 ret;
        for( int i = 0; i < 8; ++i )
            ret.data[i] = data[i] % iOther.data[i];

        return  ret;
    }

    /*! Compare this vector to the other vector for strict equality. */
    ULIS3_FORCEINLINE bool operator==(const TVec8& iOther ) const {
        for( int i = 0; i < 8; ++i )
            if( data[i] != iOther.data[i] )
                return  false;
        return  true;
    }

    /*! Compare this vector to the other vector for strict inequality. */
    ULIS3_FORCEINLINE bool operator!=(const TVec8& iOther ) const {
        return  !( (*this) == iOther );
    }

    /*! Return the unary negative version of this vector. */
    ULIS3_FORCEINLINE TVec8 operator-() const {
        TVec8 ret;
        for( int i = 0; i < 8; ++i )
            ret.data[i] = -data[i];

        return  ret;
    }

    /*! Add the input to this vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec8& operator+=(const TVec8& iOther ) {
        for( int i = 0; i < 8; ++i )
            data[i] += iOther.data[i];

        return  *this;
    }

    /*! Substract the input to this vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec8& operator-=(const TVec8& iOther ) {
        for( int i = 0; i < 8; ++i )
            data[i] -= iOther.data[i];

        return  *this;
    }

    /*! Multiply this vector by the input value and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec8& operator*=(T iValue) {
        for( int i = 0; i < 8; ++i )
            data[i] *= iValue;

        return  *this;
    }

    /*! Divide this vector by the input value and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec8& operator/=(T iValue ) {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        for( int i = 0; i < 8; ++i )
            data[i] /= iValue;

        return  *this;
    }

    /*! Compute modulo of this vector by the input value and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec8& operator%=(T iValue ) {
        ULIS3_ASSERT( iValue != static_cast< T >( 0 ), "Division by zero" );
        for( int i = 0; i < 8; ++i )
            data[i] %= iValue;

        return  *this;
    }

    /*! Multiply this vector by the input vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec8& operator*=(const TVec8& iOther ) { 
        for( int i = 0; i < 8; ++i )
            data[i] *= iOther.data[i];

        return  *this;
    }

    /*! Divide this vector by the input vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec8& operator/=(const TVec8& iOther ) {
        for( int i = 0; i < 8; ++i )
            ULIS3_ASSERT( iOther.data[i] != static_cast< T >( 0 ), "Division by zero" );

        for( int i = 0; i < 8; ++i )
            data[i] /= iOther.data[i];

        return  *this;
    }

    /*! Compute modulo of this vector by the input vector and return a reference to this vector. */
    ULIS3_FORCEINLINE TVec8& operator%=(const TVec8& iOther ) {
        for( int i = 0; i < 8; ++i )
            ULIS3_ASSERT( iOther.data[i] != static_cast< T >( 0 ), "Division by zero" );

        for( int i = 0; i < 8; ++i )
            data[i] %= iOther.data[i];

        return  *this;
    }

    /*! Access component x or y by index, return a reference to the component. */
    ULIS3_FORCEINLINE T& operator[]( int iIndex ) {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < 8, "Bad Index" );
        return  data[ iIndex ];
    }

    /*! Access component x or y by index, return a const reference to the component. */
    ULIS3_FORCEINLINE const T& operator[]( int iIndex ) const {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < 8, "Bad Index" );
        return  data[ iIndex ];
    }

    /*! Normalize this vector. */
    ULIS3_FORCEINLINE const TVec2& Normalize() {
        T dist = Distance();
        ULIS3_ASSERT( dist != static_cast< T >( 0 ), "Division by zero" );

        for( int i = 0; i < 8; ++i )
            data[i] /= dist;

        return  *this
    }

    /*! Return the normalized version of this vector. */
    ULIS3_FORCEINLINE TVec8 Normalized() const {
        TVec8 r = *this;
        r.Normalize();
        return  r;
    }

};

ULIS3_NAMESPACE_END

