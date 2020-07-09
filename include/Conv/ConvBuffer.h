// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         ConvBuffer.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the ConvBuffer entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Typedefs
typedef void (*fpConversionInvocation)( const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
ULIS3_API fpConversionInvocation QueryDispatchedConversionInvocation( uint32 iSrcFormat, uint32 iDstFormat );

/////////////////////////////////////////////////////
// Explicit Conv Entry Points
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ To Grey
template< typename T1, typename T2 > void ConvBufferGreyToGrey( const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferRGBToGrey(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSVToGrey(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSLToGrey(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYToGrey(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYKToGrey( const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYUVToGrey(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferLabToGrey(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferXYZToGrey(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYxyToGrey(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- ToRGB
template< typename T1, typename T2 > void ConvBufferGreyToRGB(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferRGBToRGB(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSVToRGB(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSLToRGB(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYToRGB(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYKToRGB(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYUVToRGB(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferLabToRGB(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferXYZToRGB(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYxyToRGB(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- ToHSV
template< typename T1, typename T2 > void ConvBufferGreyToHSV(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferRGBToHSV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSVToHSV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSLToHSV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYToHSV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYKToHSV(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYUVToHSV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferLabToHSV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferXYZToHSV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYxyToHSV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- ToHSL
template< typename T1, typename T2 > void ConvBufferGreyToHSL(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferRGBToHSL(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSVToHSL(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSLToHSL(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYToHSL(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYKToHSL(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYUVToHSL(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferLabToHSL(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferXYZToHSL(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYxyToHSL(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- ToCMY
template< typename T1, typename T2 > void ConvBufferGreyToCMY(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferRGBToCMY(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSVToCMY(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSLToCMY(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYToCMY(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYKToCMY(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYUVToCMY(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferLabToCMY(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferXYZToCMY(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYxyToCMY(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );

//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- ToCMYK
template< typename T1, typename T2 > void ConvBufferGreyToCMYK( const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferRGBToCMYK(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSVToCMYK(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSLToCMYK(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYToCMYK(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYKToCMYK( const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYUVToCMYK(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferLabToCMYK(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferXYZToCMYK(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYxyToCMYK(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- ToYUV
template< typename T1, typename T2 > void ConvBufferGreyToYUV(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferRGBToYUV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSVToYUV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSLToYUV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYToYUV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYKToYUV(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYUVToYUV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferLabToYUV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferXYZToYUV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYxyToYUV(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- ToLab
template< typename T1, typename T2 > void ConvBufferGreyToLab(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferRGBToLab(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSVToLab(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSLToLab(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYToLab(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYKToLab(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYUVToLab(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferLabToLab(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferXYZToLab(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYxyToLab(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- ToXYZ
template< typename T1, typename T2 > void ConvBufferGreyToXYZ(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferRGBToXYZ(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSVToXYZ(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSLToXYZ(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYToXYZ(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYKToXYZ(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYUVToXYZ(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferLabToXYZ(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferXYZToXYZ(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYxyToXYZ(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- ToYxy
template< typename T1, typename T2 > void ConvBufferGreyToYxy(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferRGBToYxy(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSVToYxy(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferHSLToYxy(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYToYxy(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferCMYKToYxy(  const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYUVToYxy(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferLabToYxy(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferXYZToYxy(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );
template< typename T1, typename T2 > void ConvBufferYxyToYxy(   const FFormat* iSrcFormat, const uint8* iSrc, const FFormat* iDstFormat, uint8* iDst, uint32 iLen );

ULIS3_NAMESPACE_END

