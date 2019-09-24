/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Make.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerformanceOptions.h"
#include "ULIS/Maths/ULIS.Maths.Geometry.h"

namespace ULIS { class IBlock; }

namespace ULIS {
/////////////////////////////////////////////////////
// FMakeContext
class FMakeContext
{
public:
    static ::ULIS::IBlock* MakeBlock( int width, int height, uint32_t ID, const std::string& iProfileTag = "default" );
    static ::ULIS::IBlock* MakeBlockFromExternalData( int width, int height, uint8* iData, uint32_t ID, const std::string& iProfileTag = "default" );
    static ::ULIS::IBlock* MakeBlockFromDataPerformCopy( int width, int height, uint8* iData, uint32_t ID, const std::string& iProfileTag = "default", const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions() );
    static ::ULIS::IBlock* CopyBlock( ::ULIS::IBlock* iBlock, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions() );
    static void CopyBlockInto( ::ULIS::IBlock* iSrc, ::ULIS::IBlock* iDst, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions() );
    static ::ULIS::IBlock* CopyBlockRect( ::ULIS::IBlock* iBlock, const FRect& iRect, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions() );
    static void CopyBlockRectInto( ::ULIS::IBlock* iSrc, ::ULIS::IBlock* iDst, const FRect& iRect, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions() );
};

} // namespace ULIS

