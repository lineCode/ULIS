// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         TraceTextMono_Generic.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic trace text entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Maths/Geometry.h"
#include "Base/Helpers.ipp"
#include "Thread/ParallelFor.h"

ULIS2_NAMESPACE_BEGIN
float AlphaBlendAlpha( float iAs, float iAb ) {
    return  iAs + iAb * ( 1.f - iAs );
}

float AlphaBlendChannel( float iCs, float iCb, float iAs, float iAb, float iAr ) {
    return  iAr == 0.f ? 0.f : ( iCs * iAs + iCb * iAb * ( 1.f - iAs ) ) / iAr;
}

template< typename T >
void
RasterBitmap( FBlock* iDst, FT_Bitmap* iBitmap, int iW, int iH, FT_Int iX, FT_Int iY, const tByte* iColor, uint8 iBPC, uint8 iNCC, uint8 iHEA, uint8 iSPP, uint8 iBPP, uint8 iAID, tSize iBPS, uint8* iXIDT )
{
    int xmax = iX + iBitmap->width;
    int ymax = iY + iBitmap->rows;

    tByte* dst = iDst->DataPtr() + ( iY * (int64)iBPS ) + ( iX * (int64)iBPP );
    tSize jmp = ( iW - iBitmap->width ) * iBPP; 

    int x, y, p, q;
    for( y = iY, q = 0; y < ymax; ++y, ++q ) {
        for( x = iX, p = 0; x < xmax; ++x, ++p ) {
            if( x < 0 || y < 0 || x >= iW || y >= iH ) {
                dst += iBPP;
                continue;
            }

            float srcAlpha = ConvType< uint8, float >( iBitmap->buffer[ q * iBitmap->width + p ] );
            float dstAlpha = TYPE2FLOAT( dst, iAID );
            float resAlpha = AlphaBlendAlpha( srcAlpha, dstAlpha );
            for( uint8 j = 0; j < iNCC; ++j )
            {
                uint8 r = iXIDT[j];
                float srcvf = TYPE2FLOAT( iColor, r );
                float dstvf = TYPE2FLOAT( dst, r );
                FLOAT2TYPE( dst, r, AlphaBlendChannel( srcvf, dstvf, srcAlpha, dstAlpha, resAlpha ) );
            }
            if( iHEA ) FLOAT2TYPE( dst, iAID, resAlpha );
            dst += iBPP;
        }

        dst += jmp;
    }
}

template< typename T >
void
TraceTextMono_Generic( FThreadPool* iPool, bool iBlocking, const FPerf& iPerf, FBlock* iDst, const std::string& iText, const FFont& iFont, int iSize, const tByte* iColor, int iX, int iY, FT_Matrix& iTransform )
{
    uint8* xidt;
    uint8 bpc, ncc, hea, spp, bpp, aid;
    tSize bps;
    BuildTraceTextParams( iDst, &bpc, &ncc, &hea, &spp, &bpp, &aid, &xidt, &bps );
    tSize width = iDst->Width();
    tSize height = iDst->Height();

    const char* str = iText.c_str();
    int len = (int)iText.size();

    FT_GlyphSlot  slot;
    FT_Vector     pen;

    FT_Error error = 0;
    FT_Face face = iFont.Handle();
    error = FT_Set_Pixel_Sizes( face, 0, iSize );
    ULIS2_ERROR( !error, "Error setting face size" );

    slot = face->glyph;
    pen.x = 0;
    pen.y = 0;
    int autobaseline = (int)( iSize / 1 );

    for( int n = 0; n < len; ++n ) {
        FT_Set_Transform( face, &iTransform, &pen );
        FT_UInt glyph_index = FT_Get_Char_Index( face, str[n] );
        error = FT_Load_Glyph( face, glyph_index, FT_LOAD_DEFAULT );
        ULIS2_ERROR( !error, "Error loading glyph" );
        error = FT_Render_Glyph( face->glyph, FT_RENDER_MODE_NORMAL );
        ULIS2_ERROR( !error, "Error rendering glyph" );

        RasterBitmap< T >( iDst, &slot->bitmap, width, height, iX + slot->bitmap_left, iY + ( autobaseline - slot->bitmap_top ), iColor, bpc, ncc, hea, spp, bpp, aid, bps, xidt );

        pen.x += slot->advance.x;
        pen.y += slot->advance.y;
    }
}
ULIS2_NAMESPACE_END

