/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Data.SpecReg.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <utility>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>


namespace ULIS {

/////////////////////////////////////////////////////
// Compile-Time Index Registry
template< int S >
struct TSpecReg
{
    const uint32_t n[S] = { 0 };
    constexpr const uint32_t operator[]( int i ) const { return n[i]; }
    constexpr const int Size()              const { return S; }

    template< int N, typename T, T... Nums > constexpr const TSpecReg< N > push_back_impl( uint32_t i, std::integer_sequence< T, Nums... > ) const { return { n[Nums] ..., i }; }
    constexpr const TSpecReg< S + 1 > push_back( uint32_t i ) const { return push_back_impl< S + 1 >( i, std::make_integer_sequence< int, S >() ); }
};

/////////////////////////////////////////////////////
// Utilities for registry manipulations
#define ULIS_PREVIOUS( i )                      BOOST_PP_SUB( i, 1 )
#define ULIS_CAT( a, b )                        BOOST_PP_CAT( a, b )
#define ULIS_CREATE_REG( irname, i )            constexpr ::ULIS::TSpecReg< 1 > ULIS_CAT( irname,  __COUNTER__ ) = { i };
#define ULIS_APPEND_REG_IMPL( irname, i, c )    constexpr auto ULIS_CAT( irname,  c ) = ULIS_CAT( irname, ULIS_PREVIOUS( c ) ).push_back( i );
#define ULIS_APPEND_REG( irname, i )            ULIS_APPEND_REG_IMPL( irname, i, __COUNTER__ )
#define ULIS_ASSIGN_REG( irname )               ULIS_CAT( irname, ULIS_PREVIOUS( __COUNTER__ ) )
#define ULIS_ASSIGN_REG_COUNT                   ULIS_PREVIOUS( __COUNTER__ )
#define ULIS_REG                                constexpr auto

} // namespace ULIS
