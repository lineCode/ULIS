/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_GUI_Fluid.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <iostream>
#include <ULIS_CORE>
#include "solver.h"

using namespace ::ULIS;

class SWindow : public QWidget
{
    Q_OBJECT
public:
    SWindow( QWidget* iParent = nullptr )
        : QWidget( iParent )
        , mBlock( nullptr )
        , mImage( nullptr )
        , mPixmap( QPixmap() )
        , mLabel( nullptr )
        , mTimer( nullptr )
    {
        mN          = 64;
        int size    = ( mN + 2 ) * ( mN + 2 );
        mU          = (float*)malloc( size * sizeof( float ) );
        mV          = (float*)malloc( size * sizeof( float ) );
        mUPrev      = (float*)malloc( size * sizeof( float ) );
        mVPrev      = (float*)malloc( size * sizeof( float ) );
        mDens       = (float*)malloc( size * sizeof( float ) );
        mDensPrev   = (float*)malloc( size * sizeof( float ) );
        memset( mU, 0, size * sizeof( float ) );
        memset( mV, 0, size * sizeof( float ) );
        memset( mUPrev, 0, size * sizeof( float ) );
        memset( mVPrev, 0, size * sizeof( float ) );
        memset( mDens, 0, size * sizeof( float ) );
        memset( mDensPrev, 0, size * sizeof( float ) );

        mDt = 0.01f;
        mDiff = 0.001f;
        mVisc = 0.f;
        mForce = 20.f;
        mSource = 100.0f;
        mLeftMouseDown = false;
        mRightMouseDown = false;
        mMousePos = QPoint();
        mOldPos = QPoint();

        mBlock = FMakeContext::MakeBlock( 512, 512, Format::Format_RGBA8 );
        mMiniBlock = FMakeContext::MakeBlock( mN + 2, mN + 2, Format::Format_RGBA8 );
        ::ULIS::FClearFillContext::Fill( mBlock, ::ULIS::CColor( 0, 255, 0 ) );
        mImage = new QImage( mBlock->DataPtr(), mBlock->Width(), mBlock->Height(), mBlock->BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
        mPixmap = QPixmap::fromImage( *mImage );
        mLabel = new QLabel( this );
        mLabel->setPixmap( mPixmap );
        this->setFixedSize( mPixmap.size() );

        mTimer = new QTimer();
        mTimer->setInterval( 1000.0 / 60.0 );
        QObject::connect( mTimer, SIGNAL( timeout() ), this, SLOT( tickEvent() ) );
        mTimer->start();
    }

    virtual ~SWindow()
    {
        delete  mTimer;
        delete  mLabel;
        delete  mImage;
        delete  mBlock;

        free( mU );
        free( mV );
        free( mUPrev );
        free( mVPrev );
        free( mDens );
        free( mDensPrev );
    }

private:
    Q_SLOT void tickEvent()
    {
        int size = ( mN + 2 ) * ( mN + 2 );
        for( int i = 0; i < size; ++i )
        {
            mDensPrev[i] = 0;
            mUPrev[i] = 0;
            mVPrev[i] = 0;
        }


        for( int i = 0; i < mN + 2; ++i ) {
            int indexA = ( ( i ) + ( mN + 2 ) * ( 0 ) );
            int indexB = ( ( i ) + ( mN + 2 ) * ( 1 ) );
            int indexC = ( ( i ) + ( mN + 2 ) * ( mN ) );
            int indexD = ( ( i ) + ( mN + 2 ) * ( mN+1 ) );
            mDens[ indexA ] = 0;
            mDens[ indexB ] = 0;
            mDensPrev[ indexA ] = 0;
            mDensPrev[ indexB ] = 0;
        }


        if( mLeftMouseDown )
        {
            const int x = ( mMousePos.x() / 512.f ) * ( mN + 2 );
            const int y = ( mMousePos.y() / 512.f ) * ( mN + 2 );
            const int rad = 5;
            const int xmin = FMath::Max( 0, x - rad );
            const int xmax = FMath::Min( mN + 2, x + rad );
            const int ymin = FMath::Max( 0, y - rad );
            const int ymax = FMath::Min( mN + 2, y + rad );
            for( int i = xmin; i < xmax; ++i )
            {
                for( int j = ymin; j < ymax; ++j )
                {
                    int index = ( ( i ) + ( mN + 2 ) * ( j ) );
                    mDensPrev[index] += mSource;
                }
            }
        }

        if( mRightMouseDown )
        {
            const int x = ( mMousePos.x() / 512.f ) * ( mN + 2 );
            const int y = ( mMousePos.y() / 512.f ) * ( mN + 2 );
            const int rad = 10;
            const int xmin = FMath::Max( 0, x - rad );
            const int xmax = FMath::Min( mN + 2, x + rad );
            const int ymin = FMath::Max( 0, y - rad );
            const int ymax = FMath::Min( mN + 2, y + rad );
            QPoint delta = mMousePos - mOldPos;
            for( int i = xmin; i < xmax; ++i )
            {
                for( int j = ymin; j < ymax; ++j )
                {
                    int index = ( ( i ) + ( mN + 2 ) * ( j ) );
                    mUPrev[index] += delta.x() * mForce;
                    mVPrev[index] += delta.y() * mForce;
                }
            }
        }

        vel_step( mN, mU, mV, mUPrev, mVPrev, mVisc, mDt );
        dens_step( mN, mDens, mDensPrev, mU, mV, mDiff, mDt );

        for( int i = 0; i < mN + 2; ++i ) {
            for( int j = 0; j < mN + 2; ++j ) {
                int index = ( ( i ) + ( mN + 2 ) * ( j ) );
                float value = mDens[ index ];
                value = FMath::Clamp( value, 0.f, 1.f );
                if( value > 0.5f )
                {
                    value = 1.f;
                }
                else if( value > 0.25f )
                {
                    value = 0.5f;
                }
                else
                {
                    value = 0.f;
                }
                mMiniBlock->SetPixelColor( i, j, CColor::FromGreyF( value ) );
                //mMiniBlock->SetPixelColor( i, j, CColor::FromRGBF( ( 1.f- value ), 0.5f, value ) );
            }
        }

        float scale = (float)mBlock->Width() / (float)mMiniBlock->Width();
        FTransformContext::TransformInto( mMiniBlock, mBlock, FTransformContext::GetScaleMatrix( scale, scale ), eResamplingMethod::kNearestNeighbour );
        mPixmap.convertFromImage( *mImage );
        mLabel->setPixmap( mPixmap );
    }

protected:

    virtual void mousePressEvent( QMouseEvent* event ) override
    {
        mMousePos = event->pos();
        mOldPos = mMousePos;

        if( event->button() == Qt::LeftButton )
            mLeftMouseDown = true;

        if( event->button() == Qt::RightButton )
            mRightMouseDown = true;
    }

    virtual void mouseMoveEvent( QMouseEvent* event ) override
    {
        mOldPos = mMousePos;
        mMousePos = event->pos();
    }

    virtual void mouseReleaseEvent( QMouseEvent* event ) override
    {
        if( event->button() == Qt::LeftButton )
            mLeftMouseDown = false;

        if( event->button() == Qt::RightButton )
            mRightMouseDown = false;
    }

private:
    int mN;
    float mDt;
    float mDiff;
    float mVisc;
    float mForce;
    float mSource;
    int mDvel;
    float* mU;
    float* mV;
    float* mUPrev;
    float* mVPrev;
    float* mDens;
    float* mDensPrev;
    bool mLeftMouseDown;
    bool mRightMouseDown;
    QPoint mMousePos;
    QPoint mOldPos;
    IBlock*     mBlock;
    IBlock*     mMiniBlock;
    QImage*     mImage;
    QPixmap     mPixmap;
    QLabel*     mLabel;
    QTimer*     mTimer;
};
