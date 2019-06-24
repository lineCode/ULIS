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


int main()
{
    ::ULIS::PrintSpecs();

    for( int i = 0; i < 4; ++i )
        std::cout << (int)::ULIS::TPixelLayout< ::ULIS::FBlockRGBA8::TypeId() >::red.arr[i] << std::endl;

    ::ULIS::TPixelValue< ::ULIS::FBlockRGBA8::TypeId() > myPixel;
    for( int i = 0; i < myPixel.NumChannels(); ++i )
        myPixel[i] = i * 18;

    std::cout << myPixel.ChannelLayout() << std::endl;
    for( int i = 0; i < myPixel.NumChannels(); ++i )
        std::cout << (int)myPixel[i] << std::endl;

    ::ULIS::IBlock* block = new ::ULIS::FBlockRGBA8( 200, 200 );
    Process( block );
    delete  block;

    return 0;
}

