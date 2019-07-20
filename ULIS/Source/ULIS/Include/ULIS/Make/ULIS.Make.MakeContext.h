/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Make.MakeContext.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerfStrat.h"
#include "ULIS/Make/ULIS.Make.BlockCopier.h"
#include "ULIS/Data/ULIS.Data.Block.h"

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >

/////////////////////////////////////////////////////
// TMakeContext
template< uint32 _SH >
class TMakeContext
{
public:
    // Copy
    static void CopyBlockRectInto( TBlock< _SH >* iSrc, TBlock< _SH >* iDst, const FRect& iRect, const FPerfStrat& iPerfStrat = FPerfStrat() )
    {
        FRect src_bb = FRect( 0, 0, iSrc->Width(), iSrc->Height() );
        FRect rect_bb = FRect( iArea.x, iArea.y, FMath::Min( iDst->Width(), iArea.w ), FMath::Min( iDst->Height(), iArea.h ) );
        FRect inter_bb  = src_bb & rect_bb;
        bool intersects = inter_bb.Area() > 0;
        if( inter_bb.Area() <= 0 ) return;
        FPoint shift( -ix, -iy );

        TBlockCopier< _SH >::Run( iSrc, iDst, inter_bb, shift, iPerfStrat );
    }
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS