/**
*
*   ULIS
*__________________
*
* @file     ULIS.Interface.Paint.h
* @author   Clement Berthaud
* @brief    This file provides the declarations for the FPainterContext class.
*/
#pragma once
#include "ULIS/ULIS.Config.h"
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerformanceOptions.h"
#include "ULIS/Color/ULIS.Color.CColor.h"
#include "ULIS/Maths/ULIS.Maths.Geometry.h"
#include <vector>

ULIS_CLASS_FORWARD_DECLARATION( IBlock )

namespace ULIS {
/////////////////////////////////////////////////////
/// @class      FPainterContext
/// @brief      The FPainterContext class provides a context for all Painting operations on Blocks.
class FPainterContext
{
public:
//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Public Static API
    /// @fn         static  void  DrawLine( IBlock* iBlock, const FPoint& iP0, const FPoint& iP1, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true )
    /// @brief      Draw a line without AA.
    /// @details    An aliased line of width 1px will be drawn in the block.
    /// @param      iBlock                  The pointer to the \e IBlock to draw on.
    /// @param      iP0                     The start point of the line.
    /// @param      iP1                     The end point of the line.
    /// @param      iColor                  The color to use for drawing.
    /// @param      iPerformanceOptions     The Performance Options for this operation, see \e FPerformanceOptions.
    /// @param      iCallInvalidCB          Whether or not the function should call the invalid call back in the back block after the operation finished.
    static void DrawLine( IBlock* iBlock
                        , const FPoint& iP0
                        , const FPoint& iP1
                        , const CColor& iColor
                        , const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions()
                        , bool iCallInvalidCB = true );


    /// @fn         static  void  DrawLineAA( IBlock* iBlock, const FPoint& iP0, const FPoint& iP1, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true )
    /// @brief      Draw a line with AA.
    /// @details    An anti-aliased line of width 1px will be drawn in the block.
    /// @param      iBlock                  The pointer to the \e IBlock to draw on.
    /// @param      iP0                     The start point of the line.
    /// @param      iP1                     The end point of the line.
    /// @param      iColor                  The color to use for drawing.
    /// @param      iPerformanceOptions     The Performance Options for this operation, see \e FPerformanceOptions.
    /// @param      iCallInvalidCB          Whether or not the function should call the invalid call back in the back block after the operation finished.
    static  void  DrawLineAA( IBlock* iBlock
                            , const FPoint& iP0
                            , const FPoint& iP1
                            , const CColor& iColor
                            , const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions()
                            , bool iCallInvalidCB = true );


    /// @fn         static  void  DrawCircleAndres( IBlock* iBlock, const FPoint& iCenter, const int iRadius, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true )
    /// @brief      Draw a circle without AA.
    /// @details    A circle will be drawn in the block.
    ///                 - Using Andres method.
    ///                 - No anti-aliasing.
    ///                 - Optional filled.
    /// @param      iBlock                  The pointer to the \e IBlock to draw on.
    /// @param      iCenter                 The center of the circle.
    /// @param      iRadius                 The radius of the circle.
    /// @param      iColor                  The color to use for drawing.
    /// @param      iFilled                 Wether the circle is filled or not.
    /// @param      iPerformanceOptions     The Performance Options for this operation, see \e FPerformanceOptions.
    /// @param      iCallInvalidCB          Whether or not the function should call the invalid call back in the back block after the operation finished.
    static  void  DrawCircleAndres( IBlock* iBlock
                                  , const FPoint& iCenter
                                  , const int iRadius
                                  , const CColor& iColor
                                  , const bool iFilled = false
                                  , const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions()
                                  , bool iCallInvalidCB = true );


    /// @fn         static  void  DrawCircleAndresAA( IBlock* iBlock, const FPoint& iCenter, const int iRadius, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true )
    /// @brief      Draw a circle with AA.
    /// @details    A circle will be drawn in the block.
    ///                 - Using Andres method.
    ///                 - With anti-aliasing.
    ///                 - Optional filled.
    /// @param      iBlock                  The pointer to the \e IBlock to draw on.
    /// @param      iCenter                 The center of the circle.
    /// @param      iRadius                 The radius of the circle.
    /// @param      iColor                  The color to use for drawing.
    /// @param      iFilled                 Wether the circle is filled or not.
    /// @param      iPerformanceOptions     The Performance Options for this operation, see \e FPerformanceOptions.
    /// @param      iCallInvalidCB          Whether or not the function should call the invalid call back in the back block after the operation finished.
    static  void  DrawCircleAndresAA( IBlock* iBlock
                                    , const FPoint& iCenter
                                    , const int iRadius
                                    , const CColor& iColor
                                    , const bool iFilled = false
                                    , const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions()
                                    , bool iCallInvalidCB = true );


    /// @fn         static  void  DrawCircleBresenham( IBlock* iBlock, const FPoint& iCenter, const int iRadius, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true )
    /// @brief      Draw a circle without AA.
    /// @details    A circle will be drawn in the block.
    ///                 - Using Bresenham method.
    ///                 - No anti-aliasing.
    ///                 - Optional filled.
    /// @param      iBlock                  The pointer to the \e IBlock to draw on.
    /// @param      iCenter                 The center of the circle.
    /// @param      iRadius                 The radius of the circle.
    /// @param      iColor                  The color to use for drawing.
    /// @param      iFilled                 Wether the circle is filled or not.
    /// @param      iPerformanceOptions     The Performance Options for this operation, see \e FPerformanceOptions.
    /// @param      iCallInvalidCB          Whether or not the function should call the invalid call back in the back block after the operation finished.
    static  void  DrawCircleBresenham( IBlock* iBlock
                                     , const FPoint& iCenter
                                     , const int iRadius
                                     , const CColor& iColor
                                     , const bool iFilled = false
                                     , const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions()
                                     , bool iCallInvalidCB = true );


    /// @fn         static  void  DrawCircleBresenhamAA( IBlock* iBlock, const FPoint& iCenter, const int iRadius, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true )
    /// @brief      Draw a circle with AA.
    /// @details    A circle will be drawn in the block.
    ///                 - Using Bresenham method.
    ///                 - With anti-aliasing.
    ///                 - Optional filled.
    /// @param      iBlock                  The pointer to the \e IBlock to draw on.
    /// @param      iCenter                 The center of the circle.
    /// @param      iRadius                 The radius of the circle.
    /// @param      iColor                  The color to use for drawing.
    /// @param      iFilled                 Wether the circle is filled or not.
    /// @param      iPerformanceOptions     The Performance Options for this operation, see \e FPerformanceOptions.
    /// @param      iCallInvalidCB          Whether or not the function should call the invalid call back in the back block after the operation finished.
    static  void  DrawCircleBresenhamAA( IBlock* iBlock
                                       , const FPoint& iCenter
                                       , const int iRadius
                                       , const CColor& iColor
                                       , const bool iFilled = false
                                       , const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions()
                                       , bool iCallInvalidCB = true );


    /// @fn         static  void  DrawRotatedEllipse( IBlock* iBlock, const FPoint& iCenter, const int iA, const int iB, const int iRotationDegrees, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true )
    /// @brief      Draw a rotated ellipsis without AA.
    /// @details    A rotated ellipsis will be drawn.
    ///                 - Without anti-aliasing.
    ///                 - Optional filled.
    /// @param      iBlock                  The pointer to the \e IBlock to draw on.
    /// @param      iCenter                 The center of the circle.
    /// @param      iA                      The first radius of the ellipse.
    /// @param      iB                      The second radius of the ellipse.
    /// @param      iRotationDegrees        The rotation of the ellipse.
    /// @param      iColor                  The color to use for drawing.
    /// @param      iFilled                 Wether the circle is filled or not.
    /// @param      iPerformanceOptions     The Performance Options for this operation, see \e FPerformanceOptions.
    /// @param      iCallInvalidCB          Whether or not the function should call the invalid call back in the back block after the operation finished.
    static  void  DrawRotatedEllipse( IBlock* iBlock
                                    , const FPoint& iCenter
                                    , const int iA
                                    , const int iB
                                    , const int iRotationDegrees
                                    , const CColor& iColor
                                    , const bool iFilled = false
                                    , const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions()
                                    , bool iCallInvalidCB = true );


    /// @fn         static  void  DrawRotatedEllipseAA( IBlock* iBlock, const FPoint& iCenter, const int iA, const int iB, const int iRotationDegrees, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions = FPerformanceOptions(), bool iCallInvalidCB = true )
    /// @brief      Draw a rotated ellipsis with AA.
    /// @details    A rotated ellipsis will be drawn.
    ///                 - With anti-aliasing.
    ///                 - Optional filled.
    /// @param      iBlock                  The pointer to the \e IBlock to draw on.
    /// @param      iCenter                 The center of the circle.
    /// @param      iA                      The first radius of the ellipse.
    /// @param      iB                      The second radius of the ellipse.
    /// @param      iRotationDegrees        The rotation of the ellipse.
    /// @param      iColor                  The color to use for drawing.
    /// @param      iFilled                 Wether the circle is filled or not.
    /// @param      iPerformanceOptions     The Performance Options for this operation, see \e FPerformanceOptions.
    /// @param      iCallInvalidCB          Whether or not the function should call the invalid call back in the back block after the operation finished.
    static  void  DrawRotatedEllipseAA( IBlock* iBlock
                                      , const FPoint& iCenter
                                      , const int iA
                                      , const int iB
                                      , const int iRotationDegrees
                                      , const CColor& iColor
                                      , const bool iFilled = false
                                      , const FPerformanceOptions& iPerformanceOptions = FPerformanceOptions()
                                      , bool iCallInvalidCB = true );


    static  void  DrawEllipse( IBlock* iBlock, const FPoint& iCenter, const int iA, const int iB, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true  );
    static  void  DrawEllipseAA( IBlock* iBlock, const FPoint& iCenter, const int iA, const int iB, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true  );
    static  void  DrawArcAndres( IBlock* iBlock, const FPoint& iCenter, const int iRadius, const int iStartDegree, const int iEndDegree, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true  );
    static  void  DrawArcAndresAA( IBlock* iBlock, const FPoint& iCenter, const int iRadius, const int iStartDegree, const int iEndDegree, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true  );
    static  void  DrawArcBresenham( IBlock* iBlock, const FPoint& iCenter, const int iRadius, const int iStartDegree, const int iEndDegree, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true  );
    static  void  DrawArcBresenhamAA( IBlock* iBlock, const FPoint& iCenter, const int iRadius, const int iStartDegree, const int iEndDegree, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true  );
    static  void  DrawRectangle( IBlock* iBlock, const FPoint& iTopLeft, const FPoint& iBottomRight, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true );
    static  void  DrawPolygon( IBlock* iBlock, std::vector< FPoint >& iPoints, const CColor& iColor, const bool iFilled = false, const FPerformanceOptions& iPerformanceOptions= FPerformanceOptions(), bool iCallInvalidCB = true );
    static  void  DrawQuadraticBezier( IBlock* iBlock, const FPoint& iCtrlPt0, const FPoint& iCtrlPt1, const FPoint& iCtrlPt2, const float iWeight, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions = FPerformanceOptions(), bool iCallInvalidCB = true );
    static  void  DrawQuadraticBezierAA( IBlock* iBlock, const FPoint& iCtrlPt0, const FPoint& iCtrlPt1, const FPoint& iCtrlPt2, const float iWeight, const CColor& iColor, const FPerformanceOptions& iPerformanceOptions = FPerformanceOptions(), bool iCallInvalidCB = true );
};

} // namespace ULIS

