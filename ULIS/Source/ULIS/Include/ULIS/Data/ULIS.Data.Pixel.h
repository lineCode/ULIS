/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Data.Pixel.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Data/ULIS.Data.Spec.h"
#include "ULIS/Maths/ULIS.Maths.Geometry.h"
#include "ULIS/Color/ULIS.Color.CColor.h"

namespace ULIS {


/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockSpec< _SH >
#define tData TBlockData< _SH >

/////////////////////////////////////////////////////
// TPixel
template< uint32_t _SH >
class TPixel final
{

public:
    // Template API
    template< typename T >
    constexpr  T Max() const  { return  (T)tSpec::_nf._tm; }

    template< typename T >
    constexpr  T Range() const  { return  (T)tSpec::_nf._rm; }

public:
    // Public API
    int         Depth           ()  const   { return tSpec::_nf._pd;                    }
    double      MaxD            ()  const   { return Max< double >();                   }
    int64_t     MaxI            ()  const   { return Max< int64_t >();                  }
    double      RangeD          ()  const   { return Range< double >();                 }
    int64_t     RangeI          ()  const   { return Range< int64_t >();                }
    e_tp        Type            ()  const   { return tSpec::_nf._tp;                    }
    e_cm        ColorModel      ()  const   { return tSpec::_nf._cm;                    }
    e_ea        ExtraAlpha      ()  const   { return tSpec::_nf._ea;                    }
    bool        HasAlpha        ()  const   { return ExtraAlpha() == e_ea::khasAlpha;   }
    const char* ChannelLayout   ()  const   { return tSpec::_nf._cl;                    }
    e_nm        NormalMode      ()  const   { return tSpec::_nf._nm;                    }
    bool        IsNormalized    ()  const   { return NormalMode() == e_nm::knormalized; }
    bool        IsDecimal       ()  const   { return tSpec::_nf._dm;                    }
    int         NumChannels     ()  const   { return tSpec::_nf._rc;                    }
    int         ColorChannels   ()  const   { return tSpec::_nf._nc;                    }

private:
    // Private Data
    uint8_t* ptr;
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec
#undef tData


} // namespace ULIS

