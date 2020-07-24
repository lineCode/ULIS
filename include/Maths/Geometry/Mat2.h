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
struct TMat2
{
public:
    typedef TVec2< T > tRow;
    typedef TVec2< T > tColumn;

private:
    tRow mRows[2];

public:
    TMat2();
    TMat2( T iValue );
    TMat2( T iM00, T iM10, T iM01, T iM11 );
    TMat2( const tRow& iRow0, const tRow& iRow1 );
    TMat2( const TMat2& iOther );

    template< typename U >
    TMat2( const TMat2< U >& iOther );

    TMat2( const TMat3< T >& iMat );
    TMat2( const TMat4< T >& iMat );
    TMat2( const TMat8< T >& iMat );

    ULIS3_FORCEINLINE FVec2I Size() const;
    ULIS3_FORCEINLINE int Width() const;
    ULIS3_FORCEINLINE int Height() const;
    ULIS3_FORCEINLINE int Length() const;

    ULIS3_FORCEINLINE tRow& operator[]( int iIndex );
    ULIS3_FORCEINLINE const tRow& operator[]( int iIndex ) const;

    ULIS3_FORCEINLINE TMat2& operator=( const TMat2& iOther );
    ULIS3_FORCEINLINE TMat2& operator+=( const TMat2& iOther );
    ULIS3_FORCEINLINE TMat2& operator-=( const TMat2& iOther );
    ULIS3_FORCEINLINE TMat2& operator*=( const TMat2& iOther );
    ULIS3_FORCEINLINE TMat2& operator/=( const TMat2& iOther );

    ULIS3_FORCEINLINE TMat2& operator+=( T iValue );
    ULIS3_FORCEINLINE TMat2& operator-=( T iValue );
    ULIS3_FORCEINLINE TMat2& operator*=( T iValue );
    ULIS3_FORCEINLINE TMat2& operator/=( T iValue );

    ULIS3_FORCEINLINE TMat2 operator-() const;

    ULIS3_FORCEINLINE TMat2 operator+( const TMat2& iOther );
    ULIS3_FORCEINLINE TMat2 operator-( const TMat2& iOther );
    ULIS3_FORCEINLINE TMat2 operator*( const TMat2& iOther );
    ULIS3_FORCEINLINE TMat2 operator/( const TMat2& iOther );

    ULIS3_FORCEINLINE TMat2 operator+( T iValue );
    ULIS3_FORCEINLINE TMat2 operator-( T iValue );
    ULIS3_FORCEINLINE TMat2 operator*( T iValue );
    ULIS3_FORCEINLINE TMat2 operator/( T iValue );

    ULIS3_FORCEINLINE bool operator==( const TMat2& iOther );
    ULIS3_FORCEINLINE bool operator!=( const TMat2& iOther );

    ULIS3_FORCEINLINE TMat2 Inverse();
    ULIS3_FORCEINLINE TMat2 Transpose();
    ULIS3_FORCEINLINE TMat2 Adjoint();
    ULIS3_FORCEINLINE T Determinant();
};

template< typename T >
ULIS3_FORCEINLINE TMat2< T >::tColumn operator*( const TMat2< T >& iMat, const TMat2< T >::tRow& iRow );

template< typename T >
ULIS3_FORCEINLINE TMat2< T >::tRow operator*( const TMat2< T >::tColumn& iColum, const TMat2< T >& iMat );

ULIS3_NAMESPACE_END

