
/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Paint.h
* Thomas Schmitt
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerformanceOptions.h"
#include "ULIS/Color/ULIS.Color.CColor.h"
#include "ULIS/Maths/ULIS.Maths.Geometry.h"
#include <vector>

namespace ULIS { class IBlock; }

namespace ULIS {
/////////////////////////////////////////////////////
// FPainterContext
class FPainterContext
{
public:
    static void DrawLine( IBlock* iBlock, const FPoint p0, const FPoint p1, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true );
    static void DrawLineAA( IBlock* iBlock, const FPoint p0, const FPoint p1, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true );
    
    static void DrawCircleAndres( IBlock* iBlock, const FPoint iCenter, const int iRadius, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true );
    static void DrawCircleAndresAA( IBlock* iBlock, const FPoint iCenter, const int iRadius, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true );

    static void DrawCircleBresenham( IBlock* iBlock, const FPoint iCenter, const int iRadius, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true );
    static void DrawCircleBresenhamAA( IBlock* iBlock, const FPoint iCenter, const int iRadius, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true );
    
    static void DrawRotatedEllipse( IBlock* iBlock, const FPoint iCenter, const int iA, const int iB, const int iRotationDegrees, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true );
    static void DrawRotatedEllipseAA( IBlock* iBlock, const FPoint iCenter, const int iA, const int iB, const int iRotationDegrees, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions = FPerformanceOptions(), bool callInvalidCB = true );
    
    static void DrawEllipse( IBlock* iBlock, const FPoint iCenter, const int iA, const int iB, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true  );
    static void DrawEllipseAA( IBlock* iBlock, const FPoint iCenter, const int iA, const int iB, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true  );
    
    static void DrawArcAndres( IBlock* iBlock, const FPoint iCenter, const int iRadius, const int iStartDegree, const int iEndDegree, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true  );
    static void DrawArcAndresAA( IBlock* iBlock, const FPoint iCenter, const int iRadius, const int iStartDegree, const int iEndDegree, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true  );
    
    static void DrawArcBresenham( IBlock* iBlock, const FPoint iCenter, const int iRadius, const int iStartDegree, const int iEndDegree, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true  );
    static void DrawArcBresenhamAA( IBlock* iBlock, const FPoint iCenter, const int iRadius, const int iStartDegree, const int iEndDegree, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true  );
    
    static void DrawRectangle( IBlock* iBlock, const FPoint iTopLeft, const FPoint iBottomRight, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true );
    
    static void DrawPolygon( IBlock* iBlock, std::vector< FPoint >& iPoints, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool callInvalidCB = true );
    
    static void DrawQuadraticBezier( IBlock* iBlock, const FPoint& iCtrlPt0, const FPoint& iCtrlPt1, const FPoint& iCtrlPt2, const float iWeight, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions = FPerformanceOptions(), bool callInvalidCB = true );
    static void DrawQuadraticBezierAA( IBlock* iBlock, const FPoint& iCtrlPt0, const FPoint& iCtrlPt1, const FPoint& iCtrlPt2, const float iWeight, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions = FPerformanceOptions(), bool callInvalidCB = true );
};

} // namespace ULIS

