// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ModelSupport.h
* @author       Clement Berthaud
* @brief        This file provides various model compatibility tools.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include "lcms2.h"

ULIS2_NAMESPACE_BEGIN
#pragma warning(push)
#pragma warning(disable : 26812)
static eColorModel ModelFromColorSpaceSignature( cmsColorSpaceSignature iValue )
{
    eColorModel default_cm = CM_RGB;
    switch( iValue )
    {
        case cmsSigXYZData    : return  CM_XYZ;
        case cmsSigLabData    : return  CM_Lab;
        case cmsSigLuvData    : return  CM_YUV;
        case cmsSigYxyData    : return  CM_Yxy;
        case cmsSigRgbData    : return  CM_RGB;
        case cmsSigGrayData   : return  CM_GREY;
        case cmsSigHsvData    : return  CM_RGB;
        case cmsSigHlsData    : return  CM_RGB;
        case cmsSigCmykData   : return  CM_CMYK;
        case cmsSigCmyData    : return  CM_RGB;
        case cmsSigMCH1Data   : return  default_cm;
        case cmsSigMCH2Data   : return  default_cm;
        case cmsSigMCH3Data   : return  default_cm;
        case cmsSigMCH4Data   : return  default_cm;
        case cmsSigMCH5Data   : return  default_cm;
        case cmsSigMCH6Data   : return  default_cm;
        case cmsSigMCH7Data   : return  default_cm;
        case cmsSigMCH8Data   : return  default_cm;
        case cmsSigMCH9Data   : return  default_cm;
        case cmsSigMCHAData   : return  default_cm;
        case cmsSigMCHBData   : return  default_cm;
        case cmsSigMCHCData   : return  default_cm;
        case cmsSigMCHDData   : return  default_cm;
        case cmsSigMCHEData   : return  default_cm;
        case cmsSigMCHFData   : return  default_cm;
        case cmsSigNamedData  : return  default_cm;
        case cmsSig1colorData : return  default_cm;
        case cmsSig2colorData : return  default_cm;
        case cmsSig3colorData : return  default_cm;
        case cmsSig4colorData : return  default_cm;
        case cmsSig5colorData : return  default_cm;
        case cmsSig6colorData : return  default_cm;
        case cmsSig7colorData : return  default_cm;
        case cmsSig8colorData : return  default_cm;
        case cmsSig9colorData : return  default_cm;
        case cmsSig10colorData: return  default_cm;
        case cmsSig11colorData: return  default_cm;
        case cmsSig12colorData: return  default_cm;
        case cmsSig13colorData: return  default_cm;
        case cmsSig14colorData: return  default_cm;
        case cmsSig15colorData: return  default_cm;
        case cmsSigLuvKData   : return  default_cm;
        default               : return  default_cm;
    }
}
#pragma warning(pop) 

static constexpr eColorModel ModelCompatFallback( eColorModel iModel )
{
    switch( iModel )
    {
        case CM_GREY: return  CM_GREY;
        case CM_RGB : return  CM_RGB;
        case CM_HSL : return  CM_RGB;
        case CM_HSV : return  CM_RGB;
        case CM_CMY : return  CM_CMYK;
        case CM_CMYK: return  CM_CMYK;
        case CM_Lab : return  CM_Lab;
        case CM_XYZ : return  CM_XYZ;
        case CM_Yxy : return  CM_Yxy;
        case CM_YUV : return  CM_YUV;
        default     : return  CM_RGB;
    }
}

static constexpr uint32 lcms2PixelTypeForModel( eColorModel iModel )
{
    
    switch( iModel )
    {
        case CM_GREY: return  PT_GRAY;
        case CM_RGB : return  PT_RGB;
        case CM_CMY : return  PT_CMY;
        case CM_CMYK: return  PT_CMYK;
        case CM_YUV : return  PT_YUV;
        case CM_Lab : return  PT_Lab;
        case CM_XYZ : return  PT_XYZ;
        case CM_Yxy : return  PT_Yxy;
        case CM_HSL : return  PT_HLS;
        case CM_HSV : return  PT_HSV;
        default     : return  PT_ANY;
    }
}


static constexpr uint32 F42( uint32 i )
{
    return  (COLORSPACE_SH(lcms2PixelTypeForModel((eColorModel)ULIS2_R_MODEL(i)))
            |EXTRA_SH(ULIS2_R_ALPHA(i))
            |CHANNELS_SH(ULIS2_R_CHANNELS(i))
            |BYTES_SH( ULIS2_R_DEPTH( i ) & 0x7 )
            |DOSWAP_SH(ULIS2_R_REVERSE(i))
            |SWAPFIRST_SH(ULIS2_R_SWAP(i))
            |FLOAT_SH(ULIS2_R_FLOATING(i)));
}

ULIS2_NAMESPACE_END

