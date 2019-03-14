/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.ConstStr.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.Types.h"
#include "ULIS/Base/CompileTime/ULIS.Base.IntegerSequence.h"
#include "ULIS/Base/CompileTime/ULIS.Base.CRC32.h"

namespace ULIS {

/////////////////////////////////////////////////////
// const_str
constexpr bool      ct_is_digit     ( char c) { return c <= '9' && c >= '0'; }
constexpr int       ct_stoi_impl    ( const char* str, int value = 0) { return *str ? ct_is_digit(*str) ? ct_stoi_impl(str + 1, (*str - '0') + value * 10) : throw "compile-time-error: not a digit" : value; }
constexpr const int ct_stoi         ( const char* str) { return ct_stoi_impl(str); }
constexpr const int ct_strlen       ( const char* str ) { for( int l=0; true; ++l ) if( str[l] == '\0' ) return l; }
constexpr const int ct_findindex    ( char c, const char* str ) { int cind = 0; int lpos = 0; while(1) { if( str[cind] == c ) { break; } if( !ct_is_digit( str[cind] ) ) { ++lpos; } ++cind; } return lpos; }
constexpr bool      ct_strings_equal   ( char const * a, char const * b) { return *a == *b && (*a == '\0' || ct_strings_equal(a + 1, b + 1)); }

constexpr
const int
ct_indexof( const char* word, const char* str, int from = 0 )
{
    int la = ct_strlen( word ); int lbt = ct_strlen( str ) - from; int lb = ct_strlen( str ); bool exit = la > lbt; int ret = -1;
    if( !exit ) { int start = 0; int lpos = 0;
        for( int l = from; l <= lb; ++l ) {
            const char cw = word[lpos]; const char cs = str[l];
            if( lpos == la ) { ret = start; break; }
            if( cw == cs ) { if( lpos == 0 ) { start = l; } ++lpos; }
            else { lpos=0; }
        }
    }
    return ret;
}

template< int N >
struct const_str
{
    const char s[N];
    constexpr const char* Get() const { return s; }
    constexpr char operator[]( int i ) const { return s[i]; }
    constexpr bool operator==( const const_str& other ) const { return *s == *other.s && ( *s == '\0' || ct_strings_equal( s + 1, other.s + 1 ) ); }
    operator const char*() const { return s; }
    constexpr const int Size() const { return N; }
    constexpr const int Len() const { return N-1; }
    constexpr const int ToInt() const { return ct_stoi_impl( s ); }
    constexpr const bool IsNumber() const { bool ret = true; for( int i=0; i<Len(); ++i ) { if( !ct_is_digit( s[i] ) ) { ret = false; break; } } return ret; }
    constexpr const int FindIndex( char c ) const { return ct_findindex( c, s ); }
    constexpr const uint32 Hash() const { return COMPILE_TIME_CRC32_STR( s ); }
    constexpr const int IndexOf( const char* word, int from = 0 ) const { return ct_indexof( word, s, from ); }

    static constexpr const char make_const_str_substring_impl_getchar( const char* str, int start, int num ) { return str[num+start]; }
    template< int L, typename T, T... Nums > static constexpr const const_str< L > make_const_str_substring_impl(  const char* str, int start, ::ULIS::integer_sequence< T, Nums... > ) { return { make_const_str_substring_impl_getchar( str, start, Nums ) ..., '\0' }; }
    template< int L > static constexpr const const_str< L > make_const_str_substring( const char* str, int start = 0 ) { return make_const_str_substring_impl< L >( str, start, ::ULIS::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const const_str< L + 1 > Substring( int start = 0 ) const { return make_const_str_substring< L + 1 >( s, start );}
};

template< int N, typename T, T... Nums > static constexpr const const_str< N > make_const_str_impl( const char* str, ::ULIS::integer_sequence< T, Nums... > ) { return { str[Nums] ... }; }
template< int N > static constexpr const const_str< N > make_const_str( const char (&str)[N] ) { return make_const_str_impl< N >( str, ::ULIS::make_integer_sequence< int, N >() ); }
#define CONST_STR( i ) make_const_str( i )

/*
static constexpr const uint8 SeekIndexForChar( const char* ilayout, const char* imodel, uint8 num ) { return ::ULIS::ct_findindex( imodel[num], ilayout ); }
template <uint8 N, typename T, T... Nums> static constexpr const std::array<uint8, N-1> make_impl( const char* ilayout, const char (&imodel)[N], ::ULIS::integer_sequence<T, Nums...>) { return { SeekIndexForChar( ilayout, imodel, Nums ) ... }; }
template <uint8 N> static constexpr const std::array<uint8, N-1> make_index_from_string( const char* ilayout, const char (&imodel)[N]) { return make_impl( ilayout, imodel, ::ULIS::make_integer_sequence<uint8, N-1>()); }
*/

} // namespace ULIS
