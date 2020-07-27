// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Vector8.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TVector8 class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry/VectorFunc.h"
#include "Maths/Geometry/VectorSwizzle.h"
#include "Maths/Maths.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TVector8
/// @brief      The TVector8 class provides a simple 8D vector class for vector
///             geometry applications.
/// @details    The TVector8 class is a template class that provides basic 8D
///             vector functionnalities, it can be used with any numeric types,
///             ranging from integer values to floating point values.
///
///             <a href="md_documentation_manual__operator_overloading.html">Following these guidelines for operator overloading.</a>
template< typename T >
struct TVector8
{
    // Members
    /*! The data of the 8D vector. */
    T data[8];

    // Constructors
    // Constructors
    /*! Default constructor for the vector, with default zero values. */
    ULIS3_VECTOR_FUNC TVector8();

    /*! Construct the vector from input value ( both x and y will have value iValue ) */
    ULIS3_VECTOR_FUNC TVector8( T iValue );

    /*! Construct the vector from input values. */
    ULIS3_VECTOR_FUNC TVector8( T iE0, T iE1, T iE2 = 0, T iE3 = 0, T iE4 = 0, T iE5 = 0, T iE6 = 0, T iE7 = 0 );

    /*! Construct the vector from input vector of any convertible type. */
    template< typename U >
    ULIS3_VECTOR_FUNC TVector8( const TVector8< U >& iOther );

    // Named Functions
    /*! Return the euclidean distance of the vector. */
    ULIS3_VECTOR_FUNC T Distance() const;

    /*!
    Return the squared euclidean distance of the vector.
    This can be useful for testing against another squared distance, thus
    saving a square root calculation.
    */
    ULIS3_VECTOR_FUNC T DistanceSquared() const;

    /*! Return the manhattan distance of the vector. ( abs( x ) + abs( y ) ) */
    ULIS3_VECTOR_FUNC T ManhattanDistance() const;

    /*! Return the dot product of the vector */
    ULIS3_VECTOR_FUNC T DotProduct( const TVector8& iOther ) const;

    /*! Normalize this vector. */
    ULIS3_VECTOR_FUNC const TVector8& Normalize();

    /*! Return the normalized version of this vector. */
    ULIS3_VECTOR_FUNC TVector8 Normalized() const;

    // Comparison operators
    /*! Compare this vector to the other vector for strict equality. */
    ULIS3_VECTOR_FUNC bool operator==( const TVector8& iOther ) const;

    /*! Compare this vector to the other vector for strict inequality. */
    ULIS3_VECTOR_FUNC bool operator!=( const TVector8& iOther ) const;



    // Unary Negative Operator
    ULIS3_VECTOR_FUNC TVector8 operator-() const;



    // Unary Operators with scalar
    /*! Add the input value to this vector and return a reference to this vector. */
    ULIS3_VECTOR_FUNC TVector8& operator+=( T iValue );

    /*! Substract the input value to this vector and return a reference to this vector. */
    ULIS3_VECTOR_FUNC TVector8& operator-=( T iValue );

    /*! Multiply this vector by the input value and return a reference to this vector. */
    ULIS3_VECTOR_FUNC TVector8& operator*=( T iValue );

    /*! Divide this vector by the input value and return a reference to this vector. */
    ULIS3_VECTOR_FUNC TVector8& operator/=( T iValue );

    /*! Compute modulo of this vector by the input value and return a reference to this vector. */
    ULIS3_VECTOR_FUNC TVector8& operator%=( T iValue );



    // Unary Operators with vector
    /*! Add the input to this vector and return a reference to this vector. */
    ULIS3_VECTOR_FUNC TVector8& operator+=(const TVector8& iOther );

    /*! Substract the input to this vector and return a reference to this vector. */
    ULIS3_VECTOR_FUNC TVector8& operator-=(const TVector8& iOther );

    /*! Multiply this vector by the input vector and return a reference to this vector. */
    ULIS3_VECTOR_FUNC TVector8& operator*=(const TVector8& iOther );

    /*! Divide this vector by the input vector and return a reference to this vector. */
    ULIS3_VECTOR_FUNC TVector8& operator/=(const TVector8& iOther );

    /*! Compute modulo of this vector by the input vector and return a reference to this vector. */
    ULIS3_VECTOR_FUNC TVector8& operator%=(const TVector8& iOther );



    // Other Operators
    /*! Access component x or y by index, return a reference to the component. */
    ULIS3_VECTOR_FUNC T& operator[]( int iIndex );

    /*! Access component x or y by index, return a const reference to the component. */
    ULIS3_VECTOR_FUNC const T& operator[]( int iIndex ) const;

    // Swizzle declaration
    ULIS3_DECLARE_ALL_SWIZZLE_FUNCTIONS_VEC4
};



// Constructors
template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >::TVector8()
    : data{ 0, 0, 0, 0, 0, 0, 0, 0 }
{}

template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >::TVector8( T iValue )
    : data{ iValue, iValue, iValue, iValue, iValue, iValue, iValue, iValue }
{}

template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >::TVector8( T iE0, T iE1, T iE2, T iE3, T iE4, T iE5, T iE6, T iE7 )
    : data{ iE0, iE1, iE2, iE3, iE4, iE5, iE6, iE7 }
{}



// Conversion
template< typename T >
template< typename U >
ULIS3_VECTOR_FUNC TVector8< T >:: TVector8( const TVector8< U >& iOther )
    : data{ static_cast< T >( iOther.data[0] )
          , static_cast< T >( iOther.data[1] )
          , static_cast< T >( iOther.data[2] )
          , static_cast< T >( iOther.data[3] )
          , static_cast< T >( iOther.data[4] )
          , static_cast< T >( iOther.data[5] )
          , static_cast< T >( iOther.data[6] )
          , static_cast< T >( iOther.data[7] ) }
{}



// Named Functions
template< typename T >
ULIS3_VECTOR_FUNC T TVector8< T >:: Distance() const {
    return  FMaths::Sqrt( DistanceSquared() );
}

template< typename T >
ULIS3_VECTOR_FUNC T TVector8< T >::DistanceSquared() const {
    T result = 0;

    for( int i = 0; i < 8; ++i )
        result += data[i] * data[i];

    return  result;
}

template< typename T >
ULIS3_VECTOR_FUNC T TVector8< T >::ManhattanDistance() const {
    T result = 0;

    for( int i = 0; i < 8; ++i )
        result += FMaths::Abs( data[i] );

    return  result;
}

template< typename T >
ULIS3_VECTOR_FUNC T TVector8< T >::DotProduct( const TVector8& iOther ) const {
    T result = 0;

    for( int i = 0; i < 8; ++i )
        result += data[i] * iOther.data[i];

    return  result;
}

template< typename T >
ULIS3_VECTOR_FUNC const TVector8< T >& TVector8< T >::Normalize() {
    T distance = Distance();
    ULIS3_ASSERT( distance != 0, "Division by zero" );

    for( int i = 0; i < 8; ++i )
        data[i] /= distance;

    return  *this
}

template< typename T >
ULIS3_VECTOR_FUNC TVector8< T > TVector8< T >::Normalized() const {
    TVector8< T > result = *this;
    return  result.Normalize();
}



// Comparison operators
template< typename T >
ULIS3_VECTOR_FUNC bool TVector8< T >::operator==( const TVector8< T >& iOther ) const {
    for( int i = 0; i < 8; ++i )
        if( data[i] != iOther.data[i] )
            return  false;

    return  true;
}

template< typename T >
ULIS3_VECTOR_FUNC bool TVector8< T >::operator!=(const TVector8< T >& iOther ) const {
    return  !( *this == iOther );
}



// Unary negative operator
template< typename T >
ULIS3_VECTOR_FUNC TVector8< T > TVector8< T >::operator-() const {
    return  TVector8< T >(
          -data[0]
        , -data[1]
        , -data[2]
        , -data[3]
        , -data[4]
        , -data[5]
        , -data[6]
        , -data[7]
        );
}



// Unary Operators with scalar
template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >& TVector8< T >::operator+=( T iValue ) {
    for( int i = 0; i < 8; ++i )
        data[i] += iValue;

    return  *this;
}

template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >& TVector8< T >::operator-=( T iValue ) {
    for( int i = 0; i < 8; ++i )
        data[i] -= iValue;

    return  *this;
}

template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >& TVector8< T >::operator*=( T iValue ) {
    for( int i = 0; i < 8; ++i )
        data[i] *= iValue;

    return  *this;
}

template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >& TVector8< T >::operator/=( T iValue ) {
    ULIS3_ASSERT( iValue != 0, "Division by zero" );
    for( int i = 0; i < 8; ++i )
        data[i] /= iValue;

    return  *this;
}

template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >& TVector8< T >::operator%=( T iValue ) {
    ULIS3_ASSERT( iValue != 0, "Division by zero" );
    for( int i = 0; i < 8; ++i )
        data[i] %= iValue;

    return  *this;
}



// Unary Operators with vectors
template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >& TVector8< T >::operator+=(const TVector8< T >& iOther ) {
    for( int i = 0; i < 8; ++i )
        data[i] += iOther.data[i];

    return  *this;
}

template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >& TVector8< T >::operator-=(const TVector8< T >& iOther ) {
    for( int i = 0; i < 8; ++i )
        data[i] -= iOther.data[i];

    return  *this;
}

template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >& TVector8< T >::operator*=(const TVector8< T >& iOther ) { 
    for( int i = 0; i < 8; ++i )
        data[i] *= iOther.data[i];

    return  *this;
}

template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >& TVector8< T >::operator/=(const TVector8& iOther ) {
#ifdef ULIS3_ASSERT_ENABLED
    for( int i = 0; i < 8; ++i )
        ULIS3_ASSERT( iOther.data[i] != 0, "Division by zero" );
#endif // ULIS3_ASSERT_ENABLED

    for( int i = 0; i < 8; ++i )
        data[i] /= iOther.data[i];

    return  *this;
}

template< typename T >
ULIS3_VECTOR_FUNC TVector8< T >& TVector8< T >::operator%=(const TVector8& iOther ) {
#ifdef ULIS3_ASSERT_ENABLED
    for( int i = 0; i < 8; ++i )
        ULIS3_ASSERT( iOther.data[i] != 0, "Division by zero" );
#endif // ULIS3_ASSERT_ENABLED

    for( int i = 0; i < 8; ++i )
        data[i] %= iOther.data[i];

    return  *this;
}



// Other Operators
template< typename T >
ULIS3_VECTOR_FUNC T& TVector8< T >::operator[]( int iIndex ) {
    ULIS3_ASSERT( iIndex >= 0 && iIndex < 8, "Bad Index" );
    return  data[ iIndex ];
}

template< typename T >
ULIS3_VECTOR_FUNC const T& TVector8< T >::operator[]( int iIndex ) const {
    ULIS3_ASSERT( iIndex >= 0 && iIndex < 8, "Bad Index" );
    return  data[ iIndex ];
}





// Binary Operators with scalar on left hand side
template< typename T >
ULIS3_VECTOR_FUNC T operator+( T iValue, const TVector8< T >& iVector ) {
    return  TVector8< T >(
          iValue + iVector.data[0]
        , iValue + iVector.data[1]
        , iValue + iVector.data[2]
        , iValue + iVector.data[3]
        , iValue + iVector.data[4]
        , iValue + iVector.data[5]
        , iValue + iVector.data[6]
        , iValue + iVector.data[7]
    );
}

template< typename T >
ULIS3_VECTOR_FUNC T operator-( T iValue, const TVector8< T >& iVector ) {
    return  TVector8< T >(
          iValue - iVector.data[0]
        , iValue - iVector.data[1]
        , iValue - iVector.data[2]
        , iValue - iVector.data[3]
        , iValue - iVector.data[4]
        , iValue - iVector.data[5]
        , iValue - iVector.data[6]
        , iValue - iVector.data[7]
    );
}

template< typename T >
ULIS3_VECTOR_FUNC T operator*( T iValue, const TVector8< T >& iVector ) {
    return  TVector8< T >(
          iValue * iVector.data[0]
        , iValue * iVector.data[1]
        , iValue * iVector.data[2]
        , iValue * iVector.data[3]
        , iValue * iVector.data[4]
        , iValue * iVector.data[5]
        , iValue * iVector.data[6]
        , iValue * iVector.data[7]
    );
}

template< typename T >
ULIS3_VECTOR_FUNC T operator/( T iValue, const TVector8< T >& iVector ) {
#ifdef ULIS3_ASSERT_ENABLED
    for( int i = 0; i < 8; ++i )
        ULIS3_ASSERT( iVector.data[i] != 0, "Division by zero" );
#endif // ULIS3_ASSERT_ENABLED

    return  TVector8< T >(
          iValue / iVector.data[0]
        , iValue / iVector.data[1]
        , iValue / iVector.data[2]
        , iValue / iVector.data[3]
        , iValue / iVector.data[4]
        , iValue / iVector.data[5]
        , iValue / iVector.data[6]
        , iValue / iVector.data[7]
    );
}

template< typename T >
ULIS3_VECTOR_FUNC T operator%( T iValue, const TVector8< T >& iVector ) {
#ifdef ULIS3_ASSERT_ENABLED
    for( int i = 0; i < 8; ++i )
        ULIS3_ASSERT( iVector.data[i] != 0, "Division by zero" );
#endif // ULIS3_ASSERT_ENABLED

    return  TVector8< T >(
          iValue % iVector.data[0]
        , iValue % iVector.data[1]
        , iValue % iVector.data[2]
        , iValue % iVector.data[3]
        , iValue % iVector.data[4]
        , iValue % iVector.data[5]
        , iValue % iVector.data[6]
        , iValue % iVector.data[7]
    );
}



// Binary Operators with scalar on right hand side
template< typename T >
ULIS3_VECTOR_FUNC T operator+( const TVector8< T >& iVector, T iValue ) {
    return  TVector8< T >(
          iVector.data[0] + iValue
        , iVector.data[1] + iValue
        , iVector.data[2] + iValue
        , iVector.data[3] + iValue
        , iVector.data[4] + iValue
        , iVector.data[5] + iValue
        , iVector.data[6] + iValue
        , iVector.data[7] + iValue
    );
}

template< typename T >
ULIS3_VECTOR_FUNC T operator-( const TVector8< T >& iVector, T iValue ) {
    return  TVector8< T >(
          iVector.data[0] - iValue
        , iVector.data[1] - iValue
        , iVector.data[2] - iValue
        , iVector.data[3] - iValue
        , iVector.data[4] - iValue
        , iVector.data[5] - iValue
        , iVector.data[6] - iValue
        , iVector.data[7] - iValue
    );
}

template< typename T >
ULIS3_VECTOR_FUNC T operator*( const TVector8< T >& iVector, T iValue ) {
    return  TVector8< T >(
          iVector.data[0] * iValue
        , iVector.data[1] * iValue
        , iVector.data[2] * iValue
        , iVector.data[3] * iValue
        , iVector.data[4] * iValue
        , iVector.data[5] * iValue
        , iVector.data[6] * iValue
        , iVector.data[7] * iValue
    );
}

template< typename T >
ULIS3_VECTOR_FUNC T operator/( const TVector8< T >& iVector, T iValue ) {
    ULIS3_ASSERT( iValue != 0, "Division by zero" );
    return  TVector8< T >(
          iVector.data[0] / iValue
        , iVector.data[1] / iValue
        , iVector.data[2] / iValue
        , iVector.data[3] / iValue
        , iVector.data[4] / iValue
        , iVector.data[5] / iValue
        , iVector.data[6] / iValue
        , iVector.data[7] / iValue
    );
}

template< typename T >
ULIS3_VECTOR_FUNC T operator%( const TVector8< T >& iVector, T iValue ) {
    ULIS3_ASSERT( iValue != 0, "Division by zero" );
    return  TVector8< T >(
          iVector.data[0] % iValue
        , iVector.data[1] % iValue
        , iVector.data[2] % iValue
        , iVector.data[3] % iValue
        , iVector.data[4] % iValue
        , iVector.data[5] % iValue
        , iVector.data[6] % iValue
        , iVector.data[7] % iValue
    );
}


// Binary Operators with vector
template< typename T >
ULIS3_VECTOR_FUNC T operator+( const TVector8< T >& iVector, const TVector8< T >& iOther ) {
    return  TVector8< T >(
          iVector.data[0] + iOther.data[0]
        , iVector.data[1] + iOther.data[1]
        , iVector.data[2] + iOther.data[2]
        , iVector.data[3] + iOther.data[3]
        , iVector.data[4] + iOther.data[4]
        , iVector.data[5] + iOther.data[5]
        , iVector.data[6] + iOther.data[6]
        , iVector.data[7] + iOther.data[7]
    );
}

template< typename T >
ULIS3_VECTOR_FUNC T operator-( const TVector8< T >& iVector, const TVector8< T >& iOther ) {
    return  TVector8< T >(
          iVector.data[0] - iOther.data[0]
        , iVector.data[1] - iOther.data[1]
        , iVector.data[2] - iOther.data[2]
        , iVector.data[3] - iOther.data[3]
        , iVector.data[4] - iOther.data[4]
        , iVector.data[5] - iOther.data[5]
        , iVector.data[6] - iOther.data[6]
        , iVector.data[7] - iOther.data[7]
    );
}

template< typename T >
ULIS3_VECTOR_FUNC T operator*( const TVector8< T >& iVector, const TVector8< T >& iOther ) {
    return  TVector8< T >(
          iVector.data[0] * iOther.data[0]
        , iVector.data[1] * iOther.data[1]
        , iVector.data[2] * iOther.data[2]
        , iVector.data[3] * iOther.data[3]
        , iVector.data[4] * iOther.data[4]
        , iVector.data[5] * iOther.data[5]
        , iVector.data[6] * iOther.data[6]
        , iVector.data[7] * iOther.data[7]
    );
}

template< typename T >
ULIS3_VECTOR_FUNC T operator/( const TVector8< T >& iVector, const TVector8< T >& iOther ) {
#ifdef ULIS3_ASSERT_ENABLED
    for( int i = 0; i < 8; ++i )
        ULIS3_ASSERT( iOther.data[i] != 0, "Division by zero" );
#endif // ULIS3_ASSERT_ENABLED

    return  TVector8< T >(
          iVector.data[0] / iOther.data[0]
        , iVector.data[1] / iOther.data[1]
        , iVector.data[2] / iOther.data[2]
        , iVector.data[3] / iOther.data[3]
        , iVector.data[4] / iOther.data[4]
        , iVector.data[5] / iOther.data[5]
        , iVector.data[6] / iOther.data[6]
        , iVector.data[7] / iOther.data[7]
    );
}

template< typename T >
ULIS3_VECTOR_FUNC T operator%( const TVector8< T >& iVector, const TVector8< T >& iOther ) {
#ifdef ULIS3_ASSERT_ENABLED
    for( int i = 0; i < 8; ++i )
        ULIS3_ASSERT( iOther.data[i] != 0, "Division by zero" );
#endif // ULIS3_ASSERT_ENABLED

    return  TVector8< T >(
          iVector.data[0] % iOther.data[0]
        , iVector.data[1] % iOther.data[1]
        , iVector.data[2] % iOther.data[2]
        , iVector.data[3] % iOther.data[3]
        , iVector.data[4] % iOther.data[4]
        , iVector.data[5] % iOther.data[5]
        , iVector.data[6] % iOther.data[6]
        , iVector.data[7] % iOther.data[7]
    );
}

ULIS3_NAMESPACE_END

