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
    ::ULIS::IBlock* blockB = new ::ULIS::FBlockABGR8( 256, 256 );
    ::ULIS::FBlendingContext::Blend( blockA, blockB, ::ULIS::eBlendingMode::kNormal, 0.5 );
    return 0;
}

