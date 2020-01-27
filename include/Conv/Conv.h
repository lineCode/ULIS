// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Conv.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Conv entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"

ULIS2_NAMESPACE_BEGIN
class FProfileRegistry;
/// @fn         void ProfileConv( const IPixel& iSrc, IPixel& iDst, const FProfileRegistry& iProfileRegistry, uint32 iIntent = INTENT_PERCEPTUAL )
/// @brief      Conv a pixel from source to destination with color space and intent.
/// @param      iSrc                A const reference to the source Pixel.
/// @param      iDst                A reference to the destination Pixel.
/// @param      iProfileRegistry    A reference to the profile registry used as backup if input pixels do not have profiles associated with them.
/// @param      iIntent             The profile conversion intent.
ULIS2_API void ProfileConv( const IPixel& iSrc, IPixel& iDst, const FProfileRegistry& iProfileRegistry, uint32 iIntent = 0 /* INTENT_PERCEPTUAL */ );

/// @fn         void Conv( const IPixel& iSrc, IPixel& iDst )
/// @brief      Conv a pixel from source to destination with basic model conversion.
/// @param      iSrc                A const reference to the source Pixel.
/// @param      iDst                A reference to the destination Pixel.
ULIS2_API void Conv( const IPixel& iSrc, IPixel& iDst );

// Pixel Template implementations
template< typename T1, typename T2 > void ConvT( const IPixel& iSrc, IPixel& iDst );
template< typename T1, typename T2 > void ConvToGrey(   const IPixel& iSrc, IPixel& iDst );
template< typename T1, typename T2 > void ConvToRGB(    const IPixel& iSrc, IPixel& iDst );
template< typename T1, typename T2 > void ConvToHSV(    const IPixel& iSrc, IPixel& iDst );
template< typename T1, typename T2 > void ConvToHSL(    const IPixel& iSrc, IPixel& iDst );
template< typename T1, typename T2 > void ConvToCMY(    const IPixel& iSrc, IPixel& iDst );
template< typename T1, typename T2 > void ConvToCMYK(   const IPixel& iSrc, IPixel& iDst );
template< typename T1, typename T2 > void ConvToYUV(    const IPixel& iSrc, IPixel& iDst );
template< typename T1, typename T2 > void ConvToLab(    const IPixel& iSrc, IPixel& iDst );
template< typename T1, typename T2 > void ConvToXYZ(    const IPixel& iSrc, IPixel& iDst );
template< typename T1, typename T2 > void ConvToYxy(    const IPixel& iSrc, IPixel& iDst );

/////////////////////////////////////////////////////
// Template Instanciations
#define X_DO_A( t1, t2 ) ULIS2_API_TEMPLATE void ConvT<  t1, t2 >( const IPixel& iSrc, IPixel& iDst );
#define X_DO_B( t1, t2 ) ULIS2_API_TEMPLATE void ConvToGrey< t1, t2 >( const IPixel& iSrc, IPixel& iDst );
#define X_DO_C( t1, t2 ) ULIS2_API_TEMPLATE void ConvToRGB<  t1, t2 >( const IPixel& iSrc, IPixel& iDst );
#define X_DO_D( t1, t2 ) ULIS2_API_TEMPLATE void ConvToHSV<  t1, t2 >( const IPixel& iSrc, IPixel& iDst );
#define X_DO_E( t1, t2 ) ULIS2_API_TEMPLATE void ConvToHSL<  t1, t2 >( const IPixel& iSrc, IPixel& iDst );
#define X_DO_F( t1, t2 ) ULIS2_API_TEMPLATE void ConvToCMY<  t1, t2 >( const IPixel& iSrc, IPixel& iDst );
#define X_DO_G( t1, t2 ) ULIS2_API_TEMPLATE void ConvToCMYK< t1, t2 >( const IPixel& iSrc, IPixel& iDst );
#define X_DO_H( t1, t2 ) ULIS2_API_TEMPLATE void ConvToYUV<  t1, t2 >( const IPixel& iSrc, IPixel& iDst );
#define X_DO_I( t1, t2 ) ULIS2_API_TEMPLATE void ConvToLab<  t1, t2 >( const IPixel& iSrc, IPixel& iDst );
#define X_DO_J( t1, t2 ) ULIS2_API_TEMPLATE void ConvToXYZ<  t1, t2 >( const IPixel& iSrc, IPixel& iDst );
#define X_DO_K( t1, t2 ) ULIS2_API_TEMPLATE void ConvToYxy<  t1, t2 >( const IPixel& iSrc, IPixel& iDst );
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

