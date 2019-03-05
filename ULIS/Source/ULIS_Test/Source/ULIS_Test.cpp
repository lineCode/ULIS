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
    switch( iBlock->ID() )
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


void PrintBlockProperties( IBlock* iBlock )
{
    std::cout << "Block ID: " << (int)iBlock->ID() << std::endl;
    std::cout << "Block ColorModeID: " << (int)iBlock->ColorModeID() << std::endl;
    std::cout << "Block ColorSpaceID: " << (int)iBlock->ColorSpaceID() << std::endl;
    std::cout << "Block ChannelTypeID: " << (int)iBlock->ChannelTypeID() << std::endl;
    std::cout << "Block IsLinear: " << iBlock->IsLinear() << std::endl;
    std::cout << "Block IsDecimal: " << iBlock->IsDecimal() << std::endl;
    std::cout << "Block IsPlanar: " << iBlock->IsPlanar() << std::endl;
    std::cout << "Block IsPremultiplied: " << iBlock->IsPremultiplied() << std::endl;
    std::cout << "Block HasAlpha: " << iBlock->HasAlpha() << std::endl;
    std::cout << "Block IsSwapped: " << iBlock->IsSwapped() << std::endl;
    std::cout << "Block IsAlphaFirst: " << iBlock->IsAlphaFirst() << std::endl;
    std::cout << "Block ChannelCount: " << (int)iBlock->ChannelCount() << std::endl;
    std::cout << "Block TypeName: " << iBlock->TypeName() << std::endl;
    std::cout << "Block RangeMaxI: " << iBlock->RangeMaxI() << std::endl;
    std::cout << "Block RangeMinI: " << iBlock->RangeMinI() << std::endl;
    std::cout << "Block RangeMaxD: " << iBlock->RangeMaxD() << std::endl;
    std::cout << "Block RangeMinD: " << iBlock->RangeMinD() << std::endl;
    std::cout << "Block DepthBytes: " << iBlock->DepthBytes() << std::endl;
    std::cout << "Block DepthBits: " << iBlock->DepthBits() << std::endl;
    std::cout << "Block BytesPerPixel: " << iBlock->BytesPerPixel() << std::endl;
    std::cout << "Block BitsPerPixel: " << iBlock->BitsPerPixel() << std::endl;
    std::cout << "Block Width: " << iBlock->Width() << std::endl;
    std::cout << "Block Height: " << iBlock->Height() << std::endl;
}

/* function to show bytes in memory, from location start to start+n*/
void show_mem_rep(char *start, int n)  
{ 
    int i; 
    for (i = 0; i < n; i++) 
         printf(" %.2x", start[i]); 
    printf("\n"); 
} 
  
/*Main function to call above function for 0x01234567*/
int main() 
{ 
   uint16 i = 32045;
   uint8* ptr = (uint8*)&i;
   //ptr[0] = 0;
   show_mem_rep((char *)&i, sizeof(i)); 
   getchar(); 
   return 0; 
} 

