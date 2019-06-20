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
#include "ULIS/ULIS.PP.h"

namespace ULIS {

/////////////////////////////////////////////////////
// Enum and Keyword Declaration
ULIS_MAKE_KEYS( _ml, interleaved, planar )                                          // memory_layout
ULIS_MAKE_KEYS( _am, straight, premultiplied )                                      // alpha_mode
ULIS_MAKE_KEYS( _tp, uint8, uint16, uint32, int8, int16, int32, float, double )     // type
ULIS_MAKE_KEYS( _as, natural, integer, decimal, rational, real, complex )           // arithmetical_set
ULIS_MAKE_KEYS( _cm, BIT, GREY, RGB, HSL, HSV, CMY, CMYK, YUV, YCbCr, LAB, XYZ )    // color_model
ULIS_MAKE_KEYS( _em, big, little, platform )                                        // endian_mode

/////////////////////////////////////////////////////
// FSpec
struct FSpec
{
    const  e_ml         _ml; // memory_layout
    const  e_am         _am; // alpha_mode
    const  e_tp         _tp; // type
    const  e_as         _as; // arithmetical_set
    const  e_cm         _cm; // color_model
    const  e_em         _em; // endian_mode

    const  bool         _nm; // normal
    const  uint16_t     _pd; // pixel_depth
    const  uint8_t      _nc; // num_channels
    const  bool         _ea; // extra_alpha
};


/////////////////////////////////////////////////////
// TBlockSpec
template< uint32_t > struct TBlockSpec {};

/////////////////////////////////////////////////////
// TBlockSpec Specialization
/* build a specialization of TBlockSpec from token and compute string and hash equivalents */
#define ULIS_DECLARE_STATIC_BLOCK_SPEC( spec )                                          \
    constexpr auto      ULIS_SPEC_SS( spec ) = ULIS_SPEC_TO_STR( spec );                \
    constexpr uint32    ULIS_SPEC_SH( spec ) = ULIS_SPEC_SS( spec ).CRC32();            \
    template<> struct TBlockSpec< ULIS_SPEC_SH( spec ) > {                              \
        static constexpr const char*        _ss = ULIS_SPEC_SS( spec ).s;               \
        static constexpr const uint32       _sh = ULIS_SPEC_SH( spec );                 \
        static constexpr const FSpec        _nf = ParseSpecStr( ULIS_SPEC_SS( spec ) ); \
    };                                                                                  \
    typedef TBlock< ULIS_SPEC_SH( spec ) > BOOST_PP_CAT( FBlock, spec );                \
    ULIS_APPEND_REG( ULIS_REG_BUILDER, ULIS_SPEC_SH( spec ) )

#define ULIS_DECLARE_STATIC_BLOCK_SPEC_W( ... ) ULIS_DECLARE_STATIC_BLOCK_SPEC( ULIS_BLOCK_SPEC( __VA_ARGS__ ) )

} // namespace ULIS

