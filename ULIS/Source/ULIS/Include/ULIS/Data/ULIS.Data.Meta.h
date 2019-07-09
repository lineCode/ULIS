/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Data.Block.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Color/ULIS.Color.ColorSpace.h"

namespace ULIS {
/////////////////////////////////////////////////////
// FBlockMetaData
class FBlockMetaData final
{
public:
    // Construction / Destruction
    FBlockMetaData()
    {}

    ~FBlockMetaData()
    {}

public:
    // Public API

private:
    // Private Data
    bool premultiplied;
    FColorSpace colorspace;
};


} // namespace ULIS

