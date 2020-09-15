// Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Particles.cpp
* @author       Clement Berthaud
* @brief        Particles application for ULIS2.
* @copyright    Copyright � 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Particles.h"
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>

#include <cstdlib>

SWindow::~SWindow() {
    delete  mCanvas;
    delete  mParticle;
    delete  mImage;
    delete  mPixmap;
    delete  mLabel;
    delete  mTimer;
}


SWindow::SWindow()
    : mHost( FHostDeviceInfo::Detect() )
    , mPool()
    , mCanvas( nullptr )
    , mParticle( nullptr )
    , mPos( 0, 0 )
    , mImage( nullptr )
    , mPixmap( nullptr )
    , mLabel( nullptr )
    , mTimer( nullptr )
    , mLeftButtonDown( false )
{
    mCanvas = new FBlock( 800, 600, ULIS2_FORMAT_RGBA8 );
    mParticle = new FBlock( 3, 3, ULIS2_FORMAT_RGBA8 );
    ClearRaw( mParticle, ULIS2_NOCB );
    mParticles.reserve( 1000 );
    mImage = new QImage( mCanvas->DataPtr(), mCanvas->Width(), mCanvas->Height(), mCanvas->BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    mPixmap = new QPixmap( QPixmap::fromImage( *mImage ) );
    mLabel = new QLabel( this );
    mLabel->setPixmap( *mPixmap );
    this->QWidget::setFixedSize( mPixmap->size() );
    mTimer = new QTimer();
    mTimer->setInterval( 1000.0 / 60.0 );
    QObject::connect( mTimer, SIGNAL( timeout() ), this, SLOT( tickEvent() ) );
    mTimer->start();

    FPixelValue particleColor = FPixelValue::FromRGBA8( 170, 40, 0, 255 );
    Fill( &mPool, ULIS2_BLOCKING, ULIS2_PERF_SSE42 | ULIS2_PERF_AVX2, mHost, ULIS2_NOCB, mParticle, particleColor, mParticle->Rect() );
    float midx = mParticle->Width() / 2.f;
    float midy = mParticle->Height() / 2.f;
    float ray2 = midx * midx;
    for( tSize i = 0; i < mParticle->Width(); ++i ) {
        for( tSize j = 0; j < mParticle->Height(); ++j ) {
            float dx = midx - i;
            float dy = midy - j;
            float dist2 = dx * dx + dy * dy;
            FPixelProxy prox = mParticle->PixelProxy( i, j );
            float alpha = 1.f - FMaths::Min( dist2 / ray2, 1.f );
            prox.SetAlphaF( alpha );
        }
    }
}


void
SWindow::mousePressEvent( QMouseEvent* event ) {
    if( event->button() != Qt::LeftButton )
        return;

    mLeftButtonDown = true;
    mPos = event->pos();
}

void
SWindow::mouseMoveEvent( QMouseEvent* event ) {
    mPos = event->pos();
}

void
SWindow::mouseReleaseEvent( QMouseEvent* event ) {
    if( event->button() == Qt::LeftButton )
        mLeftButtonDown = false;
}

void
SWindow::tickEvent() {
    std::cout << mParticles.size() << std::endl;
    if( mLeftButtonDown ) {
        for( int i = 0; i < 200; ++i ) {
            float dir = ( rand() % 3600 ) / 1800.f * 3.14159265359;
            float vel = sqrtf( sqrtf( ( rand() % 1000 ) / 1000.f ) ) * 2;
            mParticles.push_back( { FVec2F( mPos.x(), mPos.y() ), FVec2F( cos( dir ) * vel, sin( dir ) * vel ) } );
        }
    }

    Clear( &mPool, ULIS2_BLOCKING, ULIS2_PERF_SSE42 | ULIS2_PERF_AVX2, mHost, ULIS2_NOCB, mCanvas, mCanvas->Rect() );

    FRect sourceRect = mParticle->Rect();
    for( size_t i = 0; i < mParticles.size(); ++i ) {
        mParticles[i].p.x += mParticles[i].v.x = mParticles[i].v.x * 0.9f;
        mParticles[i].p.y += mParticles[i].v.y = mParticles[i].v.y * 0.9f;
        Blend( &mPool, ULIS2_BLOCKING, ULIS2_PERF_TSPEC | ULIS2_PERF_SSE42, mHost, ULIS2_NOCB, mParticle, mCanvas, sourceRect, mParticles[i].p, ULIS2_AA, BM_MULTIPY, AM_NORMAL, 0.3f );
    }

    mPixmap->convertFromImage( *mImage );
    mLabel->setPixmap( *mPixmap );
}

