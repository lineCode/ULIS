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
/////////////////////////////////////////////////////
// Color Enums Info:
// cmsColorSpaceSignature is the lcms2 way of telling which model is associated to a profile
// eModel it the enum for data layout, which is a subset of cmsColorSpaceSignature, and must match with lcms2 cmsColorSpaceSignature when a profile is assigned
// eColorModel it the enum for FColor models, which is a subset of eModel, and is totally profile agnostic

/////////////////////////////////////////////////////
// Supported FColor Models
enum class eColorModel : int
{
    kInvalid,
    kG,
    kRGB,
    kHSL,
    kHSV,
    kCMYK,
};


/////////////////////////////////////////////////////
// Model Correspondance
static eModelSig ModelSigFromColorModel( eColorModel iValue )
{
    switch( iValue )
    {
        case eColorModel::kInvalid:    return  eModelSig::kGrey;
        case eColorModel::kG:          return  eModelSig::kGrey;
        case eColorModel::kRGB:        return  eModelSig::kRGB;
        case eColorModel::kHSL:        return  eModelSig::kHSL;
        case eColorModel::kHSV:        return  eModelSig::kHSV;
        case eColorModel::kCMYK:       return  eModelSig::kCMYK;
    }
}


static eColorModel  ColorModelFromModelSig( eModelSig iValue )
{
    switch( iValue )
    {
        case eModelSig::kGrey:      return  eColorModel::kG;
        case eModelSig::kRGB:       return  eColorModel::kRGB;
        case eModelSig::kHSL:       return  eColorModel::kHSL;
        case eModelSig::kHSV:       return  eColorModel::kHSV;
        case eModelSig::kCMYK:      return  eColorModel::kCMYK;
        default:                    return  eColorModel::kInvalid;
    }
}

#pragma warning(push)
#pragma warning(disable : 26812)
static eModelSig ModelSigFromColorSpaceSignature( cmsColorSpaceSignature iValue )
{
    eModelSig default_cm = eModelSig::kRGB;
    switch( iValue )
    {
        case cmsSigXYZData      : return  eModelSig::kXYZ;
        case cmsSigLabData      : return  eModelSig::kLab;
        case cmsSigLuvData      : return  eModelSig::kYUV;
        case cmsSigYxyData      : return  eModelSig::kYxy;
        case cmsSigRgbData      : return  eModelSig::kRGB;
        case cmsSigGrayData     : return  eModelSig::kGrey;
        case cmsSigHsvData      : return  eModelSig::kRGB;
        case cmsSigHlsData      : return  eModelSig::kRGB;
        case cmsSigCmykData     : return  eModelSig::kCMYK;
        case cmsSigCmyData      : return  eModelSig::kRGB;
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
        case cmsSigLuvKData     : return  eModelSig::kYUVK;
        default                 : return  default_cm;
    }
}
#pragma warning(pop) 

static constexpr eModelSig ModelSigCompatFallback( eModelSig iModel )
{
    switch( iModel )
    {
        case eModelSig::kGrey:      return  eModelSig::kGrey;
        case eModelSig::kRGB:       return  eModelSig::kRGB;
        case eModelSig::kHSL:       return  eModelSig::kRGB;
        case eModelSig::kHSV:       return  eModelSig::kRGB;
        case eModelSig::kCMYK:      return  eModelSig::kCMYK;
        case eModelSig::kLab:       return  eModelSig::kLab;
        case eModelSig::kXYZ:       return  eModelSig::kXYZ;
        default:                    return  eModelSig::kRGB;
    }
}

ULIS2_NAMESPACE_END

