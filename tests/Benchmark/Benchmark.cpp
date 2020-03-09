// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Benchmark.cpp
* @author       Clement Berthaud
* @brief        Benchmark application for ULIS2.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS2>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace ::ul2;
constexpr int criticalError = 0xB00BA420;

int error( const char* iMsg ) {
    std::cout << iMsg << std::endl;
    return criticalError;
}

int clear( int argc, char *argv[] ) {
    // Expected input:
    // 0 - ignored  // 2 - Format   // 4 - Repeat   // 6 - Optimizations
    // 1 - clear    // 3 - Threads  // 5 - Size     // 7 - Extra
    if( argc != 7 ) { return error( "Bad args, abort." ); }
    tFormat format  = std::stoul( std::string( argv[2] ).c_str() );
    uint32  threads = std::atoi( std::string( argv[3] ).c_str() );
    uint32  repeat  = std::atoi( std::string( argv[4] ).c_str() );
    uint32  size    = std::atoi( std::string( argv[5] ).c_str() );
    std::string opt = std::string( argv[6] );
    uint32 optBit = 0;
    if( opt == "sse" ) optBit = ULIS2_PERF_SSE42;
    if( opt == "avx" ) optBit = ULIS2_PERF_AVX2;
    FThreadPool pool( threads );
    FHostDeviceInfo host = FHostDeviceInfo::Detect();
    uint32 perfIntent = ULIS2_PERF_MT | ULIS2_PERF_TSPEC | optBit;
    FBlock* block = new FBlock( size, size, format );
    auto startTime = std::chrono::steady_clock::now();
    for( int l = 0; l < repeat; ++l )
        Clear( &pool, ULIS2_BLOCKING, perfIntent, host, ULIS2_NOCB, block, block->Rect() );
    auto endTime = std::chrono::steady_clock::now();
    auto deltaMs = std::chrono::duration_cast< std::chrono::milliseconds>( endTime - startTime ).count();
    delete block;
    return deltaMs;
}

int fill( int argc, char *argv[] ) {
    // Expected input:
    // 0 - ignored  // 2 - Format   // 4 - Repeat   // 6 - Optimizations
    // 1 - clear    // 3 - Threads  // 5 - Size     // 7 - Extra
    if( argc != 7 ) { return error( "Bad args, abort." ); }
    tFormat format  = std::stoul( std::string( argv[2] ).c_str() );
    uint32  threads = std::atoi( std::string( argv[3] ).c_str() );
    uint32  repeat  = std::atoi( std::string( argv[4] ).c_str() );
    uint32  size    = std::atoi( std::string( argv[5] ).c_str() );
    std::string opt = std::string( argv[6] );
    uint32 optBit = 0;
    if( opt == "sse" ) optBit = ULIS2_PERF_SSE42;
    if( opt == "avx" ) optBit = ULIS2_PERF_AVX2;
    FThreadPool pool( threads );
    FHostDeviceInfo host = FHostDeviceInfo::Detect();
    uint32 perfIntent = ULIS2_PERF_MT | ULIS2_PERF_TSPEC | optBit;
    FBlock* block = new FBlock( size, size, format );
    FPixelValue source( format );
    auto startTime = std::chrono::steady_clock::now();
    for( int l = 0; l < repeat; ++l )
        Fill( &pool, ULIS2_BLOCKING, perfIntent, host, ULIS2_NOCB, block, source, block->Rect() );
    auto endTime = std::chrono::steady_clock::now();
    auto deltaMs = std::chrono::duration_cast< std::chrono::milliseconds>( endTime - startTime ).count();
    delete block;
    return deltaMs;
}

int copy( int argc, char *argv[] ) {
    // Expected input:
    // 0 - ignored  // 2 - Format   // 4 - Repeat   // 6 - Optimizations
    // 1 - clear    // 3 - Threads  // 5 - Size     // 7 - Extra
    if( argc != 7 ) { return error( "Bad args, abort." ); }
    tFormat format  = std::stoul( std::string( argv[2] ).c_str() );
    uint32  threads = std::atoi( std::string( argv[3] ).c_str() );
    uint32  repeat  = std::atoi( std::string( argv[4] ).c_str() );
    uint32  size    = std::atoi( std::string( argv[5] ).c_str() );
    std::string opt = std::string( argv[6] );
    uint32 optBit = 0;
    if( opt == "sse" ) optBit = ULIS2_PERF_SSE42;
    if( opt == "avx" ) optBit = ULIS2_PERF_AVX2;
    FThreadPool pool( threads );
    FHostDeviceInfo host = FHostDeviceInfo::Detect();
    uint32 perfIntent = ULIS2_PERF_MT | ULIS2_PERF_TSPEC | optBit;
    FBlock* src = new FBlock( size, size, format );
    FBlock* dst = new FBlock( size, size, format );
    auto startTime = std::chrono::steady_clock::now();
    for( int l = 0; l < repeat; ++l )
        Copy( &pool, ULIS2_BLOCKING, perfIntent, host, ULIS2_NOCB, src, dst, src->Rect(), FVec2I() );
    auto endTime = std::chrono::steady_clock::now();
    auto deltaMs = std::chrono::duration_cast< std::chrono::milliseconds>( endTime - startTime ).count();
    delete src;
    delete dst;
    return deltaMs;
}

int blend( int argc, char *argv[] ) {
    // Expected input:
    // 0 - ignored  // 2 - Format   // 4 - Repeat   // 6 - Optimizations
    // 1 - clear    // 3 - Threads  // 5 - Size     // 7 - Extra
    if( argc != 10 ) { return error( "Bad args, abort." ); }
    tFormat format  = std::stoul( std::string( argv[2] ).c_str() );
    uint32  threads = std::atoi( std::string( argv[3] ).c_str() );
    uint32  repeat  = std::atoi( std::string( argv[4] ).c_str() );
    uint32  size    = std::atoi( std::string( argv[5] ).c_str() );
    std::string opt = std::string( argv[6] );
    eBlendingMode   blendingMode    = static_cast< eBlendingMode >( std::atoi( std::string( argv[7] ).c_str() ) );
    eAlphaMode      alphaMode       = static_cast< eAlphaMode >( std::atoi( std::string( argv[8] ).c_str() ) );
    bool            subpixelFlag    = static_cast< bool >( std::atoi( std::string( argv[9] ).c_str() ) );
    uint32 optBit = 0;
    if( opt == "sse" ) optBit = ULIS2_PERF_SSE42;
    if( opt == "avx" ) optBit = ULIS2_PERF_AVX2;
    FThreadPool pool( threads );
    FHostDeviceInfo host = FHostDeviceInfo::Detect();
    uint32 perfIntent = ULIS2_PERF_MT | ULIS2_PERF_TSPEC | optBit;
    FBlock* src = new FBlock( size, size, format );
    FBlock* dst = new FBlock( size, size, format );
    auto startTime = std::chrono::steady_clock::now();
    for( int l = 0; l < repeat; ++l )
        Blend( &pool, ULIS2_BLOCKING, perfIntent, host, ULIS2_NOCB, src, dst, src->Rect(), FVec2F(), subpixelFlag, blendingMode, alphaMode, 0.5f );
    auto endTime = std::chrono::steady_clock::now();
    auto deltaMs = std::chrono::duration_cast< std::chrono::milliseconds>( endTime - startTime ).count();
    delete src;
    delete dst;
    return deltaMs;
}


int conv( int argc, char *argv[] ) {
    // Expected input:
    // 0 - ignored  // 2 - Format   // 4 - Repeat   // 6 - Optimizations
    // 1 - clear    // 3 - Threads  // 5 - Size     // 7 - Extra
    if( argc != 8 ) { return error( "Bad args, abort." ); }
    tFormat format  = std::stoul( std::string( argv[2] ).c_str() );
    uint32  threads = std::atoi( std::string( argv[3] ).c_str() );
    uint32  repeat  = std::atoi( std::string( argv[4] ).c_str() );
    uint32  size    = std::atoi( std::string( argv[5] ).c_str() );
    std::string opt = std::string( argv[6] );
    tFormat dstFormat = std::stoul( std::string( argv[7] ).c_str() );
    uint32 optBit = 0;
    if( opt == "sse" ) optBit = ULIS2_PERF_SSE42;
    if( opt == "avx" ) optBit = ULIS2_PERF_AVX2;
    FThreadPool pool( threads );
    FHostDeviceInfo host = FHostDeviceInfo::Detect();
    uint32 perfIntent = ULIS2_PERF_MT | ULIS2_PERF_TSPEC | optBit;
    FBlock* src = new FBlock( size, size, format );
    FBlock* dst = new FBlock( size, size, dstFormat );
    auto startTime = std::chrono::steady_clock::now();
    for( int l = 0; l < repeat; ++l )
        Conv( &pool, ULIS2_BLOCKING, perfIntent, host, ULIS2_NOCB, src, dst );
    auto endTime = std::chrono::steady_clock::now();
    auto deltaMs = std::chrono::duration_cast< std::chrono::milliseconds>( endTime - startTime ).count();
    delete src;
    delete dst;
    return deltaMs;
}

// Call examples:
// Benchmark.exe clear  0           64  1000    256     mem xxx
// Benchmark.exe fill   0           32  200     2048    sse xxx
int main( int argc, char *argv[] ) {
    // 0 - ignored  // 2 - Format   // 4 - Repeat   // 6 - Optimizations
    // 1 - clear    // 3 - Threads  // 5 - Size     // 8 - Extra

    if( argc <=1 )
        return error( "Bad args, abort." );

    std::string op = argv[1];

    int exit_code = criticalError;
         if( op == "clear"      )   exit_code = clear(  argc, argv );
    else if( op == "fill"       )   exit_code = fill(   argc, argv );
    else if( op == "copy"       )   exit_code = copy(   argc, argv );
    else if( op == "blend"      )   exit_code = blend(  argc, argv );
    else if( op == "conv"       )   exit_code = conv(   argc, argv );
    else return error( "Bad Op, abort." );

    return  exit_code;
}

