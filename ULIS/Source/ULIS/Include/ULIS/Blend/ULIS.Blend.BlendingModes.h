/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Blend.BlendingModes.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

namespace ULIS {
/////////////////////////////////////////////////////
// eBlendingMode
enum class eBlendingMode : char
{
    kNormal,
    kMultiply
};

#define ULIS_FOR_ALL_BLENDING_MODES_DO( iMode, X )                              \
    switch( iMode ) {                                                           \
        case eBlendingMode::kNormal:   X( eBlendingMode::kNormal );     break;  \
        case eBlendingMode::kMultiply: X( eBlendingMode::kMultiply );   break;  \
    }
} // namespace ULIS