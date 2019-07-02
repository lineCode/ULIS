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
    ::ULIS::InitID();

    //::ULIS::PrintSpecs();
    ::ULIS::TPixelValue< ::ULIS::FBlockBGRA8::TypeId() > pixel;
    ::ULIS::IBlock* block = new ::ULIS::FBlockBGRA8( 200, 200 );
    std::cout << block->UUID() << std::endl;
    ::ULIS::IBlock* block2 = new ::ULIS::FBlockBGRA8( 200, 200 );
    std::cout << block2->UUID() << std::endl;

    ::ULIS::FBlockBGRA8* cast_ptr = (::ULIS::FBlockBGRA8*)block;
    ::ULIS::FBlockBGRA8::tPixelProxy proxy = cast_ptr->PixelProxy( 0, 0 );
    auto test = proxy.RedirectedIndex( 0 );
    proxy.SetRed(   'R' );
    proxy.SetGreen( 'G' );
    proxy.SetBlue(  'B' );
    proxy.SetAlpha( 'A' );
    ::ULIS::FBlockBGRA8::tPixelValue value = cast_ptr->PixelValue( 0, 0 );
    std::cout << value.R() << std::endl;
    std::cout << value.G() << std::endl;
    std::cout << value.B() << std::endl;
    std::cout << value.GetAlpha() << std::endl;


    Process( block );
    delete block;
    delete block2;


    /*
    uint8_t * al = new uint8_t[4]();
    uint64_t val = (uint64_t)al;
    std::cout << (void*)al << std::endl;
    std::cout << val << std::endl;
    std::cout << val % 128 << std::endl;
    */

    return 0;
}

