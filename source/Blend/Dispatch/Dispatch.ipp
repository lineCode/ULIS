// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Dispatch.ipp
* @author       Clement Berthaud
* @brief        This file provides the declaration for the generic Blend entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Base/HostDeviceInfo.h"
#include "Blend/Modes.h"
#include "Blend/Func/ModesUtils.ipp"
#include "Blend/Dispatch/BlendInfo.h"
#include "Blend/Dispatch/Generic/BlendMT_Separable_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/BlendMT_NonSeparable_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/BlendMT_Misc_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/AlphaBlendMT_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/TiledBlendMT_Separable_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/TiledBlendMT_NonSeparable_MEM_Generic.ipp"
#include "Blend/Dispatch/Generic/TiledBlendMT_Misc_MEM_Generic.ipp"

#ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
#include "Blend/Dispatch/RGBA8/BlendMT_Separable_SSE_RGBA8.ipp"
#include "Blend/Dispatch/RGBA8/BlendMT_NonSeparable_SSE_RGBA8.ipp"
#include "Blend/Dispatch/RGBA8/TiledBlendMT_Separable_SSE_RGBA8.ipp"
#include "Blend/Dispatch/RGBA8/TiledBlendMT_NonSeparable_SSE_RGBA8.ipp"
#include "Blend/Dispatch/RGBA8/AlphaBlendMT_SSE_RGBA8.ipp"
#endif

#ifdef ULIS3_COMPILETIME_AVX2_SUPPORT
#include "Blend/Dispatch/RGBA8/BlendMT_Separable_AVX_RGBA8.ipp"
#include "Blend/Dispatch/RGBA8/TiledBlendMT_Separable_AVX_RGBA8.ipp"
#include "Blend/Dispatch/RGBA8/AlphaBlendMT_AVX_RGBA8.ipp"
#endif

#define ULIS3_SELECT_COMP_OP(   iSubpixel, _FUNCTION )      iSubpixel ? & _FUNCTION ## _Subpixel : & _FUNCTION
#define ULIS3_SELECT_COMP_OPT(  iSubpixel, _FUNCTION, _T )  iSubpixel ? & _FUNCTION ## _Subpixel < _T > : & _FUNCTION < _T >

ULIS3_NAMESPACE_BEGIN
typedef void (*fpDispatchedBlendFunc)( std::shared_ptr< const _FBlendInfoPrivate > iBlendParams );
typedef void (*fpDispatchedAlphaBlendFunc)( std::shared_ptr< const _FBlendInfoPrivate > iBlendParams );
typedef void (*fpDispatchedTiledBlendFunc)( std::shared_ptr< const _FBlendInfoPrivate > iBlendParams );

/////////////////////////////////////////////////////
// Dispatch Blend
template< typename T >
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_Generic( const _FBlendInfoPrivate& iInfo ) {
    switch( BlendingModeQualifier( iInfo.blendingMode ) ) {
        case BMQ_MISC           : return  ULIS3_SELECT_COMP_OPT( iInfo.subpixelFlag, BlendMT_Misc_MEM_Generic,          T );
        case BMQ_SEPARABLE      : return  ULIS3_SELECT_COMP_OPT( iInfo.subpixelFlag, BlendMT_Separable_MEM_Generic,     T );
        case BMQ_NONSEPARABLE   : return  ULIS3_SELECT_COMP_OPT( iInfo.subpixelFlag, BlendMT_NonSeparable_MEM_Generic,  T );
    }
    return  nullptr;
}


fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_RGBA8( const _FBlendInfoPrivate& iInfo ) {
    switch( BlendingModeQualifier( iInfo.blendingMode ) ) {
        case BMQ_MISC: {
            return  ULIS3_SELECT_COMP_OPT( iInfo.subpixelFlag, BlendMT_Misc_MEM_Generic, uint8  );
        }

        case BMQ_SEPARABLE: {
            #ifdef ULIS3_COMPILETIME_AVX2_SUPPORT
                if( iInfo.perfIntent & ULIS3_PERF_AVX2 && iInfo.hostDeviceInfo->HW_AVX2 )
                    return  ULIS3_SELECT_COMP_OP( iInfo.subpixelFlag, BlendMT_Separable_AVX_RGBA8 );
                else
            #endif
            #ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
                if( iInfo.hostDeviceInfo->HW_SSE42 )
                    return  ULIS3_SELECT_COMP_OP( iInfo.subpixelFlag, BlendMT_Separable_SSE_RGBA8 );
                else
            #endif
                    return  ULIS3_SELECT_COMP_OPT( iInfo.subpixelFlag, BlendMT_Separable_MEM_Generic,  uint8 );
        }

        case BMQ_NONSEPARABLE: {
            #ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
                if( iInfo.hostDeviceInfo->HW_SSE42 )
                    return  ULIS3_SELECT_COMP_OP( iInfo.subpixelFlag, BlendMT_NonSeparable_SSE_RGBA8 );
                else
            #endif
                    return  ULIS3_SELECT_COMP_OPT( iInfo.subpixelFlag, BlendMT_NonSeparable_MEM_Generic, uint8 );
        }
    }
    return  nullptr;
}


template< typename T >
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_imp( const _FBlendInfoPrivate& iInfo ) {
    return  QueryDispatchedBlendFunctionForParameters_Generic< T >( iInfo );
}


template<>
fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters_imp< uint8 >( const _FBlendInfoPrivate& iInfo ) {
    // RGBA8 Signature, any layout
    if( iInfo.source->HasAlpha()
     && iInfo.source->NumColorChannels()    == 3
     && iInfo.source->Model()               == CM_RGB
     && iInfo.perfIntent & ULIS3_PERF_TSPEC
     && ( iInfo.perfIntent & ULIS3_PERF_SSE42 || iInfo.perfIntent & ULIS3_PERF_AVX2 )
     && ( iInfo.hostDeviceInfo->HW_SSE42 || iInfo.hostDeviceInfo->HW_AVX2 ) ) {
        return  QueryDispatchedBlendFunctionForParameters_RGBA8( iInfo );
    }

    // Generic Fallback
    return  QueryDispatchedBlendFunctionForParameters_Generic< uint8 >( iInfo );
}


fpDispatchedBlendFunc
QueryDispatchedBlendFunctionForParameters( const _FBlendInfoPrivate& iInfo ) {
    switch( iInfo.source->Type() ) {
        case TYPE_UINT8     : return  QueryDispatchedBlendFunctionForParameters_imp< uint8   >( iInfo );
        case TYPE_UINT16    : return  QueryDispatchedBlendFunctionForParameters_imp< uint16  >( iInfo );
        case TYPE_UINT32    : return  QueryDispatchedBlendFunctionForParameters_imp< uint32  >( iInfo );
        case TYPE_UFLOAT    : return  QueryDispatchedBlendFunctionForParameters_imp< ufloat  >( iInfo );
        case TYPE_UDOUBLE   : return  QueryDispatchedBlendFunctionForParameters_imp< udouble >( iInfo );
    }
    return  nullptr;
}
/////////////////////////////////////////////////////
// Dispatch Alpha Blend

template< typename T >
fpDispatchedAlphaBlendFunc
QueryDispatchedAlphaBlendFunctionForParameters_Generic( const _FBlendInfoPrivate& iInfo ) {
    return  ULIS3_SELECT_COMP_OPT( iInfo.subpixelFlag, AlphaBlendMT_Separable_MEM_Generic, T );
}


fpDispatchedAlphaBlendFunc
QueryDispatchedAlphaBlendFunctionForParameters_RGBA8( const _FBlendInfoPrivate& iInfo ) {

    #ifdef ULIS3_COMPILETIME_AVX2_SUPPORT
        if( iInfo.perfIntent & ULIS3_PERF_AVX2 && iInfo.hostDeviceInfo->HW_AVX2 )
            return  ULIS3_SELECT_COMP_OP( iInfo.subpixelFlag, AlphaBlendMT_Separable_AVX_RGBA8 );
        else
    #endif
    #ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
        if( iInfo.hostDeviceInfo->HW_SSE42 )
            return  ULIS3_SELECT_COMP_OP( iInfo.subpixelFlag, AlphaBlendMT_Separable_SSE_RGBA8 );
        else
    #endif
            return  ULIS3_SELECT_COMP_OPT( iInfo.subpixelFlag, AlphaBlendMT_Separable_MEM_Generic, uint8 );
}


template< typename T >
fpDispatchedAlphaBlendFunc
QueryDispatchedAlphaBlendFunctionForParameters_imp( const _FBlendInfoPrivate& iInfo ) {
    return  QueryDispatchedAlphaBlendFunctionForParameters_Generic< T >( iInfo );
}


template<>
fpDispatchedAlphaBlendFunc
QueryDispatchedAlphaBlendFunctionForParameters_imp< uint8 >( const _FBlendInfoPrivate& iInfo ) {
    // RGBA8 Signature, any layout
    if( iInfo.source->HasAlpha()
     && iInfo.source->NumColorChannels()    == 3
     && iInfo.source->Model()               == CM_RGB
     && iInfo.perfIntent & ULIS3_PERF_TSPEC
     && ( iInfo.perfIntent & ULIS3_PERF_SSE42 || iInfo.perfIntent & ULIS3_PERF_AVX2 )
     && ( iInfo.hostDeviceInfo->HW_SSE42 || iInfo.hostDeviceInfo->HW_AVX2 ) ) {
        return  QueryDispatchedAlphaBlendFunctionForParameters_RGBA8( iInfo );
    }

    // Generic Fallback
    return  QueryDispatchedAlphaBlendFunctionForParameters_Generic< uint8 >( iInfo );
}


fpDispatchedAlphaBlendFunc
QueryDispatchedAlphaBlendFunctionForParameters( const _FBlendInfoPrivate& iInfo ) {
    switch( iInfo.source->Type() ) {
        case TYPE_UINT8     : return  QueryDispatchedAlphaBlendFunctionForParameters_imp< uint8   >( iInfo );
        case TYPE_UINT16    : return  QueryDispatchedAlphaBlendFunctionForParameters_imp< uint16  >( iInfo );
        case TYPE_UINT32    : return  QueryDispatchedAlphaBlendFunctionForParameters_imp< uint32  >( iInfo );
        case TYPE_UFLOAT    : return  QueryDispatchedAlphaBlendFunctionForParameters_imp< ufloat  >( iInfo );
        case TYPE_UDOUBLE   : return  QueryDispatchedAlphaBlendFunctionForParameters_imp< udouble >( iInfo );
    }
    return  nullptr;
}

/////////////////////////////////////////////////////
// Dispatch Tiled Blend
template< typename T >
fpDispatchedTiledBlendFunc
QueryDispatchedTiledBlendFunctionForParameters_Generic( const _FBlendInfoPrivate& iInfo ) {
    switch( BlendingModeQualifier( iInfo.blendingMode ) ) {
        case BMQ_MISC           : return  TiledBlendMT_Misc_MEM_Generic< T >;
        case BMQ_SEPARABLE      : return  TiledBlendMT_Separable_MEM_Generic< T >;
        case BMQ_NONSEPARABLE   : return  TiledBlendMT_NonSeparable_MEM_Generic< T >;
    }
    return  nullptr;
}


fpDispatchedTiledBlendFunc
QueryDispatchedTiledBlendFunctionForParameters_RGBA8( const _FBlendInfoPrivate& iInfo ) {
    switch( BlendingModeQualifier( iInfo.blendingMode ) ) {
        case BMQ_MISC: {
            return  &TiledBlendMT_Misc_MEM_Generic< uint8 >;
        }

        case BMQ_SEPARABLE: {
            #ifdef ULIS3_COMPILETIME_AVX2_SUPPORT
                if( iInfo.perfIntent & ULIS3_PERF_AVX2 && iInfo.hostDeviceInfo->HW_AVX2 )
                    return  &TiledBlendMT_Separable_AVX_RGBA8;
                else
            #endif
            #ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
                if( iInfo.hostDeviceInfo->HW_SSE42 )
                    return  &TiledBlendMT_Separable_SSE_RGBA8;
                else
            #endif
                    return  &TiledBlendMT_Separable_MEM_Generic< uint8 >;
        }

        case BMQ_NONSEPARABLE: {
            #ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
                if( iInfo.hostDeviceInfo->HW_SSE42 )
                    return  &TiledBlendMT_NonSeparable_SSE_RGBA8;
                else
            #endif
                    return  &TiledBlendMT_NonSeparable_MEM_Generic< uint8 >;
        }
    }
    return  nullptr;
}


template< typename T >
fpDispatchedTiledBlendFunc
QueryDispatchedTiledBlendFunctionForParameters_imp( const _FBlendInfoPrivate& iInfo ) {
    return  QueryDispatchedTiledBlendFunctionForParameters_Generic< T >( iInfo );
}


template<>
fpDispatchedTiledBlendFunc
QueryDispatchedTiledBlendFunctionForParameters_imp< uint8 >( const _FBlendInfoPrivate& iInfo ) {
    // RGBA8 Signature, any layout
    if( iInfo.source->HasAlpha()
     && iInfo.source->NumColorChannels()    == 3
     && iInfo.source->Model()               == CM_RGB
     && iInfo.perfIntent & ULIS3_PERF_TSPEC
     && ( iInfo.perfIntent & ULIS3_PERF_SSE42 || iInfo.perfIntent & ULIS3_PERF_AVX2 )
     && ( iInfo.hostDeviceInfo->HW_SSE42 || iInfo.hostDeviceInfo->HW_AVX2 ) ) {
        return  QueryDispatchedTiledBlendFunctionForParameters_RGBA8( iInfo );
    }

    // Generic Fallback
    return  QueryDispatchedTiledBlendFunctionForParameters_Generic< uint8 >( iInfo );
}


fpDispatchedTiledBlendFunc
QueryDispatchedTiledBlendFunctionForParameters( const _FBlendInfoPrivate& iInfo ) {
    switch( iInfo.source->Type() ) {
        case TYPE_UINT8     : return  QueryDispatchedTiledBlendFunctionForParameters_imp< uint8   >( iInfo );
        case TYPE_UINT16    : return  QueryDispatchedTiledBlendFunctionForParameters_imp< uint16  >( iInfo );
        case TYPE_UINT32    : return  QueryDispatchedTiledBlendFunctionForParameters_imp< uint32  >( iInfo );
        case TYPE_UFLOAT    : return  QueryDispatchedTiledBlendFunctionForParameters_imp< ufloat  >( iInfo );
        case TYPE_UDOUBLE   : return  QueryDispatchedTiledBlendFunctionForParameters_imp< udouble >( iInfo );
    }
    return  nullptr;
}

ULIS3_NAMESPACE_END

