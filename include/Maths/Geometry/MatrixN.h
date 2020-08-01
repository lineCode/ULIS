// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         MatrixN.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TMatrixNxN class.
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
/// @class      TMatrixN
/// @brief      The TMatrixN class provides a simple NxN square matrix class for
///             geometry applications.
/// @details    The TMatrixN class is a template class that provides basic matrix
///             functionnalities, it can be used with any numeric types,
///             ranging from integer values to floating point values.
template< typename T, uint8 N >
class TMatrixN
{
private:
    /*! The columns of the matrix. */
    float m[N][N];

public:
    // Constructors
    /*! Default constructor ( identity matrix ). */
    ULIS3_MATRIX_FUNC TMatrix8x8();

    /*! Constructor from input diagonal value. */
    ULIS3_MATRIX_FUNC TMatrix8x8( T iValue );

    /*! Constructor from input cells values. */
    ULIS3_MATRIX_FUNC TMatrix8x8(
          T iM00, T iM01, T iM02, T iM03, T iM04, T iM05, T iM06, T iM07
        , T iM10, T iM11, T iM12, T iM13, T iM14, T iM15, T iM16, T iM17
        , T iM20, T iM21, T iM22, T iM23, T iM24, T iM25, T iM26, T iM27
        , T iM30, T iM31, T iM32, T iM33, T iM34, T iM35, T iM36, T iM37
        , T iM40, T iM41, T iM42, T iM43, T iM44, T iM45, T iM46, T iM47
        , T iM50, T iM51, T iM52, T iM53, T iM54, T iM55, T iM56, T iM57
        , T iM60, T iM61, T iM62, T iM63, T iM64, T iM65, T iM66, T iM67
        , T iM70, T iM71, T iM72, T iM73, T iM74, T iM75, T iM76, T iM77
    );

    /*! Constructor from row vector values. */
    ULIS3_MATRIX_FUNC TMatrix8x8(
          const tColumn& iCol0
        , const tColumn& iCol1
        , const tColumn& iCol2
        , const tColumn& iCol3
        , const tColumn& iCol4
        , const tColumn& iCol5
        , const tColumn& iCol6
        , const tColumn& iCol7
    );

    /*! Copy constructor. */
    ULIS3_MATRIX_FUNC TMatrix8x8( const TMatrix8x8& iOther );

    /*! Assignment operator from matrix. */
    ULIS3_MATRIX_FUNC TMatrix8x8& operator=( const TMatrix8x8& iOther );



    // Conversion
    /*! Conversion constructor from other matrix type. */
    template< typename U >
    ULIS3_MATRIX_FUNC TMatrix8x8( const TMatrix8x8< U >& iOther );



    // Named Functions
    /*! Obtain the inverse of the matrix. */
    ULIS3_MATRIX_FUNC TMatrix8x8 Inverse();

    /*! Obtain the transpose of the matrix. */
    ULIS3_MATRIX_FUNC TMatrix8x8 Transpose();

    /*! Obtain the determinant of the matrix. */
    ULIS3_MATRIX_FUNC T Determinant();



    // Boolean operators
    /*! Equality operator. */
    ULIS3_MATRIX_FUNC bool operator==( const TMatrix8x8& iOther );

    /*! Inequality operator. */
    ULIS3_MATRIX_FUNC bool operator!=( const TMatrix8x8& iOther );



    // Unary Negative Operator
    /*! Unary negative operator. */
    ULIS3_MATRIX_FUNC TMatrix8x8 operator-() const;



    // Unary arithmetic operator with scalar
    /*! Unary addition operator with value. */
    ULIS3_MATRIX_FUNC TMatrix8x8& operator+=( T iValue );

    /*! Unary substraction operator with value. */
    ULIS3_MATRIX_FUNC TMatrix8x8& operator-=( T iValue );

    /*! Unary multiplication operator with value. */
    ULIS3_MATRIX_FUNC TMatrix8x8& operator*=( T iValue );

    /*! Unary division operator with value. */
    ULIS3_MATRIX_FUNC TMatrix8x8& operator/=( T iValue );



    // Unary arithmetic operator with matrix
    /*! Unary addition operator with matrix. */
    ULIS3_MATRIX_FUNC TMatrix8x8& operator+=( const TMatrix8x8& iOther );

    /*! Unary substraction operator with matrix. */
    ULIS3_MATRIX_FUNC TMatrix8x8& operator-=( const TMatrix8x8& iOther );

    /*! Unary multiplication operator with matrix. */
    ULIS3_MATRIX_FUNC TMatrix8x8& operator*=( const TMatrix8x8& iOther );

    /*! Unary division operator with matrix. */
    ULIS3_MATRIX_FUNC TMatrix8x8& operator/=( const TMatrix8x8& iOther );



    // Other Operators
    /*! Subscript accessor for matrix columns. */
    ULIS3_MATRIX_FUNC tColumn& operator[]( int iIndex );

    /*! Subscript accessor for const matrix columns. */
    ULIS3_MATRIX_FUNC const tColumn& operator[]( int iIndex ) const;
};



// Constructors
template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >::TMatrix8x8()
    : mCols {
          tColumn( 1, 0, 0, 0, 0, 0, 0, 0 )
        , tColumn( 0, 1, 0, 0, 0, 0, 0, 0 )
        , tColumn( 0, 0, 1, 0, 0, 0, 0, 0 )
        , tColumn( 0, 0, 0, 1, 0, 0, 0, 0 )
        , tColumn( 0, 0, 0, 0, 1, 0, 0, 0 )
        , tColumn( 0, 0, 0, 0, 0, 1, 0, 0 )
        , tColumn( 0, 0, 0, 0, 0, 0, 1, 0 )
        , tColumn( 0, 0, 0, 0, 0, 0, 0, 1 )
    }
{}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >::TMatrix8x8( T iValue )
    : mCols {
          tColumn( iValue, 0, 0, 0, 0, 0, 0, 0 )
        , tColumn( 0, iValue, 0, 0, 0, 0, 0, 0 )
        , tColumn( 0, 0, iValue, 0, 0, 0, 0, 0 )
        , tColumn( 0, 0, 0, iValue, 0, 0, 0, 0 )
        , tColumn( 0, 0, 0, 0, iValue, 0, 0, 0 )
        , tColumn( 0, 0, 0, 0, 0, iValue, 0, 0 )
        , tColumn( 0, 0, 0, 0, 0, 0, iValue, 0 )
        , tColumn( 0, 0, 0, 0, 0, 0, 0, iValue )
    }
{}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >::TMatrix8x8(
      T iM00, T iM01, T iM02, T iM03, T iM04, T iM05, T iM06, T iM07
    , T iM10, T iM11, T iM12, T iM13, T iM14, T iM15, T iM16, T iM17
    , T iM20, T iM21, T iM22, T iM23, T iM24, T iM25, T iM26, T iM27
    , T iM30, T iM31, T iM32, T iM33, T iM34, T iM35, T iM36, T iM37
    , T iM40, T iM41, T iM42, T iM43, T iM44, T iM45, T iM46, T iM47
    , T iM50, T iM51, T iM52, T iM53, T iM54, T iM55, T iM56, T iM57
    , T iM60, T iM61, T iM62, T iM63, T iM64, T iM65, T iM66, T iM67
    , T iM70, T iM71, T iM72, T iM73, T iM74, T iM75, T iM76, T iM77
    )
    : mCols {
          tColumn( iM00, iM01, iM02, iM03, iM04, iM05, iM06, iM07 )
        , tColumn( iM10, iM11, iM12, iM13, iM14, iM15, iM16, iM17 )
        , tColumn( iM20, iM21, iM22, iM23, iM24, iM25, iM26, iM27 )
        , tColumn( iM30, iM31, iM32, iM33, iM34, iM35, iM36, iM37 )
        , tColumn( iM40, iM41, iM42, iM43, iM44, iM45, iM46, iM47 )
        , tColumn( iM50, iM51, iM52, iM53, iM54, iM55, iM56, iM57 )
        , tColumn( iM60, iM61, iM62, iM63, iM64, iM65, iM66, iM67 )
        , tColumn( iM70, iM71, iM72, iM73, iM74, iM75, iM76, iM77 )
    }
{}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >::TMatrix8x8(
      const tColumn& iCol0
    , const tColumn& iCol1
    , const tColumn& iCol2
    , const tColumn& iCol3
    , const tColumn& iCol4
    , const tColumn& iCol5
    , const tColumn& iCol6
    , const tColumn& iCol7
    )
    : mCols {
          iCol0
        , iCol1
        , iCol2
        , iCol3
        , iCol4
        , iCol5
        , iCol6
        , iCol7
    }
{}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >::TMatrix8x8( const TMatrix8x8< T >& iOther )
    : mCols {
          iOther.mCols[0]
        , iOther.mCols[1]
        , iOther.mCols[2]
        , iOther.mCols[3]
        , iOther.mCols[4]
        , iOther.mCols[5]
        , iOther.mCols[6]
        , iOther.mCols[7]
    }
{}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >& TMatrix8x8< T >::operator=( const TMatrix8x8< T >& iOther ) {
    for( int i = 0; i < 8; ++i )
        mCols[i] = iOther.mCols[i];
}



// Conversion
template< typename T >
template< typename U >
ULIS3_MATRIX_FUNC TMatrix8x8< T >::TMatrix8x8( const TMatrix8x8< U >& iOther )
    : mCols {
          tColumn( iOther.mCols[0] )
        , tColumn( iOther.mCols[1] )
        , tColumn( iOther.mCols[2] )
        , tColumn( iOther.mCols[3] )
        , tColumn( iOther.mCols[4] )
        , tColumn( iOther.mCols[5] )
        , tColumn( iOther.mCols[6] )
        , tColumn( iOther.mCols[7] )
    }
{}



// Named Functions
template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > TMatrix8x8< T >::Inverse() {
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > TMatrix8x8< T >::Transpose() {
}

template< typename T >
ULIS3_MATRIX_FUNC T TMatrix8x8< T >::Determinant() {
}



// Boolean operators
template< typename T >
ULIS3_MATRIX_FUNC bool TMatrix8x8< T >::operator==( const TMatrix8x8< T >& iOther ) {
    for( int i = 0; i < 8; ++i )
        if( mCols[i] != iOther.mCols[i] )
            return  false;

    return  true;
}

template< typename T >
ULIS3_MATRIX_FUNC bool TMatrix8x8< T >::operator!=( const TMatrix8x8< T >& iOther ) {
    return  !( *this == iOther );
}



// Unary Negative Operator
template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > TMatrix8x8< T >::operator-() const {
    return  TMatrix8x8< T >(
          -mCols[0]
        , -mCols[1]
        , -mCols[2]
        , -mCols[3]
        , -mCols[4]
        , -mCols[5]
        , -mCols[6]
        , -mCols[7]
    );
}



// Unary arithmetic operator with scalar
template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >& TMatrix8x8< T >::operator+=( T iValue ) {
    for( int i = 0; i < 8; ++i )
        mCols[i] += iValue;
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >& TMatrix8x8< T >::operator-=( T iValue ) {
    for( int i = 0; i < 8; ++i )
        mCols[i] -= iValue;
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >& TMatrix8x8< T >::operator*=( T iValue ) {
    for( int i = 0; i < 8; ++i )
        mCols[i] *= iValue;
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >& TMatrix8x8< T >::operator/=( T iValue ) {
    for( int i = 0; i < 8; ++i )
        mCols[i] /= iValue;
}



// Unary arithmetic operator with matrix
template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >& TMatrix8x8< T >::operator+=( const TMatrix8x8& iOther ) {
    for( int i = 0; i < 8; ++i )
        mCols[i] += iOther.mCols[i];
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >& TMatrix8x8< T >::operator-=( const TMatrix8x8& iOther ) {
    for( int i = 0; i < 8; ++i )
        mCols[i] -= iOther.mCols[i];
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >& TMatrix8x8< T >::operator*=( const TMatrix8x8& iOther ) {
    return  ( *this = *this * iOther );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >& TMatrix8x8< T >::operator/=( const TMatrix8x8& iOther ) {
    return  ( *this *= iOther.Inverse() );
}



// Other Operators
template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >::tColumn& TMatrix8x8< T >::operator[]( int iIndex ) {
    ULIS3_ASSERT( iIndex >= 0 && iIndex < 8, "Bad Index" );
    return  mCols[ iIndex ];
}

template< typename T >
ULIS3_MATRIX_FUNC const TMatrix8x8< T >::tColumn& TMatrix8x8< T >::operator[]( int iIndex ) const {
    ULIS3_ASSERT( iIndex >= 0 && iIndex < 8, "Bad Index" );
    return  mCols[ iIndex ];
}



// Binary arithmetic operator with scalar on left hand side
template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > operator+( T iValue, const TMatrix8x8< T >& iMat ) {
    return  TMatrix8x8< T >(
          iValue + iMat[0]
        , iValue + iMat[1]
        , iValue + iMat[2]
        , iValue + iMat[3]
        , iValue + iMat[4]
        , iValue + iMat[5]
        , iValue + iMat[6]
        , iValue + iMat[7]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > operator-( T iValue, const TMatrix8x8< T >& iMat ) {
    return  TMatrix8x8< T >(
          iValue - iMat[0]
        , iValue - iMat[1]
        , iValue - iMat[2]
        , iValue - iMat[3]
        , iValue - iMat[4]
        , iValue - iMat[5]
        , iValue - iMat[6]
        , iValue - iMat[7]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > operator*( T iValue, const TMatrix8x8< T >& iMat ) {
    return  TMatrix8x8< T >(
          iValue * iMat[0]
        , iValue * iMat[1]
        , iValue * iMat[2]
        , iValue * iMat[3]
        , iValue * iMat[4]
        , iValue * iMat[5]
        , iValue * iMat[6]
        , iValue * iMat[7]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > operator/( T iValue, const TMatrix8x8< T >& iMat ) {
    return  TMatrix8x8< T >(
          iValue / iMat[0]
        , iValue / iMat[1]
        , iValue / iMat[2]
        , iValue / iMat[3]
        , iValue / iMat[4]
        , iValue / iMat[5]
        , iValue / iMat[6]
        , iValue / iMat[7]
    );
}



// Binary arithmetic operator with scalar on right hand side
template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > operator+( const TMatrix8x8< T >& iMat, T iValue ) {
    return  TMatrix8x8< T >(
          iMat[0] + iValue
        , iMat[1] + iValue
        , iMat[2] + iValue
        , iMat[3] + iValue
        , iMat[4] + iValue
        , iMat[5] + iValue
        , iMat[6] + iValue
        , iMat[7] + iValue
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > operator-( const TMatrix8x8< T >& iMat, T iValue ) {
    return  TMatrix8x8< T >(
          iMat[0] - iValue
        , iMat[1] - iValue
        , iMat[2] - iValue
        , iMat[3] - iValue
        , iMat[4] - iValue
        , iMat[5] - iValue
        , iMat[6] - iValue
        , iMat[7] - iValue
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > operator*( const TMatrix8x8< T >& iMat, T iValue ) {
    return  TMatrix8x8< T >(
          iMat[0] * iValue
        , iMat[1] * iValue
        , iMat[2] * iValue
        , iMat[3] * iValue
        , iMat[4] * iValue
        , iMat[5] * iValue
        , iMat[6] * iValue
        , iMat[7] * iValue
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > operator/( const TMatrix8x8< T >& iMat, T iValue ) {
    return  TMatrix8x8< T >(
          iMat[0] / iValue
        , iMat[1] / iValue
        , iMat[2] / iValue
        , iMat[3] / iValue
        , iMat[4] / iValue
        , iMat[5] / iValue
        , iMat[6] / iValue
        , iMat[7] / iValue
    );
}



// Binary arithmetic operator with other matrix
template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > operator+( const TMatrix8x8< T >& iMat, const TMatrix8x8< T >& iOther ) {
    return  TMatrix8x8< T >(
          iMat[0] + iOther[0]
        , iMat[1] + iOther[1]
        , iMat[2] + iOther[2]
        , iMat[3] + iOther[3]
        , iMat[4] + iOther[4]
        , iMat[5] + iOther[5]
        , iMat[6] + iOther[6]
        , iMat[7] + iOther[7]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > operator-( const TMatrix8x8< T >& iMat, const TMatrix8x8< T >& iOther ) {
    return  TMatrix8x8< T >(
          iMat[0] - iOther[0]
        , iMat[1] - iOther[1]
        , iMat[2] - iOther[2]
        , iMat[3] - iOther[3]
        , iMat[4] - iOther[4]
        , iMat[5] - iOther[5]
        , iMat[6] - iOther[6]
        , iMat[7] - iOther[7]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > operator*( const TMatrix8x8< T >& iMat, const TMatrix8x8< T >& iOther ) {
    const TVec8< T > colA0 = iMat[0];
    const TVec8< T > colA1 = iMat[1];
    const TVec8< T > colA2 = iMat[2];
    const TVec8< T > colA3 = iMat[3];
    const TVec8< T > colA4 = iMat[4];
    const TVec8< T > colA5 = iMat[5];
    const TVec8< T > colA6 = iMat[6];
    const TVec8< T > colA7 = iMat[7];
    const TVec8< T > colB0 = iOther[0];
    const TVec8< T > colB1 = iOther[1];
    const TVec8< T > colB2 = iOther[2];
    const TVec8< T > colB3 = iOther[3];
    const TVec8< T > colB4 = iOther[4];
    const TVec8< T > colB5 = iOther[5];
    const TVec8< T > colB6 = iOther[6];
    const TVec8< T > colB7 = iOther[7];

    return  TMatrix8x8< T >(
          colA0 * colB0[0] + colA1 * colB0[1] + colA2 * colB0[2] + colA3 * colB0[3] + colA4 * colB0[4] + colA5 * colB0[5] + colA6 * colB0[6] + colA7 * colB0[7]
        , colA0 * colB1[0] + colA1 * colB1[1] + colA2 * colB1[2] + colA3 * colB1[3] + colA4 * colB1[4] + colA5 * colB1[5] + colA6 * colB1[6] + colA7 * colB1[7]
        , colA0 * colB2[0] + colA1 * colB2[1] + colA2 * colB2[2] + colA3 * colB2[3] + colA4 * colB2[4] + colA5 * colB2[5] + colA6 * colB2[6] + colA7 * colB2[7]
        , colA0 * colB3[0] + colA1 * colB3[1] + colA2 * colB3[2] + colA3 * colB3[3] + colA4 * colB3[4] + colA5 * colB3[5] + colA6 * colB3[6] + colA7 * colB3[7]
        , colA0 * colB4[0] + colA1 * colB4[1] + colA2 * colB4[2] + colA3 * colB4[3] + colA4 * colB4[4] + colA5 * colB4[5] + colA6 * colB4[6] + colA7 * colB4[7]
        , colA0 * colB5[0] + colA1 * colB5[1] + colA2 * colB5[2] + colA3 * colB5[3] + colA4 * colB5[4] + colA5 * colB5[5] + colA6 * colB5[6] + colA7 * colB5[7]
        , colA0 * colB6[0] + colA1 * colB6[1] + colA2 * colB6[2] + colA3 * colB6[3] + colA4 * colB6[4] + colA5 * colB6[5] + colA6 * colB6[6] + colA7 * colB6[7]
        , colA0 * colB7[0] + colA1 * colB7[1] + colA2 * colB7[2] + colA3 * colB7[3] + colA4 * colB7[4] + colA5 * colB7[5] + colA6 * colB7[6] + colA7 * colB7[7]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T > operator/( const TMatrix8x8< T >& iMat, const TMatrix8x8< T >& iOther ) {
    return  iMat * iOther.Inverse();
}



// Binary matrix vector multiplication operators.
template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >::tColumn operator*( const TMatrix8x8< T >& iMat, const TMatrix8x8< T >::tRow& iRow ) {
    return  TVector8< T >(
          iMat[0][0] * iRow[0] + iMat[1][0] * iRow[1] + iMat[2][0] * iRow[2] + iMat[3][0] * iRow[3] + iMat[4][0] * iRow[4] + iMat[5][0] * iRow[5] + iMat[6][0] * iRow[6] + iMat[7][0] * iRow[7]
        , iMat[0][1] * iRow[0] + iMat[1][1] * iRow[1] + iMat[2][1] * iRow[2] + iMat[3][1] * iRow[3] + iMat[4][1] * iRow[4] + iMat[5][1] * iRow[5] + iMat[6][1] * iRow[6] + iMat[7][1] * iRow[7]
        , iMat[0][2] * iRow[0] + iMat[1][2] * iRow[1] + iMat[2][2] * iRow[2] + iMat[3][2] * iRow[3] + iMat[4][2] * iRow[4] + iMat[5][2] * iRow[5] + iMat[6][2] * iRow[6] + iMat[7][2] * iRow[7]
        , iMat[0][3] * iRow[0] + iMat[1][3] * iRow[1] + iMat[2][3] * iRow[2] + iMat[3][3] * iRow[3] + iMat[4][3] * iRow[4] + iMat[5][3] * iRow[5] + iMat[6][3] * iRow[6] + iMat[7][3] * iRow[7]
        , iMat[0][4] * iRow[0] + iMat[1][4] * iRow[1] + iMat[2][4] * iRow[2] + iMat[3][4] * iRow[3] + iMat[4][4] * iRow[4] + iMat[5][4] * iRow[5] + iMat[6][4] * iRow[6] + iMat[7][4] * iRow[7]
        , iMat[0][5] * iRow[0] + iMat[1][5] * iRow[1] + iMat[2][5] * iRow[2] + iMat[3][5] * iRow[3] + iMat[4][5] * iRow[4] + iMat[5][5] * iRow[5] + iMat[6][5] * iRow[6] + iMat[7][5] * iRow[7]
        , iMat[0][6] * iRow[0] + iMat[1][6] * iRow[1] + iMat[2][6] * iRow[2] + iMat[3][6] * iRow[3] + iMat[4][6] * iRow[4] + iMat[5][6] * iRow[5] + iMat[6][6] * iRow[6] + iMat[7][6] * iRow[7]
        , iMat[0][7] * iRow[0] + iMat[1][7] * iRow[1] + iMat[2][7] * iRow[2] + iMat[3][7] * iRow[3] + iMat[4][7] * iRow[4] + iMat[5][7] * iRow[5] + iMat[6][7] * iRow[6] + iMat[7][7] * iRow[7]
    );
}

template< typename T >
ULIS3_MATRIX_FUNC TMatrix8x8< T >::tRow operator*( const TMatrix8x8< T >::tColumn& iCol, const TMatrix8x8< T >& iMat ) {
    return  TVector8< T >(
          iMat[0][0] * iCol[0] + iMat[0][1] * iCol[1] + iMat[0][2] * iCol[2] + iMat[0][3] * iCol[3] + iMat[0][4] * iCol[4] + iMat[0][5] * iCol[5] + iMat[0][6] * iCol[6] + iMat[0][7] * iCol[7]
        , iMat[1][0] * iCol[0] + iMat[1][1] * iCol[1] + iMat[1][2] * iCol[2] + iMat[1][3] * iCol[3] + iMat[1][4] * iCol[4] + iMat[1][5] * iCol[5] + iMat[1][6] * iCol[6] + iMat[1][7] * iCol[7]
        , iMat[2][0] * iCol[0] + iMat[2][1] * iCol[1] + iMat[2][2] * iCol[2] + iMat[2][3] * iCol[3] + iMat[2][4] * iCol[4] + iMat[2][5] * iCol[5] + iMat[2][6] * iCol[6] + iMat[2][7] * iCol[7]
        , iMat[3][0] * iCol[0] + iMat[3][1] * iCol[1] + iMat[3][2] * iCol[2] + iMat[3][3] * iCol[3] + iMat[3][4] * iCol[4] + iMat[3][5] * iCol[5] + iMat[3][6] * iCol[6] + iMat[3][7] * iCol[7]
        , iMat[4][0] * iCol[0] + iMat[4][1] * iCol[1] + iMat[4][2] * iCol[2] + iMat[4][3] * iCol[3] + iMat[4][4] * iCol[4] + iMat[4][5] * iCol[5] + iMat[4][6] * iCol[6] + iMat[4][7] * iCol[7]
        , iMat[5][0] * iCol[0] + iMat[5][1] * iCol[1] + iMat[5][2] * iCol[2] + iMat[5][3] * iCol[3] + iMat[5][4] * iCol[4] + iMat[5][5] * iCol[5] + iMat[5][6] * iCol[6] + iMat[5][7] * iCol[7]
        , iMat[6][0] * iCol[0] + iMat[6][1] * iCol[1] + iMat[6][2] * iCol[2] + iMat[6][3] * iCol[3] + iMat[6][4] * iCol[4] + iMat[6][5] * iCol[5] + iMat[6][6] * iCol[6] + iMat[6][7] * iCol[7]
        , iMat[7][0] * iCol[0] + iMat[7][1] * iCol[1] + iMat[7][2] * iCol[2] + iMat[7][3] * iCol[3] + iMat[7][4] * iCol[4] + iMat[7][5] * iCol[5] + iMat[7][6] * iCol[6] + iMat[7][7] * iCol[7]
    );
}

ULIS3_NAMESPACE_END

