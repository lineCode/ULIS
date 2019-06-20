/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Spec.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <stdint.h>
#include <coal_core>
#include "ULIS/ULIS.PP.h"

namespace ULIS {

/////////////////////////////////////////////////////
// Enum and Keyword Declaration
ULIS_MAKE_KEYS( _ml, interleaved, planar )                                              // memory_layout
ULIS_MAKE_KEYS( _am, straight, premultiplied )                                          // alpha_mode
ULIS_MAKE_KEYS( _tp, uint8, uint16, uint32, int8, int16, int32, float, double )         // type
ULIS_MAKE_KEYS( _cm, BIT, GREY, V2, V3, V4, V5, RGB, HSL, HSV, CMY, CMYK, YUV, YCbCr, LAB, XYZ )   // color_model
ULIS_MAKE_KEYS( _em, big, little, platform )                                            // endian_mode

/////////////////////////////////////////////////////
// Spec Keys
#define ULIS_KEY_ML     ml // memory_layout
#define ULIS_KEY_TP     tp // type
#define ULIS_KEY_CM     cm // color_model
#define ULIS_KEY_CL     cl // channel_layout
#define ULIS_KEY_AM     am // alpha_mode
#define ULIS_KEY_UL     ul // upper_limit
#define ULIS_KEY_LL     ll // lower_limit
#define ULIS_KEY_EM     em // endian_mode

/* build argument with keyword and delimiters */
#define ULIS_SPEC_X( X, i ) BOOST_PP_CAT( ULIS_PARSE_KW_MAKE_TOKEN( X ), i )
/* shorthand for specific keyword arguments */
#define ULIS_SPEC_ML( i ) ULIS_SPEC_X( ULIS_KEY_ML, i )
#define ULIS_SPEC_TP( i ) ULIS_SPEC_X( ULIS_KEY_TP, i )
#define ULIS_SPEC_CM( i ) ULIS_SPEC_X( ULIS_KEY_CM, i )
#define ULIS_SPEC_CL( i ) ULIS_SPEC_X( ULIS_KEY_CL, i )
#define ULIS_SPEC_AM( i ) ULIS_SPEC_X( ULIS_KEY_AM, i )
#define ULIS_SPEC_UL( i ) ULIS_SPEC_X( ULIS_KEY_UL, i )
#define ULIS_SPEC_LL( i ) ULIS_SPEC_X( ULIS_KEY_LL, i )
#define ULIS_SPEC_EM( i ) ULIS_SPEC_X( ULIS_KEY_EM, i )

/////////////////////////////////////////////////////
// FSpec
struct FSpec
{
    // Core properties
    const  e_ml         _ml; // memory_layout
    const  e_tp         _tp; // type
    const  e_cm         _cm; // color_model
    const  char*        _cl; // channel_layout
    const  e_am         _am; // alpha_mode
    const  int64_t      _ul; // upper_limit
    const  int64_t      _ll; // lower_limit
    const  e_em         _em; // endian_mode

    // Infered properties
    const  bool         _nm; // normal
    const  bool         _dm; // decimal
    const  uint16_t     _pd; // pixel_depth
    const  uint8_t      _nc; // num_channels
    const  uint8_t      _rc; // real_channels
    const  bool         _ea; // extra_alpha
    const  bool         _ub; // upper_bound
    const  bool         _lb; // lower_bound
    const  bool         _ri; // reordered_indexes
};

/////////////////////////////////////////////////////
// Parsing
template< typename iCoal >
static constexpr auto NormalizeSpecStr( iCoal )
{
    coal str = iCoal::value();
    return  coalSubstring( str, 2, 5 );
}

/////////////////////////////////////////////////////
// TBlockSpec
template< uint32_t > struct TBlockSpec {};

/////////////////////////////////////////////////////
// TBlockSpec Specialization
/* build a specialization of TBlockSpec from token and compute string and hash equivalents */

#define ULIS_DECLSPEC_IMP( spec )                                                       \
    coal                ULIS_SPEC_SS( spec ) = ULIS_SPEC_TO_STR( spec );                \
    constexpr uint32_t  ULIS_SPEC_SH( spec ) = ULIS_SPEC_SS( spec ).hash();             \
    template<> struct ::ULIS::TBlockSpec< ULIS_SPEC_SH( spec ) > {                      \
        static constexpr const char*        _ss = ULIS_SPEC_SS( spec ).s;               \
        static constexpr const uint32_t     _sh = ULIS_SPEC_SH( spec );                 \
    };                                                                                  \

    //static constexpr const FSpec        _nf = ParseSpecStr( ULIS_SPEC_SS( spec ) ); \
    //typedef TBlock< ULIS_SPEC_SH( spec ) > BOOST_PP_CAT( FBlock, spec );                \
    //ULIS_APPEND_REG( ULIS_REG_BUILDER, ULIS_SPEC_SH( spec ) )

#define ULIS_DECLSPEC( ml, tp, cm, cl, am, ul, ll, em ) \
    ULIS_DECLSPEC_IMP(                                  \
        ULIS_BLOCK_SPEC( ULIS_SPEC_ML( ml )             \
                       , ULIS_SPEC_TP( tp )             \
                       , ULIS_SPEC_CM( cm )             \
                       , ULIS_SPEC_CL( cl )             \
                       , ULIS_SPEC_AM( am )             \
                       , ULIS_SPEC_UL( ul )             \
                       , ULIS_SPEC_LL( ll )             \
                       , ULIS_SPEC_EM( em )             \
        )                                               \
    )

} // namespace ULIS

