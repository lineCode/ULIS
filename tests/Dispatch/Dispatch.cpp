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
using namespace ::ul3;

/////////////////////////////////////////////////////
// Imp
#define INVOCATION_X_ARGS
typedef void (*fpDispatchedXFunc)( INVOCATION_X_ARGS );

template< typename T > void InvokeXGenericAVX( INVOCATION_X_ARGS ) { std::cout << "InvokeXGenericAVX called." << std::endl; }
template< typename T > void InvokeXGenericSSE( INVOCATION_X_ARGS ) { std::cout << "InvokeXGenericSSE called." << std::endl; }
template< typename T > void InvokeXGenericMEM( INVOCATION_X_ARGS ) { std::cout << "InvokeXGenericMEM called." << std::endl; }

/////////////////////////////////////////////////////
// Table
template< typename F, typename T >
struct FDispatchTable {
    static const F select_AVX;
    static const F select_SSE;
    static const F select_MEM;
};
template< typename F, typename T > const F FDispatchTable<F,T>::select_AVX = nullptr;
template< typename F, typename T > const F FDispatchTable<F,T>::select_SSE = nullptr;
template< typename F, typename T > const F FDispatchTable<F,T>::select_MEM = nullptr;

/////////////////////////////////////////////////////
// Helper
#define DECL_DISPATCH( F, AVX, SSE, MEM )                                               \
    template< typename T >                                                              \
    struct FDispatchTable< F, T > {                                                     \
        static const F select_AVX;                                                      \
        static const F select_SSE;                                                      \
        static const F select_MEM;                                                      \
    };                                                                                  \
    template< typename T > const F FDispatchTable< F, T >::select_AVX = & AVX < T >;    \
    template< typename T > const F FDispatchTable< F, T >::select_SSE = & SSE < T >;    \
    template< typename T > const F FDispatchTable< F, T >::select_MEM = & MEM < T >;

/////////////////////////////////////////////////////
// Spec
DECL_DISPATCH( fpDispatchedXFunc, InvokeXGenericAVX, InvokeXGenericSSE, InvokeXGenericMEM )

/////////////////////////////////////////////////////
// Dispatcher
template< typename F, typename E >
class TDispatcher {
public:
    static ULIS3_FORCEINLINE F Query( uint32 iPerfIntent, const FHostDeviceInfo& iHostDeviceInfo, const FFormatInfo& iFormatInfo, const E& iExtra ) {
        switch( iFormatInfo.TP ) {
            case TYPE_UINT8     : return  Query_imp< uint8   >( iPerfIntent, iHostDeviceInfo, iFormatInfo, iExtra );
            case TYPE_UINT16    : return  Query_imp< uint16  >( iPerfIntent, iHostDeviceInfo, iFormatInfo, iExtra );
            case TYPE_UINT32    : return  Query_imp< uint32  >( iPerfIntent, iHostDeviceInfo, iFormatInfo, iExtra );
            case TYPE_UFLOAT    : return  Query_imp< ufloat  >( iPerfIntent, iHostDeviceInfo, iFormatInfo, iExtra );
            case TYPE_UDOUBLE   : return  Query_imp< udouble >( iPerfIntent, iHostDeviceInfo, iFormatInfo, iExtra );
            default             : return  nullptr;
        }
    }

private:
    template< typename T >
    static ULIS3_FORCEINLINE F Query_imp( uint32 iPerfIntent, const FHostDeviceInfo& iHostDeviceInfo, const FFormatInfo& iFormatInfo, const E& iExtra ) {
        #ifdef ULIS3_COMPILETIME_AVX2_SUPPORT
            if( iPerfIntent & ULIS3_PERF_AVX2 && iHostDeviceInfo.HW_AVX2 )
                return  FDispatchTable< F, T >::select_AVX;
            else
        #endif
        #ifdef ULIS3_COMPILETIME_SSE42_SUPPORT
            if( iPerfIntent & ULIS3_PERF_SSE42 && iHostDeviceInfo.HW_SSE42 )
                return  FDispatchTable< F, T >::select_SSE;
            else
        #endif
                return  FDispatchTable< F, T >::select_MEM;
    }
};

/////////////////////////////////////////////////////
// Main
int
main() {
    uint32 intent = ULIS3_PERF_SSE42 | ULIS3_PERF_AVX2;
    FHostDeviceInfo host = FHostDeviceInfo::Detect();
    FFormatInfo format( ULIS3_FORMAT_RGBA8 );

    eBlendingMode mode = BM_NORMAL;

    fpDispatchedXFunc fptr = TDispatcher< fpDispatchedXFunc, eBlendingMode >::Query( intent, host, format, mode );
    if( fptr )
        fptr();

    return  0;
}

