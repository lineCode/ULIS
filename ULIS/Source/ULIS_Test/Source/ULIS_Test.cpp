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
#include <cstdio>
#include <cstdlib>

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
    /*
    ::ULIS::IBlock* block = new ::ULIS::FBlockBGRA8( 200, 200 );
    ::ULIS::FBlockBGRA8* ptr = (::ULIS::FBlockBGRA8*)block;

    ::ULIS::FBlockBGRA8::tPixelProxy proxy = ptr->PixelProxy( 0, 0 );
    ::ULIS::FBlockBGRA8::tPixelValue value;
    value.SetRed(   'R' );
    value.SetGreen( 'G' );
    value.SetBlue(  'B' );
    value.SetAlpha( 'A' );
    proxy = value;
    std::cout << proxy.R() << std::endl;
    std::cout << proxy.G() << std::endl;
    std::cout << proxy.B() << std::endl;
    std::cout << proxy.GetAlpha() << std::endl;
    std::cout << proxy.Depth() << std::endl;

    Process( block );
    delete block;
    */

    int width       = 99;
    int height      = 98;
    int depth       = 4;
    int alignment   = 16;
    int offset      = alignment - 1;
    int required    = width * height * depth;
    int overflow    = required & offset;
    int waste       = ( alignment - overflow ) & offset;
    int storage     = required + waste;
    int total       = offset + storage;
    uint8_t* alloc = new uint8_t[ total ];

    size_t memloc_alloc_start = (size_t)alloc;
    int alloc_start_overflow = memloc_alloc_start & offset;
    int data_start_shift = ( alignment - alloc_start_overflow ) & offset;
    size_t alloc_end_memloc = memloc_alloc_start + ( data_start_shift + storage );
    int data_end_overflow = alloc_end_memloc & offset;

    std::cout << "width:        " << width << std::endl;
    std::cout << "height:       " << height << std::endl;
    std::cout << "depth:        " << depth << std::endl;
    std::cout << "alignment:    " << alignment << std::endl;
    std::cout << "offset:       " << offset << std::endl;
    std::cout << "required:     " << required << std::endl;
    std::cout << "overflow:     " << overflow << std::endl;
    std::cout << "waste:        " << waste << std::endl;
    std::cout << "storage:      " << storage << std::endl;
    std::cout << "total:        " << total << std::endl;
    std::cout << std::endl;
    std::cout << "memloc_alloc_start:   " << memloc_alloc_start << std::endl;
    std::cout << "alloc_start_overflow: " << alloc_start_overflow << std::endl;
    std::cout << "data_start_shift:     " << data_start_shift << std::endl;
    std::cout << "alloc_end_memloc:     " << alloc_end_memloc << std::endl;
    std::cout << "data_end_overflow:    " << data_end_overflow << std::endl;

    /*
    std::cout << required << std::endl;
    std::cout << (uint64_t)(memloc) << std::endl;
    std::cout << (uint64_t)(memloc + 1) << std::endl;
    std::cout << (uint64_t)(memloc + 1 ) % 16 << std::endl;
    std::cout << (uint64_t)(((size_t)(memloc + 1 ) + (alignment - 1)) & ~(alignment - 1)) << std::endl;
    */

    /*
    void* aligned_malloc(size_t required_bytes, size_t alignment) {
    int offset = alignment - 1;
    void* P = (void * ) malloc(required_bytes + offset);
    void* q = (void * ) (((size_t)(p) + offset) & ~(alignment - 1));
    return q;
    }
    */

    return 0;
}

