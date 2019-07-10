/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Make.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Global/ULIS.Global.GlobalCPUConfig.h"
#include "ULIS/Global/ULIS.Global.GlobalThreadPool.h"

namespace ULIS {

void
Init()
{
    FGlobalCPUConfig::Get();
    FGlobalThreadPool::Get();
    srand( time(0) );
}

} // namespace ULIS

