/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Global.GlobalProfileRegistry.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Color/ULIS.Color.ProfileRegistry.h"


namespace ULIS {
/////////////////////////////////////////////////////
// FGlobalProfileRegistry
class FGlobalProfileRegistry
{
public:
    // Public API
    static FProfileRegistry& Get();
}; 

} // namespace ULIS

