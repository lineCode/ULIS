/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Maths.Utility.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

# define PI           3.14159265358979323846  /* pi */

namespace ULIS {
/////////////////////////////////////////////////////
// FMath
struct FMath
{

    static constexpr float epsilon = .000001;

    template< typename T >
    static inline T Min( T iA, T iB ) {
        return  iA < iB ? iA : iB;
    }

    template< typename T >
    static inline T Max( T iA, T iB ) {
        return  iA > iB ? iA : iB;
    }

    template< typename T >
    static inline T Min3( T iA, T iB, T iC ) {
        return  Min( iA, Min( iB, iC ) );
    }

    template< typename T >
    static inline T Max3( T iA, T iB, T iC ) {
        return  Max( iA, Max( iB, iC ) );
    }

    template< typename T >
    static inline T Clamp( T iValue, T iMin, T iMax ) {
        return  Max( iMin, Min( iValue, iMax ) );
    }
    
    template< typename T >
    static inline T Abs( T iA ) {
        return ( iA < 0 ? -iA : iA );
    }
    
    static inline double RadToDeg( double iRad )
    {
        return ( iRad * 180 / PI );
    }
    
    static inline double DegToRad( double iDeg )
    {
        return ( iDeg * PI / 180 );
    }
    
    static inline int IntegerPartOfNumber( float iNumber )
    {
        return (int)iNumber;
    }
    
    float FloatingPartOfNumber( float iNumber )
    {
        if ( iNumber > 0 )
            return iNumber - IntegerPartOfNumber( iNumber );
        else
            return iNumber - ( IntegerPartOfNumber( iNumber ) + 1 );
    }
    
    static inline int RoundNumber( float iNumber )
    {
        return (int)(iNumber + 0.5) ;
    }

    template< typename T >
    static  inline T RoundAwayFromZero( T iValue )
    {
      return iValue < 0 ? (T)floor( iValue ) : (T)ceil( iValue );
    }

}; // struct FMath


} // namespace ULIS

