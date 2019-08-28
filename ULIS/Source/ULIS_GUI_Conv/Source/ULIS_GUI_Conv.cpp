/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_GUI_Conv.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include "ULIS/Conv/ULIS.Conv.ConversionContext.h"
#include <ULIS_CORE>


int main( int argc, char *argv[] )
{
    // Qt App
    QApplication app( argc, argv );

    // ULIS Image Conv
    ::ULIS::IBlock* block8 = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockRGBA8::TypeId(), "AdobeRGB_compat" );
    ::ULIS::IBlock* blockH = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockfloatHSLhasAlphaHSLAnormalized::TypeId(), ::ULIS::DefaultProfiles::AdobeRGB_compat );
    ::ULIS::IBlock* blockf = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockBGRAf::TypeId() );
    ::ULIS::IBlock* blockg = ::ULIS::FMakeContext::MakeBlock( 1024, 1024, ::ULIS::FBlockGf::TypeId() );

    {
        ::ULIS::FValueBGRAf floatBGRAA;
        ::ULIS::FValueBGRAf floatBGRAB = std::forward< ::ULIS::FValueBGRAf&& >( floatBGRAA );
    }

    ::ULIS::FClearFillContext::Fill( block8, ::ULIS::CColor( 0, 128, 255 ) );
    ::ULIS::FClearFillContext::Clear( blockf );
    ::ULIS::FClearFillContext::Fill( blockg, ::ULIS::CColor::FromGreyF( 0.5f ) );

    ::ULIS::FConvContext::ConvTypeAndLayoutInto( block8, blockf );
    ::ULIS::FValueBGRAf floatBGRA;
    ::ULIS::TConversionContext::ConvertTypeAndLayoutInto( ((::ULIS::FBlockRGBA8*)block8)->PixelProxy( 0, 0 ), floatBGRA );
    float R = floatBGRA.R();
    float G = floatBGRA.G();
    float B = floatBGRA.B();
    float A = floatBGRA.GetAlpha();
    auto dummy = 0;

    /*
    // Qt Window
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

    return  exit_code;
    */

    return  0;
}
