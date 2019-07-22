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
#include "ULIS/Base/FeatureDetector/cpu_x86.h"

int main()
{
    //::ULIS::PrintSpecs();
    FeatureDetector::cpu_x86 feature_info;
    feature_info.detect_host();
    feature_info.print();

    ::ULIS::IBlock* blockA = ::ULIS::FMakeContext::MakeBlock( 256, 256, ::ULIS::FBlockABGR8::TypeId() );
    blockA->Fill( ::ULIS::CColor::FromRGB( 255, 0, 0, 127 ) );
    ::ULIS::IBlock* blockB = new ::ULIS::FBlockABGR8( 256, 256 );
    blockB->Fill( ::ULIS::CColor::FromRGB( 0, 0, 255, 255 ) );
    ::ULIS::FBlendingContext::Blend( blockA, blockB, ::ULIS::eBlendingMode::kNormal, 0.5 );

    uint8_t* ptr = 0;
    uint8_t* ptrstride = ptr + 45;

    return 0;
}

