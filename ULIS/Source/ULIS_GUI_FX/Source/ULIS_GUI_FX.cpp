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
    IBlock* block_background = FMakeContext::MakeBlock( 1024, 1024, Format::Format_RGBA8 );
    IBlock* block_circle = FMakeContext::MakeBlock( 1024, 1024, Format::Format_RGBA8 );
    IBlock* block_translated = FMakeContext::MakeBlock( 1024, 1024, Format::Format_RGBA8 );
    FClearFillContext::Fill( block_background, PaletteMSWindows::white );
    FClearFillContext::Clear( block_circle );
    FClearFillContext::Fill( block_translated, PaletteMSWindows::white );
    FPainterContext::DrawCircleBresenham( block_circle, FPoint( 512, 512 ), 400, PaletteMSWindows::darkCyan, true );
    glm::mat3 transform = FTransformContext::GetTranslationMatrix( 0.5, 0.5 );
    FPerformanceOptions opt;
    opt.desired_workers = 1;
    FTransformContext::TransformInto( block_circle, block_translated, transform, eResamplingMethod::kLinear, opt );
    FBlendingContext::Blend( block_translated, block_background, eBlendingMode::kNormal );

    FRect transp = FMakeContext::GetTrimmedTransparencyRect( block_circle );
    IBlock* trim = FMakeContext::CopyBlockRect( block_circle, transp );

    QImage* image   = new QImage( trim->DataPtr(), trim->Width(), trim->Height(), trim->BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
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
    delete block_background;
    delete block_circle;
    delete block_translated;

    return  exit_code;
}

