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
    ::ULIS::IBlock* blockA = ::ULIS::FMakeContext::MakeBlock( 400, 400, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::IBlock* blockB = ::ULIS::FMakeContext::MakeBlock( 400, 400, ::ULIS::FBlockRGBA8::TypeId() );
    ::ULIS::FClearFillContext::Fill( blockA, ::ULIS::CColor::FromRGB( 255, 0, 0 ) );
    ::ULIS::FClearFillContext::Fill( blockB, ::ULIS::CColor::FromRGB( 0, 0, 255 ) );
    ::ULIS::FBlendingContext::Blend( blockB, blockA, ::ULIS::eBlendingMode::kNormal, 0.5 );
    return 0;
}

