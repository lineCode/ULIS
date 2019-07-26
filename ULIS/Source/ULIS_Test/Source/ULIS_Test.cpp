/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <ULIS_CORE>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>

int main()
{
    //::ULIS::IBlock* blockA = ::ULIS::FMakeContext::MakeBlock( 400, 400, ::ULIS::FBlockRGBA8::TypeId() );
    //::ULIS::IBlock* blockB = ::ULIS::FMakeContext::MakeBlock( 400, 400, ::ULIS::FBlockRGBA8::TypeId() );
    //::ULIS::FClearFillContext::Fill( blockA, ::ULIS::CColor::FromRGB( 255, 0, 0 ) );
    //::ULIS::FClearFillContext::Fill( blockB, ::ULIS::CColor::FromRGB( 0, 0, 255 ) );
    //::ULIS::FBlendingContext::Blend( blockB, blockA, ::ULIS::eBlendingMode::kNormal, 0.5 );
    constexpr glm::vec3 IlluminantD65( 95.0489f, 100.0f, 108.8840f  );
    constexpr glm::vec3 IlluminantD50( 96.4212,  100.0f, 82.5188    );
    return 0;
}

class FTestColorSpace_sRGB_D65
{
    const glm::vec3 IlluminantD65 = glm::vec3( 95.0489f, 100.0f, 108.8840f );
    const glm::mat3x3 Forward = glm::mat3x3(  3.2406f,  -1.5372f,  -0.4986f
                                           , -0.9689f,   1.8758f,   0.0415f
                                           ,  0.0557f,  -0.2040f,   1.0570f );
};

class FTestColorSpace_sRGB_D50Adapted
{
    const glm::vec3 IlluminantD50 = glm::vec3( 96.6797f, 100.0f, 82.5188f );
    const glm::mat3x3 Forward = glm::mat3x3(  3.2406f,  -1.5372f,  -0.4986f
                                           , -0.9689f,   1.8758f,   0.0415f
                                           ,  0.0557f,  -0.2040f,   1.0570f );
};
