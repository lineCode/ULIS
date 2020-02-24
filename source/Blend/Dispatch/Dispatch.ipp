// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Dispatch.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Blend/Blend.h"
#include "Blend/Modes.h"
#include "Blend/Dispatch/Generic/BlendMT_Separable_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/BlendMT_NonSeparable_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/BlendMT_Misc_MEM_Generic.ipp"
#include "Blend/Dispatch/RGBA8/BlendMT_Separable_SSE_RGBA8.ipp"
#include "Blend/Dispatch/RGBA8/BlendMT_NonSeparable_SSE_RGBA8.ipp"
#include "Blend/Dispatch/RGBA8/BlendMT_Separable_AVX_RGBA8.ipp"

ULIS2_NAMESPACE_BEGIN

/////////////////////////////////////////////////////
// Generic Dispatcher
template< typename T >
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_Generic( const FFormatInfo& iFormatInfo, const FBlendInfo& iBlendParams ) {
    switch( BlendingModeQualifier( iBlendParams.blendingMode ) ) {
        case BMQ_MISC           : return  ULIS2_SELECT_COMP_OPT( iBlendParams.subpixelFlag, BlendMT_Misc_MEM_Generic,       T );
        case BMQ_SEPARABLE      : return  ULIS2_SELECT_COMP_OPT( iBlendParams.subpixelFlag, BlendMT_Separable_MEM_Generic,  T );
        case BMQ_NONSEPARABLE   : return  ULIS2_SELECT_COMP_OPT( iBlendParams.subpixelFlag, BlendMT_NonSeparable_MEM_Generic,  T );
    }
    ULIS2_FAIL_RET( "Bad input no dispatch path found", nullptr );
}

/////////////////////////////////////////////////////
// RGBA8 Dispatcher
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_RGBA8( const FFormatInfo& iFormatInfo, const FBlendInfo& iBlendParams ) {
    switch( BlendingModeQualifier( iBlendParams.blendingMode ) ) {
        case BMQ_MISC:
            return  ULIS2_SELECT_COMP_OPT( iBlendParams.subpixelFlag, BlendMT_Misc_MEM_Generic, uint8  );

        case BMQ_SEPARABLE:
            #ifdef __AVX2__
                if( iBlendParams.perfInfo.intent.UseAVX2() && gCpuInfo.info.HW_AVX2 )
                    return  ULIS2_SELECT_COMP_OP( iBlendParams.subpixelFlag, BlendMT_Separable_AVX_RGBA8 );
                else
            #endif // __AVX2__
            #ifdef __SSE4_2__
                if( gCpuInfo.info.HW_SSE42 )
                    return  ULIS2_SELECT_COMP_OP( iBlendParams.subpixelFlag, BlendMT_Separable_SSE_RGBA8 );
                else
            #endif // __SSE4_2__
                    return  ULIS2_SELECT_COMP_OPT( iBlendParams.subpixelFlag, BlendMT_Separable_MEM_Generic,  uint8 );

        case BMQ_NONSEPARABLE:
            #ifdef __SSE4_2__
                if( gCpuInfo.info.HW_SSE42 )
                    return  ULIS2_SELECT_COMP_OP( iBlendParams.subpixelFlag, BlendMT_NonSeparable_SSE_RGBA8 );
                else
            #endif // __SSE4_2__
                    return  ULIS2_SELECT_COMP_OPT( iBlendParams.subpixelFlag, BlendMT_NonSeparable_MEM_Generic, uint8 );
    }
    ULIS2_FAIL_RET( "Bad input no dispatch path found", nullptr );
}

/////////////////////////////////////////////////////
// Generic Dispatcher Selector
template< typename T >
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_imp( const FFormatInfo& iFormatInfo, const FBlendInfo& iBlendParams ) {
    return  QueryDispatchedBlendFunctionForParameters_Generic< T >( iFormatInfo, iBlendParams );
}

/////////////////////////////////////////////////////
// RGBA8 Dispatcher Selector Specialization
template<>
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_imp< uint8 >( const FFormatInfo& iFormatInfo, const FBlendInfo& iBlendParams ) {
    // RGBA8 Signature, any layout
    if( iFormatInfo.HEA     == 1
     && iFormatInfo.NCC     == 3
     && iFormatInfo.CM      == CM_RGB
     && iBlendParams.perfInfo.intent.UseTSPEC()
     && ( iBlendParams.perfInfo.intent.UseSSE4_2() || iBlendParams.perfInfo.intent.UseAVX2() )
     && ( gCpuInfo.info.HW_SSE42 || gCpuInfo.info.HW_AVX2 ) ) {
        return  QueryDispatchedBlendFunctionForParameters_RGBA8( iFormatInfo, iBlendParams );
    }

    // Generic Fallback
    return  QueryDispatchedBlendFunctionForParameters_Generic< uint8 >( iFormatInfo, iBlendParams );
}

/////////////////////////////////////////////////////
// Type Dispatcher Selector
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters( const FFormatInfo& iFormatInfo, const FBlendInfo& iBlendParams ) {
    switch( iFormatInfo.TP ) {
        case TYPE_UINT8     : return  QueryDispatchedBlendFunctionForParameters_imp< uint8   >( iFormatInfo, iBlendParams ); break;
        case TYPE_UINT16    : return  QueryDispatchedBlendFunctionForParameters_imp< uint16  >( iFormatInfo, iBlendParams ); break;
        case TYPE_UINT32    : return  QueryDispatchedBlendFunctionForParameters_imp< uint32  >( iFormatInfo, iBlendParams ); break;
        case TYPE_UFLOAT    : return  QueryDispatchedBlendFunctionForParameters_imp< ufloat  >( iFormatInfo, iBlendParams ); break;
        case TYPE_UDOUBLE   : return  QueryDispatchedBlendFunctionForParameters_imp< udouble >( iFormatInfo, iBlendParams ); break;
        default             : ULIS2_FAIL_RET( "Bad input format !", nullptr );
    }
}

ULIS2_NAMESPACE_END

