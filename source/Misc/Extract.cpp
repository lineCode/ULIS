// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Extract.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the Extract entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Misc/Extract.h"
#include "Data/Block.h"
#include "Maths/Geometry.h"
#include "Maths/Maths.h"
#include "Thread/ParallelFor.h"

ULIS2_NAMESPACE_BEGIN

template< typename T1, typename T2 >
void InvokeExtractInto( size_t iW, const tByte* iSrc, tByte* iDst, std::vector< uint8 > iStridesSrc, std::vector< uint8 > iStridesDst ) {
    const T1*   src = reinterpret_cast< const T1* >( iSrc );
    T2*         dst = reinterpret_cast< T2* >( iDst );
    const size_t len = iStridesSrc.size();
    for( size_t i = 0; i < iW; ++i ) {
        for( size_t j = 0; j < len; ++j )
            *( dst+ iStridesDst[j] ) = ConvType< T1, T2 >( *( src+ iStridesSrc[j] ) );
        src++;
        dst++;
    }
}

typedef void (*fpDispatchedExtractInvoke)( size_t iW, const tByte* iSrc, tByte* iDst, std::vector< uint8 > iStridesSrc, std::vector< uint8 > iStridesDst );
fpDispatchedExtractInvoke QueryDispatchedExtractInvokeForParameters( eType iSrcType, eType iDstType );

fpDispatchedExtractInvoke QueryDispatchedExtractInvokeForParameters( eType iSrcType, eType iDstType ) {
        switch( iSrcType ) {
        case TYPE_UINT8: switch( iDstType ) {
                case TYPE_UINT8:    return  InvokeExtractInto< uint8, uint8        >;
                case TYPE_UINT16:   return  InvokeExtractInto< uint8, uint16       >;
                case TYPE_UINT32:   return  InvokeExtractInto< uint8, uint32       >;
                case TYPE_UFLOAT:   return  InvokeExtractInto< uint8, ufloat       >;
                case TYPE_UDOUBLE:  return  InvokeExtractInto< uint8, udouble      >; }
        case TYPE_UINT16: switch( iDstType ) {
                case TYPE_UINT8:    return  InvokeExtractInto< uint16, uint8       >;
                case TYPE_UINT16:   return  InvokeExtractInto< uint16, uint16      >;
                case TYPE_UINT32:   return  InvokeExtractInto< uint16, uint32      >;
                case TYPE_UFLOAT:   return  InvokeExtractInto< uint16, ufloat      >;
                case TYPE_UDOUBLE:  return  InvokeExtractInto< uint16, udouble     >; }
        case TYPE_UINT32: switch( iDstType ) {
                case TYPE_UINT8:    return  InvokeExtractInto< uint32, uint8       >;
                case TYPE_UINT16:   return  InvokeExtractInto< uint32, uint16      >;
                case TYPE_UINT32:   return  InvokeExtractInto< uint32, uint32      >;
                case TYPE_UFLOAT:   return  InvokeExtractInto< uint32, ufloat      >;
                case TYPE_UDOUBLE:  return  InvokeExtractInto< uint32, udouble     >; }
        case TYPE_UFLOAT: switch( iDstType ) {
                case TYPE_UINT8:    return  InvokeExtractInto< ufloat, uint8       >;
                case TYPE_UINT16:   return  InvokeExtractInto< ufloat, uint16      >;
                case TYPE_UINT32:   return  InvokeExtractInto< ufloat, uint32      >;
                case TYPE_UFLOAT:   return  InvokeExtractInto< ufloat, ufloat      >;
                case TYPE_UDOUBLE:  return  InvokeExtractInto< ufloat, udouble     >; }
        case TYPE_UDOUBLE: switch( iDstType ) {
                case TYPE_UINT8:    return  InvokeExtractInto< udouble, uint8      >;
                case TYPE_UINT16:   return  InvokeExtractInto< udouble, uint16     >;
                case TYPE_UINT32:   return  InvokeExtractInto< udouble, uint32     >;
                case TYPE_UFLOAT:   return  InvokeExtractInto< udouble, ufloat     >;
                case TYPE_UDOUBLE:  return  InvokeExtractInto< udouble, udouble    >; }
    }
    return  nullptr;
}


void
Extract( const FExtractInfo& iExtractParams ) {
    // Assertions
    ULIS2_ASSERT( iExtractParams.source,                                                    "Bad source."                                                       );
    ULIS2_ASSERT( iExtractParams.destination,                                               "Bad destination."                                                  );
    ULIS2_ASSERT( iExtractParams.source != iExtractParams.destination,                      "Cannot extract a block to itself, use swap instead."               );
    ULIS2_ASSERT( !iExtractParams.perfInfo.intent.UseMT() || iExtractParams.perfInfo.pool,  "Multithreading flag is specified but no thread pool is provided."  );
    ULIS2_ASSERT( !iExtractParams.perfInfo.callCB || iExtractParams.perfInfo.blocking,      "Callback flag is specified on non-blocking operation."             );
    ULIS2_ASSERT( !iExtractParams.sourceExtractMask,                                        "Empty extract mask provided."                                      );
    ULIS2_ASSERT( !iExtractParams.destinationExtractMask,                                   "Empty extract mask provided."                                      );
    ULIS2_ASSERT( iExtractParams.source->Width() == iExtractParams.destination->Width(),    "Blocks sizes don't match"                                          );
    ULIS2_ASSERT( iExtractParams.source->Height() == iExtractParams.destination->Height(),  "Blocks sizes don't match"                                          );

    // Check no-op
    if( !iExtractParams.sourceExtractMask || !iExtractParams.destinationExtractMask )
        return;

    // Dst info
    const FFormatInfo& srcFormatInfo( iExtractParams.source->FormatInfo() );
    const FFormatInfo& dstFormatInfo( iExtractParams.destination->FormatInfo() );

    // Channels
    std::vector< uint8 > sourceChannelsToExtract;
    std::vector< uint8 > destinationChannelsToExtract;
    uint8 max_channels_both = FMaths::Min( FMaths::Max( srcFormatInfo.SPP, dstFormatInfo.SPP ), static_cast< uint8 >( ULIS2_MAX_CHANNELS ) );
    sourceChannelsToExtract.reserve( max_channels_both );
    destinationChannelsToExtract.reserve( max_channels_both );
    for( int i = 0; i < max_channels_both; ++i ) {
        if( iExtractParams.sourceExtractMask & 1 << i )
            sourceChannelsToExtract.push_back( iExtractParams.sourceRawIndicesFlag ? i : srcFormatInfo.IDT[i] );

        if( iExtractParams.destinationExtractMask & 1 << i )
            destinationChannelsToExtract.push_back( iExtractParams.destinationRawIndicesFlag ? i : dstFormatInfo.IDT[i] );
    }

    ULIS2_ERROR( sourceChannelsToExtract.size() == destinationChannelsToExtract.size(), "Extract masks don't map" );
    ULIS2_ERROR( sourceChannelsToExtract.size() && destinationChannelsToExtract.size(), "Bad Extraction parameters" );

    // Strides
    std::vector< uint8 >    sourceStrides;
    std::vector< uint8 >    destinationStrides;
    sourceStrides.reserve(      sourceChannelsToExtract.size()      );
    destinationStrides.reserve( destinationChannelsToExtract.size() );
    sourceStrides.push_back(        sourceChannelsToExtract[0] );
    destinationStrides.push_back(   destinationChannelsToExtract[0] );
    for( int i = 1; i < sourceChannelsToExtract.size(); ++i ) {
        sourceStrides.push_back(        ( sourceChannelsToExtract[i]        - sourceChannelsToExtract[i-1]      ) );
        destinationStrides.push_back(   ( destinationChannelsToExtract[i]   - destinationChannelsToExtract[i-1] ) );
    }

    // Bake Params
    const tByte*    srb = iExtractParams.source->DataPtr();
    tByte*          dsb = iExtractParams.destination->DataPtr();
    size_t          src_bps = iExtractParams.source->BytesPerScanLine();
    size_t          dst_bps = iExtractParams.destination->BytesPerScanLine();
    #define SRC srb + ( pLINE * src_bps )
    #define DST dsb + ( pLINE * dst_bps )
    const int   max = iExtractParams.source->Height();
    const size_t len = iExtractParams.source->Width();
    fpDispatchedExtractInvoke fptr = QueryDispatchedExtractInvokeForParameters( srcFormatInfo.TP, dstFormatInfo.TP );

    ULIS2_MACRO_INLINE_PARALLEL_FOR( iExtractParams.perfInfo.intent, iExtractParams.perfInfo.pool, iExtractParams.perfInfo.blocking
                                   , max
                                   , fptr, len, SRC, DST, sourceStrides, destinationStrides )

    iExtractParams.destination->Invalidate( iExtractParams.perfInfo.callCB );
}


FBlock* XExtract( const FXExtractInfo& iExtractParams ) {
    // Assertions
    ULIS2_ASSERT( iExtractParams.source, "Bad source." );
    FBlock* ret = new  FBlock( iExtractParams.source->Width(), iExtractParams.source->Height(), iExtractParams.destinationFormat );
    FExtractInfo nfo = {};
    nfo.source                      = iExtractParams.source;
    nfo.destination                 = ret;
    nfo.sourceRawIndicesFlag        = iExtractParams.sourceRawIndicesFlag;
    nfo.destinationRawIndicesFlag   = iExtractParams.destinationRawIndicesFlag;
    nfo.sourceExtractMask           = iExtractParams.sourceExtractMask;
    nfo.destinationExtractMask      = iExtractParams.destinationExtractMask;
    nfo.perfInfo                    = iExtractParams.perfInfo;

    Extract( nfo );

    return  ret;
}

ULIS2_NAMESPACE_END

