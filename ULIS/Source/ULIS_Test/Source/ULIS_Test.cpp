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
    ::ULIS::FBlendingContext::Blend( blockB, blockA, ::ULIS::eBlendingMode::kNormal );

    auto dummy = 0;

    return 0;
}

