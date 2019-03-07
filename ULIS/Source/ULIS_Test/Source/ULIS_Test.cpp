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
#include <ULISBlock2>
#include <cstring>
#include <array>

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


static constexpr const uint8
GetIndex( const char* ilayout, const char* imodel, uint8 num )
{
    return ::ULIS::ct_findindex( imodel[num], ilayout );
}


template <uint8 N, typename T, T... Nums>
static constexpr const std::array<uint8, N-1> make_impl( const char* ilayout, const char (&imodel)[N], ::ULIS::integer_sequence<T, Nums...>) { return { GetIndex( ilayout, imodel, Nums ) ... }; }
template <uint8 N> static constexpr const std::array<uint8, N-1> make_index_from_string( const char* ilayout, const char (&imodel)[N]) { return make_impl( ilayout, imodel, ::ULIS::make_integer_sequence<uint8, N-1>()); }
static constexpr const char layout[] = "ZYXWVUTSRQPOMNLKJIHGFEDCBA";
static constexpr const char model[] =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static constexpr const int count = ::ULIS::ct_strlen( model );
static constexpr const std::array< uint8, count > arr = make_index_from_string( layout, model );

/*Main function to call above function for 0x01234567*/
int main()
{
    std::cout<< "layout: " << layout << std::endl;
    std::cout<< "model: " << model << std::endl;
    for( int i = 0; i < arr.size(); ++i )
        std::cout << model[i] << ": " << (int)arr[i] << "; ";

    //static_assert( arer.data()[0] == 'o', "..." );

    getchar();
    return 0;
}

