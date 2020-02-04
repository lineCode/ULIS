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
#include <vectorclass.h>
#include <Windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
using namespace ::ul2;

#include <glm/gtx/matrix_transform_2d.hpp> 

int
main( int argc, char *argv[] )
{
    FBlock blockA( 1280, 800, ULIS2_FORMAT_RGBA8 );
    FBlock blockB( 64, 64, ULIS2_FORMAT_RGBA8 );
    FThreadPool pool( 4 );
    FPerf perf_best( Perf_Best_CPU );
    FCPU cpu_info;
    FPixel red( ULIS2_FORMAT_RGB8, { 255, 0, 0 } );
    FPixel green( ULIS2_FORMAT_RGB8, { 0, 255, 0 } );
    Fill( &pool,  ULIS2_BLOCKING, perf_best, cpu_info, &blockA, green, ULIS2_NOCB );
    Fill( &pool,  ULIS2_BLOCKING, perf_best, cpu_info, &blockB, red, ULIS2_NOCB );

    Blend( &pool, ULIS2_BLOCKING, perf_best, cpu_info, ULIS2_SUBPIXEL, &blockB, &blockA, glm::vec2( 64.5f, 64.5f ), BM_NORMAL, AM_NORMAL, 1.f, ULIS2_NOCB );

    // Qt Window
    QApplication app( argc, argv );
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

