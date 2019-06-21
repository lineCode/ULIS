/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Imaging.CompileTime.BlockID.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/apply.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>


namespace ULIS {

/////////////////////////////////////////////////////
// Enum and Keyword
/* Make a tuple from variadic args */
#define ULIS_KEYS( ... ) ( __VA_ARGS__ )

/* concatenate a token with 'kw' prefix to build a keyword category name */
#define ULIS_KEYWORDS_CAT( cat ) kw##cat

/* concatenate a token with 'e' prefix to build an enum category name */
#define ULIS_ENUM_CAT( cat ) e##cat

/* delegate macro for sequential 'stringization' of token */
#define ULIS_MAKE_KEYWORD_SEQ( r, data, elem ) BOOST_PP_STRINGIZE( elem )

/* delegate macro for sequential 'enumerization' of token */
#define ULIS_MAKE_ENUM_SEQ( r, data, elem ) BOOST_PP_CAT( k, elem ),

/* delegate macro for sequential concatenation of enum value with actual token */
#define ULIS_MAKE_ENUM_KEYS_TUPLE_SEQ( r, data, elem ) ( BOOST_PP_CAT( k, elem ), elem ),

/* build a keyword categroy as an array of strings from tokens */
#define ULIS_KEYS_TO_KEYWORDS( cat, keys )                                              \
    constexpr const char* ULIS_KEYWORDS_CAT( cat )[] = {                                \
        BOOST_PP_SEQ_FOR_EACH( ULIS_MAKE_KEYWORD_SEQ, 0, BOOST_PP_TUPLE_TO_SEQ( keys ) ) };

/* build an enum categroy as a cpp enum of integer values from tokens */
#define ULIS_KEYS_TO_ENUM( cat, keys )                                                  \
    enum class ULIS_ENUM_CAT( cat ) : int {                                             \
        BOOST_PP_SEQ_FOR_EACH( ULIS_MAKE_ENUM_SEQ, 0, BOOST_PP_TUPLE_TO_SEQ( keys ) ) };

/* Make Tuple and build keys */
#define ULIS_MAKE_KEYS( cat, ... ) ULIS_KEYS_TO_KEYWORDS( cat, ULIS_KEYS( __VA_ARGS__ ) ) ULIS_KEYS_TO_ENUM( cat, ULIS_KEYS( __VA_ARGS__ ) )


/////////////////////////////////////////////////////
// Keyword Token
/* token delimiter for keyword start */
#define ULIS_PARSE_KW_START_TOKEN __

/* token delimiter for keyword end */
#define ULIS_PARSE_KW_END_TOKEN _

/* stringized token delimiter for keyword start */
#define ULIS_PARSE_KW_START_TOKEN_S BOOST_PP_STRINGIZE( ULIS_PARSE_KW_START_TOKEN )

/* stringized token delimiter for keyword end */
#define ULIS_PARSE_KW_END_TOKEN_S BOOST_PP_STRINGIZE( ULIS_PARSE_KW_END_TOKEN )

/* concatenate token delimiters around input */
#define ULIS_PARSE_KW_MAKE_TOKEN( i ) BOOST_PP_CAT( BOOST_PP_CAT( ULIS_PARSE_KW_START_TOKEN, i ), ULIS_PARSE_KW_END_TOKEN )

/* stringized concatenated token delimiters around input */
#define ULIS_PARSE_KW_MAKE_TOKEN_S( i ) BOOST_PP_STRINGIZE( ULIS_PARSE_KW_MAKE_TOKEN( i ) )

/* concatenate multiple keyword arguments with no prefered order */
#define ULIS_BLOCK_SPEC( ... ) BOOST_PP_SEQ_CAT( BOOST_PP_TUPLE_TO_SEQ( ( __VA_ARGS__ ) ) )
#define ULIS_SPEC_TO_STR( spec ) coalMakeFromString( BOOST_PP_STRINGIZE( spec ) )
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


} // namespace ULIS
