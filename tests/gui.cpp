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

