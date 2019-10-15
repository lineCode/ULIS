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
#define ttMax TBlock< _SH >::StaticFastMax()
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
template< uint32 _SH > struct BlendFunc< _SH, eBlendingMode::kNormal > {
    static inline typename TBlock< _SH >::tPixelType Compute( const typename TBlock< _SH >::tPixelType& Cb, const typename TBlock< _SH >::tPixelType& Cs ) {
        return Cs;
    }
};
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Erase
template< uint32 _SH > struct BlendFunc< _SH, eBlendingMode::kErase > {
    static inline typename TBlock< _SH >::tPixelType Compute( const typename TBlock< _SH >::tPixelType& Cb, const typename TBlock< _SH >::tPixelType& Cs ) {
        return Cs;
    }
};
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Behind
template< uint32 _SH > struct BlendFunc< _SH, eBlendingMode::kBehind > {
    static inline typename TBlock< _SH >::tPixelType Compute( const typename TBlock< _SH >::tPixelType& Cb, const typename TBlock< _SH >::tPixelType& Cs ) {
        return Cb;
    }
};
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Darken
template< uint32 _SH > struct BlendFunc< _SH, eBlendingMode::kDarken > {
    static inline typename TBlock< _SH >::tPixelType Compute( const typename TBlock< _SH >::tPixelType& Cb, const typename TBlock< _SH >::tPixelType& Cs ) {
        return  FMath::Min( Cb, Cs );
    }
};
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Multiply
template< uint32 _SH > struct BlendFunc< _SH, eBlendingMode::kMultiply > {
    static inline typename TBlock< _SH >::tPixelType Compute( const typename TBlock< _SH >::tPixelType& Cb, const typename TBlock< _SH >::tPixelType& Cs ) {
        return  ttDownscale( ttNextPixelType( Cb * Cs ) );
    }
};
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- ColorBurn
template< uint32 _SH > struct BlendFunc< _SH, eBlendingMode::kColorBurn > {
    static inline typename TBlock< _SH >::tPixelType Compute( const typename TBlock< _SH >::tPixelType& Cb, const typename TBlock< _SH >::tPixelType& Cs ) {
            return  Cs == ttPixelType( 0 ) ? Cs : ttMax - ttPixelType( FMath::Min( ttNextPixelType( ttMax ), ttNextPixelType( ttUpscale( ttMax - Cb ) / Cs ) ) );
    }
};
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- LinearBurn
ULIS_SPEC_BLENDFUNC_COMPUTE_START( LinearBurn )
        return  Cs + Cb < ttMax ? ttPixelType( 0 ) : Cs + Cb - ttMax;
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Lighten
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Lighten )
        return  FMath::Max( Cb, Cs );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Screen
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Screen )
        return  Cb + Cs - ttDownscale( Cb * Cs );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- ColorDodge
ULIS_SPEC_BLENDFUNC_COMPUTE_START( ColorDodge )
        return  Cs == ttMax ? Cs : ttPixelType( FMath::Min( ttNextPixelType( ttMax ), ttNextPixelType( ttUpscale( Cb ) / ( ttMax - Cs ) ) ) );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- LinearDodge
ULIS_SPEC_BLENDFUNC_COMPUTE_START( LinearDodge )
        return  ttPixelType( FMath::Min( ttNextPixelType( ttMax ), ttNextPixelType( Cb + Cs ) ) );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Overlay
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Overlay )
        return  ttNorm( Cb ) < 0.5f ? ttDownscale( 2 * Cs * Cb ) : ttMax - ttDownscale( 2 * ( ttMax - Cs ) * ( ttMax - Cb ) );
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- SoftLight
ULIS_SPEC_BLENDFUNC_COMPUTE_START( SoftLight )
        ttPixelType q = ttDownscale( ttNextPixelType( Cb * Cb ) );
        ttNextPixelType d = 2 * Cs;
        return  q + ttDownscale( d * Cb ) - ttDownscale( d * q );
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
        return  Cb > Cs ? Cb - Cs : 0;
ULIS_SPEC_BLENDFUNC_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Divide
ULIS_SPEC_BLENDFUNC_COMPUTE_START( Divide )
        return  Cs == ttPixelType( 0 ) ? ttMax : ttPixelType( FMath::Min( ttNextPixelType( ttMax ) , ttNextPixelType( ttUpscale( Cb ) / Cs ) ) );
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