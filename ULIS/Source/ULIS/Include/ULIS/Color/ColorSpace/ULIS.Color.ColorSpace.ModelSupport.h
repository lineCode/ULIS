/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Color.ColorSpace.ModelSupport.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Data/ULIS.Data.Spec.h"

namespace ULIS {

#define ULIS_SWITCH_SUPPORTED_MODELS( iValue, ... )                                                                 \
    switch( iValue )                                                                                                \
    {                                                                                                               \
        BOOST_PP_CAT( ULIS_SWITCH_SUPPORTED_MODELS_, BOOST_PP_TUPLE_SIZE( (__VA_ARGS__) ) )( iValue, __VA_ARGS__ )  \
    }

#define ULIS_SWITCH_SUPPORTED_MODELS_1( iValue, i0 )                            \
    case i0: return  true;                                                      \
    default: return  false;

#define ULIS_SWITCH_SUPPORTED_MODELS_2( iValue, i0, i1 )                        \
    case i0: return  true;                                                      \
    case i1: return  true;                                                      \
    default: return  false;

#define ULIS_SWITCH_SUPPORTED_MODELS_3( iValue, i0, i1, i2 )                    \
    case i0: return  true;                                                      \
    case i1: return  true;                                                      \
    case i2: return  true;                                                      \
    default: return  false;

#define ULIS_SWITCH_SUPPORTED_MODELS_4( iValue, i0, i1, i2, i3 )                \
    case i0: return  true;                                                      \
    case i1: return  true;                                                      \
    case i2: return  true;                                                      \
    case i3: return  true;                                                      \
    default: return  false;

#define ULIS_SWITCH_SUPPORTED_MODELS_5( iValue, i0, i1, i2, i3, i4 )            \
    case i0: return  true;                                                      \
    case i1: return  true;                                                      \
    case i2: return  true;                                                      \
    case i3: return  true;                                                      \
    case i4: return  true;                                                      \
    default: return  false;

#define ULIS_SWITCH_SUPPORTED_MODELS_6( iValue, i0, i1, i2, i3, i4, i5 )        \
    case i0: return  true;                                                      \
    case i1: return  true;                                                      \
    case i2: return  true;                                                      \
    case i3: return  true;                                                      \
    case i4: return  true;                                                      \
    case i5: return  true;                                                      \
    default: return  false;

#define ULIS_SWITCH_SUPPORTED_MODELS_7( iValue, i0, i1, i2, i3, i4, i5, i6 )    \
    case i0: return  true;                                                      \
    case i1: return  true;                                                      \
    case i2: return  true;                                                      \
    case i3: return  true;                                                      \
    case i4: return  true;                                                      \
    case i5: return  true;                                                      \
    case i6: return  true;                                                      \
    default: return  false;


} // namespace ULIS

