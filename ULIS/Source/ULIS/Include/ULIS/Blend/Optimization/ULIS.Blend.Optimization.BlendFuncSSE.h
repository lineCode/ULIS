/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Blend.Optimization.BlendFuncSSE.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Blend/ULIS.Blend.BlendingModes.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Maths/ULIS.Maths.Utility.h"
#include <immintrin.h>

namespace ULIS {
/////////////////////////////////////////////////////
// BlendFuncSSE Functors
template< eBlendingMode _BM >
struct BlendFuncSSE {
    static inline
    __m128 Compute( const __m128& Cb, const __m128& Cs )
    {
        return  _mm_setzero_ps();
    }
};

#define ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( iMode )                          \
    template<> struct BlendFuncSSE< eBlendingMode::k ## iMode > {               \
    static inline __m128 Compute( const __m128& Cb, const __m128& Cs ) {
#define ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END }};

// SPEC BLEND
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Normal
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( Normal )
    return Cs;
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Erase
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( Erase )
    return Cb;
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Behind
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( Behind )
    return Cb;
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Darken
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( Darken )
    return  _mm_min_ps( Cb, Cs );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- Multiply
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( Multiply )
    return  _mm_div_ps( _mm_mul_ps( Cb, Cs ), _mm_set_ps1( 255.f ) );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- ColorBurn
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( ColorBurn )
    __m128 vcmp     = _mm_cmpeq_ps( Cs, _mm_setzero_ps() );
    __m128 max255f  = _mm_set_ps1( 255.f );
    __m128 computed = _mm_sub_ps( max255f, _mm_min_ps( max255f, _mm_div_ps( _mm_mul_ps( max255f, _mm_sub_ps( max255f, Cb ) ), Cs ) ) );
    return  _mm_blendv_ps( computed, Cs, vcmp );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- LinearBurn
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( LinearBurn )
    __m128 add      = _mm_add_ps( Cs, Cb );
    __m128 max255f  = _mm_set_ps1( 255.f );
    __m128 vcmp     = _mm_cmplt_ps( add, max255f );
    __m128 computed = _mm_sub_ps( add, max255f );
    return  _mm_blendv_ps( computed, _mm_setzero_ps(), vcmp );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END

//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Lighten
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( Lighten )
    return  _mm_max_ps( Cb, Cs );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Screen
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( Screen )
    return  _mm_sub_ps( _mm_add_ps( Cb, Cs ), _mm_div_ps( _mm_mul_ps( Cb, Cs ), _mm_set_ps1( 255.f ) ) );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- ColorDodge
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( ColorDodge )
    __m128 max255f  = _mm_set_ps1( 255.f );
    __m128 vcmp     = _mm_cmpeq_ps( Cs, max255f );
    __m128 computed = _mm_min_ps( max255f, _mm_div_ps( _mm_mul_ps( max255f, Cb ), _mm_sub_ps( max255f, Cs ) ) );
    return  _mm_blendv_ps( computed, Cs, vcmp );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- LinearDodge
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( LinearDodge )
    return  _mm_min_ps( _mm_set_ps1( 255.f ), _mm_add_ps( Cb, Cs ) );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Overlay
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( Overlay )
    __m128 max255f      = _mm_set_ps1( 255.f );
    __m128 twof         = _mm_set_ps1( 2.f );
    __m128 vcmp         = _mm_cmplt_ps( Cb, _mm_set_ps1( 128.f ) );
    __m128 computedA    = _mm_div_ps( _mm_mul_ps( twof, _mm_mul_ps( Cs, Cb ) ), max255f );
    __m128 computedB    = _mm_sub_ps( max255f, _mm_div_ps( _mm_mul_ps( twof, _mm_mul_ps( _mm_sub_ps( max255f, Cs ), _mm_sub_ps( max255f, Cb ) ) ), max255f ) );
    return  _mm_blendv_ps( computedB, computedA, vcmp );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- SoftLight
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( SoftLight )
    __m128 q = _mm_div_ps( _mm_mul_ps( Cb, Cs ), _mm_set_ps1( 255.f ) );
    __m128 d = _mm_mul_ps( _mm_set_ps1( 2.f ), Cs );
    return  _mm_sub_ps( _mm_add_ps( q, _mm_div_ps( _mm_mul_ps( d, Cb ), _mm_set_ps1( 255.f ) ) ), _mm_div_ps( _mm_mul_ps( d, q ), _mm_set_ps1( 255.f ) ) );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- HardLight
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( HardLight )
    return  BlendFuncSSE< eBlendingMode::kOverlay >::Compute( Cs, Cb );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- VividLight
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( VividLight )
    __m128 twof         = _mm_set_ps1( 2.f );
    __m128 vcmp         = _mm_cmplt_ps( Cs, _mm_set_ps1( 128.f ) );
    __m128 computedA    = BlendFuncSSE< eBlendingMode::kColorBurn >::Compute( Cb, _mm_mul_ps( twof, Cs ) );
    __m128 computedB    = BlendFuncSSE< eBlendingMode::kColorDodge >::Compute( Cb, _mm_mul_ps( twof, _mm_sub_ps( Cs, _mm_set_ps1( 127.f ) ) ) );
    return  _mm_blendv_ps( computedB, computedA, vcmp );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- LinearLight
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( LinearLight )
    __m128 twof         = _mm_set_ps1( 2.f );
    __m128 vcmp         = _mm_cmplt_ps( Cs, _mm_set_ps1( 128.f ) );
    __m128 computedA    = BlendFuncSSE< eBlendingMode::kLinearBurn >::Compute( Cb, _mm_mul_ps( twof, Cs ) );
    __m128 computedB    = BlendFuncSSE< eBlendingMode::kLinearDodge >::Compute( Cb, _mm_mul_ps( twof, _mm_sub_ps( Cs, _mm_set_ps1( 127.f ) ) ) );
    return  _mm_blendv_ps( computedB, computedA, vcmp );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//----------------------------------------------------------------------------- PinLight
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( PinLight )
    __m128 twof         = _mm_set_ps1( 2.f );
    __m128 vcmp         = _mm_cmplt_ps( Cs, _mm_set_ps1( 128.f ) );
    __m128 computedA    = BlendFuncSSE< eBlendingMode::kDarken >::Compute( Cb, _mm_mul_ps( twof, Cs ) );
    __m128 computedB    = BlendFuncSSE< eBlendingMode::kLighten >::Compute( Cb, _mm_mul_ps( twof, _mm_sub_ps( Cs, _mm_set_ps1( 127.f ) ) ) );
    return  _mm_blendv_ps( computedB, computedA, vcmp );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ HardMix
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( HardMix )
    __m128 computed = BlendFuncSSE< eBlendingMode::kVividLight >::Compute( Cb, Cs );
    __m128 vcmp     = _mm_cmplt_ps( computed, _mm_set_ps1( 128.f ) );
    return  _mm_blendv_ps( _mm_set_ps1( 255.f ), _mm_setzero_ps(), vcmp );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Difference
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( Difference )
    __m128 diff = _mm_sub_ps( Cb, Cs );
    return  _mm_max_ps( _mm_sub_ps( _mm_setzero_ps(), diff ), diff );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Exclusion
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( Exclusion )
    return  _mm_add_ps( Cb, _mm_sub_ps( Cs, _mm_mul_ps( _mm_set_ps1( 2.f ), _mm_div_ps( _mm_mul_ps( Cb, Cs ), _mm_set_ps1( 255.f ) ) ) ) );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Substract
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( Substract )
    __m128 vcmp = _mm_cmpgt_ps( Cb, Cs );
    __m128 diff = _mm_sub_ps( Cb, Cs );
    return  _mm_blendv_ps( _mm_setzero_ps(), diff, vcmp );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Divide
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_START( Divide )
    __m128 vcmp         = _mm_cmpeq_ps( Cs, _mm_setzero_ps() );
    __m128 max255f      = _mm_set_ps1( 255.f );
    __m128 computed     = _mm_min_ps( max255f, _mm_div_ps( _mm_mul_ps( max255f, Cb ), Cs ) );
    return  _mm_blendv_ps( computed, _mm_setzero_ps(), vcmp );
ULIS_SPEC_BLENDFUNC_SSE_COMPUTE_END

/////////////////////////////////////////////////////
// Undefines
#undef tSpec
#undef ttPixelType
#undef ttNextPixelType
#undef ttMax
#undef ttDownscale
#undef ttUpscale

} // namespace ULIS