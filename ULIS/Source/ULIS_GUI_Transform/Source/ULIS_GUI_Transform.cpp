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
    ::ULIS::IBlock* blockA = ::ULIS::FMakeContext::MakeBlock( 500, 500, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::FClearFillContext::Fill( blockA, ::ULIS::CColor( 255, 0, 0 ) );

    glm::mat3 transform = ::ULIS::FTransformContext::GetShearMatrix( 0.5, 0 );
    ::ULIS::IBlock* blockB = ::ULIS::FTransformContext::GetTransformed( blockA, transform );


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

