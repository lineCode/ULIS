
/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Paint.cpp
* Thomas Schmitt
* Please refer to LICENSE.md
*/

#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Paint/ULIS.Paint.PainterContext.h"
#include "ULIS/Interface/ULIS.Interface.Paint.h"
#include "ULIS/Interface/ULIS.Interface.Decl.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FClearFillContext
//static
void
FPainterContext::DrawLine( IBlock* iBlock, const FPoint p0, const FPoint p1, const CColor& iColor, const FPerfStrat& iPerfStrat, bool callInvalidCB )
{
    
    
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                                \
            case ::ULIS::ulis_types_reg[ n ]:                                                                                                   \
            {                                                                                                                                   \
                TPainterContext< ::ULIS::ulis_types_reg[ n ] >::DrawLine( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlock, p0, p1, iColor, iPerfStrat, callInvalidCB );     \
                break;                                                                                                                          \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}
    
void
FPainterContext::DrawCircle( IBlock* iBlock, const FPoint iCenter, const int iRadius, const CColor& iColor, const FPerfStrat& iPerfStrat, bool callInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                                \
            case ::ULIS::ulis_types_reg[ n ]:                                                                                                   \
            {                                                                                                                                   \
                TPainterContext< ::ULIS::ulis_types_reg[ n ] >::DrawCircle( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlock, iCenter, iRadius, iColor, iPerfStrat, callInvalidCB );     \
                break;                                                                                                                          \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}

} // namespace ULIS

