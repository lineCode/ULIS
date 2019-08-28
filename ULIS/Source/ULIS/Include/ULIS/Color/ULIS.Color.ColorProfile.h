/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Color.ColorProfile.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Color/ULIS.Color.Illuminants.h"
#include "ULIS/Color/ULIS.Color.ModelSupport.h"
#include "lcms2.h"
#include <string>

namespace ULIS {
/////////////////////////////////////////////////////
// DefaultProfiles
namespace DefaultProfiles
{
    static const std::string sRGB                = "sRGB";
    static const std::string AdobeRGB_compat     = "AdobeRGB_compat";
    static const std::string Lab_D65             = "Lab_D65";
    static const std::string Lab_D50             = "Lab_D50";
    static const std::string XYZ                 = "XYZ";
    static const std::string Grey_Gamma2_2_D65   = "Grey_Gamma2.2_D65";
    static const std::string Default_CMYK        = "Default_CMYK";
};

/////////////////////////////////////////////////////
// FColorProfile
class FColorProfile
{
public:
    // Construction / Destruction
    FColorProfile( const std::string& iName, cmsHPROFILE iProfile );
    ~FColorProfile();

public:
    // Public API
    e_cm ModelSignature() const;
    bool ModelSupported( e_cm iModel ) const;
    const std::string& Name() const;
    cmsHPROFILE ProfileHandle();

private:
    // Private Data
    cmsHPROFILE profile;
    e_cm model;
    std::string name;
};

} // namespace ULIS

