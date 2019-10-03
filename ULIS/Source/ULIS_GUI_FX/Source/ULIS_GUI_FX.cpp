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
    ::ULIS::IBlock* blockA = ::ULIS::FMakeContext::MakeBlock( 64, 64, ::ULIS::FBlockRGBA8::TypeId() );
    for( int i = 0; i < blockA->Height(); ++i )
        for( int j = 0; j < blockA->Width(); ++j )
            blockA->SetPixelColor( j, i, ::ULIS::CColor::FromHSLF( j / (float)blockA->Width(), 1.f, 0.5f ) );
    ::ULIS::FPerformanceOptions opt;
    opt.desired_workers = 1;
    glm::mat3 transform = ::ULIS::FTransformContext::GetRotationMatrix( 3.14 / 2 ) * ::ULIS::FTransformContext::GetScaleMatrix( 10, 10 );
    ::ULIS::IBlock* blockB = ::ULIS::FTransformContext::GetTransformed( blockA, transform, ::ULIS::eResamplingMethod::kLinear, opt );

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

