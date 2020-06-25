// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         Dispatch.cpp
* @author       Clement Berthaud
* @brief        Dispatch application for ULIS3.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS3>
#include <functional>
#include <map>
using namespace ::ul3;

/////////////////////////////////////////////////////
// Imp
#define INVOCATION_X_ARGS
typedef void (*fpDispatchedXFunc)( INVOCATION_X_ARGS );
template< typename T > void InvokeXGenericAVX0( INVOCATION_X_ARGS ) { std::cout << "InvokeXGenericAVX0 called." << std::endl; }
template< typename T > void InvokeXGenericAVX1( INVOCATION_X_ARGS ) { std::cout << "InvokeXGenericAVX1 called." << std::endl; }
template< typename T > void InvokeXGenericAVX2( INVOCATION_X_ARGS ) { std::cout << "InvokeXGenericAVX2 called." << std::endl; }
template< typename T > void InvokeXGenericSSE0( INVOCATION_X_ARGS ) { std::cout << "InvokeXGenericSSE0 called." << std::endl; }
template< typename T > void InvokeXGenericSSE1( INVOCATION_X_ARGS ) { std::cout << "InvokeXGenericSSE1 called." << std::endl; }
template< typename T > void InvokeXGenericSSE2( INVOCATION_X_ARGS ) { std::cout << "InvokeXGenericSSE2 called." << std::endl; }
template< typename T > void InvokeXGenericMEM0( INVOCATION_X_ARGS ) { std::cout << "InvokeXGenericMEM0 called." << std::endl; }
template< typename T > void InvokeXGenericMEM1( INVOCATION_X_ARGS ) { std::cout << "InvokeXGenericMEM1 called." << std::endl; }
template< typename T > void InvokeXGenericMEM2( INVOCATION_X_ARGS ) { std::cout << "InvokeXGenericMEM2 called." << std::endl; }

void InvokeXRGBA8AVX0( INVOCATION_X_ARGS ) { std::cout << "InvokeXRGBA8AVX0 called." << std::endl; }
void InvokeXRGBA8AVX1( INVOCATION_X_ARGS ) { std::cout << "InvokeXRGBA8AVX1 called." << std::endl; }
void InvokeXRGBA8AVX2( INVOCATION_X_ARGS ) { std::cout << "InvokeXRGBA8AVX2 called." << std::endl; }
void InvokeXRGBA8SSE0( INVOCATION_X_ARGS ) { std::cout << "InvokeXRGBA8SSE0 called." << std::endl; }
void InvokeXRGBA8SSE1( INVOCATION_X_ARGS ) { std::cout << "InvokeXRGBA8SSE1 called." << std::endl; }
void InvokeXRGBA8SSE2( INVOCATION_X_ARGS ) { std::cout << "InvokeXRGBA8SSE2 called." << std::endl; }
void InvokeXRGBA8MEM0( INVOCATION_X_ARGS ) { std::cout << "InvokeXRGBA8MEM0 called." << std::endl; }
void InvokeXRGBA8MEM1( INVOCATION_X_ARGS ) { std::cout << "InvokeXRGBA8MEM1 called." << std::endl; }
void InvokeXRGBA8MEM2( INVOCATION_X_ARGS ) { std::cout << "InvokeXRGBA8MEM2 called." << std::endl; }

template< typename T > fpDispatchedXFunc SelectDispatchMEMGeneric( const int& iInfo ) {
    switch( iInfo ) {
        case 0  : return  &InvokeXGenericMEM0< T >;
        case 1  : return  &InvokeXGenericMEM1< T >;
        case 2  : return  &InvokeXGenericMEM2< T >;
        default : return  nullptr;
    }
}

template< typename T > fpDispatchedXFunc SelectDispatchSSEGeneric( const int& iInfo ) {
    switch( iInfo ) {
        case 0  : return  &InvokeXGenericSSE0< T >;
        case 1  : return  &InvokeXGenericSSE1< T >;
        case 2  : return  &InvokeXGenericSSE2< T >;
        default : return  nullptr;
    }
}

template< typename T > fpDispatchedXFunc SelectDispatchAVXGeneric( const int& iInfo ) {
    switch( iInfo ) {
        case 0  : return  &InvokeXGenericAVX0< T >;
        case 1  : return  &InvokeXGenericAVX1< T >;
        case 2  : return  &InvokeXGenericAVX2< T >;
        default : return  nullptr;
    }
}

fpDispatchedXFunc SelectDispatchMEMRGBA8( const int& iInfo ) {
    switch( iInfo ) {
        case 0  : return  &InvokeXRGBA8MEM0;
        case 1  : return  &InvokeXRGBA8MEM1;
        case 2  : return  &InvokeXRGBA8MEM2;
        default : return  nullptr;
    }
}

fpDispatchedXFunc SelectDispatchSSERGBA8( const int& iInfo ) {
    switch( iInfo ) {
        case 0  : return  &InvokeXRGBA8SSE0;
        case 1  : return  &InvokeXRGBA8SSE1;
        case 2  : return  &InvokeXRGBA8SSE2;
        default : return  nullptr;
    }
}

fpDispatchedXFunc SelectDispatchAVXRGBA8( const int& iInfo ) {
    switch( iInfo ) {
        case 0  : return  &InvokeXRGBA8AVX0;
        case 1  : return  &InvokeXRGBA8AVX1;
        case 2  : return  &InvokeXRGBA8AVX2;
        default : return  nullptr;
    }
}

/////////////////////////////////////////////////////
// Table
bool TestUnorderedRGBA8( const FFormatInfo& iFormatInfo ) { return  ( iFormatInfo.TP == TYPE_UINT8 ) && ( iFormatInfo.HEA ) && ( iFormatInfo.NCC == 3 ) && ( iFormatInfo.CM == CM_RGB ); }
bool TestUnorderedRGBAF( const FFormatInfo& iFormatInfo ) { return  ( iFormatInfo.TP == TYPE_UFLOAT ) && ( iFormatInfo.HEA ) && ( iFormatInfo.NCC == 3 ) && ( iFormatInfo.CM == CM_RGB ); }
typedef bool (*fpCond)( const FFormatInfo& iFormatInfo );

template< typename F, typename E >
struct TMultiDispatchGroup {
    typedef F(*fpSelect)( const E& );
    const fpCond    select_cond;
    const fpSelect  select_AVX;
    const fpSelect  select_SSE;
    const fpSelect  select_MEM;
};

template< typename F, typename T, typename E >
struct TMultiDispatchTable {
    static const TMultiDispatchGroup< F, E > spec_table[];
    static const typename TMultiDispatchGroup< F, E >::fpSelect select_AVX_Generic;
    static const typename TMultiDispatchGroup< F, E >::fpSelect select_SSE_Generic;
    static const typename TMultiDispatchGroup< F, E >::fpSelect select_MEM_Generic;
    static const int spec_size;
};

/////////////////////////////////////////////////////
// Dispatcher
template< typename F, typename E >
class TDispatcher {
public:
    static ULIS3_FORCEINLINE F Query( uint32 iPerfIntent, const FHostDeviceInfo& iHostDeviceInfo, const FFormatInfo& iFormatInfo, const E& iExtra ) {
        for( int i = 0; i < TMultiDispatchTable< F, void, E >::spec_size - 1; ++i ) {
            if( TMultiDispatchTable< F, void, E >::spec_table[i].select_cond( iFormatInfo ) ) {
                #ifdef ULIS3_COMPILETIME_AVX2_SUPPORT
                    if( iPerfIntent & ULIS3_PERF_AVX2 && iHostDeviceInfo.HW_AVX2 )
                        return  TMultiDispatchTable< F, void, E >::spec_table[i].select_AVX( iExtra );
                    else
                #endif
                #ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
                    if( iPerfIntent & ULIS3_PERF_SSE42 && iHostDeviceInfo.HW_SSE42 )
                        return  TMultiDispatchTable< F, void, E >::spec_table[i].select_SSE( iExtra );
                    else
                #endif
                        return  TMultiDispatchTable< F, void, E >::spec_table[i].select_MEM( iExtra );
            }
        }

        switch( iFormatInfo.TP ) {
            case TYPE_UINT8     : return  Query_imp< uint8   >( iPerfIntent, iHostDeviceInfo, iFormatInfo, iExtra );
            case TYPE_UINT16    : return  Query_imp< uint16  >( iPerfIntent, iHostDeviceInfo, iFormatInfo, iExtra );
            case TYPE_UINT32    : return  Query_imp< uint32  >( iPerfIntent, iHostDeviceInfo, iFormatInfo, iExtra );
            case TYPE_UFLOAT    : return  Query_imp< ufloat  >( iPerfIntent, iHostDeviceInfo, iFormatInfo, iExtra );
            case TYPE_UDOUBLE   : return  Query_imp< udouble >( iPerfIntent, iHostDeviceInfo, iFormatInfo, iExtra );
        }
        ULIS3_ASSERT( false, "No Dispatch found." );
        return  nullptr;
    }

private:
    template< typename T >
    static ULIS3_FORCEINLINE F Query_imp( uint32 iPerfIntent, const FHostDeviceInfo& iHostDeviceInfo, const FFormatInfo& iFormatInfo, const E& iExtra ) {
        #ifdef ULIS3_COMPILETIME_AVX2_SUPPORT
            if( iPerfIntent & ULIS3_PERF_AVX2 && iHostDeviceInfo.HW_AVX2 )
                return  TMultiDispatchTable< F, T, E >::select_AVX_Generic( iExtra );
            else
        #endif
        #ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
            if( iPerfIntent & ULIS3_PERF_SSE42 && iHostDeviceInfo.HW_SSE42 )
                return  TMultiDispatchTable< F, T, E >::select_SSE_Generic( iExtra );
            else
        #endif
                return  TMultiDispatchTable< F, T, E >::select_MEM_Generic( iExtra );
    }
};

/////////////////////////////////////////////////////
// Spec

template< typename T >
struct TMultiDispatchTable< fpDispatchedXFunc, T, int > {
    static const TMultiDispatchGroup< fpDispatchedXFunc, int > spec_table[];
    static const typename TMultiDispatchGroup< fpDispatchedXFunc, int >::fpSelect select_AVX_Generic;
    static const typename TMultiDispatchGroup< fpDispatchedXFunc, int >::fpSelect select_SSE_Generic;
    static const typename TMultiDispatchGroup< fpDispatchedXFunc, int >::fpSelect select_MEM_Generic;
    static const int spec_size;
};

template< typename T > const TMultiDispatchGroup< fpDispatchedXFunc, int >  TMultiDispatchTable< fpDispatchedXFunc, T, int >::spec_table[] = {
      { &TestUnorderedRGBA8, &SelectDispatchAVXRGBA8, &SelectDispatchSSERGBA8, &SelectDispatchMEMRGBA8 }
    , { nullptr, nullptr, nullptr, nullptr }
};
template< typename T > const TMultiDispatchGroup< fpDispatchedXFunc, int >::fpSelect TMultiDispatchTable< fpDispatchedXFunc, T, int >::select_AVX_Generic = &SelectDispatchAVXGeneric< T >;
template< typename T > const TMultiDispatchGroup< fpDispatchedXFunc, int >::fpSelect TMultiDispatchTable< fpDispatchedXFunc, T, int >::select_SSE_Generic = &SelectDispatchSSEGeneric< T >;
template< typename T > const TMultiDispatchGroup< fpDispatchedXFunc, int >::fpSelect TMultiDispatchTable< fpDispatchedXFunc, T, int >::select_MEM_Generic = &SelectDispatchMEMGeneric< T >;
template< typename T > const int TMultiDispatchTable< fpDispatchedXFunc, T, int >::spec_size = sizeof( TMultiDispatchTable< fpDispatchedXFunc, T, int >::spec_table ) / sizeof( TMultiDispatchGroup< fpDispatchedXFunc, int > );

/////////////////////////////////////////////////////
// Main
int
main() {
    const size_t size = TMultiDispatchTable< fpDispatchedXFunc, uint8, int >::spec_size;

    uint32 intent = ULIS3_PERF_SSE42;
    FHostDeviceInfo host = FHostDeviceInfo::Detect();
    FFormatInfo format( ULIS3_FORMAT_RGBA8 );

    int extra = 1;

    fpDispatchedXFunc fptr = TDispatcher< fpDispatchedXFunc, int >::Query( intent, host, format, extra );
    if( fptr )
        fptr();

    return  0;
}

