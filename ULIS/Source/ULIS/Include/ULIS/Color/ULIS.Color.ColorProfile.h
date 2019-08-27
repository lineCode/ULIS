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

