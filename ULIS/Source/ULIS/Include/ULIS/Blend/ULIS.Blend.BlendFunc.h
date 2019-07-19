/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Blend.BlendFunc.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Blend/ULIS.Blend.BlendingModes.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Maths/ULIS.Maths.Utility.h"

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >
#define ttPixelType typename TBlock< _SH >::tPixelType
#define ttNextPixelType typename TBlock< _SH >::tNextPixelType
#define ttMax typename TBlock< _SH >::StaticFastMax()
#define ttDownscale ConvType< ttNextPixelType, ttPixelType >
#define ttUpscale ConvType< ttPixelType, ttNextPixelType >
#define ttNorm ConvType< ttPixelType, float >

/////////////////////////////////////////////////////
// BlendFunc Functors
template< uint32 _SH, eBlendingMode _BM >
struct BlendFunc {
    static inline
    typename TBlock< _SH >::tPixelType Compute( const typename TBlock< _SH >::tPixelType& Cb, const typename TBlock< _SH >::tPixelType& Cs )
    {
        return ttPixelType(0);
    }
};

#define ULIS_SPEC_BLENDFUNC_COMPUTE_START( iMode )                                                                                                          \
    template< uint32 _SH > struct BlendFunc< _SH, eBlendingMode::k ## iMode > {                                                                             \
    static inline typename TBlock< _SH >::tPixelType Compute( const typename TBlock< _SH >::tPixelType& Cb, const typename TBlock< _SH >::tPixelType& Cs ) {
#define ULIS_SPEC_BLENDFUNC_COMPUTE_END }};

//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Normal
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Normal )
    return Cs;
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Normal
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Behind )
    return Cb;
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Darken
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Darken )
        return  FMath::Min( Cb, Cs );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Multiply
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Multiply )
        return  ttDownscale( ttNextPixelType( Cb * Cs ) );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- ColorBurn
ULIS_SPEC_BLENDFUNC_COMPUTE_START( ColorBurn )
        return  Cs == ttPixelType( 0 ) ? Cs : ttMax - FMath::Min( ttMax, ttUpscale( ttMax - Cb ) / Cs );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- LinearBurn
ULIS_SPEC_BLENDFUNC_COMPUTE_START( LinearBurn )
        return  Cs + Cb - ttMax;
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Lighten
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Lighten )
        return  FMath::Max( Cb, Cs );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Screen
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Screen )
        return  Cb + Cs - ttDownscale( Cb * Cs )
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- ColorDodge
ULIS_SPEC_BLENDFUNC_COMPUTE_START( ColorDodge )
        return  Cs == ttMax ? Cs : FMath::Min( ttMax, ttUpscale( Cb ) / ( ttMax - Cs ) );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- LinearDodge
ULIS_SPEC_BLENDFUNC_COMPUTE_START( LinearDodge )
        return  ttPixelType( Fmath::Min( ttNextPixelType( ttMax ), ttNextPixelType( Cb + Cs ) ) );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Overlay
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Overlay )
        return  ttNorm( Cs ) < 0.5f ? ttDownscale( Cb * ( 2 * Cs ) ) : ttMax - 2 * ttDownscale( ( ttMax * Cs ) * ( ttMax - Cb ) );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- SoftLight
ULIS_SPEC_BLENDFUNC_COMPUTE_START( SoftLight )
        return  ttNorm( Cs ) < 0.5f ? ttDownscale( ( 2 * Cs - ttMax ) * ( Cb - ttDownscale( Cb * Cb ) ) ) + Cb : ( 2 * Cs - ttMax ) * ( sqrt( double( Cb ) ) - Cb ) + Cb;
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- HardLight
ULIS_SPEC_BLENDFUNC_COMPUTE_START( HardLight )
        return  BlendFunc< _SH, eBlendingMode::kOverlay >::Compute( Cs, Cb );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- VividLight
ULIS_SPEC_BLENDFUNC_COMPUTE_START( VividLight )
        return  ttNorm( Cs ) < 0.5f ? BlendFunc< _SH, eBlendingMode::kColorBurn >::Compute( Cb, 2 * Cs ) : BlendFunc< _SH, eBlendingMode::kColorDodge >::Compute( Cb, 2 * ( Cs - ( ttMax / ttPixelType( 2 ) ) ) );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- LinearLight
ULIS_SPEC_BLENDFUNC_COMPUTE_START( LinearLight )
        return  ttNorm( Cs ) < 0.5f ? BlendFunc< _SH, eBlendingMode::kLinearBurn >::Compute( Cb, 2 * Cs ) : BlendFunc< _SH, eBlendingMode::kLinearDodge >::Compute( Cb, 2 * ( Cs - ( ttMax / ttPixelType( 2 ) ) ) );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- PinLight
ULIS_SPEC_BLENDFUNC_COMPUTE_START( PinLight )
        return  ttNorm( Cs ) < 0.5f ? BlendFunc< _SH, eBlendingMode::kDarken >::Compute( Cb, 2 * Cs ) : BlendFunc< _SH, eBlendingMode::kLighten >::Compute( Cb, 2 * ( Cs - ( ttMax / ttPixelType( 2 ) ) ) );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ HardMix
ULIS_SPEC_BLENDFUNC_COMPUTE_START( HardMix )
        return  ttNorm( BlendFunc< _SH, eBlendingMode::kVividLight >::Compute( Cb, Cs ) ) < 0.5f ? 0 : 255;
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Difference
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Difference )
        return  ttPixelType( abs( double( Cb - Cs ) ) );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Exclusion
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Exclusion )
        return  Cb + Cs - 2 * ttDownscale( Cb * Cs );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Substract
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Substract )
        return  Cb + Cs < ttMax ? 0 : Cb + Cs - ttMax;
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Divide
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Divide )
        return  Cs == 0 ? 0 : Cb / Cs;
ULIS_SPEC_BLENDFUNC_COMPUTE_END

/////////////////////////////////////////////////////
// Undefines
#undef tSpec
#undef ttPixelType
#undef ttNextPixelType
#undef ttMax
#undef ttDownscale
#undef ttUpscale

} // namespace ULIS