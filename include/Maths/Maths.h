// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Maths.h
* @author       Clement Berthaud
* @brief        This file provides the FMaths class declaration.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include <cmath>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FMaths
struct ULIS2_API FMaths
{
    // Do not change this value !
    static constexpr float kEpsilonf = .000001f;
    static constexpr double kPId = 3.1415926535897932;
    static constexpr float  kPIf = 3.14159265f;

    template< typename T >
    static ULIS2_FORCEINLINE T Min( T iA, T iB ) {
        return  iA < iB ? iA : iB;
    }

    template< typename T >
    static ULIS2_FORCEINLINE T Max( T iA, T iB ) {
        return  iA > iB ? iA : iB;
    }

    template< typename T >
    static ULIS2_FORCEINLINE T Min3( T iA, T iB, T iC ) {
        return  Min( iA, Min( iB, iC ) );
    }

    template< typename T >
    static ULIS2_FORCEINLINE T Max3( T iA, T iB, T iC ) {
        return  Max( iA, Max( iB, iC ) );
    }

    template< typename T >
    static ULIS2_FORCEINLINE T Clamp( T iValue, T iMin, T iMax ) {
        return  Max( iMin, Min( iValue, iMax ) );
    }

    template< typename T >
    static ULIS2_FORCEINLINE T Abs( T iA ) {
        return ( iA < 0 ? -iA : iA );
    }

    template< typename T >
    static ULIS2_FORCEINLINE T Sign( T iValue ) {
        return  iValue < T(0) ? T(-1) : T(1);
    }

    static ULIS2_FORCEINLINE double RadToDeg( double iRad )
    {
        return ( iRad * 180 / FMaths::kPId );
    }

    static ULIS2_FORCEINLINE double DegToRad( double iDeg )
    {
        return ( iDeg * FMaths::kPId / 180 );
    }

    static ULIS2_FORCEINLINE int IntegerPartOfNumber( float iNumber )
    {
        return (int)iNumber;
    }

    static ULIS2_FORCEINLINE float FloatingPartOfNumber( float iNumber )
    {
        if ( iNumber > 0 )
            return iNumber - IntegerPartOfNumber( iNumber );
        else
            return iNumber - ( IntegerPartOfNumber( iNumber ) + 1 );
    }

    static ULIS2_FORCEINLINE int RoundNumber( float iNumber )
    {
        return  (int)( iNumber + 0.5f );
    }

    template< typename T >
    static ULIS2_FORCEINLINE T Ceil( T iValue )
    {
        return  ceil( iValue );
    }

    template< typename T >
    static ULIS2_FORCEINLINE T Floor( T iValue )
    {
        return  floor( iValue );
    }

    template< typename T >
    static ULIS2_FORCEINLINE T RoundAwayFromZero( T iValue )
    {
        return  iValue < 0 ? (T)floor( iValue ) : (T)ceil( iValue );
    }

    template< typename T >
    static ULIS2_FORCEINLINE T RoundTowardsZero( T iValue )
    {
        return  iValue < 0 ? (T)ceil( iValue ) : (T)floor( iValue );
    }

    static ULIS2_FORCEINLINE bool EpsilonComp( float iA, float iB )
    {
        return  Abs( iA - iB ) <= kEpsilonf;
    }

}; // struct FMaths

ULIS2_NAMESPACE_END

