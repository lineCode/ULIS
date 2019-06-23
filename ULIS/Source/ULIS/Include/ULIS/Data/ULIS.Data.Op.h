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
#include <assert.h>
#include "ULIS/Data/ULIS.Data.Types.h"

namespace ULIS {

auto
BlockSpec( uint32_t i )
{
    switch( i )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data ) case n: return  ::ULIS::TBlockSpec< ::ULIS::ulis_types_reg[ n ] >:: data;
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, _nf )
        #undef ULIS_REG_SWITCH_OP
        default: return  ::ULIS::FSpec{};
    }
}

void
PrintSpecs()
{
        for( int i = 0; i < ULIS_REG_SIZE; ++i )
    {
        auto spec = BlockSpec( i );
        std::cout << "======================================" << std::endl;
        std::cout << "spec-str          :   " << spec._ss << std::endl;
        std::cout << "spec-hash         :   " << (uint32_t)spec._sh << std::endl;
        std::cout << "type              :   " << ::ULIS::kw_tp[ (int)spec._tp ] << std::endl;
        std::cout << "color_model       :   " << ::ULIS::kw_cm[ (int)spec._cm ] << std::endl;
        std::cout << "extra_alpha       :   " << ::ULIS::kw_ea[ (int)spec._ea ] << std::endl;
        std::cout << "channel_layout    :   " << spec._cl << std::endl;
        std::cout << "normal_mode       :   " << ::ULIS::kw_nm[ (int)spec._nm ] << std::endl;
        std::cout << "decimal           :   " << spec._dm << std::endl;
        std::cout << "real_channels     :   " << (int)spec._rc << std::endl;
        std::cout << "num_channels      :   " << (int)spec._nc << std::endl;
        std::cout << "pixel_depth       :   " << (int)spec._pd << std::endl;
        std::cout << "type_max          :   " << (double)spec._tm << std::endl;
        std::cout << "======================================" << std::endl << std::endl;
    }
}

} // namespace ULIS

