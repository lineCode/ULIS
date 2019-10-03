/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_GUI_Transform.cpp
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
    ::ULIS::IBlock* blockA = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::FFXContext::VoronoiNoise( blockA, 1000, 49 );

    ::ULIS::ParallelFor( 1024
                       ,    [&]( ::ULIS::int32 iLine ) { 
                                for( int x = 0; x < 200; ++x ) {
                                    blockA->SetPixelColor( x, iLine, ::ULIS::CColor( 255, 0, 0 ) );
                                }
                            } );

    QImage* image   = new QImage( blockA->DataPtr(), blockA->Width(), blockA->Height(), blockA->BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
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

    return  exit_code;
}

