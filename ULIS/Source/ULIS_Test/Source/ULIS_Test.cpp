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
    using namespace ::ULIS;
    IBlock* blockA = FMakeContext::MakeBlock( 500, 500, FBlockRGBA8::TypeId() );
    IBlock* blockB = FMakeContext::MakeBlock( 500, 500, FBlockRGBA8::TypeId() );
    FClearFillContext::Fill( blockA, CColor( 255, 0, 0 ) );
    FClearFillContext::Clear( blockB );
    FBlendingContext::Blend( blockA, blockB, eBlendingMode::kNormal );
    return 0;
}
