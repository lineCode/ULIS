// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Matrix3x3.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TMatrix3x3 class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry/MatrixFunc.h"
#include "Maths/Geometry/Vector3.h"
#include "Maths/Maths.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TMatrix3x3
/// @brief      The TMatrix3x3 class provides a simple 3x3 square matrix class for
///             geometry applications.
/// @details    The TMatrix3x3 class is a template class that provides basic matrix
///             functionnalities, it can be used with any numeric types,
///             ranging from integer values to floating point values.
template< typename T >
class TMatrix3x3
{
public:
    typedef TVector2< T > tRow;
    typedef TVector2< T > tColumn;

private:
    /*! The columns of the matrix. */
    tColumn mCols[3];

public:
    // Constructors
    /*! Default constructor ( identity matrix ). */
    ULIS3_MATRIX_FUNC TMatrix3x3();

    /*! Constructor from input diagonal value. */
    ULIS3_MATRIX_FUNC TMatrix3x3( T iValue );

    /*! Constructor from input cells values. */
    ULIS3_MATRIX_FUNC TMatrix3x3(
          T iM00, T iM10, T iM20
        , T iM01, T iM11, T iM21
        , T iM02, T iM12, T iM22
    );

    /*! Constructor from row vector values. */
    ULIS3_MATRIX_FUNC TMatrix3x3(
          const tColumn& iCol0
        , const tColumn& iCol1
        , const tColumn& iCol2
    );

    /*! Copy constructor. */
    ULIS3_MATRIX_FUNC TMatrix3x3( const TMatrix3x3& iOther );

    /*! Assignment operator from matrix. */
    ULIS3_MATRIX_FUNC TMatrix3x3& operator=( const TMatrix3x3& iOther );



    // Conversion
    /*! Conversion constructor from other matrix type. */
    template< typename U >
    ULIS3_MATRIX_FUNC TMatrix3x3( const TMatrix3x3< U >& iOther );



    // Named Functions
    /*! Obtain the inverse of the matrix. */
    ULIS3_MATRIX_FUNC TMatrix3x3 Inverse();

    /*! Obtain the transpose of the matrix. */
    ULIS3_MATRIX_FUNC TMatrix3x3 Transpose();

    /*! Obtain the determinant of the matrix. */
    ULIS3_MATRIX_FUNC T Determinant();



    // Boolean operators
    /*! Equality operator. */
    ULIS3_MATRIX_FUNC bool operator==( const TMatrix3x3& iOther );

    /*! Inequality operator. */
    ULIS3_MATRIX_FUNC bool operator!=( const TMatrix3x3& iOther );



    // Unary Negative Operator
    /*! Unary negative operator. */
    ULIS3_MATRIX_FUNC TMatrix3x3 operator-() const;



    // Unary arithmetic operator with scalar
    /*! Unary addition operator with value. */
    ULIS3_MATRIX_FUNC TMatrix3x3& operator+=( T iValue );

    /*! Unary substraction operator with value. */
    ULIS3_MATRIX_FUNC TMatrix3x3& operator-=( T iValue );

    /*! Unary multiplication operator with value. */
    ULIS3_MATRIX_FUNC TMatrix3x3& operator*=( T iValue );

    /*! Unary division operator with value. */
    ULIS3_MATRIX_FUNC TMatrix3x3& operator/=( T iValue );



    // Unary arithmetic operator with matrix
    /*! Unary addition operator with matrix. */
    ULIS3_MATRIX_FUNC TMatrix3x3& operator+=( const TMatrix3x3& iOther );

    /*! Unary substraction operator with matrix. */
    ULIS3_MATRIX_FUNC TMatrix3x3& operator-=( const TMatrix3x3& iOther );

    /*! Unary multiplication operator with matrix. */
    ULIS3_MATRIX_FUNC TMatrix3x3& operator*=( const TMatrix3x3& iOther );

    /*! Unary division operator with matrix. */
    ULIS3_MATRIX_FUNC TMatrix3x3& operator/=( const TMatrix3x3& iOther );



    // Other Operators
    /*! Subscript accessor for matrix columns. */
    ULIS3_MATRIX_FUNC tColumn& operator[]( int iIndex );

    /*! Subscript accessor for const matrix columns. */
    ULIS3_MATRIX_FUNC const tColumn& operator[]( int iIndex ) const;
};



// Constructors
template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >::TMatrix3x3()
    : mCols {
          tColumn( 1, 0, 0 )
        , tColumn( 0, 1, 0 )
        , tColumn( 0, 0, 1 )
    }
{}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >::TMatrix3x3( T iValue )
    : mCols {
          tColumn( iValue, 0, 0 )
        , tColumn( 0, iValue, 0 )
        , tColumn( 0, 0, iValue )
    }
{}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >::TMatrix3x3(
      T iM00, T iM10, T iM20
    , T iM01, T iM11, T iM21
    , T iM02, T iM12, T iM22
    )
    : mCols {
          tColumn( iM00, iM01, iM02 )
        , tColumn( iM10, iM11, iM12 )
        , tColumn( iM20, iM21, iM22 )
    }
{}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >::TMatrix3x3(
      const tColumn& iCol0
    , const tColumn& iCol1
    , const tColumn& iCol2
    )
    : mCols {
          iCol0
        , iCol1
        , iCol2
    }
{}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >::TMatrix3x3( const TMatrix3x3< T >& iOther )
    : mCols {
          iOther.mCols[0]
        , iOther.mCols[1]
        , iOther.mCols[2]
    }
{}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >& TMatrix3x3< T >::operator=( const TMatrix3x3< T >& iOther ) {
    mCols[0] = iOther.mCols[0];
    mCols[1] = iOther.mCols[1];
    mCols[1] = iOther.mCols[2];
}



// Conversion
template< typename T >
template< typename U >
ULIS3_MATRIX_FUNC TMatrix3x3< T >::TMatrix3x3( const TMatrix3x3< U >& iOther )
    : mCols {
          tColumn( iOther.mCols[0] )
        , tColumn( iOther.mCols[1] )
        , tColumn( iOther.mCols[2] )
    }
{}



// Named Functions
template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > TMatrix3x3< T >::Inverse() {
    T inv_det = static_cast< T >( 1 ) / Determinant();

    return  TMatrix3x3< T >(
          + ( (*this)[1][1] * (*this)[2][2] - (*this)[2][1] * (*this)[1][2] ) * inv_det
        , - ( (*this)[1][0] * (*this)[2][2] - (*this)[2][0] * (*this)[1][2] ) * inv_det
        , + ( (*this)[1][0] * (*this)[2][1] - (*this)[2][0] * (*this)[1][1] ) * inv_det
        , - ( (*this)[0][1] * (*this)[2][2] - (*this)[2][1] * (*this)[0][2] ) * inv_det
        , + ( (*this)[0][0] * (*this)[2][2] - (*this)[2][0] * (*this)[0][2] ) * inv_det
        , - ( (*this)[0][0] * (*this)[2][1] - (*this)[2][0] * (*this)[0][1] ) * inv_det
        , + ( (*this)[0][1] * (*this)[1][2] - (*this)[1][1] * (*this)[0][2] ) * inv_det
        , - ( (*this)[0][0] * (*this)[1][2] - (*this)[1][0] * (*this)[0][2] ) * inv_det
        , + ( (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1] ) * inv_det
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > TMatrix3x3< T >::Transpose() {
    return  TMatrix3x3< T >(
          (*this)[0][0]
        , (*this)[0][1]
        , (*this)[0][2]
        , (*this)[1][0]
        , (*this)[1][1]
        , (*this)[1][2]
        , (*this)[2][0]
        , (*this)[2][1]
        , (*this)[2][2]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC T TMatrix3x3< T >::Determinant() {
    return  + (*this)[0][0] * ( (*this)[1][1] * (*this)[2][2] - (*this)[2][1] * (*this)[1][2] )
            - (*this)[1][0] * ( (*this)[0][1] * (*this)[2][2] - (*this)[2][1] * (*this)[0][2] )
            + (*this)[2][0] * ( (*this)[0][1] * (*this)[1][2] - (*this)[1][1] * (*this)[0][2] );
}



// Boolean operators
template< typename T >
ULIS3_MATRIX_FUNC bool TMatrix3x3< T >::operator==( const TMatrix3x3< T >& iOther ) {
    return  mCols[0] == iOther.mCols[0]
        &&  mCols[1] == iOther.mCols[1];
        &&  mCols[2] == iOther.mCols[2];
}

template< typename T >
ULIS3_MATRIX_FUNC bool TMatrix3x3< T >::operator!=( const TMatrix3x3< T >& iOther ) {
    return  !( *this == iOther );
}



// Unary Negative Operator
template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > TMatrix3x3< T >::operator-() const {
    return  TMatrix3x3< T >( -mCols[0], -mCols[1], -mCols[2] );
}



// Unary arithmetic operator with scalar
template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >& TMatrix3x3< T >::operator+=( T iValue ) {
    mCols[0] += iValue;
    mCols[1] += iValue;
    mCols[2] += iValue;
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >& TMatrix3x3< T >::operator-=( T iValue ) {
    mCols[0] -= iValue;
    mCols[1] -= iValue;
    mCols[2] -= iValue;
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >& TMatrix3x3< T >::operator*=( T iValue ) {
    mCols[0] *= iValue;
    mCols[1] *= iValue;
    mCols[2] *= iValue;
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >& TMatrix3x3< T >::operator/=( T iValue ) {
    mCols[0] /= iValue;
    mCols[1] /= iValue;
    mCols[2] /= iValue;
}



// Unary arithmetic operator with matrix
template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >& TMatrix3x3< T >::operator+=( const TMatrix3x3& iOther ) {
    mCols[0] += iOther.mCols[0];
    mCols[1] += iOther.mCols[1];
    mCols[2] += iOther.mCols[2];
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >& TMatrix3x3< T >::operator-=( const TMatrix3x3& iOther ) {
    mCols[0] -= iOther.mCols[0];
    mCols[1] -= iOther.mCols[1];
    mCols[2] -= iOther.mCols[2];
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >& TMatrix3x3< T >::operator*=( const TMatrix3x3& iOther ) {
    return  ( *this = *this * iOther );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >& TMatrix3x3< T >::operator/=( const TMatrix3x3& iOther ) {
    return  ( *this *= iOther.Inverse() );
}



// Other Operators
template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >::tColumn& TMatrix3x3< T >::operator[]( int iIndex ) {
    ULIS3_ASSERT( iIndex >= 0 && iIndex < 3, "Bad Index" );
    return  mCols[ iIndex ];
}

template< typename T >
ULIS3_MATRIX_FUNC const TMatrix3x3< T >::tColumn& TMatrix3x3< T >::operator[]( int iIndex ) const {
    ULIS3_ASSERT( iIndex >= 0 && iIndex < 3, "Bad Index" );
    return  mCols[ iIndex ];
}



// Binary arithmetic operator with scalar on left hand side
template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > operator+( T iValue, const TMatrix3x3< T >& iMat ) {
    return  TMatrix3x3< T >(
          iValue + iMat[0]
        , iValue + iMat[1]
        , iValue + iMat[2]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > operator-( T iValue, const TMatrix3x3< T >& iMat ) {
    return  TMatrix3x3< T >(
          iValue - iMat[0]
        , iValue - iMat[1]
        , iValue - iMat[2]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > operator*( T iValue, const TMatrix3x3< T >& iMat ) {
    return  TMatrix3x3< T >(
          iValue * iMat[0]
        , iValue * iMat[1]
        , iValue * iMat[2]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > operator/( T iValue, const TMatrix3x3< T >& iMat ) {
    return  TMatrix3x3< T >(
          iValue / iMat[0]
        , iValue / iMat[1]
        , iValue / iMat[2]
    );
}



// Binary arithmetic operator with scalar on right hand side
template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > operator+( const TMatrix3x3< T >& iMat, T iValue ) {
    return  TMatrix3x3< T >(
          iMat[0] + iValue
        , iMat[1] + iValue
        , iMat[2] + iValue
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > operator-( const TMatrix3x3< T >& iMat, T iValue ) {
    return  TMatrix3x3< T >(
          iMat[0] - iValue
        , iMat[1] - iValue
        , iMat[2] - iValue
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > operator*( const TMatrix3x3< T >& iMat, T iValue ) {
    return  TMatrix3x3< T >(
          iMat[0] * iValue
        , iMat[1] * iValue
        , iMat[2] * iValue
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > operator/( const TMatrix3x3< T >& iMat, T iValue ) {
    return  TMatrix3x3< T >(
          iMat[0] / iValue
        , iMat[1] / iValue
        , iMat[2] / iValue
    );
}



// Binary arithmetic operator with other matrix
template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > operator+( const TMatrix3x3< T >& iMat, const TMatrix3x3< T >& iOther ) {
    return  TMatrix3x3< T >(
          iMat[0] + iOther[0]
        , iMat[1] + iOther[1]
        , iMat[2] + iOther[2]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > operator-( const TMatrix3x3< T >& iMat, const TMatrix3x3< T >& iOther ) {
    return  TMatrix3x3< T >(
          iMat[0] - iOther[0]
        , iMat[1] - iOther[1]
        , iMat[2] - iOther[2]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > operator*( const TMatrix3x3< T >& iMat, const TMatrix3x3< T >& iOther ) {
    return  TMatrix3x3< T >(
        iMat[0][0] * iOther[0][0] + iMat[1][0] * iOther[0][1] + iMat[2][0] * iOther[0][2];
        iMat[0][0] * iOther[1][0] + iMat[1][0] * iOther[1][1] + iMat[2][0] * iOther[1][2];
        iMat[0][0] * iOther[2][0] + iMat[1][0] * iOther[2][1] + iMat[2][0] * iOther[2][2];
        iMat[0][1] * iOther[0][0] + iMat[1][1] * iOther[0][1] + iMat[2][1] * iOther[0][2];
        iMat[0][1] * iOther[1][0] + iMat[1][1] * iOther[1][1] + iMat[2][1] * iOther[1][2];
        iMat[0][1] * iOther[2][0] + iMat[1][1] * iOther[2][1] + iMat[2][1] * iOther[2][2];
        iMat[0][2] * iOther[0][0] + iMat[1][2] * iOther[0][1] + iMat[2][2] * iOther[0][2];
        iMat[0][2] * iOther[1][0] + iMat[1][2] * iOther[1][1] + iMat[2][2] * iOther[1][2];
        iMat[0][2] * iOther[2][0] + iMat[1][2] * iOther[2][1] + iMat[2][2] * iOther[2][2];
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T > operator/( const TMatrix3x3< T >& iMat, const TMatrix3x3< T >& iOther ) {
    return  iMat * iOther.Inverse();
}



// Binary matrix vector multiplication operators.
template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >::tColumn operator*( const TMatrix3x3< T >& iMat, const TMatrix3x3< T >::tRow& iRow ) {
    return  TVector2< T >(
          iMat[0][0] * iRow.x + iMat[1][0] * iRow.y + iMat[2][0] * iRow.z
        , iMat[0][1] * iRow.x + iMat[1][1] * iRow.y + iMat[2][1] * iRow.z
        , iMat[0][2] * iRow.x + iMat[1][2] * iRow.y + iMat[2][2] * iRow.z
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix3x3< T >::tRow operator*( const TMatrix3x3< T >::tColumn& iColum, const TMatrix3x3< T >& iMat ) {
    return  TVector2< T >(
          iMat[0][0] * iColum.x + iMat[0][1] * iColum.y + iMat[0][2] * iColum.z
        , iMat[1][0] * iColum.x + iMat[1][1] * iColum.y + iMat[1][2] * iColum.z
        , iMat[2][0] * iColum.x + iMat[2][1] * iColum.y + iMat[2][2] * iColum.z
    );
}

ULIS3_NAMESPACE_END

