// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         SummedAreaTable.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the SummedAreaTable entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Misc/SummedAreaTable.h"
#include "Misc/Filter.h"
#include "Data/Block.h"
#include "Maths/Geometry.h"
#include "Maths/Maths.h"
#include "Thread/ThreadPool.h"

ULIS3_NAMESPACE_BEGIN
/*
template< typename T >
void InvokeComputeSummedAreaTable( FThreadPool*             iThreadPool
                                 , bool                     iBlocking
                                 , uint32                   iPerfIntent
                                 , const FHostDeviceInfo&   iHostDeviceInfo
                                 , bool                     iCallCB
                                 , const FBlock*            iSource
                                 , FBlock*                  iSAT )
{
    ULIS3_ASSERT( iThreadPool,                          "Bad pool."                                             );
    ULIS3_ASSERT( iSource,                              "Bad source."                                           );
    ULIS3_ASSERT( iSAT,                                 "Bad destination."                                      );
    ULIS3_ASSERT( iSource != iSAT,                      "Cannot extract a block to itself, use swap instead."   );
    ULIS3_ASSERT( !iCallCB || iBlocking,                "Callback flag is specified on non-blocking operation." );
    ULIS3_ASSERT( iSource->Width()  == iSAT->Width(),   "Blocks sizes don't match"                              );
    ULIS3_ASSERT( iSource->Height() == iSAT->Height(),  "Blocks sizes don't match"                              );

    // Format info
    const FFormatInfo& srcFormatInfo( iSource->FormatInfo() );
    const FFormatInfo& dstFormatInfo( iSAT->FormatInfo() );

    // Bake Params and call
    const tByte*    src     = iSource->DataPtr();
    tSize           src_bps = iSource->BytesPerScanLine();
    tByte*          dst     = iDestination->DataPtr();
    tSize           dst_bps = iDestination->BytesPerScanLine();
    const int       max     = iSource->Height();
    const tSize     len     = iSource->Width();
    ULIS3_MACRO_INLINE_PARALLEL_FOR( iPerfIntent, iThreadPool, iBlocking
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
    iDestination->Invalidate( iCallCB );
}
*/

FBlock* XGetSummedAreaTable( FThreadPool*             iThreadPool
                           , bool                     iBlocking
                           , uint32                   iPerfIntent
                           , const FHostDeviceInfo&   iHostDeviceInfo
                           , bool                     iCallCB
                           , const FBlock*            iSource )
{
    // Assertions
    ULIS3_ASSERT( iThreadPool,              "Bad pool."                                             );
    ULIS3_ASSERT( iSource,                  "Bad source."                                           );
    ULIS3_ASSERT( !iCallCB || iBlocking,    "Callback flag is specified on non-blocking operation." );

    tFormat satFormat = iSource->Format() & ULIS3_E_TYPE | ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT );
    FBlock* sat = new FBlock( iSource->Width(), iSource->Height(), satFormat );
    /*
    switch( iSource->Type() ) {
        case TYPE_UINT8     : InvokeComputeSummedAreaTable< uint8 >(    iThreadPool, iBlocking, iPerfIntent, iHostDeviceInfo, iCallCB, iSource, sat );
        case TYPE_UINT16    : InvokeComputeSummedAreaTable< uint16 >(   iThreadPool, iBlocking, iPerfIntent, iHostDeviceInfo, iCallCB, iSource, sat );
        case TYPE_UINT32    : InvokeComputeSummedAreaTable< uint32 >(   iThreadPool, iBlocking, iPerfIntent, iHostDeviceInfo, iCallCB, iSource, sat );
        case TYPE_UFLOAT    : InvokeComputeSummedAreaTable< ufloat >(   iThreadPool, iBlocking, iPerfIntent, iHostDeviceInfo, iCallCB, iSource, sat );
        case TYPE_UDOUBLE   : InvokeComputeSummedAreaTable< udouble >(  iThreadPool, iBlocking, iPerfIntent, iHostDeviceInfo, iCallCB, iSource, sat );
    }
    */

    return  sat;
}

ULIS3_NAMESPACE_END

