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
#include "Thread/ParallelFor.h"
#include "Thread/ThreadPool.h"
#include "Base/Perf.h"
#include "lcms2.h"

ULIS2_NAMESPACE_BEGIN
void
ProfileConv( const IPixel& iSrc, IPixel& iDst, const FProfileRegistry& iProfileRegistry, uint32 iIntent )
{
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


void
Conv( FThreadPool*   iPool
    , bool           iBlocking
    , const FPerf&   iPerf
    , const FCPU&    iCPU
    , const FBlock*  iSrc
    , FBlock*        iDst
    , bool           iCallInvalidCB )
{
    ULIS2_ASSERT( iPool,                                    "Bad pool" );
    ULIS2_ASSERT( iSrc,                                     "Bad source" );
    ULIS2_ASSERT( iDst,                                     "Bad destination" );
    ULIS2_ASSERT( !( (!iBlocking) && (iCallInvalidCB ) ),   "Calling invalid CB on non-blocking operation may induce race condition and undefined behaviours." );
    ULIS2_ASSERT( iSrc != iDst,                             "Converting a block on itself may trigger data race, use at your own risk or ensure written areas do not overlap." );
    ULIS2_ASSERT( iSrc->Width() == iDst->Width() && iSrc->Height() == iDst->Height(), "Blocks sizes don't match" );

    fpDispatchedConvInvoke fptr = QueryDispatchedConvInvokeForParameters( iSrc->Format(), iDst->Format() );
    ULIS2_ASSERT( fptr, "No Conversion invocation found" );
    if( !fptr ) return;

    const tByte*    srb = iSrc->DataPtr();
    tByte*          dsb = iDst->DataPtr();
    tSize           src_bps = iSrc->BytesPerScanLine();
    tSize           dst_bps = iDst->BytesPerScanLine();
    #define SRC srb + ( pLINE * src_bps )
    #define DST dsb + ( pLINE * dst_bps )

    const int max = iSrc->Height();
    const FFormatInfo srcnfo = iSrc->FormatInfo();
    const FFormatInfo dstnfo = iDst->FormatInfo();
    const tSize len = iSrc->Width();
    ULIS2_MACRO_INLINE_PARALLEL_FOR( iPerf, iPool, iBlocking, max, fptr, srcnfo, SRC, dstnfo, DST, len );
    //ParallelFor( *iPool, iBlocking, iPerf, iSrc->Height(), ULIS2_PF_CALL { fptr( iSrc->FormatInfo(), SRC, iDst->FormatInfo(), DST, iSrc->Width() ); } );

    iDst->Invalidate( iCallInvalidCB );
}


FBlock* XConv( FThreadPool*   iPool
             , bool           iBlocking
             , const FPerf&   iPerf
             , const FCPU&    iCPU
             , const FBlock*  iSrc
             , tFormat        iDst )
{
    ULIS2_ASSERT( iSrc, "Bad source" );
    FBlock* ret = new FBlock( iSrc->Width(), iSrc->Height(), iDst );

    if( iSrc->Format() == iDst )
        Copy( iPool, iBlocking, iPerf, iCPU, iSrc, ret, ULIS2_NODELTA, ULIS2_NOCB );
    else
        Conv( iPool, iBlocking, iPerf, iCPU, iSrc, ret, ULIS2_NOCB );
    return  ret;
}

ULIS2_NAMESPACE_END

