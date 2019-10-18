/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_GUI.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <ULIS_CORE>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    ::ULIS::IBlock* blockA = ::ULIS::FMakeContext::MakeBlock( 220, 220, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::IBlock* blockB = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::FClearFillContext::Fill( blockB, ::ULIS::CColor( 255, 0, 0 ) );
    ::ULIS::FClearFillContext::Fill( blockA, ::ULIS::CColor( 0, 255, 0 ) );

    ::ULIS::FPerformanceOptions opt;
    opt.desired_workers = 1;
    ::ULIS::FBlendingContext::Blend( blockA, blockB, ::ULIS::eBlendingMode::kErase, 0, 0, 0.5f, opt );

    QImage* image   = new QImage( blockB->DataPtr(), blockB->Width(), blockB->Height(), blockB->BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
    QPixmap pixmap  = QPixmap::fromImage( *image );
    QWidget* w      = new QWidget();
    QLabel* label   = new QLabel( w );
    label->setPixmap( pixmap );

    w->resize( pixmap.size() );
    w->show();

    int exit_code = app.exec();

    delete label;
    delete image;
    delete w;
    delete blockA;
    delete blockB;

    return  exit_code;
}

