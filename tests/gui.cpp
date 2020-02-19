// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         gui.cpp
* @author       Clement Berthaud
* @brief        Gui application for ULIS2.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <ULIS2>
#include <chrono>

using namespace ::ul2;

int
main( int argc, char *argv[] )
{
    FThreadPool     threadPool;
    FPerf           perfIntentSSE( Perf_MT | Perf_SSE4_2  | Perf_TSPEC );
    FPerf           perfIntentAVX( Perf_MT |Perf_AVX2    | Perf_TSPEC );
    FCPU            cpuInfo;
    FFontEngine     fontEngine;
    FFontRegistry   fontRegistry( fontEngine );
    FFont           font = fontRegistry.LoadFont( "Arial", "Regular" );
    FBlock*         blockBase = XLoadFromFile( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, "C:/Users/conta/Documents/work/pattern.png", ULIS2_FORMAT_RGBA8 );
    FBlock*         blockOver = XLoadFromFile( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, "C:/Users/conta/Documents/work/Over.png", ULIS2_FORMAT_RGBA8 );
    int             wb = blockBase->Width();
    int             hb = blockBase->Height();
    FBlock          blockA( wb * 8+1, hb * 5, ULIS2_FORMAT_RGBA8 );
    FBlock          blockB( 1, 1, ULIS2_FORMAT_RGBA8 );
    FBlock          blockC( wb, 20, ULIS2_FORMAT_RGBA8 );

    int testsize = 1024;
    int testnum = 5000;
    bool testAA = true;
    {
        FBlock block1( testsize, testsize, ULIS2_FORMAT_RGBA8 );
        FBlock block2( testsize, testsize, ULIS2_FORMAT_RGBA8 );
        auto start_time = std::chrono::steady_clock::now();
        for( int l = 0; l < testnum; ++l )
        {
            Blend( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, testAA, &block1, &block2, 0,0, BM_NORMAL, AM_NORMAL, 1.f, ULIS2_CALLCB );
        }

        auto end_time   = std::chrono::steady_clock::now();
        auto delta      = std::chrono::duration_cast< std::chrono::milliseconds>(end_time - start_time ).count();
        float average   = delta / (float)testnum;
        std::cout << "AVX AA:" << average << std::endl;
    }

    {
        FBlock block1( testsize, testsize, ULIS2_FORMAT_RGBA8 );
        FBlock block2( testsize, testsize, ULIS2_FORMAT_RGBA8 );
        auto start_time = std::chrono::steady_clock::now();
        for( int l = 0; l < testnum; ++l )
        {
            Blend( &threadPool, ULIS2_BLOCKING, perfIntentSSE, cpuInfo, testAA, &block1, &block2, 0,0, BM_NORMAL, AM_NORMAL, 1.f, ULIS2_CALLCB );
        }

        auto end_time   = std::chrono::steady_clock::now();
        auto delta      = std::chrono::duration_cast< std::chrono::milliseconds>(end_time - start_time ).count();
        float average   = delta / (float)testnum;
        std::cout << "SSE AA:" << average << std::endl;
    }

    FPixel red(    ULIS2_FORMAT_RGB8, { 255,   0,      0   } );
    FPixel green(  ULIS2_FORMAT_RGB8, { 0,     255,    0   } );
    FPixel black(  ULIS2_FORMAT_RGB8, { 0,     0,      0   } );
    FPixel white(  ULIS2_FORMAT_RGB8, { 255,   255,    255 } );
    Clear( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, &blockA, ULIS2_NOCB );
    Fill( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, &blockC, black, ULIS2_NOCB );

    Fill( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, &blockA, green, ULIS2_NOCB );
    Fill( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, &blockB, red, ULIS2_NOCB );
    Blend( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, testAA, blockBase, &blockA, 0,0, BM_NORMAL, AM_NORMAL, 1.f, ULIS2_CALLCB );

    /*
    for( int i = 0; i < NUM_ALPHA_MODES; ++i ) {
        int x = ( i % 8 ) * wb;
        int y = ( i / 8 ) * hb;
        Blend( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_AA, blockBase,  &blockA, FVec2( x, y ),              BM_NORMAL,          AM_NORMAL, 1.0f, ULIS2_NOCB );
        Blend( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_AA, blockOver,  &blockA, FVec2( x, y ),              BM_NORMAL,          eAlphaMode( i ), 1.f, ULIS2_NOCB );
        Blend( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_AA, &blockC,    &blockA, FVec2( x, y + hb - 20 ),    BM_NORMAL,          AM_NORMAL, 0.5f, ULIS2_NOCB );
        RenderText( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_AA, &blockA, kwAlphaMode[ i ], font, 16, white, FVec2( x, y + hb - 16 ), FMat2( 1.f ), ULIS2_NOCB );
    }
    */

    // Qt Window
    QApplication    app( argc, argv );
    QWidget*        widget  = new QWidget();
    QImage*         image   = new QImage( blockA.DataPtr(), blockA.Width(), blockA.Height(), blockA.BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    QPixmap         pixmap  = QPixmap::fromImage( *image );
    QLabel*         label   = new QLabel( widget );
    label->setPixmap( pixmap );
    widget->resize( pixmap.size() );
    widget->show();

    std::cout << "Show";
    int exit_code = app.exec();

    delete  label;
    delete  image;
    delete  widget;
    delete  blockBase;
    delete  blockOver;
    return  exit_code;
}