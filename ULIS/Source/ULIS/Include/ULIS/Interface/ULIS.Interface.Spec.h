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
#include "ULIS/Spec/ULIS.Spec.Spec.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FSpecContext
class FSpecContext
{
public:
    static ::ULIS::FSpec BlockInfo( uint32_t i );
    static ::ULIS::FSpec BlockSpec( uint32_t i );
    static void PrintSpecs();
    static void PrintShortSpecs();
};

} // namespace ULIS

