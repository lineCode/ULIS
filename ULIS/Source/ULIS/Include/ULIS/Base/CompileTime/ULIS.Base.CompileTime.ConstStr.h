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
namespace _CT {


/////////////////////////////////////////////////////
// const_str Constexpr cpp0x compliant string manipulation operations
template< int N >
struct const_str
{
    /* primary container holding the cstr */
    const char s[N];

    /* utility functions */
    constexpr operator const char*()                        const { return s; }
    constexpr const char* Get()                             const { return s; }
    constexpr operator uint32()                             const { return CRC32(); }
    constexpr char  operator[]( int i )                     const { return s[i]; }
    constexpr bool  operator==( const const_str& other )    const { return streq( s, other.s ); }
    constexpr int Size()                                    const { return N; }
    constexpr int ToInt()                                   const { return stoi( s ); }
    constexpr bool IsNumber()                               const { return is_number( s ); }
    constexpr uint32 CRC32()                                const { return ULIS_COMPILE_TIME_CRC32_STR( s ); }
    constexpr int IndexOf( const char* w, int f=0 )         const { return indexof( w, s, f ); }

    /* substring */
    static constexpr const char const_str_impl_getchar_substring( const char* str, int start, int num ) { return str[num+start]; }
    template< int L, typename T, T... Nums > static constexpr const const_str< L > make_const_str_substring_impl(  const char* str, int start, ::ULIS::_CT::integer_sequence< T, Nums... > ) { return { const_str_impl_getchar_substring( str, start, Nums ) ..., '\0' }; }
    template< int L > static constexpr const const_str< L > make_const_str_substring( const char* str, int start = 0 ) { return make_const_str_substring_impl< L >( str, start, ::ULIS::_CT::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const const_str< L + 1 > Substring( int start = 0 ) const { return make_const_str_substring< L + 1 >( s, start );}

    /* append */
    static constexpr const char const_str_impl_getchar_append( const char* strA, const char* strB, int lenA, int num ) { return num < lenA ? strA[num] : strB[num-lenA]; }
    template< int L, typename T, T... Nums > static constexpr const const_str< L > make_const_str_append_impl(  const char* strA, const char* strB, ::ULIS::_CT::integer_sequence< T, Nums... > ) { return { const_str_impl_getchar_append( strA, strB, strlen( strA ), Nums ) ..., '\0' }; }
    template< int L > static constexpr const const_str< L > make_const_str_append( const char* strA, const char* strB ) { return make_const_str_append_impl< L >( strA, strB, ::ULIS::_CT::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const const_str< N + L - 1 > Append( const char (&str)[L] ) const { return make_const_str_append< N + L - 1 >( s, str ); }
};


/////////////////////////////////////////////////////
// const_str makers
/* construction for const_str, implementation from integer sequence */
template< int N, typename T, T... Nums >
constexpr const_str< N >
make_const_str_impl( const char* str, ::ULIS::_CT::integer_sequence< T, Nums... > )
{
    return { str[Nums] ... };
}

/* construction for const_str */
template< int N >
constexpr const_str< N >
make_const_str( const char (&str)[N] )
{
    return make_const_str_impl< N >( str, ::ULIS::_CT::make_integer_sequence< int, N >() );
}


/////////////////////////////////////////////////////
// const_str utility macro
/* utility shortcut for construction of const_str */
#define ULIS_CONST_STR( i ) ::ULIS::_CT::make_const_str( i )


} // namespace _CT
} // namespace ULIS

