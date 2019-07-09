/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.GlobalPool.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Thread/ULIS.Thread.Pool.h"


namespace ULIS {
/////////////////////////////////////////////////////
// FGlobalThreadPool
class FGlobalThreadPool
{
private:
    // Construction / Destruction
    FGlobalThreadPool ();

public:
    // Public API
    static FThreadPool& Get();
}; 

} // namespace ULIS

