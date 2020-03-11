// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Dispatch.ipp
* @author       Clement Berthaud
* @brief        This file provides the dispatched for the transform entry point functions.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Transform/Methods.h"
#include "Transform/Dispatch/TransformInfo.h"
#include "Transform/Dispatch/Generic/TransformMT_NN_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformMT_Bilinear_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformMT_Bicubic_MEM_Generic.ipp"

ULIS2_NAMESPACE_BEGIN
typedef void (*fpDispatchedTransformFunc)( std::shared_ptr< const _FTransformInfoPrivate > );

// Generic Dispatcher
template< typename T >
fpDispatchedTransformFunc
QueryDispatchedTransformFunctionForParameters_Generic( const _FTransformInfoPrivate& iInfo ) {
    switch( iInfo.method ) {
        case INTERP_NN          : return  TransformMT_NN_MEM_Generic< T >;
        case INTERP_BILINEAR    : return  TransformMT_Bilinear_MEM_Generic< T >;
        case INTERP_BICUBIC     : return  TransformMT_Bicubic_MEM_Generic< T >;
    }
    return  nullptr;
}

// Generic Dispatcher Selector
template< typename T >
fpDispatchedTransformFunc
QueryDispatchedTransformFunctionForParameters_imp( const _FTransformInfoPrivate& iInfo ) {
    return  QueryDispatchedTransformFunctionForParameters_Generic< T >( iInfo );
}

// Type Dispatcher Selector
fpDispatchedTransformFunc
QueryDispatchedTransformFunctionForParameters( const _FTransformInfoPrivate& iInfo ) {
    switch( iInfo.source->Type() ) {
        case TYPE_UINT8     : return  QueryDispatchedTransformFunctionForParameters_imp< uint8   >( iInfo ); break;
        case TYPE_UINT16    : return  QueryDispatchedTransformFunctionForParameters_imp< uint16  >( iInfo ); break;
        case TYPE_UINT32    : return  QueryDispatchedTransformFunctionForParameters_imp< uint32  >( iInfo ); break;
        case TYPE_UFLOAT    : return  QueryDispatchedTransformFunctionForParameters_imp< ufloat  >( iInfo ); break;
        case TYPE_UDOUBLE   : return  QueryDispatchedTransformFunctionForParameters_imp< udouble >( iInfo ); break;
    }
    return  nullptr;
}

ULIS2_NAMESPACE_END

