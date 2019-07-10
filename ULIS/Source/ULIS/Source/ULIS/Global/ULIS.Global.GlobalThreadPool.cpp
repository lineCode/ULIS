/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.GlobalThreadPool.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Global/ULIS.Global.GlobalThreadPool.h"


namespace ULIS {
/////////////////////////////////////////////////////
// FGlobalThreadPool
// Public API
//static
FThreadPool&
FGlobalThreadPool::Get()
{
    static FThreadPool* pool;
    if( !pool )
        pool = new FThreadPool();

    return  *pool;
}

} // namespace ULIS

