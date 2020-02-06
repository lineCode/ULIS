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
#include "Conv/ConvBuffer.h"

// Macro utils for implementations
#define U2_DREF_RED_CHAN( T, iPtr, iFmt, iChan )    ( *( ( T* )( iPtr ) + iFmt.IDT[ iChan ] ) )
#define U2_DREF_CHAN( T, iPtr, iChan )              ( *( ( T* )( iPtr ) + iChan ) )
#define U2_FWD_ALPHA                                if( iDstFormat.HEA ) { U2_DREF_CHAN( T2, iDst, iDstFormat.AID ) = iSrcFormat.HEA? ConvType< T1, T2 >( U2_DREF_CHAN( T1, iSrc, iSrcFormat.AID ) ) : MaxType< T2 >(); }

#define U2_DREF_SRC( iChan )                        U2_DREF_RED_CHAN( T1, iSrc, iSrcFormat, iChan )
#define U2_DREF_DST( iChan )                        U2_DREF_RED_CHAN( T2, iDst, iDstFormat, iChan )
#define U2_DREF_TEMP( iChan )                       U2_DREF_RED_CHAN( ufloat, temp.Ptr(), temp.FormatInfo(), iChan )

//Dispatch
#include "Conv/Dispatch/Generic/ToGrey.ipp"
#include "Conv/Dispatch/Generic/ToRGB.ipp"
#include "Conv/Dispatch/Generic/ToHSV.ipp"
#include "Conv/Dispatch/Generic/ToHSL.ipp"
#include "Conv/Dispatch/Generic/ToCMY.ipp"
#include "Conv/Dispatch/Generic/ToCMYK.ipp"
#include "Conv/Dispatch/Generic/ToYUV.ipp"
#include "Conv/Dispatch/Generic/ToLab.ipp"
#include "Conv/Dispatch/Generic/ToXYZ.ipp"
#include "Conv/Dispatch/Generic/ToYxy.ipp"

ULIS2_NAMESPACE_BEGIN

template< typename T1, typename T2 >
ULIS2_FORCEINLINE
fpDispatchedConvInvoke
QueryDispatchedConvInvokeForParameters_SelectGrey( tFormat iSrcFormat, tFormat iDstFormat )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : ULIS2_CRASH_DELIBERATE; return  nullptr;
        case CM_GREY    : return  &ConvBufferGreyToGrey  < T1, T2 >;
        case CM_RGB     : return  &ConvBufferGreyToRGB   < T1, T2 >;
        case CM_HSV     : return  &ConvBufferGreyToHSV   < T1, T2 >;
        case CM_HSL     : return  &ConvBufferGreyToHSL   < T1, T2 >;
        case CM_CMY     : return  &ConvBufferGreyToCMY   < T1, T2 >;
        case CM_CMYK    : return  &ConvBufferGreyToCMYK  < T1, T2 >;
        case CM_YUV     : return  &ConvBufferGreyToYUV   < T1, T2 >;
        case CM_Lab     : return  &ConvBufferGreyToLab   < T1, T2 >;
        case CM_XYZ     : return  &ConvBufferGreyToXYZ   < T1, T2 >;
        case CM_Yxy     : return  &ConvBufferGreyToYxy   < T1, T2 >;
    }
    return  nullptr;
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
fpDispatchedConvInvoke
QueryDispatchedConvInvokeForParameters_SelectRGB( tFormat iSrcFormat, tFormat iDstFormat )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : ULIS2_CRASH_DELIBERATE; return  nullptr;
        case CM_GREY    : return  nullptr;
        case CM_RGB     : return  nullptr;
        case CM_HSV     : return  nullptr;
        case CM_HSL     : return  nullptr;
        case CM_CMY     : return  nullptr;
        case CM_CMYK    : return  nullptr;
        case CM_YUV     : return  nullptr;
        case CM_Lab     : return  nullptr;
        case CM_XYZ     : return  nullptr;
        case CM_Yxy     : return  nullptr;
    }
    return  nullptr;
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
fpDispatchedConvInvoke
QueryDispatchedConvInvokeForParameters_SelectHSV( tFormat iSrcFormat, tFormat iDstFormat )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : ULIS2_CRASH_DELIBERATE; return  nullptr;
        case CM_GREY    : return  nullptr;
        case CM_RGB     : return  nullptr;
        case CM_HSV     : return  nullptr;
        case CM_HSL     : return  nullptr;
        case CM_CMY     : return  nullptr;
        case CM_CMYK    : return  nullptr;
        case CM_YUV     : return  nullptr;
        case CM_Lab     : return  nullptr;
        case CM_XYZ     : return  nullptr;
        case CM_Yxy     : return  nullptr;
    }
    return  nullptr;
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
fpDispatchedConvInvoke
QueryDispatchedConvInvokeForParameters_SelectHSL( tFormat iSrcFormat, tFormat iDstFormat )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : ULIS2_CRASH_DELIBERATE; return  nullptr;
        case CM_GREY    : return  nullptr;
        case CM_RGB     : return  nullptr;
        case CM_HSV     : return  nullptr;
        case CM_HSL     : return  nullptr;
        case CM_CMY     : return  nullptr;
        case CM_CMYK    : return  nullptr;
        case CM_YUV     : return  nullptr;
        case CM_Lab     : return  nullptr;
        case CM_XYZ     : return  nullptr;
        case CM_Yxy     : return  nullptr;
    }
    return  nullptr;
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
fpDispatchedConvInvoke
QueryDispatchedConvInvokeForParameters_SelectCMY( tFormat iSrcFormat, tFormat iDstFormat )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : ULIS2_CRASH_DELIBERATE; return  nullptr;
        case CM_GREY    : return  nullptr;
        case CM_RGB     : return  nullptr;
        case CM_HSV     : return  nullptr;
        case CM_HSL     : return  nullptr;
        case CM_CMY     : return  nullptr;
        case CM_CMYK    : return  nullptr;
        case CM_YUV     : return  nullptr;
        case CM_Lab     : return  nullptr;
        case CM_XYZ     : return  nullptr;
        case CM_Yxy     : return  nullptr;
    }
    return  nullptr;
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
fpDispatchedConvInvoke
QueryDispatchedConvInvokeForParameters_SelectCMYK( tFormat iSrcFormat, tFormat iDstFormat )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : ULIS2_CRASH_DELIBERATE; return  nullptr;
        case CM_GREY    : return  nullptr;
        case CM_RGB     : return  nullptr;
        case CM_HSV     : return  nullptr;
        case CM_HSL     : return  nullptr;
        case CM_CMY     : return  nullptr;
        case CM_CMYK    : return  nullptr;
        case CM_YUV     : return  nullptr;
        case CM_Lab     : return  nullptr;
        case CM_XYZ     : return  nullptr;
        case CM_Yxy     : return  nullptr;
    }
    return  nullptr;
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
fpDispatchedConvInvoke
QueryDispatchedConvInvokeForParameters_SelectYUV( tFormat iSrcFormat, tFormat iDstFormat )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : ULIS2_CRASH_DELIBERATE; return  nullptr;
        case CM_GREY    : return  nullptr;
        case CM_RGB     : return  nullptr;
        case CM_HSV     : return  nullptr;
        case CM_HSL     : return  nullptr;
        case CM_CMY     : return  nullptr;
        case CM_CMYK    : return  nullptr;
        case CM_YUV     : return  nullptr;
        case CM_Lab     : return  nullptr;
        case CM_XYZ     : return  nullptr;
        case CM_Yxy     : return  nullptr;
    }
    return  nullptr;
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
fpDispatchedConvInvoke
QueryDispatchedConvInvokeForParameters_SelectLab( tFormat iSrcFormat, tFormat iDstFormat )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : ULIS2_CRASH_DELIBERATE; return  nullptr;
        case CM_GREY    : return  nullptr;
        case CM_RGB     : return  nullptr;
        case CM_HSV     : return  nullptr;
        case CM_HSL     : return  nullptr;
        case CM_CMY     : return  nullptr;
        case CM_CMYK    : return  nullptr;
        case CM_YUV     : return  nullptr;
        case CM_Lab     : return  nullptr;
        case CM_XYZ     : return  nullptr;
        case CM_Yxy     : return  nullptr;
    }
    return  nullptr;
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
fpDispatchedConvInvoke
QueryDispatchedConvInvokeForParameters_SelectXYZ( tFormat iSrcFormat, tFormat iDstFormat )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : ULIS2_CRASH_DELIBERATE; return  nullptr;
        case CM_GREY    : return  nullptr;
        case CM_RGB     : return  nullptr;
        case CM_HSV     : return  nullptr;
        case CM_HSL     : return  nullptr;
        case CM_CMY     : return  nullptr;
        case CM_CMYK    : return  nullptr;
        case CM_YUV     : return  nullptr;
        case CM_Lab     : return  nullptr;
        case CM_XYZ     : return  nullptr;
        case CM_Yxy     : return  nullptr;
    }
    return  nullptr;
}


template< typename T1, typename T2 >
ULIS2_FORCEINLINE
fpDispatchedConvInvoke
QueryDispatchedConvInvokeForParameters_SelectYxy( tFormat iSrcFormat, tFormat iDstFormat )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iSrcFormat ) ) ) {
        case CM_ANY     : ULIS2_CRASH_DELIBERATE; return  nullptr;
        case CM_GREY    : return  nullptr;
        case CM_RGB     : return  nullptr;
        case CM_HSV     : return  nullptr;
        case CM_HSL     : return  nullptr;
        case CM_CMY     : return  nullptr;
        case CM_CMYK    : return  nullptr;
        case CM_YUV     : return  nullptr;
        case CM_Lab     : return  nullptr;
        case CM_XYZ     : return  nullptr;
        case CM_Yxy     : return  nullptr;
    }
    return  nullptr;
}

template< typename T1, typename T2 >
ULIS2_FORCEINLINE
fpDispatchedConvInvoke
QueryDispatchedConvInvokeForParameters_SelectModel( tFormat iSrcFormat, tFormat iDstFormat )
{
    switch( static_cast< eColorModel >( ULIS2_R_MODEL( iDstFormat ) ) )
    {
        case CM_ANY     :   ULIS2_CRASH_DELIBERATE; return  nullptr;
        case CM_GREY    :   return  QueryDispatchedConvInvokeForParameters_SelectGrey< T1, T2 >( iSrcFormat, iDstFormat );
        case CM_RGB     :   return  QueryDispatchedConvInvokeForParameters_SelectRGB<  T1, T2 >( iSrcFormat, iDstFormat );
        case CM_HSV     :   return  QueryDispatchedConvInvokeForParameters_SelectHSV<  T1, T2 >( iSrcFormat, iDstFormat );
        case CM_HSL     :   return  QueryDispatchedConvInvokeForParameters_SelectHSL<  T1, T2 >( iSrcFormat, iDstFormat );
        case CM_CMY     :   return  QueryDispatchedConvInvokeForParameters_SelectCMY<  T1, T2 >( iSrcFormat, iDstFormat );
        case CM_CMYK    :   return  QueryDispatchedConvInvokeForParameters_SelectCMYK< T1, T2 >( iSrcFormat, iDstFormat );
        case CM_YUV     :   return  QueryDispatchedConvInvokeForParameters_SelectYUV<  T1, T2 >( iSrcFormat, iDstFormat );
        case CM_Lab     :   return  QueryDispatchedConvInvokeForParameters_SelectLab<  T1, T2 >( iSrcFormat, iDstFormat );
        case CM_XYZ     :   return  QueryDispatchedConvInvokeForParameters_SelectXYZ<  T1, T2 >( iSrcFormat, iDstFormat );
        case CM_Yxy     :   return  QueryDispatchedConvInvokeForParameters_SelectYxy<  T1, T2 >( iSrcFormat, iDstFormat );
    }
    return  nullptr;
}

ULIS2_NAMESPACE_END

