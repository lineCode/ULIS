/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Make.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.BaseTypes.h"

namespace ULIS { class IBlock; }

namespace ULIS {
/////////////////////////////////////////////////////
// FMakeContext
class FMakeContext
{
public:
    static ::ULIS::IBlock* MakeBlock( int width, int height, uint32_t ID );
    static ::ULIS::IBlock* MakeBlock( int width, int height, uint8* iData, uint32_t ID );
};

} // namespace ULIS

