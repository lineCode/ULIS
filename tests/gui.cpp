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
    FPerf           perfIntentSSE( 0 );
    FPerf           perfIntentAVX( 0 );
    FCPU            cpuInfo;
    FFontEngine     fontEngine;
    FFontRegistry   fontRegistry( fontEngine );
    FFont           font = fontRegistry.LoadFont( "Arial", "Regular" );
    FBlock*         blockBase = XLoadFromFile( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, "C:/Users/conta/Documents/work/pattern.png", ULIS2_FORMAT_RGBA8 );
    FBlock*         blockOver = XLoadFromFile( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, "C:/Users/conta/Documents/work/Over.png", ULIS2_FORMAT_RGBA8 );
    int             wb = blockBase->Width();
    int             hb = blockBase->Height();
    FBlock          blockA( 800, 600, ULIS2_FORMAT_RGBA8 );
    FBlock          blockB( 1, 1, ULIS2_FORMAT_RGBA8 );
    FBlock          blockC( wb, 20, ULIS2_FORMAT_RGBA8 );

    float tx, ty, r, sx, sy, skx, sky;
    auto _t = MakeTranslationMatrix( 50, 20 );
    auto _r = MakeRotationMatrix( 1.57 );
    auto _s = MakeScaleMatrix( 5, 8 );
    auto comp = ComposeMatrix( ComposeMatrix( _s, _r ), _t );
    FTransform2D trans( comp );
    trans.DecomposeMatrix( &tx, &ty, &r, &sx, &sy, &skx, &sky );

    /*
    int testsize = 1024;
    int testnum = 50;
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
    */

    FPixel red(    ULIS2_FORMAT_RGB8, { 255,   0,      0   } );
    FPixel green(  ULIS2_FORMAT_RGB8, { 0,     255,    0   } );
    FPixel black(  ULIS2_FORMAT_RGB8, { 0,     0,      0   } );
    FPixel white(  ULIS2_FORMAT_RGB8, { 255,   255,    255 } );
    Clear( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, &blockA, ULIS2_NOCB );
    Fill( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, &blockC, black, ULIS2_NOCB );

    Fill( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, &blockA, green, ULIS2_NOCB );
    Fill( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, &blockB, red, ULIS2_NOCB );
    //Blend( &threadPool, ULIS2_BLOCKING, perfIntentAVX, cpuInfo, ULIS2_NOAA, blockBase, &blockA, 64.5, 64.5, BM_NORMAL, AM_NORMAL, 1.f, ULIS2_CALLCB );

    int a = (-1)%64;


    BlendRect( &threadPool
             , ULIS2_BLOCKING
             , 0
             , cpuInfo
             , ULIS2_NOAA
             , blockBase
             , &blockA
             , FRect( 0, 0, 65, 64 )
             , 0, 1, 0, 0, 65*2, 64*2
             , BM_NORMAL
             , AM_NORMAL
             , 1.f
             , ULIS2_CALLCB );

    FPerfParams perfParams = {};
    perfParams.pool       = &threadPool;
    perfParams.intent     = FPerf( 0 );
    perfParams.blocking   = ULIS2_BLOCKING;
    perfParams.callCB     = ULIS2_CALLCB;

    FBlendInfo blendParams = {};
    blendParams.source              = blockBase;
    blendParams.backdrop            = &blockA;
    blendParams.sourceRect          = FRect( 0, 0, 65, 64 );
    blendParams.tilingTranslation   = FVec2I( -1, -1 );
    blendParams.backdropPosition    = FVec2F( -20.5, -20.5 );
    blendParams.backdropCoverage    = FVec2I( 211, 5643 );
    blendParams.subpixelFlag        = ULIS2_NOAA;
    blendParams.blendingMode        = BM_NORMAL;
    blendParams.alphaMode           = AM_NORMAL;
    blendParams.opacityValue        = 1.f;
    BlendRect( perfParams, blendParams );

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