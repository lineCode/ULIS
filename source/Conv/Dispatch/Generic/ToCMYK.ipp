// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ToCMYK.ipp
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
template< typename T1, typename T2 > void ConvBufferGreyToCMYK( const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferRGBToCMYK(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferHSVToCMYK(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferHSLToCMYK(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferCMYToCMYK(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferCMYKToCMYK( const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferYUVToCMYK(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferLabToCMYK(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferXYZToCMYK(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


template< typename T1, typename T2 > void ConvBufferYxyToCMYK(  const FFormatInfo& iSrcFormat, const tByte* iSrc, const FFormatInfo& iDstFormat, tByte* iDst, tSize iLen ) {

}


ULIS2_NAMESPACE_END
