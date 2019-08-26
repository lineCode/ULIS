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

namespace ULIS {
/////////////////////////////////////////////////////
// FColorProfile
class FColorProfile
{
public:
    // Public API
    e_cm ModelSignature() const { return  model; };

private:
    // Private Data
    cmsHPROFILE profile;
    e_cm model;
};

} // namespace ULIS

