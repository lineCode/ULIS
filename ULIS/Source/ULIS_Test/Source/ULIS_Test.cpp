/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS_Test.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <iostream>
#include <ULISBlock>

void PrintFlag( uint32 iFlag )
{
    std::cout << RS_CM( iFlag ) << std::endl;
    std::cout << RS_CS( iFlag ) << std::endl;
    std::cout << RS_CT( iFlag ) << std::endl;
    std::cout << RS_LI( iFlag ) << std::endl;
    std::cout << RS_DE( iFlag ) << std::endl;
    std::cout << RS_PL( iFlag ) << std::endl;
    std::cout << RS_PR( iFlag ) << std::endl;
    std::cout << RS_NC( iFlag ) << std::endl;
    std::cout << RS_FS( iFlag ) << std::endl;
    std::cout << RS_SC( iFlag ) << std::endl;
}

int  main( int argc, char *argv[] )
{
    PrintFlag( TYPE_sRGB_RGBI8 );

    {
        IAbstractBlock* a = CreateBlock( TYPE_sRGB_RGBI8 );
        IAbstractBlock* c = CreateBlock( TYPE_sRGB_RGBI8_PLANAR );
        FBlock_sRGB_RGBI8_Planar* b = new FBlock_sRGB_RGBI8_Planar();

        //DoStuff( a );
        CallDoStuffSelectCast( a );
        DoStuff( b );
        DoStuff2( a );
        DoStuff2( b );

        delete a;
    }

    //std::cout << a->ID() << std::endl;
    std::cin.get();
}

