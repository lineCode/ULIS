// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Conv.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Conv entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Conv/Conv.h"
#include "Conv/ConvBuffer.h"
#include "Copy/Copy.h"
#include "Data/Pixel.h"
#include "Data/Block.h"
#include "Maths/Maths.h"
#include "Color/Illuminants.h"
#include "Color/ModelCompat.h"
#include "Color/ModelStructs.h"
#include "Color/ColorProfile.h"
#include "Color/ProfileRegistry.h"
#include "Color/srgb2linear.h"
#include "Thread/ThreadPool.h"
#include "lcms2.h"

ULIS2_NAMESPACE_BEGIN
/*
void ProfileConv( const IPixel& iSrc, IPixel& iDst, const FProfileRegistry& iProfileRegistry, uint32 iIntent ) {
    tFormat src_ul2_format = iSrc.Format();
    tFormat dst_ul2_format = iDst.Format();
    tFormat src_lcms2_format = F42( src_ul2_format );
    tFormat dst_lcms2_format = F42( dst_ul2_format );
    FColorProfile* src_profile = iSrc.Profile();
    FColorProfile* dst_profile = iDst.Profile();
    if( src_profile == nullptr ) src_profile = iProfileRegistry.GetDefaultProfileForModel( iSrc.Model() );
    if( dst_profile == nullptr ) dst_profile = iProfileRegistry.GetDefaultProfileForModel( iDst.Model() );

    cmsHPROFILE hInProfile  = src_profile->ProfileHandle();
    cmsHPROFILE hOutProfile = dst_profile->ProfileHandle();
    cmsHTRANSFORM hTransform;
    hTransform = cmsCreateTransform( hInProfile
                                   , src_lcms2_format
                                   , hOutProfile
                                   , dst_lcms2_format
                                   , INTENT_PERCEPTUAL, 0 );
    cmsDoTransform( hTransform, iSrc.Ptr(), iDst.Ptr(), 1 );
    cmsDeleteTransform( hTransform );
}
*/

void Conv( const IPixel& iSrc, IPixel& iDst ) {
    fpDispatchedConvInvoke fptr = QueryDispatchedConvInvokeForParameters( iSrc.Format(), iDst.Format() );
    if( fptr ) fptr( iSrc.FormatInfo(), iSrc.Ptr(), iDst.FormatInfo(), iDst.Ptr(), 1 );
}

FPixelValue Conv( const IPixel& iSrc, tFormat iDst ) {
    FPixelValue dst( iDst );
    fpDispatchedConvInvoke fptr = QueryDispatchedConvInvokeForParameters( iSrc.Format(), iDst );
    if( fptr ) fptr( iSrc.FormatInfo(), iSrc.Ptr(), dst.FormatInfo(), dst.Ptr(), 1 );
    return  dst;
}

void Conv( const FConvInfo& iConvParams ) {
    // Assertions
    ULIS2_ASSERT( iConvParams.source,                                                   "Bad source."                                                       );
    ULIS2_ASSERT( iConvParams.destination,                                              "Bad destination."                                                  );
    ULIS2_ASSERT( !iConvParams.perfInfo.intent.UseMT() || iConvParams.perfInfo.pool,    "Multithreading flag is specified but no thread pool is provided."  );
    ULIS2_ASSERT( !iConvParams.perfInfo.callCB || iConvParams.perfInfo.blocking,        "Callback flag is specified on non-blocking operation."             );
    ULIS2_ASSERT( iConvParams.source->Width() == iConvParams.destination->Width(),      "Blocks sizes don't match"                                          );
    ULIS2_ASSERT( iConvParams.source->Height() == iConvParams.destination->Height(),    "Blocks sizes don't match"                                          );

    // Check no-op
    if( iConvParams.source == iConvParams.destination )
        return;

    // Query dispatched method
    fpDispatchedConvInvoke fptr = QueryDispatchedConvInvokeForParameters( iConvParams.source->Format(), iConvParams.destination->Format() );

    // Check dispatched method
    ULIS2_ASSERT( fptr, "No Conversion invocation found" );
    if( !fptr )
        return;

    // Bake Params
    const tByte*    srb = iConvParams.source->DataPtr();
    tByte*          dsb = iConvParams.destination->DataPtr();
    tSize           src_bps = iConvParams.source->BytesPerScanLine();
    tSize           dst_bps = iConvParams.destination->BytesPerScanLine();
    #define SRC srb + ( pLINE * src_bps )
    #define DST dsb + ( pLINE * dst_bps )
    const int   max = iConvParams.source->Height();
    const tSize len = iConvParams.source->Width();
    const FFormatInfo& srcnfo = iConvParams.source->FormatInfo();
    const FFormatInfo& dstnfo = iConvParams.destination->FormatInfo();

    // Call
    ULIS2_MACRO_INLINE_PARALLEL_FOR( iConvParams.perfInfo.intent, iConvParams.perfInfo.pool, iConvParams.perfInfo.blocking
                                   , max
                                   , fptr, srcnfo, SRC, dstnfo, DST, len );

    // Invalid
    iConvParams.destination->Invalidate( iConvParams.destination->Rect(), iConvParams.perfInfo.callCB );
}

FBlock* XConv( const FXConvInfo& iConvParams ) {
    // Assertions
    ULIS2_ASSERT( iConvParams.source, "Bad source." );

    // Alloc return buffer in desired format, same size
    FBlock* ret = new FBlock( iConvParams.source->Width(), iConvParams.source->Height(), iConvParams.destinationFormat );

    if( iConvParams.source->Format() == iConvParams.destinationFormat ) {
        // If same formats, just perform a copy
        //Copy( iPool, iBlocking, iPerf, iCPU, iSrc, ret, 0, 0, ULIS2_NOCB );
    } else {
        // Else delegate call to regular Conv into ret buffer
        FConvInfo convInfo = {};
        convInfo.source         = iConvParams.source;
        convInfo.destination    = ret;
        convInfo.perfInfo       = iConvParams.perfInfo;
        convInfo.perfInfo       = iConvParams.perfInfo;
        Conv( convInfo );
    }

    return  ret;
}

ULIS2_NAMESPACE_END

