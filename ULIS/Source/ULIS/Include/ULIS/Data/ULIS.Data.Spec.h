/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Data.Spec.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <stdint.h>
#include <coal_core>
#include "ULIS/Data/ULIS.Data.PP.h"
#include "ULIS/Data/ULIS.Data.SpecReg.h"

namespace ULIS {

/////////////////////////////////////////////////////
// Enum and Keyword Declaration
ULIS_MAKE_KEYS( _tp, uint8, uint16, uint32, int8, int16, int32, float, double )         // type
ULIS_MAKE_KEYS( _cm, BIT, GREY, RGB, HSL, HSV, CMY, CMYK, YUV, YCbCr, LAB, XYZ, VEC )   // color_model
ULIS_MAKE_KEYS( _ea, hasAlpha, noAlpha )                                                // extra_alpha
ULIS_MAKE_KEYS( _nm, normalized, typeLimits )                                           // normal_mode

/////////////////////////////////////////////////////
// Spec Keys
#define ULIS_KEY_TP     tp // type
#define ULIS_KEY_CM     cm // color_model
#define ULIS_KEY_EA     ea // extra_alpha
#define ULIS_KEY_CL     cl // channel_layout
#define ULIS_KEY_NM     nm // normal_mode

/* build argument with keyword and delimiters */
//#define ULIS_SPEC_X( X, i ) BOOST_PP_CAT( ULIS_PARSE_KW_MAKE_TOKEN( X ), i )
#define ULIS_SPEC_X( X, i ) i

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
    const char*         _ss;
    const uint32_t      _sh;
    const  e_tp         _tp; // type
    const  e_cm         _cm; // color_model
    const  e_ea         _ea; // extra_alpha
    const  char*        _cl; // channel_layout
    const  e_nm         _nm; // normal_mode

    // Infered properties
    const  bool         _dm; // decimal
    const  uint8_t      _rc; // real_channels
    const  uint8_t      _nc; // num_channels
    const  uint16_t     _pd; // pixel_depth
};

/////////////////////////////////////////////////////
// Parsing
constexpr  bool  is_decimal( ::ULIS::e_tp iTp ) { return  iTp == ::ULIS::e_tp::kdouble || iTp == ::ULIS::e_tp::kfloat ? true : false; }
constexpr  FSpec parseSpec( const char* iSs, uint32_t iSh, ::ULIS::e_tp iTp, ::ULIS::e_cm iCm, ::ULIS::e_ea iEa, const char* iCl, ::ULIS::e_nm iNm )
{
    bool        dm = is_decimal( iTp );
    uint8_t     rc = ::__coal__::strlen( iCl );
    uint8_t     nc = iEa == ::ULIS::e_ea::khasAlpha ? rc - 1 : rc;
    uint16_t    pd = 8;
    return  { iSs, iSh, iTp, iCm, iEa, iCl, iNm, dm, rc, nc, pd };
}

#define ULIS_PARSE_FSPEC( ss, sh, tp, cm, ea, cl, nm )              \
    ::ULIS::parseSpec( ss, sh                                       \
                     , BOOST_PP_CAT( ::ULIS::e_tp::k, tp )          \
                     , BOOST_PP_CAT( ::ULIS::e_cm::k, cm )          \
                     , BOOST_PP_CAT( ::ULIS::e_ea::k, ea )          \
                     , BOOST_PP_STRINGIZE( cl )                     \
                     , BOOST_PP_CAT( ::ULIS::e_nm::k, nm )          \
    );
/////////////////////////////////////////////////////
// TBlockSpec
struct IBlockSpec {
    virtual  const char*    GetSpecString() const { return  "Invalid"; }
    virtual  const uint32_t GetSpecHash()   const { return  0; }
    virtual  const FSpec    GetSpec()       const { return  FSpec{}; }
};

template< uint32_t > struct TBlockSpec : public  IBlockSpec {
    static constexpr const char*        _ss = "Invalid";
    static constexpr const uint32_t     _sh = 0;
    static constexpr const FSpec        _nf = {};
};

/////////////////////////////////////////////////////
// TBlockSpec Specialization
/* build a specialization of TBlockSpec from token and compute string and hash equivalents */

#define ULIS_DECLSPEC_IMP( tp, cm, ea, cl, nm, spec )                                       \
    coal                ULIS_SPEC_SS( spec ) = ULIS_SPEC_TO_STR( spec );                    \
    constexpr uint32_t  ULIS_SPEC_SH( spec ) = ULIS_SPEC_SS( spec ).hash();                 \
    template<> struct ::ULIS::TBlockSpec< ULIS_SPEC_SH( spec ) > : public  IBlockSpec {     \
        static constexpr const char*        _ss = ULIS_SPEC_SS( spec ).s;                   \
        static constexpr const uint32_t     _sh = ULIS_SPEC_SH( spec );                     \
        static constexpr const FSpec        _nf = ULIS_PARSE_FSPEC( ULIS_SPEC_SS( spec ), ULIS_SPEC_SH( spec ), tp, cm, ea, cl, nm )    \
        virtual  const char*    GetSpecString() const override final { return  _ss; }       \
        virtual  const uint32_t GetSpecHash()   const override final { return  _sh; }       \
    };                                                                                      \
    ULIS_APPEND_REG( ULIS_REG_BUILDER, ULIS_SPEC_SH( spec ) )

    //typedef TBlock< ULIS_SPEC_SH( spec ) > BOOST_PP_CAT( FBlock, spec );                \

#define ULIS_DECLSPEC( tp, cm, ea, cl, nm ) \
    ULIS_DECLSPEC_IMP( tp, cm, ea, cl, nm,  \
        ULIS_BLOCK_SPEC( ULIS_SPEC_TP( tp ) \
                       , ULIS_SPEC_CM( cm ) \
                       , ULIS_SPEC_EA( ea ) \
                       , ULIS_SPEC_CL( cl ) \
                       , ULIS_SPEC_NM( nm ) \
        )                                   \
    )

} // namespace ULIS

