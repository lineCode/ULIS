/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Spec.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <iostream>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Data/ULIS.Data.Spec.h"

namespace ULIS {

::ULIS::FSpec BlockInfo( uint32_t i );
::ULIS::FSpec BlockSpec( uint32_t i );
void PrintSpecs();

} // namespace ULIS

