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
FColorProfile::FColorProfile()
    : profile( cmsCreate_sRGBProfile() )
    , model( e_cm::kRGB )
{
}


FColorProfile::FColorProfile( cmsHPROFILE iProfile )
    : profile( iProfile )
    , model( ColorModelFromColorSpaceSignature( cmsGetColorSpace( iProfile ) ) )
{
}


FColorProfile::~FColorProfile()
{
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
FColorProfile::ModelSupported( e_cm iModel )
{
    return  ColorModelCompatFallback( iModel ) == model;
}


} // namespace ULIS
