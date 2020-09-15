// Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         AnimatedBezier.cpp
* @author       Clement Berthaud
* @brief        AnimatedBezier application for ULIS2.
* @copyright    Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "AnimatedBezier.h"
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>

#include <cstdlib>

SWindow::~SWindow() {
    delete  mImage;
    delete  mPixmap;
    delete  mLabel;
    delete  mTimer;
    delete  mSRC;
    delete  mDST;
}


SWindow::SWindow()
    : mHost( FHostDeviceInfo::Detect() )
    , mPool()
    , mSRC( nullptr )
    , mDST( nullptr )
    , mImage( nullptr )
    , mPixmap( nullptr )
    , mLabel( nullptr )
    , mTimer( nullptr )
    , mLeftButtonDown( false )
    , mEvolutiveAngle( 0.f )
{
    uint32 perfIntent = ULIS2_PERF_MT | ULIS2_PERF_TSPEC | ULIS2_PERF_SSE42 | ULIS2_PERF_AVX2;
    std::string path = "C:/Users/PRAXINOS/Documents/work/TEST.png";
    mSRC = XLoadFromFile( &mPool, ULIS2_BLOCKING, perfIntent, mHost, ULIS2_NOCB, path, ULIS2_FORMAT_RGBA8 );
    mDST = new  FBlock( 1024, 512, ULIS2_FORMAT_RGBA8 );
    Clear( &mPool, ULIS2_BLOCKING, perfIntent, mHost, ULIS2_NOCB, mDST, mDST->Rect() );
    mImage = new QImage( mDST->DataPtr(), mDST->Width(), mDST->Height(), mDST->BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    mPixmap = new QPixmap( QPixmap::fromImage( *mImage ) );
    mLabel = new QLabel( this );
    mLabel->setPixmap( *mPixmap );
    this->QWidget::setFixedSize( mPixmap->size() );
    mTimer = new QTimer();
    mTimer->setInterval( 1000.0 / 24.0 );
    QObject::connect( mTimer, SIGNAL( timeout() ), this, SLOT( tickEvent() ) );
    mTimer->start();
    mCtrlPts = { { FVec2F( 442, 186 ), FVec2F(), FVec2F() }
               , { FVec2F( 582, 186 ), FVec2F(), FVec2F() }
               , { FVec2F( 582, 326 ), FVec2F(), FVec2F() }
               , { FVec2F( 442, 326 ), FVec2F(), FVec2F() } };
}


void
SWindow::mousePressEvent( QMouseEvent* event ) {
    if( event->button() == Qt::LeftButton ) {
        mLeftButtonDown = true;
    }
}

void
SWindow::mouseMoveEvent( QMouseEvent* event ) {
}

void
SWindow::mouseReleaseEvent( QMouseEvent* event ) {
    if( event->button() == Qt::LeftButton )
        mLeftButtonDown = false;
}

void
SWindow::keyPressEvent( QKeyEvent* event ) {
}

void
SWindow::tickEvent() {

    float len = 150;
    mEvolutiveAngle += 0.08f;
    float evoAngle0 = mEvolutiveAngle;
    float evoAngle1 = evoAngle0 + FMaths::kPIf / 2;
    float evoAngle2 = evoAngle1 + FMaths::kPIf / 2;
    float evoAngle3 = evoAngle2 + FMaths::kPIf / 2;
    mCtrlPts[0].ctrlCW  = mCtrlPts[0].point + FVec2F( cos( evoAngle0 ), sin( evoAngle0 ) ) * len;
    mCtrlPts[0].ctrlCCW = mCtrlPts[0].point + FVec2F( cos( evoAngle1 ), sin( evoAngle1 ) ) * len;
    mCtrlPts[1].ctrlCW  = mCtrlPts[1].point + FVec2F( cos( evoAngle1 ), sin( evoAngle1 ) ) * len;
    mCtrlPts[1].ctrlCCW = mCtrlPts[1].point + FVec2F( cos( evoAngle2 ), sin( evoAngle2 ) ) * len;
    mCtrlPts[2].ctrlCW  = mCtrlPts[2].point + FVec2F( cos( evoAngle2 ), sin( evoAngle2 ) ) * len;
    mCtrlPts[2].ctrlCCW = mCtrlPts[2].point + FVec2F( cos( evoAngle3 ), sin( evoAngle3 ) ) * len;
    mCtrlPts[3].ctrlCW  = mCtrlPts[3].point + FVec2F( cos( evoAngle3 ), sin( evoAngle3 ) ) * len;
    mCtrlPts[3].ctrlCCW = mCtrlPts[3].point + FVec2F( cos( evoAngle0 ), sin( evoAngle0 ) ) * len;

    Clear( &mPool, ULIS2_BLOCKING, ULIS2_PERF_SSE42 | ULIS2_PERF_AVX2, mHost, ULIS2_NOCB, mDST, mDST->Rect() );

    TransformBezier( &mPool, ULIS2_BLOCKING, ULIS2_PERF_MT | ULIS2_PERF_SSE42 | ULIS2_PERF_AVX2, mHost, ULIS2_NOCB, mSRC, mDST, mSRC->Rect(), mCtrlPts, 0.5f, 1, INTERP_BICUBIC );
    mPixmap->convertFromImage( *mImage );
    mLabel->setPixmap( *mPixmap );
}

