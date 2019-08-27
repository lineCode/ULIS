/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Global.GlobalProfileRegistry.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Global/ULIS.Global.GlobalProfileRegistry.h"


namespace ULIS {
/////////////////////////////////////////////////////
// FGlobalProfileRegistry
// Public API
//static
FProfileRegistry&
FGlobalProfileRegistry::Get()
{
    static FProfileRegistry* pro = NULL;
    if( !pro )
        pro = new FProfileRegistry();

    return  *pro;
}

} // namespace ULIS

