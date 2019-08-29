 /*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.GlobalThreadPool.h
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
public:
    // Public API
    static FThreadPool& Get();
}; 

} // namespace ULIS

