/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Color.LogicalColorSpace.CustomRGB.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Color/ULIS.Color.LogicalColorSpace.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FColorSpaceCustomRGB
class FColorSpaceCustomRGB : public ILogicalColorSpace
{
public:
    virtual e_cm AssociatedModel() const override { return e_cm::kRGB; }
};

} // namespace ULIS

