/**
*
*   ULIS
*__________________
*
* @file     ULIS.Interface.FX.cpp
* @author   Clement Berthaud
* @brief    This file provides the definitions for the ULIS.Interface.FX.h class.
*/
#include "ULIS/Interface/ULIS.Interface.FX.h"
#include "ULIS/Interface/ULIS.Interface.Decl.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/FX/ULIS.FX.FXContext.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FFXContext
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Public Static API
//static
void
FFXContext::ValueNoise( IBlock* iBlock, int iSeed, const FPerformanceOptions& iPerformanceOptions, bool iCallInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                \
            case ULIS_REG[ n ]:                                                                                 \
            {                                                                                                   \
                return  TFXContext< ULIS_REG[ n ] >::ValueNoise( (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlock       \
                                                               , iSeed, iPerformanceOptions );                  \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}


//static
void
FFXContext::VoronoiNoise( IBlock* iBlock, uint32 iCount, int iSeed, const FPerformanceOptions& iPerformanceOptions, bool iCallInvalidCB )
{
    switch( iBlock->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                \
            case ULIS_REG[ n ]:                                                                                 \
            {                                                                                                   \
                return  TFXContext< ULIS_REG[ n ] >::VoronoiNoise( (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlock     \
                                                               , iCount, iSeed, iPerformanceOptions );          \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}

} // namespace ULIS

