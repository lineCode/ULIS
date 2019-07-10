/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.GlobalCPUConfig.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Global/ULIS.Global.GlobalCPUConfig.h"


namespace ULIS {
/////////////////////////////////////////////////////
// FGlobalThreadPool
// Public API
//static
FGlobalCPUConfig&
FGlobalCPUConfig::Get()
{
    static FGlobalCPUConfig* conf;
    if( !conf )
        conf = new FGlobalCPUConfig();

    return  *conf;
}

} // namespace ULIS

