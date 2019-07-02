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


namespace ULIS {

static float epsilon = .000001;

template< typename T > T Min( T iA, T iB )
{
    return  iA < iB ? iA : iB;
}

template< typename T > T Max( T iA, T iB )
{
    return  iA > iB ? iA : iB;
}

template< typename T > T Min3( T iA, T iB, T iC )
{
    return  Min( iA, Min( iB, iC ) );
}

template< typename T > T Max3( T iA, T iB, T iC )
{
    return  Max( iA, Max( iB, iC ) );
}

template< typename T > T Clamp( T iValue, T iMin, T iMax )
{
    return  Max( iMin, Min( iValue, iMax ) );
}


} // namespace ULIS

