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
#include "ULIS/Blend/ULIS.Blend.BlendingModes.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Blend/ULIS.Blend.BlockBlender.h"

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >

/////////////////////////////////////////////////////
// TBlockBlender_Imp
template< uint32        _SH,    // Format
          eBlendingMode _BM,    // Blending Mode
          uint32        _LH,    // Layout
          e_nm          _NM,    // Normalized
          bool          _DM >   // Decimal
class TBlockBlenderImp< _SH,
                        _BM,
                        e_tp::kuint8,       // uint8
                        e_cm::kRGB,         // RGB
                        e_ea::khasAlpha,    // Alpha
                        _LH,
                        _NM,
                        _DM >
{
public:
    static void Run( TBlock< _SH >* iBlockTop,
                     TBlock< _SH >* iBlockBack,
                     typename TBlock< _SH >::tPixelType iOpacity,
                     const FRect& iROI,
                     const FPoint& iShift,
                     const FPerfStrat& iPerfStrat = FPerfStrat() )
    {
        //TMP!!!!!!!!!!
        const int x1 = iROI.y;
        const int y1 = iROI.y;
        const int x2 = x1 + iROI.w;
        const int y2 = y1 + iROI.h;
        TPixelBlender< _SH, _BM > pixel_blender( iBlockTop, iBlockBack, iOpacity, iShift );
        for( int y = y1; y < y2; ++y )
        {
            for( int x = x1; x < x2; ++x )
            {
                iBlockBack->SetPixelColor( x, y, CColor( 255, 255, 255 ) );
            }
        }
        //TMP!!!!!!!!!!
    }
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS