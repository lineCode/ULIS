// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ToRGB.ipp
* @author       Clement Berthaud
* @brief        This file provides the definition for model conversion functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Conv/ConvBuffer.h"
#include "Data/FormatInfo.h"
#include "Data/Pixel.h"

ULIS2_NAMESPACE_BEGIN
template< typename T1, typename T2 > void ConvBufferGreyToRGB( const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferRGBToRGB(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferHSVToRGB(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferHSLToRGB(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferCMYToRGB(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferCMYKToRGB( const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferYUVToRGB(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferLabToRGB(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferXYZToRGB(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferYxyToRGB(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


ULIS2_NAMESPACE_END
