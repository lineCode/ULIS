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
#include <CL/cl.hpp>
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
        float b = 0.f;
        float a = 1.f / b;
        auto dummy = 0;
    }

    cmsCIELab a = { 0.8, 0.5, 0.5 };
    cmsCIELCh b;
    cmsLab2LCh( &b, &a );
    cmsLCh2Lab( &a, &b );

    QApplication app( argc, argv );
    {
        FBlock blockA( 512, 512, ULIS2_FORMAT_CMYKAF);
        FBlock blockB( 512, 512, ULIS2_FORMAT_CMYKAF);
        FThreadPool pool;
        FPerf perf_low( Perf_Lowest );
        Blend( pool, &blockA, &blockB, FPoint(), BM_HUE, AM_NORMAL, 0.5f, perf_low );
    }
    FProfileRegistry reg;
    FPixel m0( ULIS2_FORMAT_RGBD, { 1.0, 0.0, 0.0 }, reg.GetDefaultProfileForModel( CM_RGB ) );
    FPixel m1( ULIS2_FORMAT_RGBD, { 1.0, 0.0, 0.0 }, reg.GetDefaultProfileForModel( CM_RGB ) );
    //m0 = m1;

    FPixel A( ULIS2_FORMAT_RGBD, { 1.0, 0.0, 0.0 }, reg.GetDefaultProfileForModel( CM_RGB ) );
    FPixel B( ULIS2_FORMAT_Lab8, { 255, 0, 0 },     reg.GetDefaultProfileForModel( CM_Lab ) );
    ProfileConv( A, B, reg );

    ConvT< udouble, uint8 >( A, B );

    int width   = 1024;
    int height  = 1024;
    FBlock blockA( width, height, ULIS2_FORMAT_RGBA8 );
    FBlock blockB( width, height, ULIS2_FORMAT_RGBA8 );
    //fpDispatchedBlendFunc fptr = QueryDispatch( ULIS2_FORMAT_RGBA8, BM_NORMAL, AM_ADD, FPerf() );



    eType tp = blockA.Type();
    std::cout << int(ULIS2_FORMAT_RGBA8) << std::endl;
    FThreadPool pool;
    FPerf perf_low( Perf_Lowest );
    FPerf perf_best( Perf_Best_CPU );
    Clear( pool, &blockA, perf_best );
    Clear( pool, &blockB, perf_best );
    FPixel color( ULIS2_FORMAT_RGB8, { 255, 0, 0 } );
    Fill( pool, &blockA, color, perf_best );
    Swap( pool, &blockA, 0, 2,  perf_best );
    Swap( pool, &blockA, 1, 2,  perf_best );
    Fill( pool, &blockB, color, perf_best );

    //fptr( &blockB, &blockA, FRect(), FRect(), BM_HUE, AM_NORMAL, 1.0f );

    Blend( pool, &blockB, &blockA, FPoint(), BM_HUE, AM_NORMAL, 1.0f, perf_low );
    QWidget* widget = new  QWidget();
    QImage*  image  = new  QImage( blockA.DataPtr(), blockA.Width(), blockA.Height(), blockA.BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    QPixmap  pixmap = QPixmap::fromImage( *image );
    QLabel*  label  = new  QLabel( widget );
    label->setPixmap( pixmap );

    widget->resize( pixmap.size() );
    widget->show();

    int exit_code = app.exec();

    delete label;
    delete image;
    delete widget;

    return  exit_code;
}

