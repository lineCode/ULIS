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
void
BlendMono( const FBlock*    iSource
         , FBlock*          iBackdrop
         , const FRect&     iSrcRoi
         , const FRect&     iDstRoi
         , float            iOpacity )
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
    uint8* index_table = new uint8[ ncc ];                                                  // Table of redirected index
    uint8  alpha_index;                                                                     // Alpha Index
    switch( cod )
    {
        case 1:
            for( tSize i = 0; i < ncc; ++i )
                index_table[i] = ( msp - i );
            alpha_index = 0;
            break;

        case 2:
            for( tSize i = 0; i < ncc; ++i )
                index_table[i] = ( i + 1 ) > msp ? 0 : i + 1;
            alpha_index = 0;
            break;

        case 3:
            for( tSize i = 0; i < ncc; ++i )
                index_table[i] = ( msp - i ) - 1 < 0 ? msp : ( msp - i ) - 1;
            alpha_index = msp;
            break;

        default:
            for( tSize i = 0; i < ncc; ++i )
                index_table[i] = i;
            alpha_index = msp;
    }

    // Process
    for( uint32 y = 0; y < (uint32)iSrcRoi.h; ++y )
    {
        for( uint32 x = 0; x < (uint32)iSrcRoi.w; ++x )
        {
            // Precomp
            const float alpha_bdp       = hea ? ConvType< T, float >( *( (T*)( bdp + alpha_index ) ) )              : 1.0f;
            const float alpha_src       = hea ? ConvType< T, float >( *( (T*)( bdp + alpha_index ) ) ) * iOpacity   : iOpacity;
            const float alpha_comp      = ( alpha_bdp + alpha_src ) - ( alpha_bdp * alpha_src );
            const float alpha_result    = 1.0f;
            const float var             = alpha_comp == 0 ? 0 : alpha_src / alpha_comp;
            // Compute Separable Channels
            for( tSize i = 0; i < ncc; ++i )
                *( (T*)( bdp + index_table[i] ) ) = ConvType< float, T >( 1.0f );
            // Emplace alpha result
            if( hea ) *( (T*)( bdp + alpha_index ) ) = ConvType< float, T >( alpha_result );
            src += bpp;
            bdp += bpp;
        }
        src += bps;
        bdp += bps;
    }
}


template< typename T, eBlendingMode _BM, eAlphaMode _AM >
void
Blend_imp( FThreadPool&     iPool
         , const FBlock*    iSource
         , FBlock*          iBackdrop
         , const FRect&     iSrcRoi
         , const FRect&     iDstRoi
         , float            iOpacity
         , const FPerf&     iPerf )
{
    if( iPerf.useMT )
        return;
    else
        BlendMono< T, _BM, _AM >( iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity );
}


template< typename T, eBlendingMode _BM >
void
Blend_select_AM( FThreadPool&    iPool
               , const FBlock*   iSource
               , FBlock*         iBackdrop
               , const FRect&    iSrcRoi
               , const FRect&    iDstRoi
               , eAlphaMode      iAlphaMode
               , float           iOpacity
               , const FPerf&    iPerf )
{
    switch( iAlphaMode ) {
        case eAlphaMode::kNormal:   Blend_imp< T, _BM, eAlphaMode::kNormal  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kErase:    Blend_imp< T, _BM, eAlphaMode::kErase   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kTop:      Blend_imp< T, _BM, eAlphaMode::kTop     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kBack:     Blend_imp< T, _BM, eAlphaMode::kBack    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kSub:      Blend_imp< T, _BM, eAlphaMode::kSub     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kAdd:      Blend_imp< T, _BM, eAlphaMode::kAdd     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kMul:      Blend_imp< T, _BM, eAlphaMode::kMul     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kMin:      Blend_imp< T, _BM, eAlphaMode::kMin     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kMax:      Blend_imp< T, _BM, eAlphaMode::kMax     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
        case eAlphaMode::kInvMax:   Blend_imp< T, _BM, eAlphaMode::kInvMax  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iOpacity, iPerf ); break;
    }
}


template< typename T >
void
Blend_select_BM( FThreadPool&   iPool
               , const FBlock*  iSource
               , FBlock*        iBackdrop
               , const FRect&   iSrcRoi
               , const FRect&   iDstRoi
               , eBlendingMode  iBlendingMode
               , eAlphaMode     iAlphaMode
               , float          iOpacity
               , const FPerf&   iPerf )
{
    switch( iBlendingMode )
    {
        case eBlendingMode::kNormal:        Blend_select_AM< T, eBlendingMode::kNormal       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kErase:         Blend_select_AM< T, eBlendingMode::kErase        >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kBehind:        Blend_select_AM< T, eBlendingMode::kBehind       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kDissolve:      Blend_select_AM< T, eBlendingMode::kDissolve     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kDarken:        Blend_select_AM< T, eBlendingMode::kDarken       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kMultiply:      Blend_select_AM< T, eBlendingMode::kMultiply     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kColorBurn:     Blend_select_AM< T, eBlendingMode::kColorBurn    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kLinearBurn:    Blend_select_AM< T, eBlendingMode::kLinearBurn   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kDarkerColor:   Blend_select_AM< T, eBlendingMode::kDarkerColor  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kLighten:       Blend_select_AM< T, eBlendingMode::kLighten      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kScreen:        Blend_select_AM< T, eBlendingMode::kScreen       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kColorDodge:    Blend_select_AM< T, eBlendingMode::kColorDodge   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kLinearDodge:   Blend_select_AM< T, eBlendingMode::kLinearDodge  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kLighterColor:  Blend_select_AM< T, eBlendingMode::kLighterColor >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kOverlay:       Blend_select_AM< T, eBlendingMode::kOverlay      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kSoftLight:     Blend_select_AM< T, eBlendingMode::kSoftLight    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kHardLight:     Blend_select_AM< T, eBlendingMode::kHardLight    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kVividLight:    Blend_select_AM< T, eBlendingMode::kVividLight   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kLinearLight:   Blend_select_AM< T, eBlendingMode::kLinearLight  >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kPinLight:      Blend_select_AM< T, eBlendingMode::kPinLight     >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kHardMix:       Blend_select_AM< T, eBlendingMode::kHardMix      >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kDifference:    Blend_select_AM< T, eBlendingMode::kDifference   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kExclusion:     Blend_select_AM< T, eBlendingMode::kExclusion    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kSubstract:     Blend_select_AM< T, eBlendingMode::kSubstract    >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kDivide:        Blend_select_AM< T, eBlendingMode::kDivide       >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kHue:           Blend_select_AM< T, eBlendingMode::kHue          >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kSaturation:    Blend_select_AM< T, eBlendingMode::kSaturation   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kColor:         Blend_select_AM< T, eBlendingMode::kColor        >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
        case eBlendingMode::kLuminosity:    Blend_select_AM< T, eBlendingMode::kLuminosity   >( iPool, iSource, iBackdrop, iSrcRoi, iDstRoi, iAlphaMode, iOpacity, iPerf ); break;
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
        case eType::kUint8:     Blend_select_BM< uint8  >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case eType::kUint16:    Blend_select_BM< uint16 >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case eType::kUint32:    Blend_select_BM< uint32 >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case eType::kFloat:     Blend_select_BM< float  >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
        case eType::kDouble:    Blend_select_BM< double >( iPool, iSource, iBackdrop, src_roi, dst_roi, iBlendingMode, iAlphaMode, opacity, iPerf ); break;
    }

    iBackdrop->Invalidate( dst_roi, iCallInvalidCB );
}

ULIS2_NAMESPACE_END

