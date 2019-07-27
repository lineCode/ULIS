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

#include "ULIS/Color/ULIS.Color.Constants.h"
#include "ULIS/Color/ULIS.Color.ModelSupport.h"
#include "lcms2.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FColorProfile
class FColorProfile
{
public:
    // Public API
    e_cm ModelSignature() const { return  e_cm::kRGB; };

private:
    // Private Data
    cmsHPROFILE profile;
};

} // namespace ULIS

