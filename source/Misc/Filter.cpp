// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         Filter.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Filter entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Misc/Filter.h"
#include "System/HostDeviceInfo.h"
#include "Image/RasterImage2D.h"
#include "Math/Geometry/Rectangle.h"
#include "Math/Geometry/Vector.h"
#include "Math/Math.h"
#include "Thread/ThreadPool.h"

ULIS_NAMESPACE_BEGIN

void InvokeFilter( const size_t iLen, const FBlock* iBlock, const uint8* iPtr, const size_t iSrcBPP, std::function< void( const FBlock* iBlock, const uint8* iPtr ) > iFunc ) {
    for( size_t i = 0; i < iLen; ++i ) {
        iFunc( iBlock, iPtr );
        iPtr += iSrcBPP;
    }
}

void InvokeFilterInPlace( const size_t iLen, FBlock* iBlock, uint8* iPtr, const size_t iSrcBPP, std::function< void( FBlock* iBlock, uint8* iPtr ) > iFunc ) {
    for( size_t i = 0; i < iLen; ++i ) {
        iFunc( iBlock, iPtr );
        iPtr += iSrcBPP;
    }
}

void InvokeFilterInto( const size_t iLen, const FBlock* iSrcBlock, const uint8* iSrcPtr, const size_t iSrcBPP, FBlock* iDstBlock, uint8* iDstPtr, const size_t iDstBPP, std::function< void( const FBlock* iSrcBlock, const uint8* iSrcPtr, FBlock* iDstBlock, uint8* iDstPtr ) > iFunc ) {
    for( size_t i = 0; i < iLen; ++i ) {
        iFunc( iSrcBlock, iSrcPtr, iDstBlock, iDstPtr );
        iSrcPtr += iSrcBPP;
        iDstPtr += iDstBPP;
    }
}

void Filter( FThreadPool*           iThreadPool
           , bool                   iBlocking
           , uint32                 iPerfIntent
           , const FHostDeviceInfo& iHostDeviceInfo
           , bool                   iCallCB
           , const FBlock*          iSource
           , std::function< void( const FBlock* iBlock, const uint8* iPtr ) > iFunc )
{
    // Assertions
    ULIS_ASSERT( iThreadPool,                                  "Bad pool."                                             );
    ULIS_ASSERT( iSource,                                      "Bad source."                                           );
    ULIS_ASSERT( !iCallCB || iBlocking,                        "Callback flag is specified on non-blocking operation." );
    ULIS_ASSERT( iFunc,                                        "No func provided"                                      );

    // Format info
    const FFormat& srcFormatInfo( iSource->FormatInfo() );

    // Bake Params and call
    const uint8*    src     = iSource->Bits();
    uint32           src_bps = iSource->BytesPerScanLine();
    const int       max     = iSource->Height();
    const uint32     len     = iSource->Width();
    ULIS_MACRO_INLINE_PARALLEL_FOR( iPerfIntent, iThreadPool, iBlocking
                                   , max
                                   , InvokeFilter
                                   , len, iSource, src + ( pLINE * src_bps ), srcFormatInfo.BPP, iFunc );
}

void FilterInPlace( FThreadPool*            iThreadPool
                  , bool                    iBlocking
                  , uint32                  iPerfIntent
                  , const FHostDeviceInfo&  iHostDeviceInfo
                  , bool                    iCallCB
                  , FBlock*                 iSource
                  , std::function< void( FBlock* iBlock, uint8* iPtr ) > iFunc )
{
    ULIS_ASSERT( iThreadPool,                                  "Bad pool."                                             );
    ULIS_ASSERT( iSource,                                      "Bad source."                                           );
    ULIS_ASSERT( !iCallCB || iBlocking,                        "Callback flag is specified on non-blocking operation." );
    ULIS_ASSERT( iFunc,                                        "No func provided"                                      );

    // Format info
    const FFormat& srcFormatInfo( iSource->FormatInfo() );

    // Bake Params and call
    uint8*      src     = iSource->Bits();
    uint32       src_bps = iSource->BytesPerScanLine();
    const int   max     = iSource->Height();
    const uint32 len     = iSource->Width();
    ULIS_MACRO_INLINE_PARALLEL_FOR( iPerfIntent, iThreadPool, iBlocking
                                   , max
                                   , InvokeFilterInPlace
                                   , len, iSource, src + ( pLINE * src_bps ), srcFormatInfo.BPP, iFunc );

    iSource->Dirty( iCallCB );
}

void FilterInto( FThreadPool*              iThreadPool
               , bool                      iBlocking
               , uint32                    iPerfIntent
               , const FHostDeviceInfo&    iHostDeviceInfo
               , bool                      iCallCB
               , const FBlock*             iSource
               , FBlock*                   iDestination
               , std::function< void( const FBlock* iSrcBlock, const uint8* iSrcPtr, FBlock* iDstBlock, uint8* iDstPtr ) > iFunc )
{
    ULIS_ASSERT( iThreadPool,                                  "Bad pool."                                             );
    ULIS_ASSERT( iSource,                                      "Bad source."                                           );
    ULIS_ASSERT( iDestination,                                 "Bad destination."                                      );
    ULIS_ASSERT( iSource != iDestination,                      "Cannot extract a block to itself, use swap instead."   );
    ULIS_ASSERT( !iCallCB || iBlocking,                        "Callback flag is specified on non-blocking operation." );
    ULIS_ASSERT( iSource->Width()  == iDestination->Width(),   "Blocks sizes don't match"                              );
    ULIS_ASSERT( iSource->Height() == iDestination->Height(),  "Blocks sizes don't match"                              );
    ULIS_ASSERT( iFunc,                                        "No func provided"                                      );

    // Format info
    const FFormat& srcFormatInfo( iSource->FormatInfo() );
    const FFormat& dstFormatInfo( iDestination->FormatInfo() );

    // Bake Params and call
    const uint8*    src     = iSource->Bits();
    uint32           src_bps = iSource->BytesPerScanLine();
    uint8*          dst     = iDestination->Bits();
    uint32           dst_bps = iDestination->BytesPerScanLine();
    const int       max     = iSource->Height();
    const uint32     len     = iSource->Width();
    ULIS_MACRO_INLINE_PARALLEL_FOR( iPerfIntent, iThreadPool, iBlocking
                                   , max
                                   , InvokeFilterInto
                                   , len
                                   , iSource
                                   , src + ( pLINE * src_bps )
                                   , srcFormatInfo.BPP
                                   , iDestination
                                   , dst + ( pLINE * dst_bps )
                                   , dstFormatInfo.BPP
                                   , iFunc );
    iDestination->Dirty( iCallCB );
}

ULIS_NAMESPACE_END

