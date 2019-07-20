/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.ClearFIll.ClearFillContext.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerfStrat.h"
#include "ULIS/ClearFill/ULIS.ClearFIll.BlockClearer.h"
#include "ULIS/ClearFill/ULIS.ClearFIll.BlockFiller.h"
#include "ULIS/Color/ULIS.Color.CColor.h"
#include "ULIS/Data/ULIS.Data.Block.h"

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >

/////////////////////////////////////////////////////
// TClearFillContext
template< uint32 _SH >
class TClearFillContext
{
public:
    // Fill

    static void Fill( TBlock< _SH >* iBlock, const CColor& iColor, const FPerfStrat& iPerfStrat = FPerfStrat(), bool callInvalidCB = true )
    {
        FillRect( iBlock, iColor, FRect( 0, 0, iBlock->Width(), iBlock->Height() ), iPerfStrat, callInvalidCB );
    }

    static void FillRect( TBlock< _SH >* iBlock, const CColor& iColor, const FRect& iArea, const FPerfStrat& iPerfStrat = FPerfStrat(), bool callInvalidCB = true )
    {
        FRect block_bb  = FRect( 0, 0, iBlock->Width(), iBlock->Height() );
        FRect rect_bb   = FRect( iArea.x, iArea.y, iArea.w, iArea.h );
        FRect inter_bb  = block_bb & rect_bb;
        bool intersects = inter_bb.Area() > 0;
        if( !intersects ) return;

        TBlockFiller< _SH >::Run( iBlock, TBlock<_SH>::PixelValueForColor( iColor ), inter_bb, iPerfStrat );

        if( !callInvalidCB )
            return;

        iBlock->Invalidate( inter_bb );
    }

public:
    // Clear
    static void Clear( TBlock< _SH >* iBlock, const FPerfStrat& iPerfStrat = FPerfStrat(), bool callInvalidCB = true )
    {
        ClearRect( iBlock, FRect( 0, 0, iBlock->Width(), iBlock->Height() ), iPerfStrat, callInvalidCB );
    }

    static void ClearRect( TBlock< _SH >* iBlock, const FRect& iArea, const FPerfStrat& iPerfStrat = FPerfStrat(), bool callInvalidCB = true )
    {
        FRect block_bb  = FRect( 0, 0, iBlock->Width(), iBlock->Height() );
        FRect rect_bb   = FRect( iArea.x, iArea.y, iArea.w, iArea.h );
        FRect inter_bb  = block_bb & rect_bb;
        bool intersects = inter_bb.Area() > 0;
        if( !intersects ) return;

        TBlockClearer< _SH >::Run( iBlock, inter_bb, iPerfStrat );

        if( !callInvalidCB )
            return;

        iBlock->Invalidate( inter_bb );
    }
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS