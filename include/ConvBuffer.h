// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ConvBuffer.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the ConvBuffer entry point functions.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"

ULIS2_NAMESPACE_BEGIN
/// @fn         void ConvBuffer( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat )
/// @brief      Conv a buffer from source to destination with basic model conversion.
/// @param      iSrc                A const pointer to source buffer.
/// @param      iSrcFormat          Source buffer format.
/// @param      iDst                A pointer to destination buffer.
/// @param      iDstFormat          Destination buffer format.
/// @param      iNum                Number of pixels to convert.
ULIS2_API void ConvBuffer( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );

// Buffer implementations
template< typename T1, typename T2 > void ConvBufferT(  const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
template< typename T1, typename T2 > void ConvBufferToGrey( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
template< typename T1, typename T2 > void ConvBufferToRGB(  const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
template< typename T1, typename T2 > void ConvBufferToHSV(  const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
template< typename T1, typename T2 > void ConvBufferToHSL(  const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
template< typename T1, typename T2 > void ConvBufferToCMY(  const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
template< typename T1, typename T2 > void ConvBufferToCMYK( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
template< typename T1, typename T2 > void ConvBufferToYUV(  const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
template< typename T1, typename T2 > void ConvBufferToLab(  const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
template< typename T1, typename T2 > void ConvBufferToXYZ(  const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
template< typename T1, typename T2 > void ConvBufferToYxy(  const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );


/////////////////////////////////////////////////////
// Template Instanciations
#define X_DO_A( t1, t2 ) ULIS2_API_TEMPLATE void ConvBufferT<  t1, t2 >( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
#define X_DO_B( t1, t2 ) ULIS2_API_TEMPLATE void ConvBufferToGrey< t1, t2 >( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
#define X_DO_C( t1, t2 ) ULIS2_API_TEMPLATE void ConvBufferToRGB<  t1, t2 >( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
#define X_DO_D( t1, t2 ) ULIS2_API_TEMPLATE void ConvBufferToHSV<  t1, t2 >( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
#define X_DO_E( t1, t2 ) ULIS2_API_TEMPLATE void ConvBufferToHSL<  t1, t2 >( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
#define X_DO_F( t1, t2 ) ULIS2_API_TEMPLATE void ConvBufferToCMY<  t1, t2 >( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
#define X_DO_G( t1, t2 ) ULIS2_API_TEMPLATE void ConvBufferToCMYK< t1, t2 >( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
#define X_DO_H( t1, t2 ) ULIS2_API_TEMPLATE void ConvBufferToYUV<  t1, t2 >( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
#define X_DO_I( t1, t2 ) ULIS2_API_TEMPLATE void ConvBufferToLab<  t1, t2 >( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
#define X_DO_J( t1, t2 ) ULIS2_API_TEMPLATE void ConvBufferToXYZ<  t1, t2 >( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
#define X_DO_K( t1, t2 ) ULIS2_API_TEMPLATE void ConvBufferToYxy<  t1, t2 >( const tByte* iSrc, tFormat iSrcFormat, tByte* iDst, tFormat iDstFormat, uint32 iNum );
ULIS2_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_A )
ULIS2_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_B )
ULIS2_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_C )
ULIS2_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_D )
ULIS2_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_E )
ULIS2_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_F )
ULIS2_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_G )
ULIS2_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_H )
ULIS2_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_I )
ULIS2_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_J )
ULIS2_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_K )
#undef X_DO_A
#undef X_DO_B
#undef X_DO_C
#undef X_DO_D
#undef X_DO_E
#undef X_DO_F
#undef X_DO_G
#undef X_DO_H
#undef X_DO_I
#undef X_DO_J
#undef X_DO_K

ULIS2_NAMESPACE_END

