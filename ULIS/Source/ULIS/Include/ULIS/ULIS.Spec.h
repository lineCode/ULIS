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
#include "ULIS/ULIS.SpecReg.h"

namespace ULIS {

/////////////////////////////////////////////////////
// Enum and Keyword Declaration
ULIS_MAKE_KEYS( _tp, uint8, uint16, uint32, int8, int16, int32, float, double )                     // type
ULIS_MAKE_KEYS( _cm, BIT, GREY, V2, V3, V4, V5, RGB, HSL, HSV, CMY, CMYK, YUV, YCbCr, LAB, XYZ )    // color_model
ULIS_MAKE_KEYS( _ea, hasAlpha, noAlpha )                                                            // extra_alpha
ULIS_MAKE_KEYS( _nm, normalized, typeLimits )                                                       // normal_mode

/////////////////////////////////////////////////////
// Spec Keys
#define ULIS_KEY_TP     tp // type
#define ULIS_KEY_CM     cm // color_model
#define ULIS_KEY_EA     ea // extra_alpha
#define ULIS_KEY_CL     cl // channel_layout
#define ULIS_KEY_NM     nm // normal_mode

/* build argument with keyword and delimiters */
#define ULIS_SPEC_X( X, i ) BOOST_PP_CAT( ULIS_PARSE_KW_MAKE_TOKEN( X ), i )
/* shorthand for specific keyword arguments */
#define ULIS_SPEC_TP( i ) ULIS_SPEC_X( ULIS_KEY_TP, i )
#define ULIS_SPEC_CM( i ) ULIS_SPEC_X( ULIS_KEY_CM, i )
#define ULIS_SPEC_EA( i ) ULIS_SPEC_X( ULIS_KEY_EA, i )
#define ULIS_SPEC_CL( i ) ULIS_SPEC_X( ULIS_KEY_CL, i )
#define ULIS_SPEC_NM( i ) ULIS_SPEC_X( ULIS_KEY_NM, i )

/////////////////////////////////////////////////////
// FSpec
struct FSpec
{
    // Core properties
    const  e_tp         _tp; // type
    const  e_cm         _cm; // color_model
    const  e_ea         _ea; // extra_alpha
    const  char*        _cl; // channel_layout
    bool                _nm; // normal_mode

    // Infered properties
    const  bool         _dm; // decimal
    const  uint16_t     _pd; // pixel_depth
    const  uint8_t      _nc; // num_channels
    const  uint8_t      _rc; // real_channels
};

/////////////////////////////////////////////////////
// Parsing

/////////////////////////////////////////////////////
// TBlockSpec
template< uint32_t > struct TBlockSpec {};

/////////////////////////////////////////////////////
// TBlockSpec Specialization
/* build a specialization of TBlockSpec from token and compute string and hash equivalents */

#define ULIS_DECLSPEC_IMP( tp, cm, ea, cl, nm, spec )                                   \
    coal                ULIS_SPEC_SS( spec ) = ULIS_SPEC_TO_STR( spec );                \
    constexpr uint32_t  ULIS_SPEC_SH( spec ) = ULIS_SPEC_SS( spec ).hash();             \
    template<> struct ::ULIS::TBlockSpec< ULIS_SPEC_SH( spec ) > {                      \
        static constexpr const char*        _ss = ULIS_SPEC_SS( spec ).s;               \
        static constexpr const uint32_t     _sh = ULIS_SPEC_SH( spec );                 \
    };                                                                                  \
    ULIS_APPEND_REG( ULIS_REG_BUILDER, ULIS_SPEC_SH( spec ) )

    //static constexpr const FSpec        _nf = ParseSpecStr( ULIS_SPEC_SS( spec ) ); \
    //typedef TBlock< ULIS_SPEC_SH( spec ) > BOOST_PP_CAT( FBlock, spec );                \

#define ULIS_DECLSPEC( tp, cm, ea, cl, nm ) \
    ULIS_DECLSPEC_IMP( tp, cm, ea, cl, nm,              \
        ULIS_BLOCK_SPEC( ULIS_SPEC_TP( tp )             \
                       , ULIS_SPEC_CM( cm )             \
                       , ULIS_SPEC_EA( ea )             \
                       , ULIS_SPEC_CL( cl )             \
                       , ULIS_SPEC_NM( nm )             \
        )                                               \
    )

} // namespace ULIS

