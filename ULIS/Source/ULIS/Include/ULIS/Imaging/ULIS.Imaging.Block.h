/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Block.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Imaging/ULIS.Imaging.BlockSpecInfo.h"

namespace ULIS {


/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockSpec< _SH >
#define tData TBlockData< _SH >


/////////////////////////////////////////////////////
// TBlockData
template< uint32 _SH >
class TBlockData
{
};


/////////////////////////////////////////////////////
// IBlock
class IBlock
{
public:
    // Construction / Destruction
    IBlock() {}
    virtual ~IBlock() {} // Polymorphic

public:
    // Public API
    virtual const char* Name() const = 0;
    virtual const uint32 Id() const = 0;
};


/////////////////////////////////////////////////////
// TBlock
template< uint32 _SH >
class TBlock : public IBlock
{
public:
    // Construction / Destruction
    TBlock() { d = new tData(); }
    virtual ~TBlock() { delete d; } // Polymorphic
public:
    // Public API
    FORCEINLINE virtual const char*     Name() const override final { return SpecStr(); }
    FORCEINLINE virtual const uint32    Id() const override final { return SpecHash(); }
public:
    // Constexpr API
    static constexpr const char*        SpecStr() { return tSpec::spec_str; }
    static constexpr const uint32       SpecHash() { return tSpec::spec_hash; }
private:
    // Private Data
    tData* d;
};


/////////////////////////////////////////////////////
// Undefines
#undef tSpec
#undef tData


} // namespace ULIS

