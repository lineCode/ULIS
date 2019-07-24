/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Color.AbstractColorSpace.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Data/ULIS.Data.Spec.h"

namespace ULIS {
/////////////////////////////////////////////////////
// IAbstractColorSpace
class IAbstractColorSpace
{
public:
    virtual e_cm AssociatedModel() const = 0;
};

} // namespace ULIS

