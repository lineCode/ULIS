
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
// FPainterContext
    
//static
void
FPainterContext::DrawLine( IBlock* iBlock, const FPoint p0, const FPoint p1, const CColor& iColor, const FPerfStrat& iPerfStrat, bool callInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                                                                   \
            case ::ULIS::ulis_types_reg[ n ]:                                                                                                                                      \
            {                                                                                                                                                                      \
                TPainterContext< ::ULIS::ulis_types_reg[ n ] >::DrawLine( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlock, p0, p1, iColor, iPerfStrat, callInvalidCB );     \
                break;                                                                                                                                                             \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}
    
    
//static
void
FPainterContext::DrawGradientLine( IBlock* iBlock, const FPoint p0, const FPoint p1, const CColor& iColor1, const CColor& iColor2, const FPerfStrat& iPerfStrat, bool callInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                                                                   \
            case ::ULIS::ulis_types_reg[ n ]:                                                                                                                                      \
            {                                                                                                                                                                      \
                TPainterContext< ::ULIS::ulis_types_reg[ n ] >::DrawGradientLine( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlock, p0, p1, iColor1, iColor2, iPerfStrat, callInvalidCB );     \
                break;                                                                                                                                                             \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}
    

//static
void
FPainterContext::DrawCircle( IBlock* iBlock, const FPoint iCenter, const int iRadius, const CColor& iColor, const FPerfStrat& iPerfStrat, bool callInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                                                                               \
            case ::ULIS::ulis_types_reg[ n ]:                                                                                                                                                  \
            {                                                                                                                                                                                  \
                TPainterContext< ::ULIS::ulis_types_reg[ n ] >::DrawCircle( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlock, iCenter, iRadius, iColor, iPerfStrat, callInvalidCB );     \
                break;                                                                                                                                                                         \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}
    
    
//static
void
FPainterContext::DrawArc( IBlock* iBlock, const FPoint iCenter, const int iRadius, const int iStartDegree, const int iEndDegree, const CColor& iColor, const FPerfStrat& iPerfStrat, bool callInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                                                                               \
            case ::ULIS::ulis_types_reg[ n ]:                                                                                                                                                  \
            {                                                                                                                                                                                  \
                TPainterContext< ::ULIS::ulis_types_reg[ n ] >::DrawArc( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlock, iCenter, iRadius, iStartDegree, iEndDegree, iColor, iPerfStrat, callInvalidCB );     \
                break;                                                                                                                                                                         \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}
    
    
//static
void
FPainterContext::DrawRectangle( IBlock* iBlock, const FPoint iTopLeft, const FPoint iBottomRight, const CColor& iColor, const bool iFilled, const FPerfStrat& iPerfStrat, bool callInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                                                                                         \
            case ::ULIS::ulis_types_reg[ n ]:                                                                                                                                                            \
            {                                                                                                                                                                                            \
                TPainterContext< ::ULIS::ulis_types_reg[ n ] >::DrawRectangle( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlock, iTopLeft, iBottomRight, iColor, iFilled, iPerfStrat, callInvalidCB );      \
                break;                                                                                                                                                                                   \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}
    
    
    
//static
void
FPainterContext::DrawPolygon( IBlock* iBlock, std::vector< FPoint >& iPoints, const CColor& iColor, const FPerfStrat& iPerfStrat, bool callInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                                                                                         \
            case ::ULIS::ulis_types_reg[ n ]:                                                                                                                                                            \
            {                                                                                                                                                                                            \
                TPainterContext< ::ULIS::ulis_types_reg[ n ] >::DrawPolygon( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlock, iPoints, iColor, iPerfStrat, callInvalidCB );      \
                break;                                                                                                                                                                                   \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}

} // namespace ULIS

