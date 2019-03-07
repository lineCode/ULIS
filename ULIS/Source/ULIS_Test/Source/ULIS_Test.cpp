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


static constexpr const char layout[] = "ZYXWVUTSRQPOMNLKJIHGFEDCBA";
static constexpr const char model[] =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static constexpr const int count = ::ULIS::ct_strlen( model );
static constexpr const std::array< uint8, count > arr = ::ULIS2::make_index_from_string( layout, model );


/*
// CRC32 Table (zlib polynomial)
static constexpr uint32_t crc_table[256] = {
    0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
    0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
    0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
};
template<size_t idx>
constexpr uint32_t crc32(const char * str)
{
    return (crc32<idx-1>(str) >> 8) ^ crc_table[(crc32<idx-1>(str) ^ str[idx]) & 0x000000FF];
}

// This is the stop-recursion function
template<>
constexpr uint32_t crc32<size_t(-1)>(const char * str)
{
    return 0xFFFFFFFF;
}

// This doesn't take into account the nul char
#define COMPILE_TIME_CRC32_STR(x) (crc32<sizeof(x) - 2>(x) ^ 0xFFFFFFFF)

enum TestEnum
{
    CrcVal01 = COMPILE_TIME_CRC32_STR("stack-overflow"),
};
*/


template< class T >
class rubbish
{
};


template<> class rubbish< std::array< char, 5 > >
{
};

static constexpr const std::array< char, 5 > ak = {"0000"};


/*Main function to call above function for 0x01234567*/
int main()
{
    ::ULIS2::TBlock< ::ULIS2::Block_plannar_premultiplied_uint8_32_R8G8B8A8_R0G1B2A3_integral > block;

    std::cout<< "layout: " << layout << std::endl;
    std::cout<< "model: " << model << std::endl;
    for( int i = 0; i < arr.size(); ++i )
        std::cout << model[i] << ": " << (int)arr[i] << "; ";

    static_assert( ::ULIS::ct_findwordstart( "_PLANAR", "ULIS_TYPE_sRGB_RGBI8_PLANAR" ) == 20, "..." );
    static_assert( ::ULIS::ct_findnext( 3, "_PLANAR", "_PLANAR00000_PLANAR" ) == 12, "..." );
    static_assert( ::ULIS::ct_substring< 5 >( "jambon", 0 )[0] == 'j', "..." );



    static_assert( ::ULIS::ct_substreq( ::ULIS::ct_getsubstring( "jaekj", 0, 4 ), ::ULIS::ct_getsubstring( "jaekj", 0, 4 ) ) , "..." );


    std::cout << ::ULIS::ct_substring< 5 >( "jambon", 0 ).data() << std::endl;

    static constexpr const std::array< char, 5 > b = { "0000" };

    getchar();
    return 0;
}

