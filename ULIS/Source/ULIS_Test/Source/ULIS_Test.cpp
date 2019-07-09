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

/*
template< uint32_t _SH >
void
Process_Imp( ::ULIS::TBlock< _SH >* iBlock )
{
    return;
}


void
Process( ::ULIS::IBlock* iBlock )
{
    if( !iBlock ) return;

    uint32_t id = iBlock->Id();
    switch( id )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data ) case ::ULIS::ulis_types_reg[ n ]: Process_Imp< ::ULIS::ulis_types_reg[ n ] >( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlock ); break;
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
        default: return;
    }
}
*/


int main()
{
    //::ULIS::PrintSpecs();
    int pause;
    std::cin >> pause;

    ::ULIS::IBlock* blockA = new ::ULIS::FBlockABGR8( 256, 256 );
    ::ULIS::IBlock* blockB = new ::ULIS::FBlockABGR8( 256, 256 );
    ::ULIS::FBlendingContext::Blend( blockA, blockB, ::ULIS::eBlendingMode::kNormal, 1.f, false );
    return 0;
}

