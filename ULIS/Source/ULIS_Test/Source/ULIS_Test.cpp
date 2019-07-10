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

int main()
{
    //::ULIS::PrintSpecs();

    ::ULIS::IBlock* blockA = ::ULIS::MakeBlock( 256, 256, ::ULIS::FBlockABGR8::TypeId() );
    blockA->Fill( ::ULIS::CColor::FromRGB( 255, 0, 0, 127 ) );
    ::ULIS::IBlock* blockB = new ::ULIS::FBlockABGR8( 256, 256 );
    blockB->Fill( ::ULIS::CColor::FromRGB( 0, 0, 255, 255 ) );
    ::ULIS::FBlendingContext::Blend( blockA, blockB, ::ULIS::eBlendingMode::kNormal, 0.5 );

    return 0;
}

