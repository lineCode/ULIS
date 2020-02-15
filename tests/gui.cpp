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


    FThreadPool     threadPool(1);
    FPerf           clearPerfIntent(    0           );
    FPerf           FillPerfIntent(     Perf_AVX2   );
    FPerf           blendMemperfIntent( Perf_MT           );
    FPerf           perfIntent(         Perf_MT | Perf_TSPEC | Perf_AVX2 );
    FCPU            cpuInfo;
    FFontEngine     fontEngine;
    FFontRegistry   fontRegistry( fontEngine );
    FFont           font = fontRegistry.LoadFont( "Arial", "Black" );
    FBlock*         blockDamas = XLoadFromFile( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, "C:/Users/conta/Documents/work/wallpaper/Damas_SMALL.png", ULIS2_FORMAT_RGBA8 );
    FBlock          TEST( 64, 64, ULIS2_FORMAT_RGBA8 );
    FBlock          blockBlack( 64, 64, ULIS2_FORMAT_RGBA8 );

    FColor bg( ULIS2_FORMAT_RGB8, { 20, 20, 20 } );
    FColor red( ULIS2_FORMAT_RGB8, { 255, 0, 0 } );
    Fill( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, &blockBlack, bg, ULIS2_NOCB );

    auto start_time = std::chrono::steady_clock::now();
    int num = 20000;

    fpDispatchedBlendFunc fptr = QueryDispatchedBlendFunctionForParameters( blockBlack.Format(), BM_NORMAL, AM_NORMAL, ULIS2_NOAA, perfIntent, cpuInfo );

    for( int l = 0; l < num; ++l )
    {
        fptr( &threadPool, false, perfIntent, &blockBlack, &TEST, blockBlack.Rect(), blockBlack.Rect(), glm::vec2(0.f), BM_NORMAL, AM_NORMAL, 1.f );
        //Blend( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_NOSUBPIXEL, &blockBlack, &TEST, ULIS2_NODELTA, BM_NORMAL, AM_NORMAL, 0.9f, ULIS2_NOCB );
        //Clear( &threadPool, ULIS2_NONBLOCKING, perfIntent, cpuInfo, &blockBlack, ULIS2_NOCB );
        //ClearRaw( &blockBlack, ULIS2_NOCB );
    }

    auto end_time   = std::chrono::steady_clock::now();
    auto delta      = std::chrono::duration_cast< std::chrono::milliseconds>(end_time - start_time ).count();
    float average   = delta / (float)num;
    std::cout << average << std::endl;

    Blend( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_NOSUBPIXEL, &blockBlack, blockDamas, ULIS2_NODELTA, BM_NORMAL, AM_NORMAL, 0.75f, ULIS2_NOCB );

    FColor color( ULIS2_FORMAT_RGBA8, { 255, 255, 255, 127 } );
    std::string text = "Damas";
    int ulis2size = 100;
    FRect metrics2 = TextMetrics( text, font, ulis2size, glm::vec2( 0.f ), ULIS2_NOTRANSFORM );
    int x = ( blockDamas->Width() / 2 - metrics2.w / 2 ) - metrics2.x;
    int y = ( blockDamas->Height() / 2 - metrics2.h / 2 ) - metrics2.y;
    metrics2.x = x + metrics2.x;
    metrics2.y = y + metrics2.y;
    RenderText( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_AA, blockDamas, text, font, ulis2size, color, glm::vec2( x, y ), glm::mat2( 1.f ), ULIS2_NOCB );

    // Qt Window
    QApplication    app( argc, argv );
    QWidget*        widget  = new QWidget();
    QImage*         image   = new QImage( blockDamas->DataPtr(), blockDamas->Width(), blockDamas->Height(), blockDamas->BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    QPixmap         pixmap  = QPixmap::fromImage( *image );
    QLabel*         label   = new QLabel( widget );
    label->setPixmap( pixmap );
    widget->resize( pixmap.size() );
    widget->show();

    int exit_code = app.exec();
    delete  label;
    delete  image;
    delete  widget;
    delete  blockDamas;
    return  exit_code;
}

