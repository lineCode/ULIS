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


namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >

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
    bool premultiplied
};


/////////////////////////////////////////////////////
// Undefines
#undef tSpec


} // namespace ULIS

