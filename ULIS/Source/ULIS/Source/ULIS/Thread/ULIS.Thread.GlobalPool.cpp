/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Thread.GlobalPool.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Thread/ULIS.Thread.GlobalPool.h"


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

