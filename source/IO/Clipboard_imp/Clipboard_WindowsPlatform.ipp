// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Clipboard_Windows.ipp
* @author       Clement Berthaud
* @brief        This file provides the definition for the clipboard IO entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "IO/Clipboard.h"
#include "Data/Block.h"
#include "Base/CPU.h"
#include "Conv/Conv.h"
#include "Conv/ConvBuffer.h"
#include "Thread/ParallelFor.h"

#include <array>
#include <algorithm>

#include <Windows.h>


#include <clip.h>

ULIS2_NAMESPACE_BEGIN
FBlock* XLoadFromClipboard( const FXLoadFromClipboardInfo& iLoadParams ) {
    if( !ClipboardHasImageData() )
        return  nullptr;

    clip::image_spec spec;
    clip::get_image_spec( spec );

    bool locked = OpenClipboard( nullptr );
    if( !locked ) return  nullptr;
    BITMAPINFO* bi = (BITMAPINFO*)GetClipboardData( CF_DIB );
    if(!bi) return  nullptr;

    int w = bi->bmiHeader.biWidth;
    int h = bi->bmiHeader.biHeight;
    int bits_per_pixel = bi->bmiHeader.biBitCount;
    if( w <= 0 || h <= 0 )                              return  nullptr;
    if( bits_per_pixel != 24 && bits_per_pixel != 32 )  return  nullptr;
    if( bi->bmiHeader.biCompression != BI_RGB && bi->bmiHeader.biCompression != BI_BITFIELDS )  return  nullptr;

    tFormat srcFormat = 0;
    if( bits_per_pixel == 24 ) srcFormat = ULIS2_FORMAT_BGR8;
    if( bits_per_pixel == 32 ) srcFormat = ULIS2_FORMAT_BGRA8;

    tByte* src = ( ((tByte*)bi) + bi->bmiHeader.biSize );
    tFormat dstFormat = iLoadParams.desiredFormat;
    if( dstFormat <= 0 ) dstFormat = srcFormat;

    FBlock tmp( src, w, h, srcFormat, nullptr, FOnInvalid( nullptr, nullptr ), OnCleanup_DoNothing );
    FBlock* ret = new FBlock( w, h, dstFormat );

    // Assertions
    ULIS2_ASSERT( !iLoadParams.perfInfo.intent.UseMT() || iLoadParams.perfInfo.pool,    "Multithreading flag is specified but no thread pool is provided."  );
    ULIS2_ASSERT( !iLoadParams.perfInfo.callCB || iLoadParams.perfInfo.blocking,        "Callback flag is specified on non-blocking operation."             );

    fpDispatchedConvInvoke fptr = QueryDispatchedConvInvokeForParameters( srcFormat, dstFormat );

    // Check dispatched method
    ULIS2_ASSERT( fptr, "No Conversion invocation found" );
    if( !fptr )
        return  nullptr;

    // Bake Params
    int dc = bits_per_pixel == 24 ? 3 & w : 0;
    tSize   src_bps = ( bits_per_pixel / 8 ) * tmp.Width() + dc;
    tSize   dst_bps = ret->BytesPerScanLine();
    const int   numLines = h;
    const tSize len = w;
    const tByte*    srb = tmp.DataPtr() + src_bps * ( numLines - 1 );
    tByte*          dsb = ret->DataPtr();
    #define SRC srb - ( pLINE * src_bps )
    #define DST dsb + ( pLINE * dst_bps )
    const FFormatInfo& srcnfo = tmp.FormatInfo();
    const FFormatInfo& dstnfo = ret->FormatInfo();

    // Call
    ULIS2_MACRO_INLINE_PARALLEL_FOR( iLoadParams.perfInfo.intent, iLoadParams.perfInfo.pool, iLoadParams.perfInfo.blocking
                                   , numLines
                                   , fptr, srcnfo, SRC, dstnfo, DST, len );

    CloseClipboard();
    return  ret;
}


void SaveToClipboard( const FSaveToClipboardInfo& iSaveParams ) {
    // Assertions
    ULIS2_ASSERT( iSaveParams.source,                                                   "Bad source."                                                       );
    ULIS2_ASSERT( !iSaveParams.perfInfo.intent.UseMT() || iSaveParams.perfInfo.pool,    "Multithreading flag is specified but no thread pool is provided."  );
    ULIS2_ASSERT( !iSaveParams.perfInfo.callCB || iSaveParams.perfInfo.blocking,        "Callback flag is specified on non-blocking operation."             );

    FXConvInfo convInfo = {};
    convInfo.source             = iSaveParams.source;
    convInfo.destinationFormat  = ULIS2_FORMAT_ABGR8;
    convInfo.perfInfo           = iSaveParams.perfInfo;
    FBlock* tmpConv = XConv( convInfo );

    clip::image_spec spec;
      spec.width = tmpConv->Width();
      spec.height = tmpConv->Height();
      spec.bits_per_pixel = tmpConv->BytesPerPixel() * 8;
      spec.bytes_per_row = tmpConv->BytesPerScanLine();
      spec.red_mask = 0xff;
      spec.green_mask = 0xff00;
      spec.blue_mask = 0xff0000;
      spec.alpha_mask = 0xff000000;
      spec.red_shift = 0;
      spec.green_shift = 8;
      spec.blue_shift = 16;
      spec.alpha_shift = 24;
      
  clip::image img( tmpConv->DataPtr(), spec );
  clip::set_image(img);

}

bool ClipboardHasImageData() {
    bool locked = OpenClipboard( nullptr );
    bool hasImageData = locked && IsClipboardFormatAvailable(CF_DIB);
    CloseClipboard();
    return  hasImageData;
}

ULIS2_NAMESPACE_END

