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

template< typename T >
void 
InvokeComputeSummedAreaTable_XPass_MEM_Generic( const uint32 iLen, const FBlock* iSource, FBlock* iSAT, const tByte* iSrc, tByte* iDst ) {
    const FFormatInfo& fmt = iSource->FormatInfo();
    const T*    src = reinterpret_cast< const T* >( iSrc )  + fmt.SPP;
    float*      dst = reinterpret_cast< float* >( iDst )    + fmt.SPP;

    for( uint32 x = 1; x < iLen; ++x ) {

        for( uint8 j = 0; j < fmt.SPP; ++j )
            dst[j] = static_cast< float >( src[j] + src[j - fmt.SPP ] );

        src += fmt.SPP;
        dst += fmt.SPP;
    }
}

template< typename T >
void 
InvokeComputeSummedAreaTable_YPass_MEM_Generic( const uint32 iLen, const FBlock* iSource, FBlock* iSAT, const tByte* iSrc, tByte* iDst ) {
    const FFormatInfo& fmt = iSource->FormatInfo();
    const tSize src_stride = iSource->Width();
    const tSize dst_stride = iSAT->Width();
    const T* src = reinterpret_cast< const T* >( iSrc ) + src_stride;
    float*   dst = reinterpret_cast< float* >( iDst )   + dst_stride;

    for( uint32 y = 1; y < iLen; ++y ) {

        for( uint8 j = 0; j < fmt.SPP; ++j )
            dst[j] = static_cast< float >( src[j] + src[j - fmt.SPP ] );

        src += src_stride;
        dst += dst_stride;
    }
}

template< typename T >
void ComputeSummedAreaTable_Generic( FThreadPool*             iThreadPool
                                   , bool                     iBlocking
                                   , uint32                   iPerfIntent
                                   , const FHostDeviceInfo&   iHostDeviceInfo
                                   , const FBlock*            iSource
                                   , FBlock*                  iSAT )
{
    const tByte*    src     = iSource->DataPtr();
    tByte*          bdp     = iSAT->DataPtr();
    const tSize     src_bps = iSource->BytesPerScanLine();
    const tSize     bdp_bps = iSAT->BytesPerScanLine();
    const tSize     src_bpp = iSource->BytesPerPixel();
    const tSize     bdp_bpp = iSAT->BytesPerPixel();
    const int       w       = iSource->Width();
    const int       h       = iSource->Height();
    ULIS3_MACRO_INLINE_PARALLEL_FOR( iPerfIntent, iThreadPool, iBlocking
                                   , h
                                   , InvokeComputeSummedAreaTable_XPass_MEM_Generic< T >
                                   , w, iSource, iSAT
                                   , src + pLINE * src_bps
                                   , bdp + pLINE * bdp_bps );
    iThreadPool->WaitForCompletion();
    ULIS3_MACRO_INLINE_PARALLEL_FOR( iPerfIntent, iThreadPool, iBlocking
                                   , w
                                   , InvokeComputeSummedAreaTable_YPass_MEM_Generic< T >
                                   , h, iSource, iSAT
                                   , src + pLINE * src_bpp
                                   , bdp + pLINE * bdp_bpp );
}

typedef void (*fpDispatchedSATFunc)( FThreadPool*             iThreadPool
                                   , bool                     iBlocking
                                   , uint32                   iPerfIntent
                                   , const FHostDeviceInfo&   iHostDeviceInfo
                                   , const FBlock*            iSource
                                   , FBlock*                  iSAT );

template< typename T >
fpDispatchedSATFunc
QueryDispatchedSATFunctionForParameters_Generic( uint32 iPerfIntent, const FHostDeviceInfo& iHostDeviceInfo, const FFormatInfo& iFormatInfo ) {
    return  ComputeSummedAreaTable_Generic< T >;
}

template< typename T >
fpDispatchedSATFunc
QueryDispatchedSATFunctionForParameters_imp( uint32 iPerfIntent, const FHostDeviceInfo& iHostDeviceInfo, const FFormatInfo& iFormatInfo ) {
    return  QueryDispatchedSATFunctionForParameters_Generic< T >( iPerfIntent, iHostDeviceInfo, iFormatInfo );
}

fpDispatchedSATFunc
QueryDispatchedSATFunctionForParameters( uint32 iPerfIntent, const FHostDeviceInfo& iHostDeviceInfo, const FFormatInfo& iFormatInfo ) {
    switch( iFormatInfo.TP ) {
        case TYPE_UINT8     : return  QueryDispatchedSATFunctionForParameters_imp< uint8   >( iPerfIntent, iHostDeviceInfo, iFormatInfo );
        case TYPE_UINT16    : return  QueryDispatchedSATFunctionForParameters_imp< uint16  >( iPerfIntent, iHostDeviceInfo, iFormatInfo );
        case TYPE_UINT32    : return  QueryDispatchedSATFunctionForParameters_imp< uint32  >( iPerfIntent, iHostDeviceInfo, iFormatInfo );
        case TYPE_UFLOAT    : return  QueryDispatchedSATFunctionForParameters_imp< ufloat  >( iPerfIntent, iHostDeviceInfo, iFormatInfo );
        case TYPE_UDOUBLE   : return  QueryDispatchedSATFunctionForParameters_imp< udouble >( iPerfIntent, iHostDeviceInfo, iFormatInfo );
    }
    return  nullptr;
}


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

    tFormat satFormat = ( ( iSource->Format() & ULIS3_E_TYPE ) | ULIS3_W_TYPE( ULIS3_TYPE_UFLOAT ) );
    FBlock* sat = new FBlock( iSource->Width(), iSource->Height(), satFormat );

    // Query dispatched method
    fpDispatchedSATFunc fptr = QueryDispatchedSATFunctionForParameters( iPerfIntent, iHostDeviceInfo, iSource->Format() );
    ULIS3_ASSERT( fptr, "No dispatch function found." );
    fptr( iThreadPool, iBlocking, iPerfIntent, iHostDeviceInfo, iSource, sat );

    sat->Invalidate( iCallCB );

    return  sat;
}

ULIS3_NAMESPACE_END

