// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Geometry.h
* @author       Clement Berthaud
* @brief        This file provides geometry class declarations.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// TVec2
template< typename T >
struct ULIS2_API TVec2
{
    T x;
    T y;

    TVec2() : x( 0 ), y( 0 ) {}
    TVec2( T ix, T iy ) : x( ix ), y( iy ) {};

    ULIS2_FORCEINLINE T Distance() const {                              return  sqrt( x * x + y *y ); }
    ULIS2_FORCEINLINE T DistanceSquared() const {                       return  x * x + y * y; }
    ULIS2_FORCEINLINE T ManhattanDistance() const {                     return  x + y; }
    ULIS2_FORCEINLINE float operator|( const TVec2& iOther ) const {   return  x * iOther.x + y * iOther.y; }
    ULIS2_FORCEINLINE float DotProduct( const TVec2& iOther ) {        return  ( *this | B ); }
    ULIS2_FORCEINLINE TVec2 operator+( const TVec2& iOther ) const {  return  TVec2( x + iOther.x, y + iOther.y ); }
    ULIS2_FORCEINLINE TVec2 operator-(const TVec2& iOther ) const {   return  TVec2( x - iOther.x, y - iOther.y ); }
    ULIS2_FORCEINLINE TVec2 operator-( float iValue ) const {          return  TVec2( x - iValue, y - iValue ); }
    ULIS2_FORCEINLINE TVec2 operator+( float iValue ) const {          return  TVec2( x + iValue, y + iValue ); }
    ULIS2_FORCEINLINE TVec2 operator*( float iValue ) const {          return  TVec2( x * iValue, y * iValue ); }
    ULIS2_FORCEINLINE TVec2 operator/( float iValue ) const {          return  TVec2( x / iValue, y / iValue ); }
    ULIS2_FORCEINLINE TVec2 operator*(const TVec2& iOther ) const {   return  TVec2( x * iOther.x, y * iOther.y ); }
    ULIS2_FORCEINLINE TVec2 operator/(const TVec2& iOther ) const {   return  TVec2( x / iOther.x, y / iOther.y ); }
    ULIS2_FORCEINLINE bool operator==(const TVec2& iOther ) const {    return  x == iOther.x && y == iOther.y; }
    ULIS2_FORCEINLINE bool operator!=(const TVec2& iOther ) const {    return x != iOther.x || y != iOther.y; }
    ULIS2_FORCEINLINE TVec2 operator-() const {                        return  TVec2(-x, -y, -Z); }
    ULIS2_FORCEINLINE TVec2 operator+=(const TVec2& iOther ) {        x += iOther.x; y += iOther.y; return  *this; }
    ULIS2_FORCEINLINE TVec2 operator-=(const TVec2& iOther ) {        x -= iOther.x; y -= iOther.y; return  *this; }
    ULIS2_FORCEINLINE TVec2 operator*=(float iValue) {                 x *= iValue; y *= iValue; return  *this; }
    ULIS2_FORCEINLINE TVec2 operator/=(float iValue ) {                x /= iValue; y /= iValue; return  *this; }
    ULIS2_FORCEINLINE TVec2 operator*=(const TVec2& iOther ) {        x *= iOther.x; y *= iOther.y; return  *this; }
    ULIS2_FORCEINLINE TVec2 operator/=(const TVec2& iOther ) {        x /= iOther.x; y /= iOther.y; return  *this; }
    ULIS2_FORCEINLINE float& operator[](int32 iIndex ) { ULIS2_ASSERT( iIndex >= 0 && iIndex < 3, "Bad Index" ); return  ( &x )[ iIndex ]; }
    ULIS2_FORCEINLINE float operator[]( int32 iIndex)const { ULIS2_ASSERT( iIndex >= 0 && iIndex < 3, "Bad Index" ); return  ( &x )[ iIndex ]; }
    ULIS2_FORCEINLINE void Normalize() { float dist = Distance(); x /= dist; y /= dist; }
};

/////////////////////////////////////////////////////
// FRect
struct ULIS2_API FRect
{
    int x;
    int y;
    int w;
    int h;

    FRect();
    FRect( int ix, int iy, int iW, int iH );
    static FRect FromXYWH( int ix, int iy, int iW, int iH );
    static FRect FromMinMax( int ixMin, int iyMin, int ixMax, int iyMax );
    FRect operator&( const FRect& iOther ) const;
    FRect operator|( const FRect& iOther ) const;
    bool operator==( const FRect& iOther ) const;
    int Area() const;
    void TransformAffine( const FTransform2D& iTransform );
    void TransformPerspective( const FTransform2D& iTransform );
    FRect TransformedAffine( const FTransform2D& iTransform ) const;
    FRect TransformedPerspective( const FTransform2D& iTransform ) const;
    void FitInPositiveRange();
    void Shift( const FVec2I& iVec );
    FVec2I GetShift() const;
};

ULIS2_NAMESPACE_END

