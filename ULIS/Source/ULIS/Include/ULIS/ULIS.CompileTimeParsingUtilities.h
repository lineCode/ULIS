/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Block.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <array>


namespace ULIS {

constexpr bool      ct_is_digit     ( char c) { return c <= '9' && c >= '0'; }
constexpr int       ct_stoi_impl    ( const char* str, int value = 0) { return *str ? ct_is_digit(*str) ? ct_stoi_impl(str + 1, (*str - '0') + value * 10) : throw "compile-time-error: not a digit" : value; }
constexpr const int ct_stoi         ( const char* str) { return ct_stoi_impl(str); }
constexpr const int ct_strlen       ( const char* str ) { for( int l=0; true; ++l ) if( str[l] == '\0' ) return l; }
constexpr const int ct_findindex    ( char c, const char* str ) { int cind = 0; int lpos = 0; while(1) { if( str[cind] == c ) { break; } if( !ct_is_digit( str[cind] ) ) { ++lpos; } ++cind; } return lpos; }
constexpr bool      strings_equal   ( char const * a, char const * b) { return *a == *b && (*a == '\0' || strings_equal(a + 1, b + 1)); }

constexpr
const int
ct_findnext( int from, const char* word, const char* str )
{
    int la = ct_strlen( word );
    int lbt = ct_strlen( str ) - from;
    int lb = ct_strlen( str );
    bool exit = la > lbt;
    int ret = -1;

    if( !exit )
    {
        int start = 0;
        int lpos = 0;
        for( int l = from; l <= lb; ++l )
        {
            const char cw = word[lpos];
            const char cs = str[l];

            if( lpos == la )
            {
                ret = start;
                break;
            }

            if( cw == cs )
            {
                if( lpos == 0 )
                    start = l;
                ++lpos;
            }
            else
            {
                lpos=0;
            }
        }
    }

    return ret;
}


constexpr const int ct_findwordstart( const char* word, const char* str ) { return ct_findnext( 0, word, str ); }

/*
template < int ... Nums >
struct indices
{
    template < int I >
    static constexpr auto append(boost::mpl::int_<I>)
    {
        return indices<Nums...,I>();
    }
};
 
constexpr indices<> make_indices(boost::mpl::int_<0>)
{
    return indices<>();
}
 
template < int I >
constexpr auto make_indices(boost::mpl::int_<I>)
{
    using prev = boost::mpl::int_<I-1>;
    return make_indices(prev()).append(prev());
}
*/


/// A type that represents a parameter pack of zero or more integers.
template<typename T, T... I>
struct integer_sequence
{
    static_assert( std::is_integral<T>::value, "Integral type" );

    using type = T;

    static constexpr T size = sizeof...(I);

    /// Generate an integer_sequence with an additional element.
    template<T N>
    using append = integer_sequence<T, I..., N>;

    using next = append<size>;
};

template<typename T, T... I>
constexpr T integer_sequence<T, I...>::size;

template<std::size_t... I>
using index_sequence = integer_sequence<std::size_t, I...>;

namespace detail
{
// Metafunction that generates an integer_sequence of T containing [0, N)
template<typename T, T Nt, std::size_t N>
    struct iota
    {
    static_assert( Nt >= 0, "N cannot be negative" );

    using type = typename iota<T, Nt-1, N-1>::type::next;
    };

// Terminal case of the recursive metafunction.
template<typename T, T Nt>
    struct iota<T, Nt, 0ul>
    {
    using type = integer_sequence<T>;
    };
}


// make_integer_sequence<T, N> is an alias for integer_sequence<T, 0,...N-1>
template<typename T, T N>
using make_integer_sequence = typename detail::iota<T, N, N>::type;

template<int N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;


// index_sequence_for<A, B, C> is an alias for index_sequence<0, 1, 2>
template<typename... Args>
using index_sequence_for = make_index_sequence<sizeof...(Args)>;


static constexpr const uint8 GetIndex( const char* ilayout, const char* imodel, uint8 num ) { return ::ULIS::ct_findindex( imodel[num], ilayout ); }
template <uint8 N, typename T, T... Nums> static constexpr const std::array<uint8, N-1> make_impl( const char* ilayout, const char (&imodel)[N], ::ULIS::integer_sequence<T, Nums...>) { return { GetIndex( ilayout, imodel, Nums ) ... }; }
template <uint8 N> static constexpr const std::array<uint8, N-1> make_index_from_string( const char* ilayout, const char (&imodel)[N]) { return make_impl( ilayout, imodel, ::ULIS::make_integer_sequence<uint8, N-1>()); }


struct Substring
{
    const char* str;
    int start, lenght;
};


static
constexpr
const Substring
ct_getsubstring( const char* str, int start, int end )
{
    return {str, start, end - start };
}


constexpr const int ct_substrstrlen( const Substring str )
{
    return str.lenght;
}



constexpr
const bool
ct_substreq( const Substring A, const Substring B )
{
    bool exit = A.lenght != B.lenght;
    int ret = false;
    if( !exit )
    {
        ret = true;
        for( int l = 0; l <= A.lenght; ++l )
        {
            const char cA = A.str[ l + A.start ];
            const char cB = B.str[ l + B.start ];

            if( cA != cB )
            {
                ret = false;
                break;
            }
        }
    }
    return ret;
}






static
constexpr
const char
GetChar( const char* str, int start, uint8 num )
{
    return str[num+start];
}

template< int N, typename T, T... Nums >
static
constexpr
const std::array< char, N >
ct_substring_impl( const char* str, int start, integer_sequence<T, Nums...> )
{
    return { GetChar( str, start, Nums ) ... };
}

template< int N >
static
constexpr
const std::array< char, N >
ct_substring( const char* str, int start )
{
    return ct_substring_impl< N >( str, start, make_integer_sequence<int, N>());
}

} // namespace ULIS
