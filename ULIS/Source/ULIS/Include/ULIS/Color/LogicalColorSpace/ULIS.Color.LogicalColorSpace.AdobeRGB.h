/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Color.LogicalColorSpace.AdobeRGB.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Color/ULIS.Color.LogicalColorSpace.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FColorSpaceAdobeRGB
class FColorSpaceAdobeRGB : public ILogicalColorSpace
{
public:
    virtual e_cm AssociatedModel() const override { return e_cm::kRGB; }
};

} // namespace ULIS

