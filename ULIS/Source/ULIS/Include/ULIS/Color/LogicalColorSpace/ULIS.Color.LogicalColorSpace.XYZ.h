/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Color.LogicalColorSpace.XYZ.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Color/ULIS.Color.LogicalColorSpace.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FColorSpaceXYZ
class FColorSpaceXYZ : public ILogicalColorSpace
{
public:
    virtual e_cm AssociatedModel() const override { return e_cm::kXYZ; }
};

} // namespace ULIS

