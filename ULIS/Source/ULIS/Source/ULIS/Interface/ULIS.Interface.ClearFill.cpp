/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Blend.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/ClearFill/ULIS.ClearFIll.ClearFillContext.h"
#include "ULIS/Interface/ULIS.Interface.ClearFill.h"
#include "ULIS/Interface/ULIS.Interface.Decl.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FClearFillContext
//static
void
FClearFillContext::Fill( IBlock* iBlock, const CColor& iColor, const FPerfStrat& iPerfStrat, bool callInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                        \
            case ULIS_REG[ n ]:                                                                                           \
            {                                                                                                                           \
                TClearFillContext< ULIS_REG[ n ] >::Fill( (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlock          \
                                                                      , iColor, iPerfStrat, callInvalidCB );                            \
                break;                                                                                                                  \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}


//static
void
FClearFillContext::FillRect( IBlock* iBlock, const CColor& iColor, const FRect& iRect, const FPerfStrat& iPerfStrat, bool callInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                        \
            case ULIS_REG[ n ]:                                                                                           \
            {                                                                                                                           \
                TClearFillContext< ULIS_REG[ n ] >::FillRect( (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlock      \
                                                                          , iColor, iRect, iPerfStrat, callInvalidCB );                 \
                break;                                                                                                                  \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}


//static
void
FClearFillContext::Clear( IBlock* iBlock, const FPerfStrat& iPerfStrat, bool callInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                        \
            case ULIS_REG[ n ]:                                                                                           \
            {                                                                                                                           \
                TClearFillContext< ULIS_REG[ n ] >::Clear( (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlock         \
                                                                       , iPerfStrat, callInvalidCB );                                   \
                break;                                                                                                                  \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}


//static
void
FClearFillContext::ClearRect( IBlock* iBlock, const FRect& iRect, const FPerfStrat& iPerfStrat, bool callInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                        \
            case ULIS_REG[ n ]:                                                                                           \
            {                                                                                                                           \
                TClearFillContext< ULIS_REG[ n ] >::ClearRect( (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlock     \
                                                                           ,iRect,  iPerfStrat, callInvalidCB );                        \
                break;                                                                                                                  \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}

} // namespace ULIS

