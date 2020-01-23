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

// Mono Mem Generic
#include "Blend/Dispatch/Generic/Mono/MEM/BlendMono_Separable_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/Mono/MEM/BlendMono_NonSeparable_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/Mono/MEM/BlendMono_Misc_MEM_Generic.ipp"

ULIS2_NAMESPACE_BEGIN
template< typename T >
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_imp( uint32 iFormat, eBlendingMode iBlendingMode, eAlphaMode iAlphaMode, bool iSubpixel, const FPerf& iPerf ) {
    if( iPerf.UseMT() ) {
        if( iPerf.UseAVX2() ) {
            if( iSubpixel ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : return  nullptr;
                    case BMQ_NONSEPARABLE   : return  nullptr;
                    case BMQ_MISC           : return  nullptr;
                }
            } else {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : return  nullptr;
                    case BMQ_NONSEPARABLE   : return  nullptr;
                    case BMQ_MISC           : return  nullptr;
                }
            }
        } else if( iPerf.UseSSE4_2() ) {
            if( iSubpixel ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : return  nullptr;
                    case BMQ_NONSEPARABLE   : return  nullptr;
                    case BMQ_MISC           : return  nullptr;
                }
            } else {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : return  nullptr;
                    case BMQ_NONSEPARABLE   : return  nullptr;
                    case BMQ_MISC           : return  nullptr;
                }
            }
        } else {
            if( iSubpixel ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : return  nullptr;
                    case BMQ_NONSEPARABLE   : return  nullptr;
                    case BMQ_MISC           : return  nullptr;
                }
            } else {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : return  nullptr;
                    case BMQ_NONSEPARABLE   : return  nullptr;
                    case BMQ_MISC           : return  nullptr;
                }
            }
        }
    } else {
        if( iPerf.UseAVX2() ) {
            if( iSubpixel ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : return  nullptr;
                    case BMQ_NONSEPARABLE   : return  nullptr;
                    case BMQ_MISC           : return  nullptr;
                }
            } else {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : return  nullptr;
                    case BMQ_NONSEPARABLE   : return  nullptr;
                    case BMQ_MISC           : return  nullptr;
                }
            }
        } else if( iPerf.UseSSE4_2() ) {
            if( iSubpixel ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : return  nullptr;
                    case BMQ_NONSEPARABLE   : return  nullptr;
                    case BMQ_MISC           : return  nullptr;
                }
            } else {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : return  nullptr;
                    case BMQ_NONSEPARABLE   : return  nullptr;
                    case BMQ_MISC           : return  nullptr;
                }
            }
        } else {
            if( iSubpixel ) {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : return  nullptr;
                    case BMQ_NONSEPARABLE   : return  nullptr;
                    case BMQ_MISC           : return  nullptr;
                }
            } else {
                switch( BlendingModeQualifier( iBlendingMode ) ) {
                    case BMQ_SEPARABLE      : return  QueryDispatchedBlendFunctionForParameters_Mono_Separable_MEM< T >( iBlendingMode, iAlphaMode, iSubpixel );
                    case BMQ_NONSEPARABLE   : return  nullptr;
                    case BMQ_MISC           : return  nullptr;
                }
            }
        }
    }
    ULIS2_ASSERT( false, "Bad input no dispatch path found" );
    return  nullptr;
}

fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters( uint32 iFormat, eBlendingMode iBlendingMode, eAlphaMode iAlphaMode, bool iSubpixel, const FPerf& iPerf ) {
    switch( static_cast< eType >( ULIS2_R_TYPE( iFormat ) ) ) {
        case TYPE_UINT8     : return  QueryDispatchedBlendFunctionForParameters_imp< uint8   >( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf ); break;
        case TYPE_UINT16    : return  QueryDispatchedBlendFunctionForParameters_imp< uint16  >( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf ); break;
        case TYPE_UINT32    : return  QueryDispatchedBlendFunctionForParameters_imp< uint32  >( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf ); break;
        case TYPE_UFLOAT    : return  QueryDispatchedBlendFunctionForParameters_imp< ufloat  >( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf ); break;
        case TYPE_UDOUBLE   : return  QueryDispatchedBlendFunctionForParameters_imp< udouble >( iFormat, iBlendingMode, iAlphaMode, iSubpixel, iPerf ); break;
        default             : ULIS2_ASSERT( false, "Bad input format !" ); return  nullptr;
    }
}
ULIS2_NAMESPACE_END

