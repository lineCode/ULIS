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
    cmsToneCurve* gamma_2_2 = cmsBuildGamma( 0, 2.2 );

    mLockedSoftwareProfiles[ "sRGB" ]               = new FColorProfile( cmsCreate_sRGBProfile() );
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


} // namespace ULIS
