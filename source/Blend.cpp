// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Blend.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Blend entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Blend.h"
#include "Block.h"
#include "Geometry.h"

ULIS2_NAMESPACE_BEGIN
template< typename T, eBlendingMode _BM, eAlphaMode _AM >
void BlendMono_MEM_Separable( const FBlock* iSource
                            , FBlock*       iBackdrop
                            , const FRect&  iSrcRoi
                            , const FRect&  iDstRoi
                            , float         iOpacity )
{

    // Gather Data
    const tFormat   fmt = iSource->Format();                                                // Format
    const tSize     bpc = iSource->BytesPerSample();                                        // Bytes Per Channel
    const tSize     ncc = iSource->NumColorChannels();                                      // Num Color Channel
    const bool      hea = iSource->HasAlpha();                                              // Has Extra Alpha
    const tSize     spp = ncc + hea;                                                        // Samples Per Pixel
    const tSize     bpp = bpc * spp;                                                        // Bytes Per Pixel
    const tSize     w   = iSource->Width();                                                 // Width
    const tSize     bps = bpp * w;                                                          // Bytes Per Scanline
    uint8           msp = spp - 1;                                                          // Max Sample
    uint8           cod = ULIS2_R_RS( fmt );                                                // Reverse-Swap code
    const tByte*    src = iSource->DataPtr()   + ( iSrcRoi.y * bps ) + ( iSrcRoi.x * bpp ); // Source Pointer in src ROI
    tByte*          bdp = iBackdrop->DataPtr() + ( iDstRoi.y * bps ) + ( iDstRoi.x * bpp ); // Backdrop Pointer in dst ROI

    // Build Redirection Tables
    uint8* index_table  = new uint8[ spp ];
    uint8 alpha_index   = 0;
    switch( cod ) {
        case 1:  for( tSize i = 0; i < spp; ++i ) index_table[i] = ( msp - i );                                     alpha_index = 0;    break;
        case 2:  for( tSize i = 0; i < spp; ++i ) index_table[i] = ( i + 1 ) > msp ? 0 : i + 1;                     alpha_index = 0;    break;
        case 3:  for( tSize i = 0; i < spp; ++i ) index_table[i] = ( msp - i ) - 1 < 0 ? msp : ( msp - i ) - 1;     alpha_index = msp;  break;
        default: for( tSize i = 0; i < spp; ++i ) index_table[i] = i;                                               alpha_index = msp;  break;
    }

    // Data Holders to abstract away the Alpha.
    float*  srcd = new  float[ ncc + 1 ];
    float*  bdpd = new  float[ ncc + 1 ];
    for( tSize i = 0; i < ncc + 1; ++i )
    { srcd[i] = 1.f;    bdpd[i] = 1.f; }

    // Process
    const tSize count = iSrcRoi.w * iSrcRoi.h;
    for( tSize i = 0; i < count; ++i )
    {
        for( tSize j = 0; j < ( spp ); ++j )
        {
            uint8 r = index_table[j];
            srcd[ r ] = ConvType< T, float >( *( (T*)( src + r ) ) );
            bdpd[ r ] = ConvType< T, float >( *( (T*)( bdp + r ) ) );
        }

        // Precomp
        const float alpha_bdp       = bdpd[ alpha_index ];
        const float alpha_src       = srcd[ alpha_index ] * iOpacity;
        const float alpha_comp      = ( alpha_bdp + alpha_src ) - ( alpha_bdp * alpha_src );
        const float alpha_result    = 1.0f;
        const float var             = alpha_comp == 0 ? 0 : alpha_src / alpha_comp;
        // Compute Separable Channels in float
        for( tSize j = 0; j < ncc; ++j )
            bdpd[ index_table[ j ] ] = 1.f;
        bdpd[ alpha_index ] = alpha_result;

        // Emplace result
        for( tSize j = 0; j < spp; ++j )
            *( (T*)( bdp + index_table[ j ] ) ) = ConvType< float, T >( bdpd[ index_table[ j ] ] );

        // Increment ptrs by one pixel
        src += bpp;
        bdp += bpp;
    }

    // Delete temporary data
    delete [] index_table;
    delete [] srcd;
    delete [] bdpd;
}

template< typename T, eBlendingMode _BM, eAlphaMode _AM >
void BlendMono_MEM_NonSeparable( const FBlock*  iSource
                               , FBlock*        iBackdrop
                               , const FRect&   iSrcRoi
                               , const FRect&   iDstRoi
                               , float          iOpacity )
{
}

template< typename T, eBlendingMode _BM, eAlphaMode _AM >
void BlendMono_MEM_Unusual( const FBlock*   iSource
                          , FBlock*         iBackdrop
                          , const FRect&    iSrcRoi
                          , const FRect&    iDstRoi
                          , float           iOpacity )
{
}

template< typename T, eBlendingMode _BM, eAlphaMode _AM >
void ULIS2_FORCEINLINE BlendMono_MEM( const FBlock* iSource
                                    , FBlock*       iBackdrop
                                    , const FRect&  iSrcRoi
                                    , const FRect&  iDstRoi
                                    , float         iOpacity )
{
    switch( BlendingModeQualifier( _BM ) )
    {
        case BMQ_SEPARABLE      : BlendMono_MEM_Separable<      T, _BM, _AM >( iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity );
        case BMQ_NONSEPARABLE   : BlendMono_MEM_NonSeparable<   T, _BM, _AM >( iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity );
        case BMQ_UNUSUAL        : BlendMono_MEM_Unusual<        T, _BM, _AM >( iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity );
    }
}

// BlendMono Generic
template< typename T, eBlendingMode _BM, eAlphaMode _AM >
void ULIS2_FORCEINLINE BlendMono( const FBlock* iSource
                                , FBlock*       iBackdrop
                                , const FRect&  iSrcRoi
                                , const FRect&  iDstRoi
                                , float         iOpacity
                                , const FPerf&  iPerf )
{
    if( iPerf.UseAVX2() )
    {
        BlendMono_MEM< T, _BM, _AM >( iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity );
    }
    else if( iPerf.UseSSE4_2() )
    {
        BlendMono_MEM< T, _BM, _AM >( iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity );
    }
    else
    {
        BlendMono_MEM< T, _BM, _AM >( iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity );
    }
}


template< typename T, eBlendingMode _BM, eAlphaMode _AM >
void ULIS2_FORCEINLINE Blend_imp( FThreadPool&  iPool
                                , const FBlock* iSource
                                , FBlock*       iBackdrop
                                , const FRect&  iSrcRoi
                                , const FRect&  iDstRoi
                                , float         iOpacity
                                , const FPerf&  iPerf )
{
    if( iPerf.UseMT() )
        BlendMono< T, _BM, _AM >( iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf );
    else
        BlendMono< T, _BM, _AM >( iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf );
}


template< typename T, eBlendingMode _BM >
void ULIS2_FORCEINLINE Blend_select_AM( FThreadPool&    iPool
                                      , const FBlock*   iSource
                                      , FBlock*         iBackdrop
                                      , const FRect&    iSrcRoi
                                      , const FRect&    iDstRoi
                                      , eAlphaMode      iAlphaMode
                                      , float           iOpacity
                                      , const FPerf&    iPerf )
{
    switch( iAlphaMode ) {
        case AM_NORMAL  :   Blend_imp< T, _BM, AM_NORMAL    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_ERASE   :   Blend_imp< T, _BM, AM_ERASE     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_TOP     :   Blend_imp< T, _BM, AM_TOP       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_BACK    :   Blend_imp< T, _BM, AM_BACK      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_SUB     :   Blend_imp< T, _BM, AM_SUB       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_ADD     :   Blend_imp< T, _BM, AM_ADD       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_MUL     :   Blend_imp< T, _BM, AM_MUL       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_MIN     :   Blend_imp< T, _BM, AM_MIN       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_MAX     :   Blend_imp< T, _BM, AM_MAX       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case AM_INVMAX  :   Blend_imp< T, _BM, AM_INVMAX    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
    }
}


template< typename T >
void ULIS2_FORCEINLINE Blend_select_BM( FThreadPool&    iPool
                                      , const FBlock*   iSource
                                      , FBlock*         iBackdrop
                                      , const FRect&    iSrcRoi
                                      , const FRect&    iDstRoi
                                      , eBlendingMode   iBlendingMode
                                      , eAlphaMode      iAlphaMode
                                      , float           iOpacity
                                      , const FPerf&    iPerf )
{
    switch( iBlendingMode ) {
        case BM_NORMAL          :   Blend_select_AM< T, BM_NORMAL       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_TOP             :   Blend_select_AM< T, BM_TOP          >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_BACK            :   Blend_select_AM< T, BM_BACK         >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_BEHIND          :   Blend_select_AM< T, BM_BEHIND       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_DISSOLVE        :   Blend_select_AM< T, BM_DISSOLVE     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_DARKEN          :   Blend_select_AM< T, BM_DARKEN       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_MULTIPY         :   Blend_select_AM< T, BM_MULTIPY      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_COLORBURN       :   Blend_select_AM< T, BM_COLORBURN    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_LINEARBURN      :   Blend_select_AM< T, BM_LINEARBURN   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_DARKERCOLOR     :   Blend_select_AM< T, BM_DARKERCOLOR  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_LIGHTEN         :   Blend_select_AM< T, BM_LIGHTEN      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_SCREEN          :   Blend_select_AM< T, BM_SCREEN       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_COLORDODGE      :   Blend_select_AM< T, BM_COLORDODGE   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_LINEARDODGE     :   Blend_select_AM< T, BM_LINEARDODGE  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_LIGHTERCOLOR    :   Blend_select_AM< T, BM_LIGHTERCOLOR >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_OVERLAY         :   Blend_select_AM< T, BM_OVERLAY      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_SOFTLIGHT       :   Blend_select_AM< T, BM_SOFTLIGHT    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_HARDLIGHT       :   Blend_select_AM< T, BM_HARDLIGHT    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_VIVIDLIGHT      :   Blend_select_AM< T, BM_VIVIDLIGHT   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_LINEARLIGHT     :   Blend_select_AM< T, BM_LINEARLIGHT  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_PINLIGHT        :   Blend_select_AM< T, BM_PINLIGHT     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_HARDMIX         :   Blend_select_AM< T, BM_HARDMIX      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_DIFFERENCE      :   Blend_select_AM< T, BM_DIFFERENCE   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_EXCLUSION       :   Blend_select_AM< T, BM_EXCLUSION    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_SUBSTRACT       :   Blend_select_AM< T, BM_SUBSTRACT    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_DIVIDE          :   Blend_select_AM< T, BM_DIVIDE       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_HUE             :   Blend_select_AM< T, BM_HUE          >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_SATURATION      :   Blend_select_AM< T, BM_SATURATION   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_COLOR           :   Blend_select_AM< T, BM_COLOR        >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case BM_LUMINOSITY      :   Blend_select_AM< T, BM_LUMINOSITY   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
    }
}


void
Blend( FThreadPool&     iPool
     , const FBlock*    iSource
     , FBlock*          iBackdrop
     , const FPoint&    iDstPos
     , eBlendingMode    iBlendingMode
     , eAlphaMode       iAlphaMode
     , float            iOpacity
     , const FPerf&     iPerf
     , bool             iCallInvalidCB )
{
    BlendRect( iPool
         , iSource
         , iBackdrop
         , iSource->Rect()
         , iDstPos
         , iBlendingMode
         , iAlphaMode
         , iOpacity
         , iPerf
         , iCallInvalidCB );
}


void
BlendRect( FThreadPool&     iPool
         , const FBlock*    iSource
         , FBlock*          iBackdrop
         , const FRect&     iSrcRect
         , const FPoint&    iDstPos
         , eBlendingMode    iBlendingMode
         , eAlphaMode       iAlphaMode
         , float            iOpacity
         , const FPerf&     iPerf
         , bool             iCallInvalidCB )
{
    ULIS2_ASSERT( iSource->Model() == iBackdrop->Model(),                       "Models do not match" );
    ULIS2_ASSERT( iSource->Type() == iBackdrop->Type(),                         "Types do not match" );
    ULIS2_ASSERT( iSource->SamplesPerPixel() == iBackdrop->SamplesPerPixel(),   "Samples do not match" );
    ULIS2_ASSERT( iSource,                                                      "Bad source" );
    ULIS2_ASSERT( iBackdrop,                                                    "Bad destination" );
    ULIS2_ASSERT( iSource != iBackdrop,                                         "Destination and source cannot be the same" );

    // Gather src rect and shift to destination
    FRect target_rect = iSrcRect & iSource->Rect();
    target_rect.x = iDstPos.x;
    target_rect.y = iDstPos.y;
    // Gather dst rect
    // Interset target with dst, target may be out of range
    FRect dst_roi = target_rect & iBackdrop->Rect();
    // Gather src rect and fit size to fix overflow
    FRect src_roi = dst_roi;
    src_roi.x = iSrcRect.x;
    src_roi.y = iSrcRect.y;

    // Check if this is a no-op
    if( src_roi.Area() <= 0 )
        return;

    float opacity = FMaths::Clamp( iOpacity, 0.f, 1.f );
    switch( iSource->Type() ) {
        case TYPE_UINT8:    Blend_select_BM< uint8   >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case TYPE_UINT16:   Blend_select_BM< uint16  >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case TYPE_UINT32:   Blend_select_BM< uint32  >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case TYPE_UFLOAT:   Blend_select_BM< ufloat  >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case TYPE_UDOUBLE:  Blend_select_BM< udouble >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
    }

    iBackdrop->Invalidate( dst_roi, iCallInvalidCB );
}

ULIS2_NAMESPACE_END
