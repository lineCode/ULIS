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
FCPUConfig&
FGlobalCPUConfig::Get()
{
    static FCPUConfig* conf;
    if( !conf )
        conf = new FCPUConfig();

    return  *conf;
}

} // namespace ULIS

