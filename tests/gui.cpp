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
#include <chrono>
#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>

int
main( int argc, char *argv[] ) {
    ::ul2::FThreadPool  threadPool;
    ::ul2::FPerf perfIntent_NONE( 0 );
    ::ul2::FPerf perfIntent_MT( ::ul2::Perf_MT );
    ::ul2::FPerf perfIntent_SSE_TSPEC( ::ul2::Perf_SSE4_2 | ::ul2::Perf_TSPEC );
    ::ul2::FPerf perfIntent_AVX_TSPEC( ::ul2::Perf_AVX2   | ::ul2::Perf_TSPEC );

    ::ul2::FPerfInfo perfInfo = {};
    perfInfo.pool       = &threadPool;
    perfInfo.intent     = perfIntent_AVX_TSPEC;
    perfInfo.blocking   = ULIS2_NONBLOCKING;
    perfInfo.callCB     = ULIS2_NOCB;

    ::ul2::FBlock       blockA( 800, 600,   ULIS2_FORMAT_RGBA8 );
    ::ul2::FBlock       blockB( 55, 55,     ULIS2_FORMAT_RGBA8 );
    ::ul2::FPixelValue  red(    ULIS2_FORMAT_RGBA8, { 255, 0, 0, 255 } );
    ::ul2::FPixelValue  green(  ULIS2_FORMAT_RGBA8, { 0, 255, 0, 255 } );

    ::ul2::FFillInfo fillInfo = {};
    fillInfo.destination    = &blockA;
    fillInfo.color          = &green;
    fillInfo.area           = blockA.Rect();
    fillInfo.perfInfo       = perfInfo;
    ::ul2::Fill( fillInfo );

    fillInfo.destination    = &blockB;
    fillInfo.color          = &red;
    fillInfo.area           = blockB.Rect();
    ::ul2::Fill( fillInfo );

    ::ul2::Fence( threadPool );

    //::ul2::SaveToFile( &threadPool, true, perfIntent_AVX_TSPEC, ::ul2::gCpuInfo, &blockB, "here.png", ::ul2::eImageFormat::IM_PNG );

    ::ul2::FBlendInfo blendInfo = {};
    blendInfo.source            = &blockB;
    blendInfo.backdrop          = &blockA;
    blendInfo.sourceRect        = ::ul2::FRect( 0, 0, 65, 65 );
    blendInfo.backdropPosition  = ::ul2::FVec2F( -20.5f, -20.5f );
    blendInfo.subpixelFlag      = ULIS2_AA;
    blendInfo.blendingMode      = ::ul2::BM_NORMAL;
    blendInfo.alphaMode         = ::ul2::AM_NORMAL;
    blendInfo.opacityValue      = 1.f;
    blendInfo.perfInfo          = perfInfo;
    ::ul2::Blend( blendInfo );

    // Qt Window
    QApplication    app( argc, argv );
    QWidget*        widget  = new QWidget();
    QImage*         image   = new QImage( blockA.DataPtr(), blockA.Width(), blockA.Height(), blockA.BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    QPixmap         pixmap  = QPixmap::fromImage( *image );
    QLabel*         label   = new QLabel( widget );
    label->setPixmap( pixmap );
    widget->resize( pixmap.size() );
    widget->show();

    int exit_code = app.exec();

    delete  label;
    delete  image;
    delete  widget;
    return  exit_code;
}

