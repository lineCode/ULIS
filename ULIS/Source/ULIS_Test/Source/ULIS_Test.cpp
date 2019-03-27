/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <iostream>
#include <cstring>
#include <ULIS_Core>
#include <array>

#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>

using namespace ::ULIS;

/*
constexpr regt< 1 > regbase = { 0 };
constexpr auto reg1 = regbase.push_back( 3244 );
constexpr auto reg2 = reg1.push_back( 4126 );
*/

/*
ULIS_CREATE_REG( okreg, 454 )
ULIS_APPEND_REG( okreg, 1 )
ULIS_APPEND_REG( okreg, 2 )
ULIS_APPEND_REG( okreg, 3 )
constexpr auto reg = ULIS_ASSIGN_REG( okreg );

int Gen( int i )
{
    switch( i )
    {
        case reg[0]:
            return reg[0];

        case reg[1]:
            return reg[1];
    }
}
*/

//@todo: impl this index indirection
/*
static constexpr const uint8 SeekIndexForChar( const char* ilayout, const char* imodel, uint8 num ) { return ::ULIS::ct_charindex_without_digits( imodel[num], ilayout ); }
template <uint8 N, typename T, T... Nums> static constexpr const std::array<uint8, N-1> make_impl( const char* ilayout, const char (&imodel)[N], ::ULIS::integer_sequence<T, Nums...>) { return { SeekIndexForChar( ilayout, imodel, Nums ) ... }; }
template <uint8 N> static constexpr const std::array<uint8, N-1> make_index_from_string( const char* ilayout, const char (&imodel)[N]) { return make_impl( ilayout, imodel, ::ULIS::make_integer_sequence<uint8, N-1>()); }


static constexpr const char layout[] = "B8G8R8A8";
static constexpr const char model[] =  "RGBA";
static constexpr const int count = ::ULIS::strlen( model );
static constexpr const std::array< uint8, count > arr = make_index_from_string( layout, model );
*/


//ULIS_DECLARE_STATIC_BLOCK_SPEC_W( ULIS_SPEC_ML( interleaved ) )

namespace ULIS {
#define ULIS_REG_BUILDER ulis_reg_builder
ULIS_CREATE_REG( ULIS_REG_BUILDER, 0 )

ULIS_DECLARE_STATIC_BLOCK_SPEC_W(
    ULIS_SPEC_ML( interleaved ),
    ULIS_SPEC_AM( straight ),
    ULIS_SPEC_TP( uint8 ),
    ULIS_SPEC_AS( natural ),
    ULIS_SPEC_CM( RGB )
    )

ULIS_DECLARE_STATIC_BLOCK_SPEC_W(
    ULIS_SPEC_ML( planar ),
    ULIS_SPEC_AM( straight ),
    ULIS_SPEC_TP( uint8 ),
    ULIS_SPEC_AS( natural )
    )

constexpr auto regx = ULIS_ASSIGN_REG( ULIS_REG_BUILDER );
static_assert( regx[0] == 0, "..." );
static_assert( regx[1] == _SH__ml_interleaved__am_straight__tp_uint8__as_natural__cm_RGB, "..." );
static_assert( regx[2] == _SH__ml_planar__am_straight__tp_uint8__as_natural, "..." );
}


int main()
{
    constexpr auto c_fmt = ULIS_CONST_STR( "Spec__ml_interleaved__am_straight__tp_uint8" );
    constexpr auto a_fmt = ULIS_CONST_STR( "Spec__tp_uint8__am_straight__ml_interleaved" );

    /*
    constexpr const int imlstart    = ULIS_PARSE_KW_START( a_fmt, "_tp:" );
    constexpr const int imlnext     = ULIS_PARSE_KW_NEXT( a_fmt, "_tp:" );
    constexpr const int imlend      = ULIS_PARSE_KW_END( a_fmt, "_tp:" );
    constexpr const int imlstop     = ULIS_PARSE_KW_STOP( a_fmt, "_tp:" );
    constexpr const int dml         = ULIS_PARSE_KW_DELTA( a_fmt, "_tp:" );
    constexpr  auto tmp0            = ULIS_PARSE_KW_SUBSTR( a_fmt, "_tp:" );
    constexpr auto r_fmt = ULIS_CONST_STR( "Spec" ).Append< ::ULIS::_CT::strlen( "_tp:" ) + 1 >( "_tp:" ).Append< dml + 1 >( tmp0.s );
    */
    constexpr auto g_fmt = ULIS_CONST_STR( "Spec" ).ULIS_PARSE_KW_APPEND_W( a_fmt, ml ).ULIS_PARSE_KW_APPEND_W( a_fmt, am ).ULIS_PARSE_KW_APPEND_W( a_fmt, tp );

    static_assert( g_fmt == c_fmt, "..." );
    static_assert( g_fmt.CRC32() == c_fmt.CRC32(), "..." );

    for( int i = 0; i < regx.Size(); ++ i )
        std::cout << (uint32)regx[i] << std::endl;

    std::cout << FBlock__ml_interleaved__am_straight__tp_uint8__as_natural__cm_RGB::SpecStr() << std::endl;
    std::cout << FBlock__ml_interleaved__am_straight__tp_uint8__as_natural__cm_RGB::SpecHash() << std::endl;
    std::cout << a_fmt.s << std::endl;
    std::cout << a_fmt.s << std::endl;
    std::cout << c_fmt.s << std::endl;
    std::cout << g_fmt.s << std::endl;
    std::cout << a_fmt.CRC32() << std::endl;
    std::cout << a_fmt.CRC32() << std::endl;
    std::cout << c_fmt.CRC32() << std::endl;
    std::cout << c_fmt.CRC32() << std::endl;
    std::cout << g_fmt.CRC32() << std::endl;
    std::cout << g_fmt.CRC32() << std::endl;
    getchar();
    return 0;
}

