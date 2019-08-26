
/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Conv.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Conv/ULIS.Conv.ConversionContext.h"
#include "ULIS/Interface/ULIS.Interface.Conv.h"
#include "ULIS/Interface/ULIS.Interface.Decl.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FConvContext


template< uint32 _SHSrc >
void  ConvTypeAndLayoutInto_Imp( const TBlock< _SHSrc >* iBlockSrc, IBlock* iBlockDst, const FPerfStrat& iPerfStrat )
{
    switch( iBlockDst->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                        \
            case ::ULIS::ulis_types_reg[ n ]:                                                                                           \
            {                                                                                                                           \
                TConversionContext::ConvertTypeAndLayoutInto< _SHSrc, ::ULIS::ulis_types_reg[ n ] >(                                    \
                                                                 iBlockSrc,                                                             \
                                                                 (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlockDst,             \
                                                                 iPerfStrat );                                                          \
                break;                                                                                                                  \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}


//static
void
FConvContext::ConvTypeAndLayoutInto( const IBlock* iBlockSrc, IBlock* iBlockDst, const FPerfStrat& iPerfStrat )
{
    switch( iBlockSrc->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                        \
            case ::ULIS::ulis_types_reg[ n ]:                                                                                           \
            {                                                                                                                           \
                ConvTypeAndLayoutInto_Imp< ::ULIS::ulis_types_reg[ n ] >( (::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >*)iBlockSrc,    \
                                                                          iBlockDst,                                                    \
                                                                          iPerfStrat );                                                 \
                break;                                                                                                                  \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}


} // namespace ULIS

