/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Color.LogicalColorSpace.Lab.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Color/ULIS.Color.LogicalColorSpace.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FColorSpaceLab
class FColorSpaceLab : public ILogicalColorSpace
{
public:
    virtual e_cm AssociatedModel() const override { return e_cm::kLab; }
};

} // namespace ULIS

