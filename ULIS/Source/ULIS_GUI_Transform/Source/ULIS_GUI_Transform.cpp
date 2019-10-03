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
    float size = 16;
    float scale = 50;
    ::ULIS::IBlock* blockA = ::ULIS::FMakeContext::MakeBlock( size, size, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::IBlock* blockB = ::ULIS::FMakeContext::MakeBlock( size * scale, size * scale, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::FClearFillContext::Clear( blockA );

    for( int y = 0; y < size; ++y ) {
        for( int x = 0; x < size; ++x ) {
            blockA->SetPixelColor( x, y, ::ULIS::CColor::FromHSVF( float( x / size ), 1.f, float( y / size ), 1.f ) );
        }
    }

    glm::mat3 transform = ::ULIS::FTransformContext::GetScaleMatrix( scale, scale );
    ::ULIS::FTransformContext::TransformInto( blockA, blockB, transform );

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

