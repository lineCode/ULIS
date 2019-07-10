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

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >


/////////////////////////////////////////////////////
// Basic Compositing
template< uint32 _SH >
static inline
typename TBlock< _SH >::tPixelType
Union( typename TBlock< _SH >::tPixelType b,
       typename TBlock< _SH >::tPixelType s )
{
    return  ( b + s ) - ConvType< typename TBlock< _SH >::tNextPixelType,
                          typename TBlock< _SH >::tPixelType >
                        ((typename TBlock< _SH >::tNextPixelType)( b * s ) );
}

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
        typename TBlock< _SH >::tPixelType  alphaBack = pixelBack.GetAlpha();
        typename TBlock< _SH >::tPixelType  alphaTop  = ConvType< typename TBlock< _SH >::tNextPixelType, typename TBlock< _SH >::tPixelType >( (typename TBlock< _SH >::tNextPixelType)( pixelTop.GetAlpha() * opacity ) );
        typename TBlock< _SH >::tPixelType  alphaResult = Union< _SH >( alphaBack, alphaTop );
        typename TBlock< _SH >::tPixelType  var = alphaResult == 0 ? 0 : ( alphaTop * TBlock< _SH >::StaticMax() ) / alphaResult;
        /*
        Cb.at< T >( 0, 0 ) = Composer< mode, T >::BasicCompositing( Cb.at< T >( 0, 0 ), Cs.at< T >( 0, 0 ), ab, var );
        Cb.at< T >( 0, 1 ) = Composer< mode, T >::BasicCompositing( Cb.at< T >( 0, 1 ), Cs.at< T >( 0, 1 ), ab, var );
        Cb.at< T >( 0, 2 ) = Composer< mode, T >::BasicCompositing( Cb.at< T >( 0, 2 ), Cs.at< T >( 0, 2 ), ab, var );
        Cb.at< T >( 0, 3 ) = ar;
        */
        auto dummy = 0;
    }

    TBlock< _SH >* top;
    TBlock< _SH >* back;
    typename TBlock< _SH >::tPixelType opacity;
    const FPoint& shift;
};

/////////////////////////////////////////////////////
// TBlockBlender_Imp
template< uint32 _SH, eBlendingMode _BM, e_tp _TP, e_cm _CM, e_ea _EA, uint32 _LH, e_nm _NM, bool _DM >
class TBlockBlenderImp
{
public:
    static void Run( TBlock< _SH >* iBlockTop, TBlock< _SH >* iBlockBack, typename TBlock< _SH >::tPixelType iOpacity, const FRect& iROI, const FPoint& iShift )
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
// TBlockBlender
template< uint32 _SH, eBlendingMode _BM >
class TBlockBlender
{
public:
    static void Run( TBlock< _SH >* iBlockTop, TBlock< _SH >* iBlockBack, typename TBlock< _SH >::tPixelType iOpacity, const FRect& iROI, const FPoint& iShift )
    {
        TBlockBlenderImp< _SH, _BM, tSpec::_nf._tp, tSpec::_nf._cm, tSpec::_nf._ea, tSpec::_nf._lh, tSpec::_nf._nm, tSpec::_nf._dm >::Run( iBlockTop, iBlockBack, iOpacity, iROI, iShift );
    }
};

/////////////////////////////////////////////////////
// TBlendingContext
template< uint32 _SH >
class TBlendingContext
{
public:
    static void Blend( TBlock< _SH >* iBlockTop, TBlock< _SH >* iBlockBack, eBlendingMode iMode, float iOpacity = 1.f, int ix = 0, int iy = 0, bool callInvalidCB = true )
    {
        if( iOpacity == 0.f )
            return;

        assert( iOpacity > 0.f && iOpacity <= 1.f );

        FRect back_bb = { 0, 0,     iBlockBack->Width(),    iBlockBack->Height()    };
        FRect top_bb =  { ix, iy,   iBlockTop->Width(),     iBlockTop->Height()     };
        FRect inter_bb = back_bb & top_bb;
        if( inter_bb.Area() <= 0 ) return;

        FPoint shift( -ix, -iy );

        #define ULIS_SWITCH_OP( iMode )  TBlockBlender< _SH, iMode >::Run( iBlockTop, iBlockBack, ConvType< float, typename TBlock< _SH >::tPixelType >( iOpacity ), inter_bb, shift )
        ULIS_FOR_ALL_BLENDING_MODES_DO( iMode, ULIS_SWITCH_OP )
        #undef ULIS_SWITCH_OP

        if( !callInvalidCB )
            return;

        iBlockBack->Invalidate( inter_bb );
    }

    static void Blend( TBlock< _SH >* iBlockTop, TBlock< _SH >* iBlockBack, eBlendingMode iMode, const FRect& iArea, float iOpacity = 1.f, bool callInvalidCB = true )
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

        #define ULIS_SWITCH_OP( iMode )  TBlockBlender< _SH, iMode >::Run( iBlockTop, iBlockBack, ConvType< float, typename TBlock< _SH >::tPixelType >( iOpacity ), inter_bb, shift )
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