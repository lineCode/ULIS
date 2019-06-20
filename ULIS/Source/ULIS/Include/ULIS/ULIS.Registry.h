/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.CompileTime.Registry.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once


namespace ULIS {
namespace _CT {

/////////////////////////////////////////////////////
// Compile-Time Index Registry
template< int S >
struct regt
{
    constexpr const int operator[]( int i ) const { return n[i]; }
    const uint32 n[S] = { 0 };
    constexpr const int Size() const { return S; }
    template< int N, typename T, T... Nums > constexpr const regt< N > push_back_impl( uint32 i, ::ULIS::_CT::integer_sequence< T, Nums... > ) const { return { n[Nums] ..., i }; }
    constexpr const regt< S + 1 > push_back( uint32 i ) const { return push_back_impl< S + 1 >( i, ::ULIS::_CT::make_integer_sequence< int, S >() ); }
};


/////////////////////////////////////////////////////
// Utilities for registry manipulations
#define ULIS_PREVIOUS( i ) BOOST_PP_SUB( i, 1 )
#define ULIS_CAT( a, b ) BOOST_PP_CAT( a, b )
#define ULIS_CREATE_REG( irname, i ) constexpr ::ULIS::_CT::regt< 1 > ULIS_CAT( irname,  __COUNTER__ ) = { i };
#define ULIS_APPEND_REG_IMPL( irname, i, c ) constexpr auto ULIS_CAT( irname,  c ) = ULIS_CAT( irname, ULIS_PREVIOUS( c ) ).push_back( i );
#define ULIS_APPEND_REG( irname, i ) ULIS_APPEND_REG_IMPL( irname, i, __COUNTER__ )
#define ULIS_ASSIGN_REG( irname ) ULIS_CAT( irname, ULIS_PREVIOUS( __COUNTER__ ) )


} // namespace _CT
} // namespace ULIS

