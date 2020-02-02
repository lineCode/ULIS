// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Dispatch.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Text entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Text/Dispatch/Generic/TraceTextMono_Generic.ipp"

ULIS2_NAMESPACE_BEGIN
// Generic Dispatcher
template< typename T >
fpDispatchedTextFunc
QueryDispatchedBlendFunctionForParameters_Generic( uint32 iFormat, bool iAntialiasing, const FPerf& iPerf, const FCPU& iCPU ) {
    return  &TraceTextMono_Generic< T >;
}

// Generic Dispatcher Selector
template< typename T >
fpDispatchedTextFunc
QueryDispatchedBlendFunctionForParameters_imp( uint32 iFormat, bool iAntialiasing, const FPerf& iPerf, const FCPU& iCPU ) {
    return  QueryDispatchedBlendFunctionForParameters_Generic< T >( iFormat, iAntialiasing, iPerf, iCPU );
}

// Type Dispatcher Selector
fpDispatchedTextFunc
QueryDispatchedTextFunctionForParameters( uint32 iFormat, bool iAntialiasing, const FPerf& iPerf, const FCPU& iCPU ) {
    switch( static_cast< eType >( ULIS2_R_TYPE( iFormat ) ) ) {
        case TYPE_UINT8     : return  QueryDispatchedBlendFunctionForParameters_imp< uint8   >( iFormat, iAntialiasing, iPerf, iCPU ); break;
        case TYPE_UINT16    : return  QueryDispatchedBlendFunctionForParameters_imp< uint16  >( iFormat, iAntialiasing, iPerf, iCPU ); break;
        case TYPE_UINT32    : return  QueryDispatchedBlendFunctionForParameters_imp< uint32  >( iFormat, iAntialiasing, iPerf, iCPU ); break;
        case TYPE_UFLOAT    : return  QueryDispatchedBlendFunctionForParameters_imp< ufloat  >( iFormat, iAntialiasing, iPerf, iCPU ); break;
        case TYPE_UDOUBLE   : return  QueryDispatchedBlendFunctionForParameters_imp< udouble >( iFormat, iAntialiasing, iPerf, iCPU ); break;
        default             : ULIS2_ASSERT( false, "Bad input format !" ); return  nullptr;
    }
}

ULIS2_NAMESPACE_END

