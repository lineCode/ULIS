/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Color.ColorProfile.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Color/ULIS.Color.ColorProfile.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FColorProfile
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FColorProfile::FColorProfile( const std::string& iName, cmsHPROFILE iProfile )
    : profile( iProfile )
    , model( ColorModelFromColorSpaceSignature( cmsGetColorSpace( iProfile ) ) )
    , name( iName )
{
}


FColorProfile::~FColorProfile()
{
    cmsCloseProfile( profile );
    profile = nullptr;
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
e_cm
FColorProfile::ModelSignature()  const
{
    return  model;
}


bool
FColorProfile::ModelSupported( e_cm iModel ) const
{
    return  ColorModelCompatFallback( iModel ) == model;
}


const std::string&
FColorProfile::Name() const
{
    return  name;
}


cmsHPROFILE
FColorProfile::ProfileHandle()
{
    return  profile;
}


} // namespace ULIS
