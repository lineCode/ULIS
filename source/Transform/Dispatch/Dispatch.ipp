// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Dispatch.ipp
* @author       Clement Berthaud
* @brief        This file provides the dispatched for the transform entry point functions.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Data/Block.h"
#include "Data/FormatInfo.h"
#include "Transform/Methods.h"
#include "Transform/Dispatch/TransformInfo.h"
#include "Transform/Dispatch/Generic/ResizeMT_NN_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/ResizeMT_Bilinear_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/ResizeMT_Bicubic_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/ResizeMT_Area_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformAffineMT_NN_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformAffineMT_Bilinear_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformAffineMT_Bicubic_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformPerspectiveMT_NN_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformPerspectiveMT_Bilinear_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformPerspectiveMT_Bicubic_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformBezier_NN_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformBezier_Bilinear_MEM_Generic.ipp"
#include "Transform/Dispatch/Generic/TransformBezier_Bicubic_MEM_Generic.ipp"

#ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
#include "Transform/Dispatch/RGBA8/ResizeMT_NN_SSE_RGBA8.ipp"
#include "Transform/Dispatch/RGBA8/ResizeMT_Bilinear_SSE_RGBA8.ipp"
#include "Transform/Dispatch/RGBA8/ResizeMT_Bicubic_SSE_RGBA8.ipp"
#include "Transform/Dispatch/RGBA8/ResizeMT_Area_SSE_RGBA8.ipp"
#include "Transform/Dispatch/RGBA8/TransformAffineMT_NN_SSE_RGBA8.ipp"
#include "Transform/Dispatch/RGBA8/TransformAffineMT_Bilinear_SSE_RGBA8.ipp"
#include "Transform/Dispatch/RGBA8/TransformAffineMT_Bicubic_SSE_RGBA8.ipp"
#include "Transform/Dispatch/RGBA8/TransformPerspectiveMT_NN_SSE_RGBA8.ipp"
#include "Transform/Dispatch/RGBA8/TransformPerspectiveMT_Bilinear_SSE_RGBA8.ipp"
#include "Transform/Dispatch/RGBA8/TransformPerspectiveMT_Bicubic_SSE_RGBA8.ipp"
#include "Transform/Dispatch/RGBA8/TransformBezier_NN_SSE_RGBA8.ipp"
#include "Transform/Dispatch/RGBA8/TransformBezier_Bilinear_SSE_RGBA8.ipp"
#include "Transform/Dispatch/RGBA8/TransformBezier_Bicubic_SSE_RGBA8.ipp"
#endif

ULIS3_NAMESPACE_BEGIN
typedef void (*fpDispatchedTransformFunc)( std::shared_ptr< const _FTransformInfoPrivate > );
typedef void (*fpDispatchedResizeFunc)( std::shared_ptr< const _FResizeInfoPrivate > );
typedef void (*fpDispatchedBezierTransformFunc)( std::shared_ptr< const _FTransformInfoPrivate >, std::shared_ptr< const FBlock >, std::shared_ptr< const FBlock > );
/////////////////////////////////////////////////////
// AFFINE
// Generic Dispatcher
template< typename T >
fpDispatchedTransformFunc
QueryDispatchedTransformAffineFunctionForParameters_Generic( const _FTransformInfoPrivate& iInfo ) {
    switch( iInfo.method ) {
        case INTERP_NN          : return  TransformAffineMT_NN_MEM_Generic< T >;
        case INTERP_BILINEAR    : return  TransformAffineMT_Bilinear_MEM_Generic< T >;
        case INTERP_BICUBIC     : return  TransformAffineMT_Bicubic_MEM_Generic< T >;
    }
    return  nullptr;
}

fpDispatchedTransformFunc
QueryDispatchedTransformAffineFunctionForParameters_RGBA8( const _FTransformInfoPrivate& iInfo ) {
#ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
    if( iInfo.hostDeviceInfo->HW_SSE42 ) {
        switch( iInfo.method ) {
            case INTERP_NN          : return  &TransformAffineMT_NN_SSE_RGBA8;
            case INTERP_BILINEAR    : return  &TransformAffineMT_Bilinear_SSE_RGBA8;
            case INTERP_BICUBIC     : return  &TransformAffineMT_Bicubic_SSE_RGBA8;
        }
    }
    else
#endif
    {
        switch( iInfo.method ) {
            case INTERP_NN          : return  TransformAffineMT_NN_MEM_Generic< uint8 >;
            case INTERP_BILINEAR    : return  TransformAffineMT_Bilinear_MEM_Generic< uint8 >;
            case INTERP_BICUBIC     : return  TransformAffineMT_Bicubic_MEM_Generic< uint8 >;
        }
    }

    return  nullptr;
}

// Generic Dispatcher Selector
template< typename T >
fpDispatchedTransformFunc
QueryDispatchedTransformAffineFunctionForParameters_imp( const _FTransformInfoPrivate& iInfo ) {
    return  QueryDispatchedTransformAffineFunctionForParameters_Generic< T >( iInfo );
}

template<>
fpDispatchedTransformFunc
QueryDispatchedTransformAffineFunctionForParameters_imp< uint8 >( const _FTransformInfoPrivate& iInfo ) {
    // RGBA8 Signature, any layout
    if( iInfo.source->HasAlpha()
     && iInfo.source->NumColorChannels()    == 3
     && iInfo.source->Model()               == CM_RGB
     && iInfo.perfIntent & ULIS3_PERF_TSPEC
     && ( iInfo.perfIntent & ULIS3_PERF_SSE42 || iInfo.perfIntent & ULIS3_PERF_AVX2 )
     && ( iInfo.hostDeviceInfo->HW_SSE42 || iInfo.hostDeviceInfo->HW_AVX2 ) ) {
        return  QueryDispatchedTransformAffineFunctionForParameters_RGBA8( iInfo );
    }

    // Generic Fallback
    return  QueryDispatchedTransformAffineFunctionForParameters_Generic< uint8 >( iInfo );
}

// Type Dispatcher Selector
fpDispatchedTransformFunc
QueryDispatchedTransformAffineFunctionForParameters( const _FTransformInfoPrivate& iInfo ) {
    switch( iInfo.source->Type() ) {
        case TYPE_UINT8     : return  QueryDispatchedTransformAffineFunctionForParameters_imp< uint8   >( iInfo ); break;
        case TYPE_UINT16    : return  QueryDispatchedTransformAffineFunctionForParameters_imp< uint16  >( iInfo ); break;
        case TYPE_UINT32    : return  QueryDispatchedTransformAffineFunctionForParameters_imp< uint32  >( iInfo ); break;
        case TYPE_UFLOAT    : return  QueryDispatchedTransformAffineFunctionForParameters_imp< ufloat  >( iInfo ); break;
        case TYPE_UDOUBLE   : return  QueryDispatchedTransformAffineFunctionForParameters_imp< udouble >( iInfo ); break;
    }
    return  nullptr;
}



/////////////////////////////////////////////////////
// PERSPECTIVE
// Generic Dispatcher
template< typename T >
fpDispatchedTransformFunc
QueryDispatchedTransformPerspectiveFunctionForParameters_Generic( const _FTransformInfoPrivate& iInfo ) {
    switch( iInfo.method ) {
        case INTERP_NN          : return  TransformPerspectiveMT_NN_MEM_Generic< T >;
        case INTERP_BILINEAR    : return  TransformPerspectiveMT_Bilinear_MEM_Generic< T >;
        case INTERP_BICUBIC     : return  TransformPerspectiveMT_Bicubic_MEM_Generic< T >;
    }
    return  nullptr;
}

fpDispatchedTransformFunc
QueryDispatchedTransformPerspectiveFunctionForParameters_RGBA8( const _FTransformInfoPrivate& iInfo ) {
#ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
    if( iInfo.hostDeviceInfo->HW_SSE42 ) {
        switch( iInfo.method ) {
            case INTERP_NN          : return  &TransformPerspectiveMT_NN_SSE_RGBA8;
            case INTERP_BILINEAR    : return  &TransformPerspectiveMT_Bilinear_SSE_RGBA8;
            case INTERP_BICUBIC     : return  &TransformPerspectiveMT_Bicubic_SSE_RGBA8;
        }
    }
    else
#endif
    {
        switch( iInfo.method ) {
            case INTERP_NN          : return  TransformPerspectiveMT_NN_MEM_Generic< uint8 >;
            case INTERP_BILINEAR    : return  TransformPerspectiveMT_Bilinear_MEM_Generic< uint8 >;
            case INTERP_BICUBIC     : return  TransformPerspectiveMT_Bicubic_MEM_Generic< uint8 >;
        }
    }

    return  nullptr;
}

// Generic Dispatcher Selector
template< typename T >
fpDispatchedTransformFunc
QueryDispatchedTransformPerspectiveFunctionForParameters_imp( const _FTransformInfoPrivate& iInfo ) {
    return  QueryDispatchedTransformPerspectiveFunctionForParameters_Generic< T >( iInfo );
}


template<>
fpDispatchedTransformFunc
QueryDispatchedTransformPerspectiveFunctionForParameters_imp< uint8 >( const _FTransformInfoPrivate& iInfo ) {
    // RGBA8 Signature, any layout
    if( iInfo.source->HasAlpha()
     && iInfo.source->NumColorChannels()    == 3
     && iInfo.source->Model()               == CM_RGB
     && iInfo.perfIntent & ULIS3_PERF_TSPEC
     && ( iInfo.perfIntent & ULIS3_PERF_SSE42 || iInfo.perfIntent & ULIS3_PERF_AVX2 )
     && ( iInfo.hostDeviceInfo->HW_SSE42 || iInfo.hostDeviceInfo->HW_AVX2 ) ) {
        return  QueryDispatchedTransformPerspectiveFunctionForParameters_RGBA8( iInfo );
    }

    // Generic Fallback
    return  QueryDispatchedTransformPerspectiveFunctionForParameters_Generic< uint8 >( iInfo );
}


// Type Dispatcher Selector
fpDispatchedTransformFunc
QueryDispatchedTransformPerspectiveFunctionForParameters( const _FTransformInfoPrivate& iInfo ) {
    switch( iInfo.source->Type() ) {
        case TYPE_UINT8     : return  QueryDispatchedTransformPerspectiveFunctionForParameters_imp< uint8   >( iInfo ); break;
        case TYPE_UINT16    : return  QueryDispatchedTransformPerspectiveFunctionForParameters_imp< uint16  >( iInfo ); break;
        case TYPE_UINT32    : return  QueryDispatchedTransformPerspectiveFunctionForParameters_imp< uint32  >( iInfo ); break;
        case TYPE_UFLOAT    : return  QueryDispatchedTransformPerspectiveFunctionForParameters_imp< ufloat  >( iInfo ); break;
        case TYPE_UDOUBLE   : return  QueryDispatchedTransformPerspectiveFunctionForParameters_imp< udouble >( iInfo ); break;
    }
    return  nullptr;
}


/////////////////////////////////////////////////////
// BEZIER
// Generic Dispatcher
template< typename T >
fpDispatchedBezierTransformFunc
QueryDispatchedTransformBezierFunctionForParameters_Generic( const _FTransformInfoPrivate& iInfo ) {
    switch( iInfo.method ) {
        case INTERP_NN          : return  TransformBezierMT_NN_MEM_Generic< T >;
        case INTERP_BILINEAR    : return  TransformBezierMT_Bilinear_MEM_Generic< T >;
        case INTERP_BICUBIC     : return  TransformBezierMT_Bicubic_MEM_Generic< T >;
    }
    return  nullptr;
}

// Generic Dispatcher Selector
fpDispatchedBezierTransformFunc
QueryDispatchedTransformBezierFunctionForParameters_RGBA8( const _FTransformInfoPrivate& iInfo ) {
#ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
    if( iInfo.hostDeviceInfo->HW_SSE42 ) {
        switch( iInfo.method ) {
            case INTERP_NN          : return  &TransformBezierMT_NN_SSE_RGBA8;
            case INTERP_BILINEAR    : return  &TransformBezierMT_Bilinear_SSE_RGBA8;
            case INTERP_BICUBIC     : return  &TransformBezierMT_Bicubic_SSE_RGBA8;
        }
    }
    else
#endif
    {
        switch( iInfo.method ) {
            case INTERP_NN          : return  TransformBezierMT_NN_MEM_Generic< uint8 >;
            case INTERP_BILINEAR    : return  TransformBezierMT_Bilinear_MEM_Generic< uint8 >;
            case INTERP_BICUBIC     : return  TransformBezierMT_Bicubic_MEM_Generic< uint8 >;
        }
    }

    return  nullptr;
}

// Generic Dispatcher Selector
template< typename T >
fpDispatchedBezierTransformFunc
QueryDispatchedTransformBezierFunctionForParameters_imp( const _FTransformInfoPrivate& iInfo ) {
    return  QueryDispatchedTransformBezierFunctionForParameters_Generic< T >( iInfo );
}

template<>
fpDispatchedBezierTransformFunc
QueryDispatchedTransformBezierFunctionForParameters_imp< uint8 >( const _FTransformInfoPrivate& iInfo ) {
    // RGBA8 Signature, any layout
    if( iInfo.source->HasAlpha()
     && iInfo.source->NumColorChannels()    == 3
     && iInfo.source->Model()               == CM_RGB
     && iInfo.perfIntent & ULIS3_PERF_TSPEC
     && ( iInfo.perfIntent & ULIS3_PERF_SSE42 || iInfo.perfIntent & ULIS3_PERF_AVX2 )
     && ( iInfo.hostDeviceInfo->HW_SSE42 || iInfo.hostDeviceInfo->HW_AVX2 ) ) {
        return  QueryDispatchedTransformBezierFunctionForParameters_RGBA8( iInfo );
    }

    // Generic Fallback
    return  QueryDispatchedTransformBezierFunctionForParameters_Generic< uint8 >( iInfo );
}

// Type Dispatcher Selector
fpDispatchedBezierTransformFunc
QueryDispatchedTransformBezierFunctionForParameters( const _FTransformInfoPrivate& iInfo ) {
    switch( iInfo.source->Type() ) {
        case TYPE_UINT8     : return  QueryDispatchedTransformBezierFunctionForParameters_imp< uint8   >( iInfo ); break;
        case TYPE_UINT16    : return  QueryDispatchedTransformBezierFunctionForParameters_imp< uint16  >( iInfo ); break;
        case TYPE_UINT32    : return  QueryDispatchedTransformBezierFunctionForParameters_imp< uint32  >( iInfo ); break;
        case TYPE_UFLOAT    : return  QueryDispatchedTransformBezierFunctionForParameters_imp< ufloat  >( iInfo ); break;
        case TYPE_UDOUBLE   : return  QueryDispatchedTransformBezierFunctionForParameters_imp< udouble >( iInfo ); break;
    }
    return  nullptr;
}

/////////////////////////////////////////////////////
// RESIZE
// Generic Dispatcher
template< typename T >
fpDispatchedResizeFunc
QueryDispatchedResizeFunctionForParameters_Generic( const _FResizeInfoPrivate& iInfo ) {
    switch( iInfo.method ) {
        case INTERP_NN          : return  ResizeMT_NN_MEM_Generic< T >;
        case INTERP_BILINEAR    : return  ResizeMT_Bilinear_MEM_Generic< T >;
        case INTERP_BICUBIC     : return  ResizeMT_Bicubic_MEM_Generic< T >;
        case INTERP_AREA        : return  ResizeMT_Area_MEM_Generic< T >;
    }
    return  nullptr;
}

fpDispatchedResizeFunc
QueryDispatchedResizeFunctionForParameters_RGBA8( const _FResizeInfoPrivate& iInfo ) {
#ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
    if( iInfo.hostDeviceInfo->HW_SSE42 ) {
        switch( iInfo.method ) {
            case INTERP_NN          : return  &ResizeMT_NN_SSE_RGBA8;
            case INTERP_BILINEAR    : return  &ResizeMT_Bilinear_SSE_RGBA8;
            case INTERP_BICUBIC     : return  &ResizeMT_Bicubic_SSE_RGBA8;
            case INTERP_AREA        : return  &ResizeMT_Area_SSE_RGBA8;
        }
    }
    else
#endif
    {
        switch( iInfo.method ) {
            case INTERP_NN          : return  ResizeMT_NN_MEM_Generic< uint8 >;
            case INTERP_BILINEAR    : return  ResizeMT_Bilinear_MEM_Generic< uint8 >;
            case INTERP_BICUBIC     : return  ResizeMT_Bicubic_MEM_Generic< uint8 >;
            case INTERP_AREA        : return  ResizeMT_Area_MEM_Generic< uint8 >;
        }
    }

    return  nullptr;
}

// Generic Dispatcher Selector
template< typename T >
fpDispatchedResizeFunc
QueryDispatchedResizeFunctionForParameters_imp( const _FResizeInfoPrivate& iInfo ) {
    return  QueryDispatchedResizeFunctionForParameters_Generic< T >( iInfo );
}

// Generic Dispatcher Selector
template<>
fpDispatchedResizeFunc
QueryDispatchedResizeFunctionForParameters_imp< uint8 >( const _FResizeInfoPrivate& iInfo ) {
    // RGBA8 Signature, any layout
    if( iInfo.source->HasAlpha()
     && iInfo.source->NumColorChannels()    == 3
     && iInfo.source->Model()               == CM_RGB
     && iInfo.perfIntent & ULIS3_PERF_TSPEC
     && ( iInfo.perfIntent & ULIS3_PERF_SSE42 || iInfo.perfIntent & ULIS3_PERF_AVX2 )
     && ( iInfo.hostDeviceInfo->HW_SSE42 || iInfo.hostDeviceInfo->HW_AVX2 ) ) {
        return  QueryDispatchedResizeFunctionForParameters_RGBA8( iInfo );
    }

    // Generic Fallback
    return  QueryDispatchedResizeFunctionForParameters_Generic< uint8 >( iInfo );
}

// Type Dispatcher Selector
fpDispatchedResizeFunc
QueryDispatchedResizeFunctionForParameters( const _FResizeInfoPrivate& iInfo ) {
    switch( iInfo.source->Type() ) {
        case TYPE_UINT8     : return  QueryDispatchedResizeFunctionForParameters_imp< uint8   >( iInfo ); break;
        case TYPE_UINT16    : return  QueryDispatchedResizeFunctionForParameters_imp< uint16  >( iInfo ); break;
        case TYPE_UINT32    : return  QueryDispatchedResizeFunctionForParameters_imp< uint32  >( iInfo ); break;
        case TYPE_UFLOAT    : return  QueryDispatchedResizeFunctionForParameters_imp< ufloat  >( iInfo ); break;
        case TYPE_UDOUBLE   : return  QueryDispatchedResizeFunctionForParameters_imp< udouble >( iInfo ); break;
    }
    return  nullptr;
}
ULIS3_NAMESPACE_END

