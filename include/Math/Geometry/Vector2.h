// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Vector2.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TVector2 class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Math/Geometry/VectorFunc.h"
#include "Math/Geometry/VectorSwizzle.h"
#include "Math/Math.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TVector2
/// @brief      The TVector2 class provides a simple 2D vector class for vector
///             geometry applications.
/// @details    The TVector2 class is a template class that provides basic 2D
///             vector functionnalities, it can be used with any numeric types,
///             ranging from integer values to floating point values.
///
///             Swizzle operators are also available for all vector types, you
///             can call vec.xxx() or vec.xyyy(), etc.
///
///             <a href="md_documentation_manual__operator_overloading.html">Following these guidelines for operator overloading.</a>
template< typename T >
struct TVector2
{
    // Members
    /*! The x component of the 2D vector. */
    T x;

    /*! The y component of the 2D vector. */
    T y;



    // Constructors
    /*! Default constructor for the vector, with default zero values. */
    ULIS_VECTOR_FUNC TVector2();

    /*! Construct the vector from input value ( both x and y will have value iValue ) */
    ULIS_VECTOR_FUNC TVector2( T iValue );

    /*! Construct the vector from input values. */
    ULIS_VECTOR_FUNC TVector2( T iX, T iY );



    // Conversion
    /*! Construct the vector from TVector3. */
    ULIS_VECTOR_FUNC TVector2( const TVector3< T >& iVec );

    /*! Construct the vector from TVector4. */
    ULIS_VECTOR_FUNC TVector2( const TVector4< T >& iVec );

    /*! Construct the vector from input vector of any convertible type. */
    template< typename U >
    ULIS_VECTOR_FUNC TVector2( const TVector2< U >& iOther );



    // Named Functions
    /*! Return the euclidean distance of the vector. */
    ULIS_VECTOR_FUNC T Distance() const;

    /*!
    Return the squared euclidean distance of the vector.
    This can be useful for testing against another squared distance, thus
    saving a square root calculation.
    */
    ULIS_VECTOR_FUNC T DistanceSquared() const;

    /*! Return the manhattan distance of the vector. ( abs( x ) + abs( y ) ) */
    ULIS_VECTOR_FUNC T ManhattanDistance() const;

    /*! Return the dot product of the vector */
    ULIS_VECTOR_FUNC T DotProduct( const TVector2& iOther ) const;

    /*! Normalize this vector. */
    ULIS_VECTOR_FUNC const TVector2& Normalize();

    /*! Return the normalized version of this vector. */
    ULIS_VECTOR_FUNC TVector2 Normalized() const;



    // Comparison operators
    /*! Compare this vector to the other vector for strict equality. */
    ULIS_VECTOR_FUNC bool operator==( const TVector2& iOther ) const;

    /*! Compare this vector to the other vector for strict inequality. */
    ULIS_VECTOR_FUNC bool operator!=( const TVector2& iOther ) const;



    // Unary Negative Operator
    /*! Unary Negative Operator */
    ULIS_VECTOR_FUNC TVector2 operator-() const;



    // Unary Operators with scalar
    /*! Add the input value to this vector and return a reference to this vector. */
    ULIS_VECTOR_FUNC TVector2& operator+=( T iValue );

    /*! Substract the input value to this vector and return a reference to this vector. */
    ULIS_VECTOR_FUNC TVector2& operator-=( T iValue );

    /*! Multiply this vector by the input value and return a reference to this vector. */
    ULIS_VECTOR_FUNC TVector2& operator*=( T iValue );

    /*! Divide this vector by the input value and return a reference to this vector. */
    ULIS_VECTOR_FUNC TVector2& operator/=( T iValue );

    /*! Compute modulo of this vector by the input value and return a reference to this vector. */
    ULIS_VECTOR_FUNC TVector2& operator%=( T iValue );



    // Unary Operators with vector
    /*! Add the input to this vector and return a reference to this vector. */
    ULIS_VECTOR_FUNC TVector2& operator+=(const TVector2& iOther );

    /*! Substract the input to this vector and return a reference to this vector. */
    ULIS_VECTOR_FUNC TVector2& operator-=(const TVector2& iOther );

    /*! Multiply this vector by the input vector and return a reference to this vector. */
    ULIS_VECTOR_FUNC TVector2& operator*=(const TVector2& iOther );

    /*! Divide this vector by the input vector and return a reference to this vector. */
    ULIS_VECTOR_FUNC TVector2& operator/=(const TVector2& iOther );

    /*! Compute modulo of this vector by the input vector and return a reference to this vector. */
    ULIS_VECTOR_FUNC TVector2& operator%=(const TVector2& iOther );



    // Other Operators
    /*! Access component x or y by index, return a reference to the component. */
    ULIS_VECTOR_FUNC T& operator[]( int iIndex );

    /*! Access component x or y by index, return a const reference to the component. */
    ULIS_VECTOR_FUNC const T& operator[]( int iIndex ) const;

    // Swizzle declaration
    ULIS_DECLARE_ALL_SWIZZLE_FUNCTIONS_VEC2
};



// Constructors
template< typename T >
ULIS_VECTOR_FUNC TVector2< T >::TVector2()
    : x( 0 )
    , y( 0 )
{}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T >::TVector2( T iValue )
    : x( iValue )
    , y( iValue )
{}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T >::TVector2( T iX, T iY )
    : x( iX )
    , y( iY )
{}



// Conversion
template< typename T >
template< typename U >
ULIS_VECTOR_FUNC TVector2< T >:: TVector2( const TVector2< U >& iOther )
    : x( static_cast< T >( iOther.x ) )
    , y( static_cast< T >( iOther.y ) )
{}



// Named Functions
template< typename T >
ULIS_VECTOR_FUNC T TVector2< T >:: Distance() const {
    return  FMath::Sqrt( x * x + y * y );
}

template< typename T >
ULIS_VECTOR_FUNC T TVector2< T >::DistanceSquared() const {
    return  x * x + y * y;
}

template< typename T >
ULIS_VECTOR_FUNC T TVector2< T >::ManhattanDistance() const {
    return  FMath::Abs( x ) + FMath::Abs( y );
}

template< typename T >
ULIS_VECTOR_FUNC T TVector2< T >::DotProduct( const TVector2& iOther ) const {
    return  x * iOther.x + y * iOther.y;
}

template< typename T >
ULIS_VECTOR_FUNC const TVector2< T >& TVector2< T >::Normalize() {
    T distance = Distance();
    ULIS_ASSERT( distance != 0, "Division by zero" );
    x /= distance;
    y /= distance;
    return  *this
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > TVector2< T >::Normalized() const {
    TVector2< T > result = *this;
    return  result.Normalize();
}



// Comparison operators
template< typename T >
ULIS_VECTOR_FUNC bool TVector2< T >::operator==( const TVector2< T >& iOther ) const {
    return  x == iOther.x && y == iOther.y;
}

template< typename T >
ULIS_VECTOR_FUNC bool TVector2< T >::operator!=(const TVector2< T >& iOther ) const {
    return  !( *this == iOther );
}



// Unary negative operator
template< typename T >
ULIS_VECTOR_FUNC TVector2< T > TVector2< T >::operator-() const {
    return  TVector2< T >( -x, -y );
}



// Unary Operators with scalar
template< typename T >
ULIS_VECTOR_FUNC TVector2< T >& TVector2< T >::operator+=( T iValue ) {
    x += iValue;
    y += iValue;
    return  *this;
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T >& TVector2< T >::operator-=( T iValue ) {
    x -= iValue;
    y -= iValue;
    return  *this;
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T >& TVector2< T >::operator*=( T iValue ) {
    x *= iValue;
    y *= iValue;
    return  *this;
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T >& TVector2< T >::operator/=( T iValue ) {
    ULIS_ASSERT( iValue != 0, "Division by zero" );
    x /= iValue;
    y /= iValue;
    return  *this;
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T >& TVector2< T >::operator%=( T iValue ) {
    ULIS_ASSERT( iValue != 0, "Division by zero" );
    x %= iValue;
    y %= iValue;
    return  *this;
}



// Unary Operators with vectors
template< typename T >
ULIS_VECTOR_FUNC TVector2< T >& TVector2< T >::operator+=(const TVector2< T >& iOther ) {
    x += iOther.x;
    y += iOther.y;
    return  *this;
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T >& TVector2< T >::operator-=(const TVector2< T >& iOther ) {
    x -= iOther.x;
    y -= iOther.y;
    return  *this;
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T >& TVector2< T >::operator*=(const TVector2< T >& iOther ) { 
    x *= iOther.x;
    y *= iOther.y;
    return  *this;
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T >& TVector2< T >::operator/=(const TVector2& iOther ) {
    ULIS_ASSERT( iOther.x != 0, "Division by zero" );
    ULIS_ASSERT( iOther.y != 0, "Division by zero" );
    x /= iOther.x;
    y /= iOther.y;
    return  *this;
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T >& TVector2< T >::operator%=(const TVector2& iOther ) {
    ULIS_ASSERT( iOther.x != 0, "Division by zero" );
    ULIS_ASSERT( iOther.y != 0, "Division by zero" );
    x %= iOther.x;
    y %= iOther.y;
    return  *this;
}



// Other Operators
template< typename T >
ULIS_VECTOR_FUNC T& TVector2< T >::operator[]( int iIndex ) {
    ULIS_ASSERT( iIndex >= 0 && iIndex < 2, "Bad Index" );
    return  ( &x )[ iIndex ];
}

template< typename T >
ULIS_VECTOR_FUNC const T& TVector2< T >::operator[]( int iIndex ) const {
    ULIS_ASSERT( iIndex >= 0 && iIndex < 2, "Bad Index" );
    return  ( &x )[ iIndex ];
}





// Binary Operators with scalar on left hand side
template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator+( T iValue, const TVector2< T >& iVector ) {
    return  TVector2< T >(
          iValue + iVector.x
        , iValue + iVector.y
    );
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator-( T iValue, const TVector2< T >& iVector ) {
    return  TVector2< T >(
          iValue - iVector.x
        , iValue - iVector.y
    );
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator*( T iValue, const TVector2< T >& iVector ) {
    return  TVector2< T >(
          iValue * iVector.x
        , iValue * iVector.y
    );
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator/( T iValue, const TVector2< T >& iVector ) {
    ULIS_ASSERT( iVector.x != 0, "Division by zero" );
    ULIS_ASSERT( iVector.y != 0, "Division by zero" );
    return  TVector2< T >(
          iValue / iVector.x
        , iValue / iVector.y
    );
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator%( T iValue, const TVector2< T >& iVector ) {
    ULIS_ASSERT( iVector.x != 0, "Division by zero" );
    ULIS_ASSERT( iVector.y != 0, "Division by zero" );
    return  TVector2< T >(
          iValue % iVector.x
        , iValue % iVector.y
    );
}



// Binary Operators with scalar on right hand side
template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator+( const TVector2< T >& iVector, T iValue ) {
    return  TVector2< T >(
          iVector.x + iValue
        , iVector.y + iValue
    );
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator-( const TVector2< T >& iVector, T iValue ) {
    return  TVector2< T >(
          iVector.x - iValue
        , iVector.y - iValue
    );
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator*( const TVector2< T >& iVector, T iValue ) {
    return  TVector2< T >(
          iVector.x * iValue
        , iVector.y * iValue
    );
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator/( const TVector2< T >& iVector, T iValue ) {
    ULIS_ASSERT( iValue != 0, "Division by zero" );
    return  TVector2< T >(
          iVector.x / iValue
        , iVector.y / iValue
    );
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator%( const TVector2< T >& iVector, T iValue ) {
    ULIS_ASSERT( iValue != 0, "Division by zero" );
    return  TVector2< T >(
          iVector.x % iValue
        , iVector.y % iValue
    );
}


// Binary Operators with vector
template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator+( const TVector2< T >& iVector, const TVector2< T >& iOther ) {
    return  TVector2< T >(
          iVector.x + iOther.x
        , iVector.y + iOther.y
    );
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator-( const TVector2< T >& iVector, const TVector2< T >& iOther ) {
    return  TVector2< T >(
          iVector.x - iOther.x
        , iVector.y - iOther.y
    );
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator*( const TVector2< T >& iVector, const TVector2< T >& iOther ) {
    return  TVector2< T >(
          iVector.x * iOther.x
        , iVector.y * iOther.y
    );
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator/( const TVector2< T >& iVector, const TVector2< T >& iOther ) {
    ULIS_ASSERT( iOther.x != 0, "Division by zero" );
    ULIS_ASSERT( iOther.y != 0, "Division by zero" );
    return  TVector2< T >(
          iVector.x / iOther.x
        , iVector.y / iOther.y
    );
}

template< typename T >
ULIS_VECTOR_FUNC TVector2< T > operator%( const TVector2< T >& iVector, const TVector2< T >& iOther ) {
    ULIS_ASSERT( iOther.x != 0, "Division by zero" );
    ULIS_ASSERT( iOther.y != 0, "Division by zero" );
    return  TVector2< T >(
          iVector.x % iOther.x
        , iVector.y % iOther.y
    );
}

ULIS_NAMESPACE_END

