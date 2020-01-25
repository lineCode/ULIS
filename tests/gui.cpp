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
#include <ULIS2>
#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
using namespace ::ul2;

int
main( int argc, char *argv[] )
{
    {
        int size = 64;
        FBlock blockGreyA( size, size, ULIS2_FORMAT_GAF );
        FBlock blockGreyB( size, size, ULIS2_FORMAT_GAF );
        FBlock blockRGBAA( size, size, ULIS2_FORMAT_RGBA8 );
        FBlock blockRGBAB( size, size, ULIS2_FORMAT_RGBA8 );
        FBlock blockCMYKADA( size, size, ULIS2_FORMAT_CMYKAD );
        FBlock blockCMYKADB( size, size, ULIS2_FORMAT_CMYKAD );

        FThreadPool pool;
        FPerf perf_mono_sse( Perf_SSE4_2 );
        Clear( &pool, &blockGreyA, FPerf(), ULIS2_NO_CB );
        Clear( &pool, &blockGreyB, FPerf(), ULIS2_NO_CB );
        blockGreyB.PixelProxy( 0, 0 ).SetGreyF( 0.2f );
        blockGreyB.PixelProxy( 0, 0 ).SetAlphaF( 0.5f );

        Blend( &pool, ULIS2_BLOCKING, &blockGreyB, &blockGreyA, glm::vec2( 0 ), BM_NORMAL, AM_NORMAL, 0.8f, perf_mono_sse, ULIS2_CALL_CB );
        Blend( &pool, ULIS2_BLOCKING, &blockRGBAB, &blockRGBAA, glm::vec2( 0 ), BM_NORMAL, AM_NORMAL, 0.8f, perf_mono_sse, ULIS2_CALL_CB );
        Blend( &pool, ULIS2_BLOCKING, &blockCMYKADB, &blockCMYKADA, glm::vec2( 0 ), BM_NORMAL, AM_NORMAL, 0.8f, perf_mono_sse, ULIS2_CALL_CB );
    }



    QApplication app( argc, argv );
    int width   = 512;
    int height  = 512;
    FBlock blockA( width, height, ULIS2_FORMAT_RGBA8 );
    FBlock blockB( width, height, ULIS2_FORMAT_RGBA8 );

    FThreadPool pool;
    FPerf perf_low( Perf_Lowest );
    FPerf perf_best( Perf_Best_CPU );
    FPixel green(   ULIS2_FORMAT_RGB8, { 0, 255, 0 } );
    FPixel red(     ULIS2_FORMAT_RGB8, { 255, 0, 0 } );
    Fill( pool, &blockA, green, perf_best );
    Fill( pool, &blockB, red,   perf_best );
    BlendSubpixelRect( &pool, ULIS2_BLOCKING, &blockB, &blockA, FRect( 0, 0, 32, 32 ), glm::vec2( 32.5f, 32.5f ), BM_COLOR, AM_NORMAL, 0.8f, perf_low, ULIS2_CALL_CB );

    QWidget* widget = new  QWidget();
    QImage*  image  = new  QImage( blockA.DataPtr(), blockA.Width(), blockA.Height(), blockA.BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    QPixmap  pixmap = QPixmap::fromImage( *image );
    QLabel*  label  = new  QLabel( widget );
    label->setPixmap( pixmap );

    widget->resize( pixmap.size() );
    widget->show();

    int exit_code = app.exec();

    delete  label;
    delete  image;
    delete  widget;

    return  exit_code;
}

