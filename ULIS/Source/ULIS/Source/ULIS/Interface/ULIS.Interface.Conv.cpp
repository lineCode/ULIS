
/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Conv.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Interface/ULIS.Interface.Conv.h"
#include "ULIS/Interface/ULIS.Interface.Decl.h"
#include "ULIS/Conv/ULIS.Conv.ConversionContext.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FConversionContext


template< uint32 _SHSrc >
void  ConvTypeAndLayoutInto_Imp( const TBlock< _SHSrc >* iBlockSrc, IBlock* iBlockDst, const FPerfStrat& iPerfStrat )
{
    switch( iBlockDst->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                        \
            case ULIS_REG[ n ]:                                                                                           \
            {                                                                                                                           \
                TConversionContext::ConvertTypeAndLayoutInto< _SHSrc, ULIS_REG[ n ] >(                                    \
                                                                 iBlockSrc,                                                             \
                                                                 (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlockDst,             \
                                                                 iPerfStrat );                                                          \
                break;                                                                                                                  \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}


//static
void
FConversionContext::ConvTypeAndLayoutInto( const IBlock* iBlockSrc, IBlock* iBlockDst, const FPerfStrat& iPerfStrat )
{
    switch( iBlockSrc->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                        \
            case ULIS_REG[ n ]:                                                                                           \
            {                                                                                                                           \
                ConvTypeAndLayoutInto_Imp< ULIS_REG[ n ] >( (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlockSrc,    \
                                                                          iBlockDst,                                                    \
                                                                          iPerfStrat );                                                 \
                break;                                                                                                                  \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }
}

} // namespace ULIS

