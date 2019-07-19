/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Blend.BlendingContext.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerfStrat.h"
#include "ULIS/Base/ULIS.Base.WeakPRNG.h"
#include "ULIS/Blend/ULIS.Blend.BlendingModes.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Blend/ULIS.Blend.BlockBlender.h"

// Load optimizations
#include "ULIS/Blend/Optimization/ULIS.Blend.Optimization.RGBA8.h"

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >

/////////////////////////////////////////////////////
// TBlendingContext
template< uint32 _SH >
class TBlendingContext
{
public:
    static void Blend( TBlock< _SH >* iBlockTop, TBlock< _SH >* iBlockBack, eBlendingMode iMode, float iOpacity = 1.f, int ix = 0, int iy = 0, bool callInvalidCB = true, const FPerfStrat& iPerfStrat = FPerfStrat() )
    {
        if( iOpacity == 0.f )
            return;

        assert( iOpacity > 0.f && iOpacity <= 1.f );

        FRect back_bb = { 0, 0,     iBlockBack->Width(),    iBlockBack->Height()    };
        FRect top_bb =  { ix, iy,   iBlockTop->Width(),     iBlockTop->Height()     };
        FRect inter_bb = back_bb & top_bb;
        if( inter_bb.Area() <= 0 ) return;

        FPoint shift( -ix, -iy );

        ResetPRNGSeed();
        #define ULIS_SWITCH_OP( iMode )  TBlockBlender< _SH, iMode >::Run( iBlockTop, iBlockBack, ConvType< float, typename TBlock< _SH >::tPixelType >( iOpacity ), inter_bb, shift, iPerfStrat )
        ULIS_FOR_ALL_BLENDING_MODES_DO( iMode, ULIS_SWITCH_OP )
        #undef ULIS_SWITCH_OP

        if( !callInvalidCB )
            return;

        iBlockBack->Invalidate( inter_bb );
    }

    static void Blend( TBlock< _SH >* iBlockTop, TBlock< _SH >* iBlockBack, eBlendingMode iMode, const FRect& iArea, float iOpacity = 1.f, bool callInvalidCB = true, const FPerfStrat& iPerfStrat = FPerfStrat() )
    {
        if( iOpacity == 0.f )
            return;

        assert( iOpacity > 0.f && iOpacity <= 1.f );

        FRect back_bb   = FRect( 0, 0, iBlockBack->Width(), iBlockBack->Height() );
        FRect top_bb    = FRect( iArea.x, iArea.y, iArea.w, iArea.h );
        FRect inter_bb = back_bb & top_bb;
        bool intersects = inter_bb.Area() > 0;
        if( !intersects ) return;
        FPoint shift( 0, 0 );

        ResetPRNGSeed();
        #define ULIS_SWITCH_OP( iMode ) TBlockBlender< _SH, iMode >::Run( iBlockTop, iBlockBack, ConvType< float, typename TBlock< _SH >::tPixelType >( iOpacity ), inter_bb, shift, iPerfStrat )
        ULIS_FOR_ALL_BLENDING_MODES_DO( iMode, ULIS_SWITCH_OP )
        #undef ULIS_SWITCH_OP

        if( !callInvalidCB )
            return;

        iBlockBack->Invalidate( inter_bb );
    }
};


/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS