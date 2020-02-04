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
// MT Mem Generic
#include "Blend/Dispatch/Generic/BlendMT_Separable_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/BlendMT_NonSeparable_CM_DEFAULT_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/BlendMT_NonSeparable_CM_Grey_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/BlendMT_NonSeparable_CM_RGB_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/BlendMT_NonSeparable_CM_CMYK_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/BlendMT_NonSeparable_CM_Lab_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/BlendMT_Misc_MEM_Generic.ipp"
// MT SSE RGBA8
#include "Blend/Dispatch/RGBA8/BlendMT_Separable_SSE_RGBA8.ipp"
#include "Blend/Dispatch/RGBA8/BlendMT_NonSeparable_SSE_RGBA8.ipp"
#include "Blend/Dispatch/RGBA8/BlendMT_Misc_SSE_RGBA8.ipp"

// Note on dispatch:
// First, the appropriate template instanciation is selected for type
// The type dispatcher calls the Generic Dispatcher Selector for T
// Type specialisation can be hooked to select a specialized dispatcher for type
// Such dispatchers may select specific implementations according to layout, format, color model
// The final dispatcher may call the Generic implementations as a fallback, or the specialized implementations if available
// The generic implementation does not provides SSE or AVX implementation as such optimisation cannot be generic without hurting performances.
// If you use a format extensively, you can implement your own specialized dispatcher and implementations.
// Using a plugin system for that could be nice but i'd rather keep all implementations directly within the library.
// - Clement.

ULIS2_NAMESPACE_BEGIN
// Generic Dispatcher
template< typename T >
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_Generic( uint32 iFormat, eBlendingMode iBlendingMode, eAlphaMode iAlphaMode, bool iSubpixel, const FPerf& iPerf, const FCPU& iCPU ) {
    switch( BlendingModeQualifier( iBlendingMode ) ) {
        case BMQ_MISC           : return  ULIS2_SELECT_COMP_OPT( iSubpixel, BlendMT_Misc_MEM_Generic, T );
        case BMQ_SEPARABLE      : return  ULIS2_SELECT_COMP_OPT( iSubpixel, BlendMT_Separable_MEM_Generic, T );
        case BMQ_NONSEPARABLE   :
            switch( static_cast< eColorModel >( ULIS2_R_MODEL( iFormat ) ) ) {
                case CM_ANY:    ULIS2_ASSERT( false, "Bad input model" ); return  nullptr;
                case CM_GREY:   return  ULIS2_SELECT_COMP_OPT( iSubpixel, BlendMT_NonSeparable_CM_Grey_MEM_Generic,      T );
                case CM_RGB:    return  ULIS2_SELECT_COMP_OPT( iSubpixel, BlendMT_NonSeparable_CM_RGB_MEM_Generic,       T );
                case CM_CMYK:   return  ULIS2_SELECT_COMP_OPT( iSubpixel, BlendMT_NonSeparable_CM_CMYK_MEM_Generic,      T );
                case CM_Lab:    return  ULIS2_SELECT_COMP_OPT( iSubpixel, BlendMT_NonSeparable_CM_Lab_MEM_Generic,       T );
                default:        return  ULIS2_SELECT_COMP_OPT( iSubpixel, BlendMT_NonSeparable_CM_DEFAULT_MEM_Generic,   T );
            }
    }
    ULIS2_ASSERT( false, "Bad input no dispatch path found" );
    return  nullptr;
}

// RGBA8 Dispatcher
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_RGBA8( uint32 iFormat, eBlendingMode iBlendingMode, eAlphaMode iAlphaMode, bool iSubpixel, const FPerf& iPerf, const FCPU& iCPU ) {
    switch( BlendingModeQualifier( iBlendingMode ) ) {
        case BMQ_MISC           : return  ULIS2_SELECT_COMP_OP( iSubpixel, BlendMT_Misc_SSE_RGBA8 );
        case BMQ_SEPARABLE      : return  ULIS2_SELECT_COMP_OP( iSubpixel, BlendMT_Separable_SSE_RGBA8 );
        case BMQ_NONSEPARABLE   : return  ULIS2_SELECT_COMP_OP( iSubpixel, BlendMT_NonSeparable_SSE_RGBA8 );
    }
    ULIS2_ASSERT( false, "Bad input no dispatch path found" );
    return  nullptr;
}

// Generic Dispatcher Selector
template< typename T >
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_imp( uint32 iFormat, eBlendingMode iBlendingMode, eAlphaMode iAlphaMode, bool iSubpixel, const FPerf& iPerf, const FCPU& iCPU ) {
    return  QueryDispatchedBlendFunctionForParameters_Generic< T >( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf, iCPU );
}

// RGBA8 Dispatcher Selector
template<>
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_imp< uint8 >( uint32 iFormat, eBlendingMode iBlendingMode, eAlphaMode iAlphaMode, bool iSubpixel, const FPerf& iPerf, const FCPU& iCPU ) {
    // Check RGBA8 Signature, any layout
    if(     static_cast< bool >(        ULIS2_R_ALPHA( iFormat )    ) == true
        &&  static_cast< eColorModel >( ULIS2_R_MODEL( iFormat )    ) == CM_RGB
        &&  static_cast< uint8 >(       ULIS2_R_CHANNELS( iFormat ) ) == 3_u8   ) {
        // Dispatch optimisation RGBA8
        return  QueryDispatchedBlendFunctionForParameters_RGBA8( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf, iCPU );
    }

    // Fallback Generic
    return  QueryDispatchedBlendFunctionForParameters_Generic< uint8 >( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf, iCPU );
}

// Type Dispatcher Selector
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters( uint32 iFormat, eBlendingMode iBlendingMode, eAlphaMode iAlphaMode, bool iSubpixel, const FPerf& iPerf, const FCPU& iCPU ) {
    switch( static_cast< eType >( ULIS2_R_TYPE( iFormat ) ) ) {
        case TYPE_UINT8     : return  QueryDispatchedBlendFunctionForParameters_imp< uint8   >( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf, iCPU ); break;
        case TYPE_UINT16    : return  QueryDispatchedBlendFunctionForParameters_imp< uint16  >( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf, iCPU ); break;
        case TYPE_UINT32    : return  QueryDispatchedBlendFunctionForParameters_imp< uint32  >( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf, iCPU ); break;
        case TYPE_UFLOAT    : return  QueryDispatchedBlendFunctionForParameters_imp< ufloat  >( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf, iCPU ); break;
        case TYPE_UDOUBLE   : return  QueryDispatchedBlendFunctionForParameters_imp< udouble >( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf, iCPU ); break;
        default             : ULIS2_ASSERT( false, "Bad input format !" ); return  nullptr;
    }
}

ULIS2_NAMESPACE_END

