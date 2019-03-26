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

#include "ULIS/Base/CompileTime/ULIS.Base.CompileTime.ConstStr.h"

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>

namespace ULIS {
/////////////////////////////////////////////////////
// Macro utilities
#define ULIS_KEYS( ... ) ( __VA_ARGS__ )
#define ULIS_KEYWORDS_CAT( cat )            kw##cat
#define ULIS_ENUM_CAT( cat )                e##cat
#define ULIS_MAKE_KEYWORD( r, data, elem )  BOOST_PP_STRINGIZE( elem )
#define ULIS_MAKE_ENUM( r, data, elem )     BOOST_PP_CAT( k, elem ),
#define ULIS_MAKE_ENUM_KEYS_TUPLE( r, data, elem )  ( BOOST_PP_CAT( k, elem ), elem ),

#define ULIS_KEYS_TO_KEYWORDS( cat, keys )                                              \
    constexpr const char* ULIS_KEYWORDS_CAT( cat )[] = {                                \
        BOOST_PP_SEQ_FOR_EACH( ULIS_MAKE_KEYWORD, 0, BOOST_PP_TUPLE_TO_SEQ( keys ) ) };

#define ULIS_KEYS_TO_ENUM( cat, keys )                                                  \
    enum class ULIS_ENUM_CAT( cat ) : char {                                            \
        BOOST_PP_SEQ_FOR_EACH( ULIS_MAKE_ENUM, 0, BOOST_PP_TUPLE_TO_SEQ( keys ) ) };

/////////////////////////////////////////////////////
// enum and keyword declaration
// memory_layout
#define ULIS_KEYS_ML ULIS_KEYS( interleaved, planar )
ULIS_KEYS_TO_KEYWORDS(  _ml, ULIS_KEYS_ML )
ULIS_KEYS_TO_ENUM(      _ml, ULIS_KEYS_ML )
// alpha_mode
#define ULIS_KEYS_AM ULIS_KEYS( straight, premultiplied )
ULIS_KEYS_TO_KEYWORDS(  _am, ULIS_KEYS_AM )
ULIS_KEYS_TO_ENUM(      _am, ULIS_KEYS_AM )
// type
#define ULIS_KEYS_TP ULIS_KEYS( uint8, uint16, uint32, int8, int16, int32, float, double )
ULIS_KEYS_TO_KEYWORDS(  _tp, ULIS_KEYS_TP )
ULIS_KEYS_TO_ENUM(      _tp, ULIS_KEYS_TP )
// arithmetical_set
#define ULIS_KEYS_AS ULIS_KEYS( natural, integer, decimal, rational, real, complex )
ULIS_KEYS_TO_KEYWORDS(  _as, ULIS_KEYS_AS )
ULIS_KEYS_TO_ENUM(      _as, ULIS_KEYS_AS )
// color_model
#define ULIS_KEYS_CM ULIS_KEYS( RGB, HSL, HSV, LAB, XYZ, CMY, CMYK )
ULIS_KEYS_TO_KEYWORDS(  _cm, ULIS_KEYS_CM )
ULIS_KEYS_TO_ENUM(      _cm, ULIS_KEYS_CM )
// endian_mode
#define ULIS_KEYS_EM ULIS_KEYS( big, little, default )
ULIS_KEYS_TO_KEYWORDS(  _em, ULIS_KEYS_EM )
ULIS_KEYS_TO_ENUM(      _em, ULIS_KEYS_EM )
// normal_mode
#define ULIS_KEYS_NM ULIS_KEYS( anormal, normal )
ULIS_KEYS_TO_KEYWORDS(  _nm, ULIS_KEYS_NM )
ULIS_KEYS_TO_ENUM(      _nm, ULIS_KEYS_NM )

#define ULIS_KEYS_ALL ULIS_KEYS( ULIS_KEYS_DATA_TYPE )


/////////////////////////////////////////////////////
// BlockInfo
struct FBlockInfo
{
    const  e_ml         _ml; // memory_layout
    const  e_am         _am; // alpha_mode
    const  e_tp         _tp; // type
    const  e_as         _as; // arithmetical_set
    const  e_cm         _cm; // color_model
    const  e_em         _em; // endian_mode
    const  uint16       _pd; // pixel_depth
    const  uint8        _nc; // num_channels
    const  bool         _ea; // extra_alpha
};


/////////////////////////////////////////////////////
// NormSpecStr
template< int N >
static
constexpr
const
auto
NormSpecStr( const nCT::const_str< N > spec_str )
{
    const int start_ml = spec_str.IndexOf( "_ml:" );
    return spec_str.Substring< 2 >( start_ml );
}


/////////////////////////////////////////////////////
// ParseSpecStr
template< int N >
static constexpr const FBlockInfo ParseSpecStr( nCT::const_str< N > spec_str )
{
    return  { e_ml::kinterleaved
            , e_am::kstraight
            , e_tp::kuint8
            , e_as::knatural
            , e_cm::kRGB
            , e_em::kdefault
            , 32
            , 4
            , true
            };
}


/////////////////////////////////////////////////////
// TBlockSpec
template< uint32 > class TBlock;
template< uint32 > struct TBlockSpec {};

#define ULIS_SPEC_X( X, i ) _##X##:##i
#define ULIS_SPEC_ML( i ) ULIS_SPEC_X( ml, i )
#define ULIS_SPEC_AM( i ) ULIS_SPEC_X( am, i )
#define ULIS_SPEC_TP( i ) ULIS_SPEC_X( tp, i )
#define ULIS_SPEC_AS( i ) ULIS_SPEC_X( as, i )
#define ULIS_SPEC_CM( i ) ULIS_SPEC_X( cm, i )
#define ULIS_SPEC_EM( i ) ULIS_SPEC_X( em, i )

#define ULIS_BLOCK_SPEC( ... ) BOOST_PP_SEQ_CAT( BOOST_PP_TUPLE_TO_SEQ( ( __VA_ARGS__ ) ) )

/*
ULIS_BLOCK_SPEC( _ml:interleaved
               , _am:straight
               , _tp:uint8
                )
*/

#define ULIS_DECLARE_STATIC_BLOCK_SPEC( spec )                                          \
    static constexpr const uint32 Spec_##spec = CONST_STR( #spec ).CRC32();             \
    template<> struct TBlockSpec< Spec_##spec > {                                       \
        static constexpr const char*        _ss = #spec;                                \
        static constexpr const uint32       _sh = Spec_##spec;                          \
        static constexpr const FBlockInfo   _nf = ParseSpecStr( CONST_STR( #spec ) );   \
    };                                                                                  \
    typedef TBlock< Spec_##spec > F##spec;

} // namespace ULIS

