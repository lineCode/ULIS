// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         ConvBuffer.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the ConvBuffer entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Conv/ConvBuffer.h"
#include "Conv/ConvDispatch.ipp"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// Conversion Dispatcher
fpConversionInvocation QueryDispatchedConversionInvocation( tFormat iSrcFormat, tFormat iDstFormat )
{
        switch( static_cast< eType >( ULIS3_R_TYPE( iSrcFormat ) ) ) {
        case TYPE_UINT8: switch( static_cast< eType >( ULIS3_R_TYPE( iDstFormat ) ) ) {
                case TYPE_UINT8:    return  QueryDispatchedConversionInvocation_SelectModel< uint8, uint8       >( iSrcFormat, iDstFormat );
                case TYPE_UINT16:   return  QueryDispatchedConversionInvocation_SelectModel< uint8, uint16      >( iSrcFormat, iDstFormat );
                case TYPE_UINT32:   return  QueryDispatchedConversionInvocation_SelectModel< uint8, uint32      >( iSrcFormat, iDstFormat );
                case TYPE_UFLOAT:   return  QueryDispatchedConversionInvocation_SelectModel< uint8, ufloat      >( iSrcFormat, iDstFormat );
                case TYPE_UDOUBLE:  return  QueryDispatchedConversionInvocation_SelectModel< uint8, udouble     >( iSrcFormat, iDstFormat ); }
        case TYPE_UINT16: switch( static_cast< eType >( ULIS3_R_TYPE( iDstFormat ) ) ) {
                case TYPE_UINT8:    return  QueryDispatchedConversionInvocation_SelectModel< uint16, uint8      >( iSrcFormat, iDstFormat );
                case TYPE_UINT16:   return  QueryDispatchedConversionInvocation_SelectModel< uint16, uint16     >( iSrcFormat, iDstFormat );
                case TYPE_UINT32:   return  QueryDispatchedConversionInvocation_SelectModel< uint16, uint32     >( iSrcFormat, iDstFormat );
                case TYPE_UFLOAT:   return  QueryDispatchedConversionInvocation_SelectModel< uint16, ufloat     >( iSrcFormat, iDstFormat );
                case TYPE_UDOUBLE:  return  QueryDispatchedConversionInvocation_SelectModel< uint16, udouble    >( iSrcFormat, iDstFormat ); }
        case TYPE_UINT32: switch( static_cast< eType >( ULIS3_R_TYPE( iDstFormat ) ) ) {
                case TYPE_UINT8:    return  QueryDispatchedConversionInvocation_SelectModel< uint32, uint8      >( iSrcFormat, iDstFormat );
                case TYPE_UINT16:   return  QueryDispatchedConversionInvocation_SelectModel< uint32, uint16     >( iSrcFormat, iDstFormat );
                case TYPE_UINT32:   return  QueryDispatchedConversionInvocation_SelectModel< uint32, uint32     >( iSrcFormat, iDstFormat );
                case TYPE_UFLOAT:   return  QueryDispatchedConversionInvocation_SelectModel< uint32, ufloat     >( iSrcFormat, iDstFormat );
                case TYPE_UDOUBLE:  return  QueryDispatchedConversionInvocation_SelectModel< uint32, udouble    >( iSrcFormat, iDstFormat ); }
        case TYPE_UFLOAT: switch( static_cast< eType >( ULIS3_R_TYPE( iDstFormat ) ) ) {
                case TYPE_UINT8:    return  QueryDispatchedConversionInvocation_SelectModel< ufloat, uint8      >( iSrcFormat, iDstFormat );
                case TYPE_UINT16:   return  QueryDispatchedConversionInvocation_SelectModel< ufloat, uint16     >( iSrcFormat, iDstFormat );
                case TYPE_UINT32:   return  QueryDispatchedConversionInvocation_SelectModel< ufloat, uint32     >( iSrcFormat, iDstFormat );
                case TYPE_UFLOAT:   return  QueryDispatchedConversionInvocation_SelectModel< ufloat, ufloat     >( iSrcFormat, iDstFormat );
                case TYPE_UDOUBLE:  return  QueryDispatchedConversionInvocation_SelectModel< ufloat, udouble    >( iSrcFormat, iDstFormat ); }
        case TYPE_UDOUBLE: switch( static_cast< eType >( ULIS3_R_TYPE( iDstFormat ) ) ) {
                case TYPE_UINT8:    return  QueryDispatchedConversionInvocation_SelectModel< udouble, uint8     >( iSrcFormat, iDstFormat );
                case TYPE_UINT16:   return  QueryDispatchedConversionInvocation_SelectModel< udouble, uint16    >( iSrcFormat, iDstFormat );
                case TYPE_UINT32:   return  QueryDispatchedConversionInvocation_SelectModel< udouble, uint32    >( iSrcFormat, iDstFormat );
                case TYPE_UFLOAT:   return  QueryDispatchedConversionInvocation_SelectModel< udouble, ufloat    >( iSrcFormat, iDstFormat );
                case TYPE_UDOUBLE:  return  QueryDispatchedConversionInvocation_SelectModel< udouble, udouble   >( iSrcFormat, iDstFormat ); }
    }

    return  nullptr;
}

/////////////////////////////////////////////////////
// Template Instanciations
#define X_DO_01( T, U )   template ULIS3_API void ConvBufferGreyToGrey< T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_02( T, U )   template ULIS3_API void ConvBufferRGBToGrey<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_03( T, U )   template ULIS3_API void ConvBufferHSVToGrey<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_04( T, U )   template ULIS3_API void ConvBufferHSLToGrey<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_05( T, U )   template ULIS3_API void ConvBufferCMYToGrey<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_06( T, U )   template ULIS3_API void ConvBufferCMYKToGrey< T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_07( T, U )   template ULIS3_API void ConvBufferYUVToGrey<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_08( T, U )   template ULIS3_API void ConvBufferLabToGrey<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_09( T, U )   template ULIS3_API void ConvBufferXYZToGrey<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_10( T, U )   template ULIS3_API void ConvBufferYxyToGrey<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_11( T, U )   template ULIS3_API void ConvBufferGreyToRGB<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_12( T, U )   template ULIS3_API void ConvBufferRGBToRGB<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_13( T, U )   template ULIS3_API void ConvBufferHSVToRGB<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_14( T, U )   template ULIS3_API void ConvBufferHSLToRGB<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_15( T, U )   template ULIS3_API void ConvBufferCMYToRGB<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_16( T, U )   template ULIS3_API void ConvBufferCMYKToRGB<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_17( T, U )   template ULIS3_API void ConvBufferYUVToRGB<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_18( T, U )   template ULIS3_API void ConvBufferLabToRGB<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_19( T, U )   template ULIS3_API void ConvBufferXYZToRGB<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_20( T, U )   template ULIS3_API void ConvBufferYxyToRGB<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_21( T, U )   template ULIS3_API void ConvBufferGreyToHSV<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_22( T, U )   template ULIS3_API void ConvBufferRGBToHSV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_23( T, U )   template ULIS3_API void ConvBufferHSVToHSV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_24( T, U )   template ULIS3_API void ConvBufferHSLToHSV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_25( T, U )   template ULIS3_API void ConvBufferCMYToHSV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_26( T, U )   template ULIS3_API void ConvBufferCMYKToHSV<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_27( T, U )   template ULIS3_API void ConvBufferYUVToHSV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_28( T, U )   template ULIS3_API void ConvBufferLabToHSV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_29( T, U )   template ULIS3_API void ConvBufferXYZToHSV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_30( T, U )   template ULIS3_API void ConvBufferYxyToHSV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_31( T, U )   template ULIS3_API void ConvBufferGreyToHSL<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_32( T, U )   template ULIS3_API void ConvBufferRGBToHSL<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_33( T, U )   template ULIS3_API void ConvBufferHSVToHSL<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_34( T, U )   template ULIS3_API void ConvBufferHSLToHSL<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_35( T, U )   template ULIS3_API void ConvBufferCMYToHSL<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_36( T, U )   template ULIS3_API void ConvBufferCMYKToHSL<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_37( T, U )   template ULIS3_API void ConvBufferYUVToHSL<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_38( T, U )   template ULIS3_API void ConvBufferLabToHSL<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_39( T, U )   template ULIS3_API void ConvBufferXYZToHSL<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_40( T, U )   template ULIS3_API void ConvBufferYxyToHSL<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_41( T, U )   template ULIS3_API void ConvBufferGreyToCMY<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_42( T, U )   template ULIS3_API void ConvBufferRGBToCMY<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_43( T, U )   template ULIS3_API void ConvBufferHSVToCMY<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_44( T, U )   template ULIS3_API void ConvBufferHSLToCMY<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_45( T, U )   template ULIS3_API void ConvBufferCMYToCMY<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_46( T, U )   template ULIS3_API void ConvBufferCMYKToCMY<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_47( T, U )   template ULIS3_API void ConvBufferYUVToCMY<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_48( T, U )   template ULIS3_API void ConvBufferLabToCMY<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_49( T, U )   template ULIS3_API void ConvBufferXYZToCMY<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_50( T, U )   template ULIS3_API void ConvBufferYxyToCMY<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_51( T, U )   template ULIS3_API void ConvBufferGreyToCMYK< T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_52( T, U )   template ULIS3_API void ConvBufferRGBToCMYK<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_53( T, U )   template ULIS3_API void ConvBufferHSVToCMYK<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_54( T, U )   template ULIS3_API void ConvBufferHSLToCMYK<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_55( T, U )   template ULIS3_API void ConvBufferCMYToCMYK<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_56( T, U )   template ULIS3_API void ConvBufferCMYKToCMYK< T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_57( T, U )   template ULIS3_API void ConvBufferYUVToCMYK<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_58( T, U )   template ULIS3_API void ConvBufferLabToCMYK<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_59( T, U )   template ULIS3_API void ConvBufferXYZToCMYK<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_60( T, U )   template ULIS3_API void ConvBufferYxyToCMYK<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_61( T, U )   template ULIS3_API void ConvBufferGreyToYUV<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_62( T, U )   template ULIS3_API void ConvBufferRGBToYUV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_63( T, U )   template ULIS3_API void ConvBufferHSVToYUV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_64( T, U )   template ULIS3_API void ConvBufferHSLToYUV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_65( T, U )   template ULIS3_API void ConvBufferCMYToYUV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_66( T, U )   template ULIS3_API void ConvBufferCMYKToYUV<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_67( T, U )   template ULIS3_API void ConvBufferYUVToYUV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_68( T, U )   template ULIS3_API void ConvBufferLabToYUV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_69( T, U )   template ULIS3_API void ConvBufferXYZToYUV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_70( T, U )   template ULIS3_API void ConvBufferYxyToYUV<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_71( T, U )   template ULIS3_API void ConvBufferGreyToLab<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_72( T, U )   template ULIS3_API void ConvBufferRGBToLab<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_73( T, U )   template ULIS3_API void ConvBufferHSVToLab<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_74( T, U )   template ULIS3_API void ConvBufferHSLToLab<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_75( T, U )   template ULIS3_API void ConvBufferCMYToLab<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_76( T, U )   template ULIS3_API void ConvBufferCMYKToLab<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_77( T, U )   template ULIS3_API void ConvBufferYUVToLab<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_78( T, U )   template ULIS3_API void ConvBufferLabToLab<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_79( T, U )   template ULIS3_API void ConvBufferXYZToLab<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_80( T, U )   template ULIS3_API void ConvBufferYxyToLab<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_81( T, U )   template ULIS3_API void ConvBufferGreyToXYZ<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_82( T, U )   template ULIS3_API void ConvBufferRGBToXYZ<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_83( T, U )   template ULIS3_API void ConvBufferHSVToXYZ<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_84( T, U )   template ULIS3_API void ConvBufferHSLToXYZ<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_85( T, U )   template ULIS3_API void ConvBufferCMYToXYZ<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_86( T, U )   template ULIS3_API void ConvBufferCMYKToXYZ<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_87( T, U )   template ULIS3_API void ConvBufferYUVToXYZ<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_88( T, U )   template ULIS3_API void ConvBufferLabToXYZ<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_89( T, U )   template ULIS3_API void ConvBufferXYZToXYZ<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_90( T, U )   template ULIS3_API void ConvBufferYxyToXYZ<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_91( T, U )   template ULIS3_API void ConvBufferGreyToYxy<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_92( T, U )   template ULIS3_API void ConvBufferRGBToYxy<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_93( T, U )   template ULIS3_API void ConvBufferHSVToYxy<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_94( T, U )   template ULIS3_API void ConvBufferHSLToYxy<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_95( T, U )   template ULIS3_API void ConvBufferCMYToYxy<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_96( T, U )   template ULIS3_API void ConvBufferCMYKToYxy<  T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_97( T, U )   template ULIS3_API void ConvBufferYUVToYxy<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_98( T, U )   template ULIS3_API void ConvBufferLabToYxy<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_99( T, U )   template ULIS3_API void ConvBufferXYZToYxy<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
#define X_DO_FF( T, U )   template ULIS3_API void ConvBufferYxyToYxy<   T, U >( const FFormat& iSrcFormat, const uint8* iSrc, const FFormat& iDstFormat, uint8* iDst, uint32 iLen );
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_01 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_02 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_03 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_04 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_05 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_06 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_07 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_08 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_09 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_10 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_11 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_12 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_13 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_14 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_15 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_16 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_17 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_18 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_19 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_20 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_21 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_22 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_23 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_24 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_25 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_26 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_27 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_28 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_29 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_30 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_31 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_32 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_33 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_34 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_35 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_36 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_37 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_38 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_39 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_40 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_41 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_42 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_43 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_44 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_45 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_46 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_47 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_48 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_49 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_50 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_51 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_52 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_53 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_54 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_55 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_56 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_57 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_58 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_59 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_60 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_61 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_62 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_63 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_64 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_65 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_66 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_67 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_68 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_69 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_70 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_71 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_72 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_73 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_74 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_75 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_76 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_77 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_78 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_79 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_80 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_81 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_82 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_83 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_84 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_85 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_86 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_87 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_88 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_89 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_90 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_91 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_92 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_93 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_94 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_95 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_96 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_97 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_98 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_99 )
ULIS3_FOR_ALL_TYPES_COMBINATIONS_DO( X_DO_FF )
#undef X_DO_01
#undef X_DO_02
#undef X_DO_03
#undef X_DO_04
#undef X_DO_05
#undef X_DO_06
#undef X_DO_07
#undef X_DO_08
#undef X_DO_09
#undef X_DO_10
#undef X_DO_11
#undef X_DO_12
#undef X_DO_13
#undef X_DO_14
#undef X_DO_15
#undef X_DO_16
#undef X_DO_17
#undef X_DO_18
#undef X_DO_19
#undef X_DO_20
#undef X_DO_21
#undef X_DO_22
#undef X_DO_23
#undef X_DO_24
#undef X_DO_25
#undef X_DO_26
#undef X_DO_27
#undef X_DO_28
#undef X_DO_29
#undef X_DO_30
#undef X_DO_31
#undef X_DO_32
#undef X_DO_33
#undef X_DO_34
#undef X_DO_35
#undef X_DO_36
#undef X_DO_37
#undef X_DO_38
#undef X_DO_39
#undef X_DO_40
#undef X_DO_41
#undef X_DO_42
#undef X_DO_43
#undef X_DO_44
#undef X_DO_45
#undef X_DO_46
#undef X_DO_47
#undef X_DO_48
#undef X_DO_49
#undef X_DO_50
#undef X_DO_51
#undef X_DO_52
#undef X_DO_53
#undef X_DO_54
#undef X_DO_55
#undef X_DO_56
#undef X_DO_57
#undef X_DO_58
#undef X_DO_59
#undef X_DO_60
#undef X_DO_61
#undef X_DO_62
#undef X_DO_63
#undef X_DO_64
#undef X_DO_65
#undef X_DO_66
#undef X_DO_67
#undef X_DO_68
#undef X_DO_69
#undef X_DO_70
#undef X_DO_71
#undef X_DO_72
#undef X_DO_73
#undef X_DO_74
#undef X_DO_75
#undef X_DO_76
#undef X_DO_77
#undef X_DO_78
#undef X_DO_79
#undef X_DO_80
#undef X_DO_81
#undef X_DO_82
#undef X_DO_83
#undef X_DO_84
#undef X_DO_85
#undef X_DO_86
#undef X_DO_87
#undef X_DO_88
#undef X_DO_89
#undef X_DO_90
#undef X_DO_91
#undef X_DO_92
#undef X_DO_93
#undef X_DO_94
#undef X_DO_95
#undef X_DO_96
#undef X_DO_97
#undef X_DO_98
#undef X_DO_99
#undef X_DO_FF

ULIS3_NAMESPACE_END

