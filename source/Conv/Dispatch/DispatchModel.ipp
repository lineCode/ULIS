// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         DispatchModel.ipp
* @author       Clement Berthaud
* @brief        This file provides the definition for the model dispatcher for the conv entry point functions
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
//Dispatch
#include "Conv/Dispatch/Generic/ToGrey.ipp"

ULIS2_NAMESPACE_BEGIN

template< typename T1, typename T2 >
ULIS2_FORCEINLINE
void
ConvToGrey( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : ULIS2_CRASH_DELIBERATE; return;
        case CM_GREY    : ConvBufferGreyToGrey  < T1, T2 >  ( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_RGB     : ConvBufferGreyToRGB   < T1, T2 >  ( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_HSV     : ConvBufferGreyToHSV   < T1, T2 >  ( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_HSL     : ConvBufferGreyToHSL   < T1, T2 >  ( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_CMY     : ConvBufferGreyToCMY   < T1, T2 >  ( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_CMYK    : ConvBufferGreyToCMYK  < T1, T2 >  ( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_YUV     : ConvBufferGreyToYUV   < T1, T2 >  ( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_Lab     : ConvBufferGreyToLab   < T1, T2 >  ( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_XYZ     : ConvBufferGreyToXYZ   < T1, T2 >  ( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_Yxy     : ConvBufferGreyToYxy   < T1, T2 >  ( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
    }
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
void
ConvToRGB( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : break;
        case CM_GREY    : break;
        case CM_RGB     : break;
        case CM_HSV     : break;
        case CM_HSL     : break;
        case CM_CMY     : break;
        case CM_CMYK    : break;
        case CM_YUV     : break;
        case CM_Lab     : break;
        case CM_XYZ     : break;
        case CM_Yxy     : break;
    }
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
void
ConvToHSV( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : break;
        case CM_GREY    : break;
        case CM_RGB     : break;
        case CM_HSV     : break;
        case CM_HSL     : break;
        case CM_CMY     : break;
        case CM_CMYK    : break;
        case CM_YUV     : break;
        case CM_Lab     : break;
        case CM_XYZ     : break;
        case CM_Yxy     : break;
    }
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
void
ConvToHSL( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : break;
        case CM_GREY    : break;
        case CM_RGB     : break;
        case CM_HSV     : break;
        case CM_HSL     : break;
        case CM_CMY     : break;
        case CM_CMYK    : break;
        case CM_YUV     : break;
        case CM_Lab     : break;
        case CM_XYZ     : break;
        case CM_Yxy     : break;
    }
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
void
ConvToCMY( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : break;
        case CM_GREY    : break;
        case CM_RGB     : break;
        case CM_HSV     : break;
        case CM_HSL     : break;
        case CM_CMY     : break;
        case CM_CMYK    : break;
        case CM_YUV     : break;
        case CM_Lab     : break;
        case CM_XYZ     : break;
        case CM_Yxy     : break;
    }
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
void
ConvToCMYK( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : break;
        case CM_GREY    : break;
        case CM_RGB     : break;
        case CM_HSV     : break;
        case CM_HSL     : break;
        case CM_CMY     : break;
        case CM_CMYK    : break;
        case CM_YUV     : break;
        case CM_Lab     : break;
        case CM_XYZ     : break;
        case CM_Yxy     : break;
    }
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
void
ConvToYUV( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : break;
        case CM_GREY    : break;
        case CM_RGB     : break;
        case CM_HSV     : break;
        case CM_HSL     : break;
        case CM_CMY     : break;
        case CM_CMYK    : break;
        case CM_YUV     : break;
        case CM_Lab     : break;
        case CM_XYZ     : break;
        case CM_Yxy     : break;
    }
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
void
ConvToLab( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : break;
        case CM_GREY    : break;
        case CM_RGB     : break;
        case CM_HSV     : break;
        case CM_HSL     : break;
        case CM_CMY     : break;
        case CM_CMYK    : break;
        case CM_YUV     : break;
        case CM_Lab     : break;
        case CM_XYZ     : break;
        case CM_Yxy     : break;
    }
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
void
ConvToXYZ( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : break;
        case CM_GREY    : break;
        case CM_RGB     : break;
        case CM_HSV     : break;
        case CM_HSL     : break;
        case CM_CMY     : break;
        case CM_CMYK    : break;
        case CM_YUV     : break;
        case CM_Lab     : break;
        case CM_XYZ     : break;
        case CM_Yxy     : break;
    }
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
void
ConvToYxy( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : break;
        case CM_GREY    : break;
        case CM_RGB     : break;
        case CM_HSV     : break;
        case CM_HSL     : break;
        case CM_CMY     : break;
        case CM_CMYK    : break;
        case CM_YUV     : break;
        case CM_Lab     : break;
        case CM_XYZ     : break;
        case CM_Yxy     : break;
    }
}

template< typename T1, typename T2 >
ULIS2_FORCEINLINE
void ConvBufferT( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iDstFormat ) ) )
    {
        case CM_ANY     :   ULIS2_CRASH_DELIBERATE; return;
        case CM_GREY    :   ConvToGrey< T1, T2 >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_RGB     :   ConvToRGB<  T1, T2 >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_HSV     :   ConvToHSV<  T1, T2 >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_HSL     :   ConvToHSL<  T1, T2 >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_CMY     :   ConvToCMY<  T1, T2 >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_CMYK    :   ConvToCMYK< T1, T2 >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_YUV     :   ConvToYUV<  T1, T2 >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_Lab     :   ConvToLab<  T1, T2 >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_XYZ     :   ConvToXYZ<  T1, T2 >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
        case CM_Yxy     :   ConvToYxy<  T1, T2 >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );   return;
    }
}

ULIS2_NAMESPACE_END

