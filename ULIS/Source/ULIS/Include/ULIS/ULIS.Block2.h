/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Block.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <stdint.h>
#include <limits>
#include "ULIS/ULIS.CompileTimeParsingUtilities.h"
#include "ULIS/ULIS.Base.h"

namespace ULIS2 {
using namespace ::ULIS;

/////////////////////////////////////////////////////
// Colormode IDs
#define ULIS_BIT    0x0
#define ULIS_GRAY   0x1
#define ULIS_RGB    0x2
#define ULIS_CMY    0x3
#define ULIS_CMYK   0x4
#define ULIS_LAB    0x5
#define ULIS_XYZ    0x6
#define ULIS_HSV    0x7
#define ULIS_HSL    0x8

/////////////////////////////////////////////////////
// Type IDs
#define ULIS_I8     0x0
#define ULIS_I16    0x1
#define ULIS_I32    0x2
#define ULIS_UI8    0x3
#define ULIS_UI16   0x4
#define ULIS_UI32   0x5
#define ULIS_F      0x6
#define ULIS_D      0x7

template< uint16 > class TBlock;
template< uint16 d > struct TBlock_Spec { static constexpr const char* m = ""; };
#define ULIS_DECLARE_STATIC_BLOCK_SPEC( i ) static constexpr const int i = __LINE__; template<> struct TBlock_Spec< i > { static constexpr const char* m = #i; static constexpr const int id = i; }; typedef TBlock< i > F##i;
ULIS_DECLARE_STATIC_BLOCK_SPEC( Block_plannar_premultiplied_uint8_32_R8G8B8A8_R0G1B2A3_integral )

/////////////////////////////////////////////////////
// TBlockData
template< uint16 block_spec_id >
class TBlockData
{
    typedef TBlock_Spec< block_spec_id > tSpec;
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
    virtual const int Id() const = 0;
};

/////////////////////////////////////////////////////
// TBlock
template< uint16 block_spec_id >
class TBlock : public IBlock
{
    typedef TBlock_Spec< block_spec_id > tSpec;
    typedef TBlockData< block_spec_id > tData;

public:
    // Construction / Destruction
    TBlock() { d = new tData(); }
    virtual ~TBlock() { delete d; } // Polymorphic

public:
    // Public API
    FORCEINLINE virtual const char* Name() const override final { return tSpec::m; }
    FORCEINLINE virtual const int Id() const override final { return tSpec::id; }

public:
    // Constexpr API
    static constexpr const char* Spec() { return tSpec::m; }

private:
    // Private Data
    tData* d;
};


} // namespace ULIS2
