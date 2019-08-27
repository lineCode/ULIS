/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Color.ProfileRegistry.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Color/ULIS.Color.ProfileRegistry.h"
#include "ULIS/Color/ULIS.Color.DefaultCMYK_SNAP.h"

namespace ULIS {
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

    mLockedSoftwareProfiles[ "sRGB" ]               = new FColorProfile( cmsCreate_sRGBProfile() );
    mLockedSoftwareProfiles[ "AdobeRGB_compat" ]    = new FColorProfile( cmsCreateRGBProfile( &whitepoint_D65, &AdobeRGB_compat_chroma, gamma3_2_2 ) );

    mLockedSoftwareProfiles[ "Lab_D65" ]            = new FColorProfile( cmsCreateLab4Profile( &whitepoint_D65 ) );
    mLockedSoftwareProfiles[ "Lab_D50" ]            = new FColorProfile( cmsCreateLab4Profile( &whitepoint_D50 ) );

    mLockedSoftwareProfiles[ "XYZ" ]                = new FColorProfile( cmsCreateXYZProfile() );
    mLockedSoftwareProfiles[ "Grey_Gamma2.2_D65" ]  = new FColorProfile( cmsCreateGrayProfile( &whitepoint_D65, gamma_2_2 ) );

    mLockedSoftwareProfiles[ "Default_CMYK" ]       = new FColorProfile( cmsOpenProfileFromMem( Default_Profile_CMYK_SNAP, sizeof( Default_Profile_CMYK_SNAP ) ) );

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
FProfileRegistry::GetProfile( const std::string iKey )
{
    if ( mLockedSoftwareProfiles.find( iKey ) != mLockedSoftwareProfiles.end() )
        return  mLockedSoftwareProfiles[iKey];

    if ( mFileBasedProfiles.find( iKey ) != mFileBasedProfiles.end() )
        return  mFileBasedProfiles[iKey];

    return  nullptr;
}


std::string
FProfileRegistry::DefaultProfileForModel( e_cm iModel )
{
    switch( iModel )
    {
        case e_cm::kG:      return  "Grey_Gamma2.2_D65";
        case e_cm::kRGB:    return  "sRGB";
        case e_cm::kHSL:    return  "sRGB";
        case e_cm::kHSV:    return  "sRGB";
        case e_cm::kCMYK:   return  "Default_CMYK";
        case e_cm::kLab:    return  "Lab_D65";
        case e_cm::kXYZ:    return  "XYZ";
        default:            return  "invalid";
    }
}


} // namespace ULIS
