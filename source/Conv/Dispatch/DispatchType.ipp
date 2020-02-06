// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         DispatchType.ipp
* @author       Clement Berthaud
* @brief        This file provides the definition for the type dispatcher for the conv entry point functions
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
//Dispatch
#include "Conv/Dispatch/DispatchModel.ipp"

ULIS2_NAMESPACE_BEGIN
void
ConvBufferDispatchType( tFormat iSrcFormat, const tByte* iSrc, tSize iSrcBytes, tFormat iDstFormat, tByte* iDst, tSize iDstBytes )
{
        switch( static_cast< eType >( ULIS2_R_TYPE( iSrcFormat ) ) ) {
        case TYPE_UINT8: switch( static_cast< eType >( ULIS2_R_TYPE( iDstFormat ) ) ) {
                case TYPE_UINT8:    ConvBufferT< uint8, uint8       >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UINT16:   ConvBufferT< uint8, uint16      >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UINT32:   ConvBufferT< uint8, uint32      >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UFLOAT:   ConvBufferT< uint8, ufloat      >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UDOUBLE:  ConvBufferT< uint8, udouble     >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return; }
        case TYPE_UINT16: switch( static_cast< eType >( ULIS2_R_TYPE( iDstFormat ) ) ) {
                case TYPE_UINT8:    ConvBufferT< uint16, uint8      >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UINT16:   ConvBufferT< uint16, uint16     >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UINT32:   ConvBufferT< uint16, uint32     >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UFLOAT:   ConvBufferT< uint16, ufloat     >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UDOUBLE:  ConvBufferT< uint16, udouble    >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return; }
        case TYPE_UINT32: switch( static_cast< eType >( ULIS2_R_TYPE( iDstFormat ) ) ) {
                case TYPE_UINT8:    ConvBufferT< uint32, uint8      >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UINT16:   ConvBufferT< uint32, uint16     >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UINT32:   ConvBufferT< uint32, uint32     >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UFLOAT:   ConvBufferT< uint32, ufloat     >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UDOUBLE:  ConvBufferT< uint32, udouble    >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return; }
        case TYPE_UFLOAT: switch( static_cast< eType >( ULIS2_R_TYPE( iDstFormat ) ) ) {
                case TYPE_UINT8:    ConvBufferT< ufloat, uint8      >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UINT16:   ConvBufferT< ufloat, uint16     >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UINT32:   ConvBufferT< ufloat, uint32     >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UFLOAT:   ConvBufferT< ufloat, ufloat     >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UDOUBLE:  ConvBufferT< ufloat, udouble    >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return; }
        case TYPE_UDOUBLE: switch( static_cast< eType >( ULIS2_R_TYPE( iDstFormat ) ) ) {
                case TYPE_UINT8:    ConvBufferT< udouble, uint8     >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UINT16:   ConvBufferT< udouble, uint16    >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UINT32:   ConvBufferT< udouble, uint32    >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UFLOAT:   ConvBufferT< udouble, ufloat    >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return;
                case TYPE_UDOUBLE:  ConvBufferT< udouble, udouble   >( iSrcFormat, iSrc, iSrcBytes, iDstFormat, iDst, iDstBytes );  return; }
    }
}
ULIS2_NAMESPACE_END

