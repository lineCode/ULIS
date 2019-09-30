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
    ::ULIS::IBlock* blockB = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::FPerformanceOptions opt;
    ::ULIS::FFXContext::VoronoiNoise( blockA, 1000, opt );
    ::ULIS::FFXContext::VoronoiNoise( blockB, 100, opt );
    ::ULIS::IBlock* blockC = ::ULIS::FTransformContext::GetTransformed( blockB, ::ULIS::FTransformContext::GetRotationMatrix( ::ULIS::FMath::kPIf / 2 ) );
    ::ULIS::IBlock* blockD = ::ULIS::FTransformContext::GetTransformed( blockA, ::ULIS::FTransformContext::GetRotationMatrix( ::ULIS::FMath::kPIf ) );
    ::ULIS::FBlendingContext::Blend( blockB, blockA, ::ULIS::eBlendingMode::kPinLight );
    ::ULIS::FBlendingContext::Blend( blockC, blockA, ::ULIS::eBlendingMode::kPinLight );
    ::ULIS::FBlendingContext::Blend( blockD, blockA, ::ULIS::eBlendingMode::kPinLight );
    ::ULIS::IBlock* blockE = ::ULIS::FTransformContext::GetTransformed( blockA, ::ULIS::FTransformContext::GetRotationMatrix( -::ULIS::FMath::kPIf / 2 ) );
    ::ULIS::FBlendingContext::Blend( blockE, blockA, ::ULIS::eBlendingMode::kPinLight );

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
    delete blockB;

    return  exit_code;
}

