/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Blend.PixelBlender.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Blend/ULIS.Blend.BlendingModes.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Blend/ULIS.Blend.BasicCompositing.h"

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >

/////////////////////////////////////////////////////
// TPixelBlender
template< uint32 _SH, eBlendingMode _BM >
struct TPixelBlender
{
    TPixelBlender( TBlock< _SH >* iBlockTop, TBlock< _SH >* iBlockBack, typename TBlock< _SH >::tPixelType iOpacity, const FPoint& iShift )
        : top( iBlockTop )
        , back( iBlockBack )
        , opacity( iOpacity )
        , shift( iShift )
    {}

    void Apply( int x, int y )
    {
        typename TBlock< _SH >::tPixelProxy pixelBack = back->PixelProxy( x, y );
        typename TBlock< _SH >::tPixelProxy pixelTop  = top->PixelProxy( x + shift.x, y + shift.y );
        const typename TBlock< _SH >::tPixelType  alphaBack = pixelBack.GetAlpha();
        const typename TBlock< _SH >::tPixelType  alphaTop  = ConvType< typename TBlock< _SH >::tNextPixelType, typename TBlock< _SH >::tPixelType >( (typename TBlock< _SH >::tNextPixelType)( pixelTop.GetAlpha() * opacity ) );
        const typename TBlock< _SH >::tPixelType  alphaResult = Union< _SH >( alphaBack, alphaTop );
        const typename TBlock< _SH >::tPixelType  var = alphaResult == 0 ? 0 : ( alphaTop * TBlock< _SH >::StaticMax() ) / alphaResult;
        const int max_chan = TBlock< _SH >::StaticNumColorChannels();
        for( int i = 0; i < max_chan; ++i )
            pixelBack.SetComponent( i, Composer< _SH, _BM >::BasicCompositing( pixelBack.GetComponent( i ), pixelTop.GetComponent( i ), alphaBack, var ) );
        pixelBack.SetAlpha( alphaResult );
    }

    TBlock< _SH >* top;
    TBlock< _SH >* back;
    typename TBlock< _SH >::tPixelType opacity;
    const FPoint& shift;
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS