// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Mat2.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the TMat2 class.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Maths/Geometry/Vec2.h"
#include <cmath>

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TMat2
/// @brief      The TMat2 class provides a simple 2x2 square matrix class for
///             geometry applications.
/// @details    The TMat2 class is a template class that provides basic matrix
///             functionnalities, it can be used with any numeric types,
///             ranging from integer values to floating point values.
template< typename T >
class TMat2
{
public:
    /*! The row type. */
    typedef TVec2< T > tRow;

    /*! The column type. */
    typedef TVec2< T > tColumn;

private:
    /*! The rows of the matrix. */
    tRow mRows[2];

public:
    /*! Default constructor ( identity matrix ). */
    TMat2()
        : mRows { tRow( 1, 0 )
                , tRow( 0, 1 ) }
    {}

    /*! Constructor from input diagonal value. */
    TMat2( T iValue )
        : mRows { tRow( iValue, 0 )
                , tRow( 0, iValue ) }
    {}

    /*! Constructor from input cells values. */
    TMat2( T iM00, T iM10, T iM01, T iM11 )
        : mRows { tRow( iM00, iM10 )
                , tRow( iM01, iM11 ) }
    {}

    /*! Constructor from row vector values. */
    TMat2( const tRow& iRow0, const tRow& iRow1 )
        : mRows { iRow0
                , iRow1 }
    {}

    /*! Copy constructor. */
    TMat2( const TMat2& iOther )
        : mRows { iOther.mRows[0]
                , iOther.mRows[1] }
    {}

    /*! Conversion constructor from other matrix type. */
    template< typename U >
    TMat2( const TMat2< U >& iOther )
        : mRows { iOther.mRows[0]
                , iOther.mRows[1] }
    {}

    /*! Subscript accessor for matrix rows. */
    ULIS3_FORCEINLINE tRow& operator[]( int iIndex ) {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < 2, "Bad Index" );
        return  mRows[ iIndex ];
    }

    /*! Subscript accessor for const matrix rows. */
    ULIS3_FORCEINLINE const tRow& operator[]( int iIndex ) const {
        ULIS3_ASSERT( iIndex >= 0 && iIndex < 2, "Bad Index" );
        return  mRows[ iIndex ];
    }

    /*! Assignment operator from matrix. */
    ULIS3_FORCEINLINE TMat2& operator=( const TMat2& iOther );

    /*! Unary addition operator with matrix. */
    ULIS3_FORCEINLINE TMat2& operator+=( const TMat2& iOther );

    /*! Unary substraction operator with matrix. */
    ULIS3_FORCEINLINE TMat2& operator-=( const TMat2& iOther );

    /*! Unary multiplication operator with matrix. */
    ULIS3_FORCEINLINE TMat2& operator*=( const TMat2& iOther );

    /*! Unary division operator with matrix. */
    ULIS3_FORCEINLINE TMat2& operator/=( const TMat2& iOther );

    /*! Unary division operator with value. */
    ULIS3_FORCEINLINE TMat2& operator+=( T iValue );

    /*! Unary substraction operator with value. */
    ULIS3_FORCEINLINE TMat2& operator-=( T iValue );

    /*! Unary multiplication operator with value. */
    ULIS3_FORCEINLINE TMat2& operator*=( T iValue );

    /*! Unary division operator with value. */
    ULIS3_FORCEINLINE TMat2& operator/=( T iValue );

    /*! Unary negative operator. */
    ULIS3_FORCEINLINE TMat2 operator-() const;

    /*! Addition operator with matrix. */
    ULIS3_FORCEINLINE TMat2 operator+( const TMat2& iOther );

    /*! Substraction operator with matrix. */
    ULIS3_FORCEINLINE TMat2 operator-( const TMat2& iOther );

    /*! Multiplication operator with matrix. */
    ULIS3_FORCEINLINE TMat2 operator*( const TMat2& iOther );

    /*! Division operator with matrix. */
    ULIS3_FORCEINLINE TMat2 operator/( const TMat2& iOther );

    /*! Addition operator with value. */
    ULIS3_FORCEINLINE TMat2 operator+( T iValue );

    /*! Substraction operator with value. */
    ULIS3_FORCEINLINE TMat2 operator-( T iValue );

    /*! Multiplication operator with value. */
    ULIS3_FORCEINLINE TMat2 operator*( T iValue );

    /*! Division operator with value. */
    ULIS3_FORCEINLINE TMat2 operator/( T iValue );

    /*! Equality operator. */
    ULIS3_FORCEINLINE bool operator==( const TMat2& iOther );

    /*! Inequality operator. */
    ULIS3_FORCEINLINE bool operator!=( const TMat2& iOther );

    /*! Obtain the inverse of the matrix. */
    ULIS3_FORCEINLINE TMat2 Inverse();

    /*! Obtain the transpose of the matrix. */
    ULIS3_FORCEINLINE TMat2 Transpose();

    /*! Obtain the determinant of the matrix. */
    ULIS3_FORCEINLINE T Determinant();
};

/*! Binary matrix by row multiplication operator. */
template< typename T >
ULIS3_FORCEINLINE TMat2< T >::tColumn operator*( const TMat2< T >& iMat, const TMat2< T >::tRow& iRow );

/*! Binary column by matrix multiplication operator. */
template< typename T >
ULIS3_FORCEINLINE TMat2< T >::tRow operator*( const TMat2< T >::tColumn& iColum, const TMat2< T >& iMat );

ULIS3_NAMESPACE_END

