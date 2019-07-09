/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Make.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Interface/ULIS.Interface.Make.h"
#include "ULIS/Interface/ULIS.Interface.Decl.h"

namespace ULIS {

::ULIS::IBlock*
MakeBlock( int width, int height, uint32_t ID )
{
    switch( ID )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data ) case ::ULIS::ulis_types_reg[ n ]: return  new ::ULIS::TBlock< ::ULIS::ulis_types_reg[ n ] >( width, height );
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
        default: return  nullptr;
    }
}

} // namespace ULIS

