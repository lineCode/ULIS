/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Data.Op.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <assert.h>
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

