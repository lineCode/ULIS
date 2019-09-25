/**
*
*   ULIS
*__________________
*
* @file     ULIS.Interface.Blend.cpp
* @author   Clement Berthaud
* @brief    This file provides the definitions for the FBlendingContext class.
*/
#include "ULIS/Interface/ULIS.Interface.Blend.h"
#include "ULIS/Interface/ULIS.Interface.Decl.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Blend/ULIS.Blend.BlendingContext.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FBlendingContext
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Public Static API
//static
void
FBlendingContext::Blend( IBlock* iBlockTop
                       , IBlock* iBlockBack
                       , eBlendingMode iMode
                       , int iX
                       , int iY
                       , float iOpacity
                       , const FPerformanceOptions& iPerformanceOptions
                       , bool iCallInvalidCB )
{
    assert( iBlockTop->Id() == iBlockBack->Id() );
    switch( iBlockTop->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                            \
            case ULIS_REG[ n ]:                                                                                                             \
            {                                                                                                                               \
                TBlendingContext< ULIS_REG[ n ] >::Blend( (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlockTop                                       \
                                                        , (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlockBack                                      \
                                                        , iMode, iOpacity, iX, iY, iPerformanceOptions, iCallInvalidCB );                   \
                break;                                                                                                                      \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}


//static
void
FBlendingContext::Blend( IBlock* iBlockTop
                       , IBlock* iBlockBack
                       , eBlendingMode iMode
                       , const FRect& iArea
                       , float iOpacity
                       , const FPerformanceOptions& iPerformanceOptions
                       , bool iCallInvalidCB )
{
    assert( iBlockTop->Id() == iBlockBack->Id() );
    switch( iBlockTop->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                            \
            case ULIS_REG[ n ]:                                                                                                             \
            {                                                                                                                               \
                TBlendingContext< ULIS_REG[ n ] >::Blend( (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlockTop                                       \
                                                        , (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlockBack                                      \
                                                        , iMode, iArea, iOpacity, iPerformanceOptions, iCallInvalidCB );                    \
                break;                                                                                                                      \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}

} // namespace ULIS

