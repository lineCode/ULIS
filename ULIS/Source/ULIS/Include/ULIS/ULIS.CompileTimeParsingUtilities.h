/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Block.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

namespace ULIS {

constexpr bool ct_is_digit(char c) { return c <= '9' && c >= '0'; }
constexpr int ct_stoi_impl(const char* str, int value = 0) { return *str ? ct_is_digit(*str) ? ct_stoi_impl(str + 1, (*str - '0') + value * 10) : throw "compile-time-error: not a digit" : value; }
constexpr const int ct_stoi(const char* str) { return ct_stoi_impl(str); }
constexpr const int ct_strlen( const char* str ) { for( int l=0; true; ++l ) if( str[l] == '\0' ) return l; }
constexpr const int ct_findindex( char c, const char* str )
{
    /*
    int i = -1;
    if( c == 'R' ) i = 0;
    if( c == 'G' ) i = 1;
    if( c == 'B' ) i = 2;
    if( c == 'A' ) i = 3;
    return i;
    */

    int cind = 0;
    int lpos = 0;
    while(1)
    {
        if( str[cind] == c )
            break;

        if( !ct_is_digit( str[cind] ) )
            ++lpos;
        ++cind;
    }
    return lpos;
}


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


} // namespace ULIS
