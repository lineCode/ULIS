/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.GlobalPool.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Interface/ULIS.Interface.GlobalPool.h"


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

