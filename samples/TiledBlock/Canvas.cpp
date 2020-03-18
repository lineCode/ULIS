// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Canvas.cpp
* @author       Clement Berthaud
* @brief        TiledBlock application for ULIS2.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Canvas.h"
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>

SCanvas::~SCanvas() {
    delete  mTimer;
    delete  mTilePool;
    delete  mImage;
    delete  mPixmap;
    delete  mLabel;
    delete  mCanvas;
}


SCanvas::SCanvas()
    : mHost( FHostDeviceInfo::Detect() )
    , mPool()
    , mCanvas(      nullptr )
    , mTilePool(    nullptr )
    , mImage(       nullptr )
    , mPixmap(      nullptr )
    , mLabel(       nullptr )
    , mTimer(       nullptr )
{
    uint32 perfIntent = ULIS2_PERF_MT | ULIS2_PERF_TSPEC | ULIS2_PERF_SSE42 | ULIS2_PERF_AVX2;

    mCanvas = new  FBlock( 900, 600, ULIS2_FORMAT_RGBA8 );

    Clear( &mPool, ULIS2_BLOCKING, perfIntent, mHost, ULIS2_NOCB, mCanvas, mCanvas->Rect() );

    mImage  = new QImage( mCanvas->DataPtr(), mCanvas->Width(), mCanvas->Height(), mCanvas->BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    mPixmap = new QPixmap( QPixmap::fromImage( *mImage ) );
    mLabel  = new QLabel( this );
    mLabel->setPixmap( *mPixmap );
    this->QWidget::setFixedSize( mPixmap->size() );

    mTimer = new QTimer();
    mTimer->setInterval( 1000.0 / 24.0 );
    QObject::connect( mTimer, SIGNAL( timeout() ), this, SLOT( tickEvent() ) );
    mTimer->start();

    int tileSize    =   64;         // px
    uint64 maxRAM   =   100000;     // 1 billion Bytes, 1 Gb
    int timeoutms   =   20;
    mTilePool = new FTilePool( tileSize, tileSize, ULIS2_FORMAT_RGBA8, nullptr, maxRAM, 0, FThreadPool::MaxWorkers(), timeoutms );
    mTilePool->ClearNow( 1000 );
}


void
SCanvas::mousePressEvent( QMouseEvent* event ) {
}

void
SCanvas::mouseMoveEvent( QMouseEvent* event ) {
}

void
SCanvas::mouseReleaseEvent( QMouseEvent* event ) {
}

void
SCanvas::keyPressEvent( QKeyEvent* event ) {
    if( event->key() == Qt::Key::Key_0 )
        mTilePool->SetRAMUsageCapTarget( 0 );

    if( event->key() == Qt::Key::Key_1 )
        mTilePool->SetRAMUsageCapTarget( 100000000 );

    if( event->key() == Qt::Key::Key_2 )
        mTilePool->SetRAMUsageCapTarget( 200000000 );

    if( event->key() == Qt::Key::Key_3 )
        mTilePool->SetRAMUsageCapTarget( 400000000 );

    if( event->key() == Qt::Key::Key_4 )
        mTilePool->SetRAMUsageCapTarget( 1000000000 );

    if( event->key() == Qt::Key::Key_5 )
        mTilePool->SetRAMUsageCapTarget( 2000000000 );

    if( event->key() == Qt::Key::Key_Plus ) {
        mTilePool->PurgeAllNow();
    }
}

void
SCanvas::tickEvent() {
    mTilePool->Tick();

    Clear( &mPool, ULIS2_BLOCKING, ULIS2_PERF_SSE42 | ULIS2_PERF_AVX2, mHost, ULIS2_NOCB, mCanvas, mCanvas->Rect() );
    mPixmap->convertFromImage( *mImage );
    mLabel->setPixmap( *mPixmap );
}

