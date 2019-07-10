/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.GlobalCPUConfig.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.CPUConfig.h"


namespace ULIS {
/////////////////////////////////////////////////////
// FGlobalCPUConfig
class FGlobalCPUConfig
{
public:
    // Public API
    static FCPUConfig& Get();
}; 

} // namespace ULIS

