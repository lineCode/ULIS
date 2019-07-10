/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Blend.BlockBlender.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerfStrat.h"
#include "ULIS/Blend/ULIS.Blend.BlendingModes.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Blend/ULIS.Blend.PixelBlender.h"

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >

/////////////////////////////////////////////////////
// TBlockBlender_Default
template< uint32 _SH, eBlendingMode _BM, e_tp _TP, e_cm _CM, e_ea _EA, uint32 _LH, e_nm _NM, bool _DM >
class TBlockBlender_Default
{
public:
    static void Run( TBlock< _SH >* iBlockTop, TBlock< _SH >* iBlockBack, typename TBlock< _SH >::tPixelType iOpacity, const FRect& iROI, const FPoint& iShift, const FPerfStrat& iPerfStrat = FPerfStrat() )
    {
        const int x1 = iROI.y;
        const int y1 = iROI.y;
        const int x2 = x1 + iROI.w;
        const int y2 = y1 + iROI.h;
        TPixelBlender< _SH, _BM > pixel_blender( iBlockTop, iBlockBack, iOpacity, iShift );
        for( int y = y1; y < y2; ++y )
            for( int x = x1; x < x2; ++x )
                pixel_blender.Apply( x, y );
    }
};


/////////////////////////////////////////////////////
// TBlockBlender_Imp
template< uint32 _SH, eBlendingMode _BM, e_tp _TP, e_cm _CM, e_ea _EA, uint32 _LH, e_nm _NM, bool _DM >
class TBlockBlenderImp
{
public:
    static inline void Run( TBlock< _SH >* iBlockTop, TBlock< _SH >* iBlockBack, typename TBlock< _SH >::tPixelType iOpacity, const FRect& iROI, const FPoint& iShift, const FPerfStrat& iPerfStrat = FPerfStrat() )
    {
        TBlockBlender_Default< _SH, _BM, tSpec::_nf._tp, tSpec::_nf._cm, tSpec::_nf._ea, tSpec::_nf._lh, tSpec::_nf._nm, tSpec::_nf._dm >::Run( iBlockTop, iBlockBack, iOpacity, iROI, iShift, iPerfStrat );
    }
};

/////////////////////////////////////////////////////
// TBlockBlender
template< uint32 _SH, eBlendingMode _BM >
class TBlockBlender
{
public:
    static inline void Run( TBlock< _SH >* iBlockTop, TBlock< _SH >* iBlockBack, typename TBlock< _SH >::tPixelType iOpacity, const FRect& iROI, const FPoint& iShift, const FPerfStrat& iPerfStrat = FPerfStrat() )
    {
        TBlockBlenderImp< _SH, _BM, tSpec::_nf._tp, tSpec::_nf._cm, tSpec::_nf._ea, tSpec::_nf._lh, tSpec::_nf._nm, tSpec::_nf._dm >::Run( iBlockTop, iBlockBack, iOpacity, iROI, iShift, iPerfStrat );
    }
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS