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

using namespace ::ULIS;

void PrintFlag( typefield iFlag )
{
    std::cout << ULIS_RS_CM( iFlag ) << std::endl;
    std::cout << ULIS_RS_CS( iFlag ) << std::endl;
    std::cout << ULIS_RS_CT( iFlag ) << std::endl;
    std::cout << ULIS_RS_LI( iFlag ) << std::endl;
    std::cout << ULIS_RS_DE( iFlag ) << std::endl;
    std::cout << ULIS_RS_PL( iFlag ) << std::endl;
    std::cout << ULIS_RS_PR( iFlag ) << std::endl;
    std::cout << ULIS_RS_NC( iFlag ) << std::endl;
    std::cout << ULIS_RS_FS( iFlag ) << std::endl;
    std::cout << ULIS_RS_SC( iFlag ) << std::endl;
    std::cout << ULIS_RS_HE( iFlag ) << std::endl;
}


/////////////////////////////////////////////////////
// Utility

template< typefield T >
void DoStuff( TBlock< T >* iBlock )
{
    auto dummy = 0;
}


void DoStuff2( IBlock* iBlock )
{
    auto dummy = 0;
}


IBlock* CreateBlock( uint32 id )
{
    switch( id )
    {
        case ULIS_TYPE_sRGB_RGBI8:
        {
            return  new FBlock_sRGB_RGBI8();
            break;
        }

        case ULIS_TYPE_sRGB_RGBI8_PLANAR:
        {
            return  new FBlock_sRGB_RGBI8_Planar();
            break;
        }
    }
    return NULL;
}


void CallDoStuffSelectCast( IBlock* iBlock )
{
    switch( iBlock->RuntimeID() )
    {
        case ULIS_TYPE_sRGB_RGBI8:
        {
            DoStuff( (TBlock< ULIS_TYPE_sRGB_RGBI8 >*)iBlock );
            break;
        }

        case ULIS_TYPE_sRGB_RGBI8_PLANAR:
        {
            DoStuff( (TBlock< ULIS_TYPE_sRGB_RGBI8_PLANAR >*)iBlock );
            break;
        }
    }
}

template< typefield T >
void DoAssert( TBlock< T >* iBlock )
{
    static_assert( TBlock< T >::Typefield() == ULIS_TYPE_sRGB_RGBI8, "Bad Type" );
    auto dummy = 0;
}


int  main( int argc, char *argv[] )
{
    PrintFlag( ULIS_TYPE_sRGB_RGBI8 );

    {
        IBlock* a = CreateBlock( ULIS_TYPE_sRGB_RGBI8 );
        IBlock* c = CreateBlock( ULIS_TYPE_sRGB_RGBI8_PLANAR );
        FBlock_sRGB_RGBI8_Planar* b = new FBlock_sRGB_RGBI8_Planar();
        a->Bytes();

        DoAssert( (FBlock_sRGB_RGBI8*)a);

        //DoStuff( a );
        CallDoStuffSelectCast( a );
        DoStuff( b );
        DoStuff2( a );
        DoStuff2( b );

        delete a;
    }

    const char* a = typeid(int).name();
    TBlockDataInfo< ULIS_TYPE_sRGB_RGBI8, int8 > bdtinfo;
    std::cout << (int)bdtinfo.cm << std::endl;
    std::cout << (int)bdtinfo.cs << std::endl;
    std::cout << (int)bdtinfo.ct << std::endl;
    std::cout << (int)bdtinfo.li << std::endl;
    std::cout << (int)bdtinfo.de << std::endl;
    std::cout << (int)bdtinfo.pl << std::endl;
    std::cout << (int)bdtinfo.pr << std::endl;
    std::cout << (int)bdtinfo.nc << std::endl;
    std::cout << (int)bdtinfo.fs << std::endl;
    std::cout << (int)bdtinfo.sc << std::endl;
    std::cout << (int)bdtinfo.he << std::endl;
    std::cout << bdtinfo.type_name() << std::endl;
    std::cin.get();
}

