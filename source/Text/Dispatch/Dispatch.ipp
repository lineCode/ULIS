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
QueryDispatchedTextFunctionForParameters_Generic( const FTextInfo& iTextInfo ) {
    return  &TraceTextMono_Generic< T >;
}

// Generic Dispatcher Selector
template< typename T >
fpDispatchedTextFunc
QueryDispatchedTextFunctionForParameters_imp( const FTextInfo& iTextInfo ) {
    return  QueryDispatchedTextFunctionForParameters_Generic< T >( iTextInfo );
}

// Type Dispatcher Selector
fpDispatchedTextFunc
QueryDispatchedTextFunctionForParameters( const FTextInfo& iTextInfo ) {
    switch( iTextInfo.destination->Type() ) {
        case TYPE_UINT8     : return  QueryDispatchedTextFunctionForParameters_imp< uint8   >( iTextInfo ); break;
        case TYPE_UINT16    : return  QueryDispatchedTextFunctionForParameters_imp< uint16  >( iTextInfo ); break;
        case TYPE_UINT32    : return  QueryDispatchedTextFunctionForParameters_imp< uint32  >( iTextInfo ); break;
        case TYPE_UFLOAT    : return  QueryDispatchedTextFunctionForParameters_imp< ufloat  >( iTextInfo ); break;
        case TYPE_UDOUBLE   : return  QueryDispatchedTextFunctionForParameters_imp< udouble >( iTextInfo ); break;
        default             : ULIS2_FAIL_RET( "Bad input format !", nullptr );
    }
}

ULIS2_NAMESPACE_END

