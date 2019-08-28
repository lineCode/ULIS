/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Decl.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Interface/ULIS.Interface.Decl.h"

namespace ULIS {
/////////////////////////////////////////////////////
// Extern template declarations
void ULIS_DECL_EXPORT_SYMBOL() { return; }
/*
#define ULIS_REG_OP( z, n, data ) template class TBlock< ::ULIS::ulis_types_reg[ n ] >;
ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_OP, void )
#undef ULIS_REG_OP
*/
} // namespace ULIS

