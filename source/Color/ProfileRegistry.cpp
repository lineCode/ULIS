// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ProfileRegistry.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the FProfileRegistry class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Color/ProfileRegistry.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FProfileRegistry
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FProfileRegistry::FProfileRegistry()
{
    cmsToneCurve* gamma_2_2     = cmsBuildGamma( 0, 2.2 );
    cmsToneCurve* gamma3_2_2[3] = { gamma_2_2, gamma_2_2, gamma_2_2 };

    cmsCIExyYTRIPLE AdobeRGB_compat_chroma;
    AdobeRGB_compat_chroma.Red      = cmsCIExyY{ 0.6400, 0.3300, 0.0300 };
    AdobeRGB_compat_chroma.Green    = cmsCIExyY{ 0.2100, 0.7100, 0.0800 };
    AdobeRGB_compat_chroma.Blue     = cmsCIExyY{ 0.1500, 0.0600, 0.7900 };

    mLockedSoftwareProfiles[ DefaultProfiles::sRGB ]               = new FColorProfile( DefaultProfiles::sRGB,                cmsCreate_sRGBProfile() );
    mLockedSoftwareProfiles[ DefaultProfiles::AdobeRGB_compat ]    = new FColorProfile( DefaultProfiles::AdobeRGB_compat,     cmsCreateRGBProfile( &whitepoint_D65, &AdobeRGB_compat_chroma, gamma3_2_2 ) );
    mLockedSoftwareProfiles[ DefaultProfiles::Lab_D65 ]            = new FColorProfile( DefaultProfiles::Lab_D65,             cmsCreateLab4Profile( &whitepoint_D65 ) );
    mLockedSoftwareProfiles[ DefaultProfiles::Lab_D50 ]            = new FColorProfile( DefaultProfiles::Lab_D50,             cmsCreateLab4Profile( &whitepoint_D50 ) );
    mLockedSoftwareProfiles[ DefaultProfiles::XYZ ]                = new FColorProfile( DefaultProfiles::XYZ,                 cmsCreateXYZProfile() );
    mLockedSoftwareProfiles[ DefaultProfiles::Grey_Gamma2_2_D65 ]  = new FColorProfile( DefaultProfiles::Grey_Gamma2_2_D65,   cmsCreateGrayProfile( &whitepoint_D65, gamma_2_2 ) );

    cmsFreeToneCurve( gamma_2_2 );
}


FProfileRegistry::~FProfileRegistry()
{
    for( auto it : mLockedSoftwareProfiles )
        delete  it.second;
    mLockedSoftwareProfiles.clear();

    for( auto it : mFileBasedProfiles )
        delete  it.second;
    mFileBasedProfiles.clear();
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
FColorProfile*
FProfileRegistry::GetProfile( const std::string iKey ) const
{
    if ( mLockedSoftwareProfiles.find( iKey ) != mLockedSoftwareProfiles.end() )
        return  mLockedSoftwareProfiles.at( iKey );

    if ( mFileBasedProfiles.find( iKey ) != mFileBasedProfiles.end() )
        return  mFileBasedProfiles.at( iKey );

    return  nullptr;
}


std::string
FProfileRegistry::DefaultProfileNameForModel( eColorModel iModel ) const
{
    switch( iModel )
    {
        case CM_GREY:   return  "Grey_Gamma2.2_D65";
        case CM_RGB:    return  "sRGB";
        case CM_HSL:    return  "sRGB";
        case CM_HSV:    return  "sRGB";
        case CM_Lab:    return  "Lab_D65";
        case CM_XYZ:    return  "XYZ";
        default:        return  "invalid";
    }
}


FColorProfile*
FProfileRegistry::GetDefaultProfileForModel( eColorModel iModel ) const
{
    return  GetProfile( DefaultProfileNameForModel( iModel ) );
}

ULIS2_NAMESPACE_END

