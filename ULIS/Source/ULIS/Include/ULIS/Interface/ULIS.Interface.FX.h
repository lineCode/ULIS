/**
*
*   ULIS
*__________________
*
* @file     ULIS.Interface.FX.h
* @author   Clement Berthaud
* @brief    This file provides the declarations for the FFXContext class.
*/
#pragma once
#include "ULIS/ULIS.Config.h"
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerformanceOptions.h"
#include "ULIS/Color/ULIS.Color.CColor.h"
#include "ULIS/Maths/ULIS.Maths.Geometry.h"

ULIS_CLASS_FORWARD_DECLARATION( IBlock )

namespace ULIS {
/////////////////////////////////////////////////////
/// @class      FFXContext
/// @brief      The FFXContext class provides a context for all FX operations on Blocks.
class FFXContext
{
public:
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Public Static API
    static  void  ValueNoise( IBlock* iBlock, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true );
    static  void  VoronoiNoise( IBlock* iBlock, uint32 iCount, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true );

};

} // namespace ULIS

