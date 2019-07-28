/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_GUI_Chromaticity.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <ULIS_CORE>
#include <ULIS/Color/ULIS.Color.ColorMatching.h>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    ::ULIS::IBlock* block = ::ULIS::FMakeContext::MakeBlock( 512, 512, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::FClearFillContext::Fill( block, ::ULIS::CColor( 20, 20, 20 ) );

    cmsHPROFILE hInProfile;
    cmsHPROFILE hOutProfile;
    cmsHTRANSFORM hTransform;
    hInProfile  = cmsCreateXYZProfile();
    hOutProfile = cmsCreate_sRGBProfile();

    hTransform = cmsCreateTransform( hInProfile
                                   , TYPE_XYZ_DBL
                                   , hOutProfile
                                   , TYPE_RGBA_8
                                   , INTENT_PERCEPTUAL, 0 );
    cmsCloseProfile( hInProfile  );
    cmsCloseProfile( hOutProfile );

    for( int i = 60; i < 280; ++i ) // 1nanometer step 830 - 360 = 470
    {
        // CIE1931 chromaticity diagram
        cmsCIEXYZ XYZ = ::ULIS::CMF_XYZ_CIE_2_1931_1nm[i];
        cmsCIExyY xyY;
        cmsXYZ2xyY( &xyY, &XYZ );
        int x = xyY.x * block->Width();
        int y = (1.0 - xyY.y) * block->Height();
        cmsDoTransform( hTransform, &XYZ, block->PixelPtr( x, y ), 1 );

        // Uniform chromaticity scale
        /*
        cmsCIEXYZ XYZ = ::ULIS::CMF_XYZ_CIE_2_1931_1nm[i];
        double sum = ( XYZ.X + 15 * XYZ.Y + 3 * XYZ.Z );
        double u = ( 4 * XYZ.X ) / sum;
        double v = ( 9 * XYZ.Y ) / sum;
        int x = u * block->Width();
        int y = (1.0 - v) * block->Height();
        cmsDoTransform( hTransform, &XYZ, block->PixelPtr( x, y ), 1 );
        */
    }

    cmsDeleteTransform( hTransform );

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
}

