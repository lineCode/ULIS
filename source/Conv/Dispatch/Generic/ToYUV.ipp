// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ToYUV.ipp
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
template< typename T1, typename T2 > void ConvBufferGreyToYUV( const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferRGBToYUV(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferHSVToYUV(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferHSLToYUV(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferCMYToYUV(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferCMYKToYUV( const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferYUVToYUV(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferLabToYUV(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferXYZToYUV(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferYxyToYUV(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


ULIS2_NAMESPACE_END
