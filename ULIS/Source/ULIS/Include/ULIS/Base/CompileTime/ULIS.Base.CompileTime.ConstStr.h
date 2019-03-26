/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.CompileTime.ConstStr.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.Types.h"
#include "ULIS/Base/CompileTime/ULIS.Base.CompileTime.CharOp.h"
#include "ULIS/Base/CompileTime/ULIS.Base.CompileTime.IntegerSequence.h"
#include "ULIS/Base/CompileTime/ULIS.Base.CompileTime.CRC32.h"

namespace ULIS {
namespace nCT {


/////////////////////////////////////////////////////
// const_str
template< int N >
struct const_str
{
    const char s[N];
    constexpr const char* Get() const { return s; }
    constexpr char operator[]( int i ) const { return s[i]; }
    constexpr bool operator==( const const_str& other ) const { return ct_strings_equal( s, other.s ); }
    operator const char*() const { return s; }
    constexpr const int Size() const { return N; }
    constexpr const int Len() const { return N-1; }
    constexpr const int ToInt() const { return ct_stoi_impl( s ); }
    constexpr const bool IsNumber() const { bool ret = true; for( int i=0; i<Len(); ++i ) { if( !ct_is_digit( s[i] ) ) { ret = false; break; } } return ret; }
    //constexpr const int CharIndex( char c ) const { return ct_charindex( c, s ); }
    constexpr const uint32 CRC32() const { return COMPILE_TIME_CRC32_STR( s ); }
    constexpr const int IndexOf( const char* word, const int from = 0 ) const { return ct_indexof( word, s, from ); }

    //Substring
    static constexpr const char const_str_impl_getchar_substring( const char* str, int start, int num ) { return str[num+start]; }
    template< int L, typename T, T... Nums > static constexpr const const_str< L > make_const_str_substring_impl(  const char* str, int start, ::ULIS::nCT::integer_sequence< T, Nums... > ) { return { const_str_impl_getchar_substring( str, start, Nums ) ..., '\0' }; }
    template< int L > static constexpr const const_str< L > make_const_str_substring( const char* str, int start = 0 ) { return make_const_str_substring_impl< L >( str, start, ::ULIS::nCT::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const const_str< L + 1 > Substring( int start = 0 ) const { return make_const_str_substring< L + 1 >( s, start );}

    //Append
    static constexpr const char const_str_impl_getchar_append( const char* strA, const char* strB, int lenA, int num ) { return num < lenA ? strA[num] : strB[num-lenA]; }
    template< int L, typename T, T... Nums > static constexpr const const_str< L > make_const_str_append_impl(  const char* strA, const char* strB, ::ULIS::nCT::integer_sequence< T, Nums... > ) { return { const_str_impl_getchar_append( strA, strB, ct_strlen( strA ), Nums ) ..., '\0' }; }
    template< int L > static constexpr const const_str< L > make_const_str_append( const char* strA, const char* strB ) { return make_const_str_append_impl< L >( strA, strB, ::ULIS::nCT::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const const_str< N + L - 1 > Append( const char (&str)[L] ) const { return make_const_str_append< N + L - 1 >( s, str ); }
};


template< int N, typename T, T... Nums > static constexpr const const_str< N > make_const_str_impl( const char* str, ::ULIS::nCT::integer_sequence< T, Nums... > ) { return { str[Nums] ... }; }
template< int N > static constexpr const const_str< N > make_const_str( const char (&str)[N] ) { return make_const_str_impl< N >( str, ::ULIS::nCT::make_integer_sequence< int, N >() ); }
#define CONST_STR( i ) ::ULIS::nCT::make_const_str( i )


} // namespace nCT
} // namespace ULIS

