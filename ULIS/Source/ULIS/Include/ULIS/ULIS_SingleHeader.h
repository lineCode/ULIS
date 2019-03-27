/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_SingleHeader.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <type_traits>
#include <stdint.h>

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define RESTRICT    __restrict
#define FORCEINLINE __forceinline
/////////////////////////////////////////////////////
// Fundamental Typedefs
typedef uint8_t     uint8;
typedef uint16_t    uint16;
typedef uint32_t    uint32;
typedef uint64_t    uint64;
typedef int8_t      int8;
typedef int16_t     int16;
typedef int32_t     int32;
typedef int64_t     int64;
typedef uint32      typefield;
typedef uint8       typefieldId;
typedef bool        typefieldBit;
typedef const char* cstr;

namespace _CT {
/////////////////////////////////////////////////////
// Short Macro
#define USFC( n, f, l, c, b ) for(int n=f;n<l;++n){if(c){break;}b}
/////////////////////////////////////////////////////
// CharOp
constexpr bool  isdig( char c )                     { return c >= '0' && c <= '9'; }
constexpr int   sslen( cstr s )                     { return *s ? 1 + sslen(s + 1) : 0; }
constexpr bool  isnum( cstr s )                     { bool r=1;for(int i=0;i<sslen(s);++i){if(!isdig(s[i])){r=0;break;}}return r; }
constexpr bool  ssequ( cstr a,  cstr b )            { return *a==*b && (*a =='\0' || ssequ(a+1,b+1)); }
constexpr int   sstoi( cstr s,  int v = 0 )         { return *s?isdig(*s)?sstoi(s+1,(*s-'0')+v*10):throw "error":v; }
constexpr int   indof( cstr w, cstr s, int f = 0 )  { int r = -1; bool e = false; for( int i = f; i <= sslen( s ); ++i ) { if( exit ) { break; } for( int j = 0; j <= sslen( w ); ++j ) { if( s[i+j] != w[j] ) { break; } if( j == sslen( w ) - 1 ) { r = i; e = true; break; } } } return r; }
/////////////////////////////////////////////////////
// CRC32
static constexpr unsigned int crc_table[256] = {
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
    0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
    0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
    0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
    0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
    0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
    0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
    0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
    0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
    0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
    0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
    0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
    0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
    0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
    0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
    0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
    0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
    0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
    0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
    0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
    0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
    0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
    0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
    0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
    0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
    0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
    0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
    0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
    0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
    0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
    0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
    0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};
template<int size, int idx = 0, class dummy = void>
struct MM{
    static constexpr unsigned int crc32(const char * str, unsigned int prev_crc = 0xFFFFFFFF) {
        return MM<size, idx+1>::crc32(str, (prev_crc >> 8) ^ crc_table[(prev_crc ^ str[idx]) & 0xFF] );
    }
};

template<int size, class dummy>
struct MM<size, size, dummy>{
    static constexpr unsigned int crc32(const char * str, unsigned int prev_crc = 0xFFFFFFFF) {
        return prev_crc^ 0xFFFFFFFF;
    }
};

#define ULIS_COMPILE_TIME_CRC32_STR(x) (MM<sizeof(x)-1>::crc32(x))
/////////////////////////////////////////////////////
// IntegerSequence
template<typename T, T... I>
struct integer_sequence {
    static_assert( std::is_integral<T>::value, "Integral type" );
    using type = T;
    static constexpr T size = sizeof...(I);
    template<T N> using append = integer_sequence<T, I..., N>;
    using next = append<size>;
};
template<typename T, T... I> constexpr T integer_sequence<T, I...>::size;
template<std::size_t... I> using index_sequence = integer_sequence<std::size_t, I...>;
namespace detail {
template<typename T, T Nt, std::size_t N>
struct iota {
    static_assert( Nt >= 0, "N cannot be negative" );
    using type = typename iota<T, Nt-1, N-1>::type::next;
};
template<typename T, T Nt> struct iota<T, Nt, 0ul> { using type = integer_sequence<T>; };
} // namespace detail
template<typename T, T N> using make_integer_sequence = typename detail::iota<T, N, N>::type;
template<int N> using make_index_sequence = make_integer_sequence<std::size_t, N>;
template<typename... Args> using index_sequence_for = make_index_sequence<sizeof...(Args)>;
/////////////////////////////////////////////////////
// ConstStr
template< int N >
struct const_str
{
    const char s[N];
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
    static constexpr const char const_str_impl_getchar_substring( const char* str, int start, int num ) { return str[num+start]; }
    template< int L, typename T, T... Nums > static constexpr const const_str< L > make_const_str_substring_impl(  const char* str, int start, ::ULIS::_CT::integer_sequence< T, Nums... > ) { return { const_str_impl_getchar_substring( str, start, Nums ) ..., '\0' }; }
    template< int L > static constexpr const const_str< L > make_const_str_substring( const char* str, int start = 0 ) { return make_const_str_substring_impl< L >( str, start, ::ULIS::_CT::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const const_str< L + 1 > Substring( int start = 0 ) const { return make_const_str_substring< L + 1 >( s, start );}
    static constexpr const char const_str_impl_getchar_append( const char* strA, const char* strB, int lenA, int num ) { return num < lenA ? strA[num] : strB[num-lenA]; }
    template< int L, typename T, T... Nums > static constexpr const const_str< L > make_const_str_append_impl(  const char* strA, const char* strB, ::ULIS::_CT::integer_sequence< T, Nums... > ) { return { const_str_impl_getchar_append( strA, strB, strlen( strA ), Nums ) ..., '\0' }; }
    template< int L > static constexpr const const_str< L > make_const_str_append( const char* strA, const char* strB ) { return make_const_str_append_impl< L >( strA, strB, ::ULIS::_CT::make_integer_sequence< int, L-1 >() ); }
    template< int L > constexpr const const_str< N + L - 1 > Append( const char (&str)[L] ) const { return make_const_str_append< N + L - 1 >( s, str ); }
};
template< int N, typename T, T... Nums > constexpr const_str< N > make_const_str_impl( const char* str, ::ULIS::_CT::integer_sequence< T, Nums... > ) { return { str[Nums] ... }; }
template< int N > constexpr const_str< N > make_const_str( const char (&str)[N] ) { return make_const_str_impl< N >( str, ::ULIS::_CT::make_integer_sequence< int, N >() ); }
#define ULIS_CONST_STR( i ) ::ULIS::_CT::make_const_str( i )
/////////////////////////////////////////////////////
// Registry
template< int S >
struct regt
{
    constexpr const int operator[]( int i ) const { return n[i]; }
    const uint32 n[S] = { 0 };
    constexpr const int Size() const { return S; }
    template< int N, typename T, T... Nums > constexpr const regt< N > push_back_impl( uint32 i, ::ULIS::_CT::integer_sequence< T, Nums... > ) const { return { n[Nums] ..., i }; }
    constexpr const regt< S + 1 > push_back( uint32 i ) const { return push_back_impl< S + 1 >( i, ::ULIS::_CT::make_integer_sequence< int, S >() ); }
};
#define ULIS_PREVIOUS( i ) BOOST_PP_SUB( i, 1 )
#define ULIS_CAT( a, b ) BOOST_PP_CAT( a, b )
#define ULIS_CREATE_REG( irname, i ) constexpr ::ULIS::_CT::regt< 1 > ULIS_CAT( irname,  __COUNTER__ ) = { i };
#define ULIS_APPEND_REG_IMPL( irname, i, c ) constexpr auto ULIS_CAT( irname,  c ) = ULIS_CAT( irname, ULIS_PREVIOUS( c ) ).push_back( i );
#define ULIS_APPEND_REG( irname, i ) ULIS_APPEND_REG_IMPL( irname, i, __COUNTER__ )
#define ULIS_ASSIGN_REG( irname ) ULIS_CAT( irname, ULIS_PREVIOUS( __COUNTER__ ) )
/////////////////////////////////////////////////////
// Enum and Keyword
#define ULIS_KEYS( ... ) ( __VA_ARGS__ )
#define ULIS_KEYWORDS_CAT( cat ) kw##cat
#define ULIS_ENUM_CAT( cat ) e##cat
#define ULIS_MAKE_KEYWORD_SEQ( r, data, elem ) BOOST_PP_STRINGIZE( elem )
#define ULIS_MAKE_ENUM_SEQ( r, data, elem ) BOOST_PP_CAT( k, elem ),
#define ULIS_MAKE_ENUM_KEYS_TUPLE_SEQ( r, data, elem ) ( BOOST_PP_CAT( k, elem ), elem ),
#define ULIS_KEYS_TO_KEYWORDS( cat, keys )                                              \
    constexpr const char* ULIS_KEYWORDS_CAT( cat )[] = {                                \
        BOOST_PP_SEQ_FOR_EACH( ULIS_MAKE_KEYWORD_SEQ, 0, BOOST_PP_TUPLE_TO_SEQ( keys ) ) };
#define ULIS_KEYS_TO_ENUM( cat, keys )                                                  \
    enum class ULIS_ENUM_CAT( cat ) : int {                                             \
        BOOST_PP_SEQ_FOR_EACH( ULIS_MAKE_ENUM_SEQ, 0, BOOST_PP_TUPLE_TO_SEQ( keys ) ) };
/////////////////////////////////////////////////////
// Keyword Token
#define ULIS_PARSE_KW_START_TOKEN __
#define ULIS_PARSE_KW_END_TOKEN _
#define ULIS_PARSE_KW_START_TOKEN_S BOOST_PP_STRINGIZE( ULIS_PARSE_KW_START_TOKEN )
#define ULIS_PARSE_KW_END_TOKEN_S BOOST_PP_STRINGIZE( ULIS_PARSE_KW_END_TOKEN )
#define ULIS_PARSE_KW_MAKE_TOKEN( i ) BOOST_PP_CAT( BOOST_PP_CAT( ULIS_PARSE_KW_START_TOKEN, i ), ULIS_PARSE_KW_END_TOKEN )
#define ULIS_PARSE_KW_MAKE_TOKEN_S( i ) BOOST_PP_STRINGIZE( ULIS_PARSE_KW_MAKE_TOKEN( i ) )
#define ULIS_SPEC_X( X, i ) BOOST_PP_CAT( ULIS_PARSE_KW_MAKE_TOKEN( X ), i )
#define ULIS_SPEC_ML( i ) ULIS_SPEC_X( ml, i )
#define ULIS_SPEC_AM( i ) ULIS_SPEC_X( am, i )
#define ULIS_SPEC_TP( i ) ULIS_SPEC_X( tp, i )
#define ULIS_SPEC_AS( i ) ULIS_SPEC_X( as, i )
#define ULIS_SPEC_CM( i ) ULIS_SPEC_X( cm, i )
#define ULIS_SPEC_EM( i ) ULIS_SPEC_X( em, i )
#define ULIS_BLOCK_SPEC( ... ) BOOST_PP_SEQ_CAT( BOOST_PP_TUPLE_TO_SEQ( ( __VA_ARGS__ ) ) )
#define ULIS_SPEC_TO_STR( spec ) ULIS_CONST_STR( BOOST_PP_STRINGIZE( spec ) )
#define ULIS_SPEC_SS( spec )    BOOST_PP_CAT( _SS, spec )
#define ULIS_SPEC_SH( spec )    BOOST_PP_CAT( _SH, spec )
/////////////////////////////////////////////////////
// String Parsing
#define ULIS_PARSE_KW_START(    _iss, ikw )     ( _iss.IndexOf( ikw ) + ::ULIS::_CT::strlen( ikw ) )
#define ULIS_PARSE_KW_NEXT(     _iss, ikw )     ( _iss.IndexOf( ULIS_PARSE_KW_END_TOKEN_S, ULIS_PARSE_KW_START( _iss, ikw ) + 1 ) )
#define ULIS_PARSE_KW_END(      _iss, ikw )     ( _iss.Size() - 1 )
#define ULIS_PARSE_KW_STOP(     _iss, ikw )     ( ULIS_PARSE_KW_NEXT( _iss, ikw ) == -1 ? ULIS_PARSE_KW_END( _iss, ikw ) : ULIS_PARSE_KW_NEXT( _iss, ikw ) )
#define ULIS_PARSE_KW_DELTA(    _iss, ikw )     ( ULIS_PARSE_KW_STOP( _iss, ikw ) ) - ( ULIS_PARSE_KW_START( _iss, ikw ) )
#define ULIS_PARSE_KW_SUBSTR(   _iss, ikw )     _iss.Substring< ULIS_PARSE_KW_DELTA( _iss, ikw ) >( ULIS_PARSE_KW_START( _iss, ikw ) )
#define ULIS_PARSE_KW_APPEND(   _iss, ikw )     Append< ::ULIS::_CT::strlen( ikw ) + 1 >( ikw ).Append< ULIS_PARSE_KW_DELTA( _iss, ikw ) + 1 >( ULIS_PARSE_KW_SUBSTR( _iss, ikw ).s )
#define ULIS_PARSE_KW_APPEND_W( _iss, itk )     ULIS_PARSE_KW_APPEND( _iss, ULIS_PARSE_KW_MAKE_TOKEN_S( itk ) )
/////////////////////////////////////////////////////
// BlockSpec
#define ULIS_DECLARE_STATIC_BLOCK_SPEC( spec )                                          \
    constexpr auto      ULIS_SPEC_SS( spec ) = ULIS_SPEC_TO_STR( spec );                \
    constexpr uint32    ULIS_SPEC_SH( spec ) = ULIS_SPEC_SS( spec ).CRC32();            \
    template<> struct TBlockSpec< ULIS_SPEC_SH( spec ) > {                              \
        static constexpr const char*        _ss = ULIS_SPEC_SS( spec ).s;               \
        static constexpr const uint32       _sh = ULIS_SPEC_SH( spec );                 \
        static constexpr const FBlockInfo   _nf = ParseSpecStr( ULIS_SPEC_SS( spec ) ); \
    };                                                                                  \
    typedef TBlock< ULIS_SPEC_SH( spec ) > BOOST_PP_CAT( FBlock, spec );                \
    ULIS_APPEND_REG( ULIS_REG_BUILDER, ULIS_SPEC_SH( spec ) )
#define ULIS_DECLARE_STATIC_BLOCK_SPEC_W( ... ) ULIS_DECLARE_STATIC_BLOCK_SPEC( ULIS_BLOCK_SPEC( __VA_ARGS__ ) )
} // namespace _CT
} // namespace ULIS