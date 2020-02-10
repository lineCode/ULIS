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
#include "Base/Core.h"
#include "Transform/Transform.h"
#include "Transform/Methods.h"
// Dispatch
#include "Transform/Dispatch/Generic/TransformMT_NearestNeighbour_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformMT_Bilinear_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformMT_Bicubic_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformMT_Area_MEM_Generic.ipp"

ULIS2_NAMESPACE_BEGIN
// Generic Dispatcher
template< typename T >
fpDispatchedTransformFunc
QueryDispatchedTransformFunctionForParameters_Generic( uint32 iFormat, eResamplingMethod iInterpolationType, const FPerf& iPerf, const FCPU& iCPU ) {
    return  nullptr;
}

// Generic Dispatcher Selector
template< typename T >
fpDispatchedTransformFunc
QueryDispatchedTransformFunctionForParameters_imp( uint32 iFormat, eResamplingMethod iInterpolationType, const FPerf& iPerf, const FCPU& iCPU ) {
    return  QueryDispatchedTransformFunctionForParameters_Generic< T >( iFormat, iInterpolationType, iPerf, iCPU );
}

// Type Dispatcher Selector
fpDispatchedTransformFunc
QueryDispatchedTransformFunctionForParameters( uint32 iFormat, eResamplingMethod iInterpolationType, const FPerf& iPerf, const FCPU& iCPU ) {
    switch( static_cast< eType >( ULIS2_R_TYPE( iFormat ) ) ) {
        case TYPE_UINT8     : return  QueryDispatchedTransformFunctionForParameters_imp< uint8   >( iFormat, iInterpolationType, iPerf, iCPU ); break;
        case TYPE_UINT16    : return  QueryDispatchedTransformFunctionForParameters_imp< uint16  >( iFormat, iInterpolationType, iPerf, iCPU ); break;
        case TYPE_UINT32    : return  QueryDispatchedTransformFunctionForParameters_imp< uint32  >( iFormat, iInterpolationType, iPerf, iCPU ); break;
        case TYPE_UFLOAT    : return  QueryDispatchedTransformFunctionForParameters_imp< ufloat  >( iFormat, iInterpolationType, iPerf, iCPU ); break;
        case TYPE_UDOUBLE   : return  QueryDispatchedTransformFunctionForParameters_imp< udouble >( iFormat, iInterpolationType, iPerf, iCPU ); break;
        default             : ULIS2_ASSERT( false, "Bad input format !" ); return  nullptr;
    }
}

ULIS2_NAMESPACE_END

