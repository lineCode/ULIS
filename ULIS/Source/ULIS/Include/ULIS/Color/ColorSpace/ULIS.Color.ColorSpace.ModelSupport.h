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
#include "lcms2.h"

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

static e_cm ColorModelFromColorSpaceSignature( cmsColorSpaceSignature iValue )
{
    e_cm default_cm = e_cm::kRGB;
    switch( iValue )
    {
        case cmsSigXYZData      : return  e_cm::kXYZ;
        case cmsSigLabData      : return  e_cm::kLab;
        case cmsSigLuvData      : return  default_cm;
        case cmsSigYCbCrData    : return  default_cm;
        case cmsSigYxyData      : return  default_cm;
        case cmsSigRgbData      : return  e_cm::kRGB;
        case cmsSigGrayData     : return  e_cm::kG;
        case cmsSigHsvData      : return  e_cm::kRGB;
        case cmsSigHlsData      : return  e_cm::kRGB;
        case cmsSigCmykData     : return  e_cm::kCMYK;
        case cmsSigCmyData      : return  e_cm::kRGB;
        case cmsSigMCH1Data     : return  default_cm;
        case cmsSigMCH2Data     : return  default_cm;
        case cmsSigMCH3Data     : return  default_cm;
        case cmsSigMCH4Data     : return  default_cm;
        case cmsSigMCH5Data     : return  default_cm;
        case cmsSigMCH6Data     : return  default_cm;
        case cmsSigMCH7Data     : return  default_cm;
        case cmsSigMCH8Data     : return  default_cm;
        case cmsSigMCH9Data     : return  default_cm;
        case cmsSigMCHAData     : return  default_cm;
        case cmsSigMCHBData     : return  default_cm;
        case cmsSigMCHCData     : return  default_cm;
        case cmsSigMCHDData     : return  default_cm;
        case cmsSigMCHEData     : return  default_cm;
        case cmsSigMCHFData     : return  default_cm;
        case cmsSigNamedData    : return  default_cm;
        case cmsSig1colorData   : return  default_cm;
        case cmsSig2colorData   : return  default_cm;
        case cmsSig3colorData   : return  default_cm;
        case cmsSig4colorData   : return  default_cm;
        case cmsSig5colorData   : return  default_cm;
        case cmsSig6colorData   : return  default_cm;
        case cmsSig7colorData   : return  default_cm;
        case cmsSig8colorData   : return  default_cm;
        case cmsSig9colorData   : return  default_cm;
        case cmsSig10colorData  : return  default_cm;
        case cmsSig11colorData  : return  default_cm;
        case cmsSig12colorData  : return  default_cm;
        case cmsSig13colorData  : return  default_cm;
        case cmsSig14colorData  : return  default_cm;
        case cmsSig15colorData  : return  default_cm;
        case cmsSigLuvKData     : return  default_cm;
        default                 : return  default_cm;
    }
}

} // namespace ULIS

