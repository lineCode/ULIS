// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Matrix2x2.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TMatrix2x2 class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry/MatrixFunc.h"
#include "Maths/Geometry/Vector2.h"
#include "Maths/Maths.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TMatrix2x2
/// @brief      The TMatrix2x2 class provides a simple 2x2 square matrix class for
///             geometry applications.
/// @details    The TMatrix2x2 class is a template class that provides basic matrix
///             functionnalities, it can be used with any numeric types,
///             ranging from integer values to floating point values.
template< typename T >
class TMatrix2x2
{
public:
    typedef TVector2< T > tRow;
    typedef TVector2< T > tColumn;

private:
    /*! The rows of the matrix. */
    tRow mRows[2];

public:
    // Constructors
    /*! Default constructor ( identity matrix ). */
    ULIS3_MATRIX_FUNC TMatrix2x2();

    /*! Constructor from input diagonal value. */
    ULIS3_MATRIX_FUNC TMatrix2x2( T iValue );

    /*! Constructor from input cells values. */
    ULIS3_MATRIX_FUNC TMatrix2x2( T iM00, T iM10, T iM01, T iM11 );

    /*! Constructor from row vector values. */
    ULIS3_MATRIX_FUNC TMatrix2x2( const tRow& iRow0, const tRow& iRow1 );

    /*! Copy constructor. */
    ULIS3_MATRIX_FUNC TMatrix2x2( const TMatrix2x2& iOther );

    /*! Assignment operator from matrix. */
    ULIS3_MATRIX_FUNC ULIS3_FORCEINLINE TMatrix2x2& operator=( const TMatrix2x2& iOther );



    // Conversion
    /*! Conversion constructor from other matrix type. */
    template< typename U >
    ULIS3_MATRIX_FUNC TMatrix2x2( const TMatrix2x2< U >& iOther );



    // Other Operators
    /*! Subscript accessor for matrix rows. */
    ULIS3_MATRIX_FUNC ULIS3_FORCEINLINE tRow& operator[]( int iIndex );

    /*! Subscript accessor for const matrix rows. */
    ULIS3_MATRIX_FUNC ULIS3_FORCEINLINE const tRow& operator[]( int iIndex ) const;



    // Named Functions
    /*! Obtain the inverse of the matrix. */
    ULIS3_FORCEINLINE TMatrix2x2 Inverse();

    /*! Obtain the transpose of the matrix. */
    ULIS3_FORCEINLINE TMatrix2x2 Transpose();

    /*! Obtain the determinant of the matrix. */
    ULIS3_FORCEINLINE T Determinant();


    /*! Unary addition operator with matrix. */
    ULIS3_FORCEINLINE TMatrix2x2& operator+=( const TMatrix2x2& iOther ) {
        mRows[0] += iOther.mRows[0];
        mRows[1] += iOther.mRows[1];
    }

    /*! Unary substraction operator with matrix. */
    ULIS3_FORCEINLINE TMatrix2x2& operator-=( const TMatrix2x2& iOther ) {
        mRows[0] -= iOther.mRows[0];
        mRows[1] -= iOther.mRows[1];
    }

    /*! Unary multiplication operator with matrix. */
    ULIS3_FORCEINLINE TMatrix2x2& operator*=( const TMatrix2x2& iOther ) {
    }

    /*! Unary division operator with matrix. */
    ULIS3_FORCEINLINE TMatrix2x2& operator/=( const TMatrix2x2& iOther );

    /*! Unary division operator with value. */
    ULIS3_FORCEINLINE TMatrix2x2& operator+=( T iValue );

    /*! Unary substraction operator with value. */
    ULIS3_FORCEINLINE TMatrix2x2& operator-=( T iValue );

    /*! Unary multiplication operator with value. */
    ULIS3_FORCEINLINE TMatrix2x2& operator*=( T iValue );

    /*! Unary division operator with value. */
    ULIS3_FORCEINLINE TMatrix2x2& operator/=( T iValue );

    /*! Unary negative operator. */
    ULIS3_FORCEINLINE TMatrix2x2 operator-() const;

    /*! Addition operator with matrix. */
    ULIS3_FORCEINLINE TMatrix2x2 operator+( const TMatrix2x2& iOther );

    /*! Substraction operator with matrix. */
    ULIS3_FORCEINLINE TMatrix2x2 operator-( const TMatrix2x2& iOther );

    /*! Multiplication operator with matrix. */
    ULIS3_FORCEINLINE TMatrix2x2 operator*( const TMatrix2x2& iOther );

    /*! Division operator with matrix. */
    ULIS3_FORCEINLINE TMatrix2x2 operator/( const TMatrix2x2& iOther );

    /*! Addition operator with value. */
    ULIS3_FORCEINLINE TMatrix2x2 operator+( T iValue );

    /*! Substraction operator with value. */
    ULIS3_FORCEINLINE TMatrix2x2 operator-( T iValue );

    /*! Multiplication operator with value. */
    ULIS3_FORCEINLINE TMatrix2x2 operator*( T iValue );

    /*! Division operator with value. */
    ULIS3_FORCEINLINE TMatrix2x2 operator/( T iValue );

    /*! Equality operator. */
    ULIS3_FORCEINLINE bool operator==( const TMatrix2x2& iOther );

    /*! Inequality operator. */
    ULIS3_FORCEINLINE bool operator!=( const TMatrix2x2& iOther );
};

/*! Binary matrix by row multiplication operator. */
template< typename T >
ULIS3_FORCEINLINE TMatrix2x2< T >::tColumn operator*( const TMatrix2x2< T >& iMat, const TMatrix2x2< T >::tRow& iRow );

/*! Binary column by matrix multiplication operator. */
template< typename T >
ULIS3_FORCEINLINE TMatrix2x2< T >::tRow operator*( const TMatrix2x2< T >::tColumn& iColum, const TMatrix2x2< T >& iMat );

ULIS3_NAMESPACE_END

