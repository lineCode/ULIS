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
    using namespace ::ULIS;
    QApplication app( argc, argv );
    IBlock* src = FMakeContext::MakeBlock( 1024, 1024, Format::Format_RGBA8 );
    IBlock* dst = FMakeContext::MakeBlock( 1024, 1024, Format::Format_RGBA8 );
    //FFXContext::Clouds( src );
    FClearFillContext::Clear( src );
    FPainterContext::DrawCircleAndres( src, FPoint( 512, 512 ), 500, CColor( 255, 0, 0 ), true );
    FKernel kernel( FSize( 3, 3 )
                  , { 1,  1,  1
                    , 1, -8,  1
                    , 1,  1,  1 } );
    FFXContext::Convolution( src, dst, kernel );

    QImage*     image   = new QImage( dst->DataPtr()
                                    , dst->Width()
                                    , dst->Height()
                                    , dst->BytesPerScanLine()
                                    , QImage::Format::Format_RGBA8888 );
    QPixmap     pixmap  = QPixmap::fromImage( *image );
    QWidget*    w       = new QWidget();
    QLabel*     label   = new QLabel( w );
    label->setPixmap( pixmap );

    w->resize( pixmap.size() );
    w->show();

    int exit_code = app.exec();

    delete label;
    delete image;
    delete w;
    delete src;
    delete dst;

    return  exit_code;
}

