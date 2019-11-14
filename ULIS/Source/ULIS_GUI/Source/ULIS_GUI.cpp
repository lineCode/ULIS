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
#define STB_IMAGE_IMPLEMENTATION
#include <ULIS/stb/stb_image.h>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    int width, height, channels;
    stbi_set_flip_vertically_on_load( false );
    unsigned char *raw = stbi_load( "C:/Users/PRAXINOS/Documents/work/ULIS/coboi_alpha.png"
                                    , &width
                                    , &height
                                    , &channels
                                    , STBI_rgb_alpha );
    ::ULIS::IBlock* block = ::ULIS::FMakeContext::MakeBlockFromExternalDataTakeOwnership( width, height, raw, ::ULIS::Format::Format_RGBA8 );
    ::ULIS::IBlock* overlay = ::ULIS::FMakeContext::MakeBlock( width, height, ::ULIS::Format::Format_RGBA8 );
    ::ULIS::FClearFillContext::Fill( overlay, ::ULIS::CColor( 255, 0, 0 ) );
    ::ULIS::FBlendingContext::Blend( overlay, block, 0, 0, ::ULIS::eBlendingMode::kDissolve, ::ULIS::eAlphaMode::kNormal, 0.5f );
    raw = nullptr;

    QImage* image   = new QImage( block->DataPtr(), block->Width(), block->Height(), block->BytesPerScanLine(), QImage::Format::Format_RGBA8888 );
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
    delete block;
    delete overlay;

    return  exit_code;
}

