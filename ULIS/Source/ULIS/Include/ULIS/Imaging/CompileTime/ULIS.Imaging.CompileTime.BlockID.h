/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Imaging.CompileTime.BlockID.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/CompileTime/ULIS.Base.ConstStr.h"

namespace ULIS {

// String specification
// Prefix_[MemoryLayout_][AlphaMode_]Type_PixelDepthBits_ChannelLayout_Model_[DefaultValuesOnBuild_][Endianess_]
// Prefix: Block
// [MemoryLayout_]: Interleaved / Plannar, default Interleaved
// [AlphaMode_]: Straight / Premultiplied, default Straight
// Type_: one of uint8, uint16, uint32, uint64, int8, int16, int32, int64, float, double
// PixelDepthBits_: either 2^N, N e [ 0, +oo ]
// ChannelLayout_: Channel Name + Channel bitsn eg: R8G8B8A8, if no depth is specified, we divide PixelDepthBits by number of channels
// Model_: Either RGB; RGBA; CMY; CMYK; HSV; HSVA; etc ...
// [DefaultValuesOnBuild_]: M, m, 0 ( Max, min, 0 )
// [Endianess_]: Big / Little, default is platform Endianess
// Ex:Block_Interleaved_Staight_uint8_32_R8G8B8A8_RGBA_Default
// Deduced information:
// SubByte
// Channel Index Indirection
// Decimal / Integer

struct BlockInfo
{
    enum class eMemoryLayout : char
    {
        kInterleaved,
        kPlannar
    };

    enum class eAlphaMode : char
    {
        kStraight,
        kPremultiplied
    };

    enum class eType : char
    {
        kUint8,
        kUint16,
        kUint32,
        kUint64,
        kInt8,
        kInt16,
        kInt32,
        kInt64,
        kFloat,
        kDouble
    };

    enum class eEndianess : char
    {
        kBig,
        kLittle,
        kPlatform
    };

    enum class eKind : char
    {
        kIntegral,
        kDecimal
    };

    eMemoryLayout memory_layout; // 1 bit
    eAlphaMode alpha_mode; // 1 bit
    eType type; // 4 bit
    uint16 pixel_depth_bits; // 16 bit
    const char* channels_layout;
    uint32 channels_layout_crc32; // 32 bit
    const char* model;
    uint32 model_crc32; // 32 bit
    const char* short_model;
    uint32 short_model_crc32; // 32 bit
    bool has_alpha; // 1 bit
    bool sub_byte; // 1 bit
    eEndianess endianness; // 2 bit
    eKind kind; // 1 bit
    bool normalized; // 1 bit
};

template< int N >
static constexpr const uint64 ParseID( const_str< N > str )
{
    int size = str.Size();
    int len = str.Len();
    return 0;
}

} // namespace ULIS

