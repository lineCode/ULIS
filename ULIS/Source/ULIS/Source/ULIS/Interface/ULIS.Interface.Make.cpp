/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Make.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Make/ULIS.Make.MakeContext.h"
#include "ULIS/Interface/ULIS.Interface.Make.h"
#include "ULIS/Interface/ULIS.Interface.Decl.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FMakeContext

//static
::ULIS::IBlock*
FMakeContext::MakeBlock( int width, int height, uint32_t ID )
{
    switch( ID )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data ) case ::ULIS::ulis_types_reg[ n ]: return  new ::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >( width, height );
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
        default: return  nullptr;
    }
}

//static
::ULIS::IBlock*
FMakeContext::MakeBlockFromExternalData( int width, int height, uint8* iData, uint32_t ID )
{
    switch( ID )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data ) case ::ULIS::ulis_types_reg[ n ]: return  new ::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >( width, height, iData );
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
        default: return  nullptr;
    }
}


//static
::ULIS::IBlock*
FMakeContext::MakeBlockFromDataPerformCopy( int width, int height, uint8* iData, uint32_t ID, const FPerfStrat& iPerfStrat )
{
    ::ULIS::IBlock* src = MakeBlockFromExternalData( width, height, iData, ID );
    ::ULIS::IBlock* ret = MakeBlock( width, height, ID );
    CopyBlockInto( src, ret );
    delete src;
    return  ret;
}


//static
::ULIS::IBlock*
FMakeContext::CopyBlock( ::ULIS::IBlock* iBlock, const FPerfStrat& iPerfStrat )
{
    return  CopyBlockRect( iBlock, FRect( 0, 0, iBlock->Width(), iBlock->Height() ), iPerfStrat );
}


//static
void
FMakeContext::CopyBlockInto( ::ULIS::IBlock* iSrc, ::ULIS::IBlock* iDst, const FPerfStrat& iPerfStrat )
{
    CopyBlockRectInto( iSrc, iDst, FRect( 0, 0, iSrc->Width(), iSrc->Height() ), iPerfStrat );
}


//static
::ULIS::IBlock*
FMakeContext::CopyBlockRect( ::ULIS::IBlock* iBlock, const FRect& iRect, const FPerfStrat& iPerfStrat )
{
    ::ULIS::IBlock* ret = MakeBlock( iRect.w, iRect.h, iBlock->Id() );
    CopyBlockRectInto( iBlock, ret, iRect, iPerfStrat );
    return  ret;
}


//static
void
FMakeContext::CopyBlockRectInto( ::ULIS::IBlock* iSrc, ::ULIS::IBlock* iDst, const FRect& iRect, const FPerfStrat& iPerfStrat )
{
    assert( iSrc->Id() == iDst->Id() );

    switch( iSrc->Id )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                    \
            case ::ULIS::ulis_types_reg[ n ]:                                                       \
            {                                                                                       \
                        ::ULIS::TMakeContext< ::ULIS::ulis_types_reg[ n ] >                         \
                        ::CopyBlockRectInto( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iSrc   \
                                           , (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iDst   \
                                           , iRect, iPerfStrat );                                   \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}

} // namespace ULIS

