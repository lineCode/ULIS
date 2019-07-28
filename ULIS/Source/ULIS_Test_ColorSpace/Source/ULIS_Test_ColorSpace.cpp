/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test_ColorSpace.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <ULIS_CORE>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <sstream>
#include <iomanip>
#include "lcms2.h"

void printvec2( const char* iTitle, const glm::vec2& iVec )
{
    std::cout << iTitle << " " << iVec.x << " " << iVec.y << std::endl;
}

void printvec3( const char* iTitle, const glm::vec3& iVec )
{
    std::cout << iTitle << " " << iVec.x << " " << iVec.y << " " << iVec.z << std::endl;
}

static const cmsHPROFILE defaultLabProfile = cmsCreateLab4Profile(0);

int main()
{
    std::cout << "Chromaticity pairs" << std::endl;
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_A      ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_A      );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_B      ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_B      );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_C      ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_C      );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_D50    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_D50    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_D55    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_D55    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_D65    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_D65    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_D75    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_D75    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_E      ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_E      );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F1     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F1     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F2     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F2     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F3     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F3     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F4     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F4     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F5     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F5     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F6     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F6     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F7     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F7     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F8     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F8     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F9     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F9     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F10    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F10    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F11    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F11    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F12    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F12    );
    std::cout << std::endl;
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_A     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_A     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_B     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_B     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_C     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_C     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_D50   ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_D50   );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_D55   ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_D55   );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_D65   ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_D65   );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_D75   ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_D75   );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_E     ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_E     );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F1    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F1    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F2    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F2    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F3    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F3    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F4    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F4    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F5    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F5    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F6    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F6    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F7    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F7    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F8    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F8    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F9    ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F9    );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F10   ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F10   );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F11   ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F11   );
    printvec2( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F12   ", ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F12   );
    std::cout << std::endl;
    std::cout << "Tristimulus values" << std::endl;
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_A      ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_A      ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_B      ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_B      ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_C      ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_C      ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_D50    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_D50    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_D55    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_D55    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_D65    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_D65    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_D75    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_D75    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_E      ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_E      ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F1     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F1     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F2     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F2     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F3     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F3     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F4     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F4     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F5     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F5     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F6     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F6     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F7     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F7     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F8     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F8     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F9     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F9     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F10    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F10    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F11    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F11    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1931_2_F12    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1931_2_F12    ) );
    std::cout << std::endl;
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_A     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_A     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_B     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_B     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_C     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_C     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_D50   ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_D50   ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_D55   ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_D55   ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_D65   ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_D65   ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_D75   ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_D75   ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_E     ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_E     ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F1    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F1    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F2    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F2    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F3    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F3    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F4    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F4    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F5    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F5    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F6    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F6    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F7    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F7    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F8    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F8    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F9    ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F9    ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F10   ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F10   ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F11   ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F11   ) );
    printvec3( "standardIlluminant_chromaticityCoordinates_CIE_1964_10_F12   ", ::ULIS::standardIlluminantTristimulusFromChromaticity( ::ULIS::standardIlluminant_chromaticityCoordinates_CIE_1964_10_F12   ) );

    cmsHPROFILE hInProfile;
    cmsHPROFILE hOutProfile;
    cmsHTRANSFORM hTransform;
    cmsUInt8Number RGB[3];
    cmsCIELab Lab = { 50, 255, 255 };
    hInProfile  = cmsCreateLab4Profile( &::ULIS::whitepoint_D65 );
    hOutProfile = cmsCreate_sRGBProfile();

    cmsColorSpaceSignature sig = cmsGetColorSpace( hInProfile );
    assert( sig == cmsSigLabData );
    hTransform = cmsCreateTransform( hInProfile
                                   , TYPE_Lab_DBL
                                   , hOutProfile
                                   , TYPE_RGB_8
                                   , INTENT_PERCEPTUAL, 0 );

    cmsCloseProfile( hInProfile  );
    cmsCloseProfile( hOutProfile );
    cmsDoTransform( hTransform, &Lab, RGB, 1 );
    cmsDeleteTransform( hTransform );
    auto dummy = 0;

    ::ULIS::FBlockRGBA8* block = new ::ULIS::FBlockRGBA8( 500, 500 );
    ::ULIS::FClearFillContext::Clear( block );
    ::ULIS::FBlockRGBA8::tPixelValue pixel;
    pixel.SetRed    ( 255   );
    pixel.SetGreen  ( 255   );
    pixel.SetBlue   ( 255   );
    pixel.SetAlpha  ( 0     );

    return 0;
}