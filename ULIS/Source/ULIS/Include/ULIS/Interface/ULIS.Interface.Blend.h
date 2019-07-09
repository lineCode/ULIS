/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Blend.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Blend/ULIS.Blend.BlendingModes.h"

namespace ULIS { class IBlock; }

namespace ULIS {
/////////////////////////////////////////////////////
// FBlendingContext
class FBlendingContext
{
public:
    // Blend
    // Blends two Blocks
    // Result is stored in-place in iBlockBack
    // Params:
    // iBlockTop: the block on top
    // iBlockBack: the block that receives the blend ( in-place )
    // iMode: the mode
    // iOpacity: the opcaity of iBlockTop
    // x: where is iBlockTop blended on x axis
    // y: where is iBlockTop blended on y axis
    // callInvalidCB: should we call the invalid callback once done ( default true )
    static void Blend( IBlock* iBlockTop, IBlock* iBlockBack, eBlendingMode iMode, float iOpacity = 1.f, int ix = 0, int iy = 0, bool callInvalidCB = true );

    // Blend
    // Blends two Blocks
    // Result is stored in-place in iBlockBack
    // Params:
    // iBlockTop: the block on top
    // iBlockBack: the block that receives the blend ( in-place )
    // iMode: the mode
    // iOpacity: the opcaity of iBlockTop
    // iArea: the area to blend
    // callInvalidCB: should we call the invalid callback once done ( default true )
    static void Blend( IBlock* iBlockTop, IBlock* iBlockBack, eBlendingMode iMode, const FRect& iArea, float iOpacity = 1.f, bool callInvalidCB = true );
};

} // namespace ULIS

