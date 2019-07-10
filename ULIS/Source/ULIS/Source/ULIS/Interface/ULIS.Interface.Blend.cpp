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
#include "ULIS/Blend/ULIS.Blend.BlendingContext.h"
#include "ULIS/Interface/ULIS.Interface.Blend.h"
#include "ULIS/Interface/ULIS.Interface.Decl.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FBlendingContext
//static
void
FBlendingContext::Blend( IBlock* iBlockTop, IBlock* iBlockBack, eBlendingMode iMode, float iOpacity, int ix, int iy, bool callInvalidCB )
{
    assert( iBlockTop->Id() == iBlockBack->Id() );

    switch( iBlockTop->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data ) case ::ULIS::ulis_types_reg[ n ]: TBlendingContext< ::ULIS::ulis_types_reg[ n ] >::Blend( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlockTop, (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlockBack, iMode, iOpacity, ix, iy, callInvalidCB ); break;
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}


//static
void
FBlendingContext::Blend( IBlock* iBlockTop, IBlock* iBlockBack, eBlendingMode iMode, const FRect& iArea, float iOpacity, bool callInvalidCB )
{
    assert( iBlockTop->Id() == iBlockBack->Id() );

    switch( iBlockTop->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data ) case ::ULIS::ulis_types_reg[ n ]: TBlendingContext< ::ULIS::ulis_types_reg[ n ] >::Blend( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlockTop, (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlockBack, iMode, iArea, iOpacity, callInvalidCB ); break;
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}

} // namespace ULIS

