/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Color.ColorSpace.ColorSpace.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Color/ColorSpace/Constants/ULIS.Color.ColorSpace.Constants.StandardIlluminant.h"
#include "ULIS/Color/ColorSpace/ULIS.Color.ColorSpace.ModelSupport.h"

namespace ULIS {
/////////////////////////////////////////////////////
// IColorSpace
class IColorSpace
{
public:
    virtual e_cm AssociatedModel() const = 0;
};

} // namespace ULIS

