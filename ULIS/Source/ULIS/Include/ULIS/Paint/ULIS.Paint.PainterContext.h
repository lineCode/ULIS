/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Paint.PainterContext.h
* Thomas Schmitt
* Please refer to LICENSE.md
*/

#pragma once

#include <assert.h>
#include <vector>
#include <map>
#include <iostream>
#include <chrono>
#include <ctime>
#include "ULIS/Interface/ULIS.Interface.ClearFill.h"
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerfStrat.h"
#include "ULIS/Data/ULIS.Data.Block.h"

namespace ULIS {
/////////////////////////////////////////////////////
// Defines
#define tSpec TBlockInfo< _SH >
#define BENCHMARKMODE true
/////////////////////////////////////////////////////
// TPainterContext
template< uint32 _SH >
class TPainterContext
{
public:
    static void DrawLine( TBlock< _SH >*            iBlock
                         , const FPoint             iP0
                         , const FPoint             iP1
                         , const CColor&            iColor
                         , const FPerfStrat&        iPerfStrat
                         , bool                     callInvalidCB )
    {
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        
        FPoint p0;
        FPoint p1;
    

        if( ::ULIS::FMath::Abs( iP1.y - iP0.y ) < ::ULIS::FMath::Abs( iP1.x - iP0.x )) //x slope > y slope
        {
            if( iP1.x > iP0.x )
            {
                p0 = iP0;
                p1 = iP1;
            }
            else
            {
                p0 = iP1;
                p1 = iP0;
            }
            
            int dx = p1.x - p0.x;
            int dy = p1.y - p0.y;
            int yStep = 1;
        
            if( dy < 0)
            {
                yStep = -1;
                dy = -dy;
            }
        
            int slopeDifferential = 2 * dy - dx;
            int y = p0.y;
        
            for( int x = p0.x; x <= p1.x; x++)
            {
                iBlock->SetPixelValue( x, y, val );
                
                if( slopeDifferential > 0 )
                {
                    y += yStep;
                    slopeDifferential-=(2 * dx);
                }
                slopeDifferential+=(2 * dy);
            }
        }
        else //y slope > x slope
        {
            if( iP1.y > iP0.y )
            {
                p0 = iP0;
                p1 = iP1;
            }
            else
            {
                p0 = iP1;
                p1 = iP0;
            }
            
            int dx = p1.x - p0.x;
            int dy = p1.y - p0.y;
            int xStep = 1;
        
            if( dx < 0)
            {
                xStep = -1;
                dx = -dx;
            }
        
            int slopeDifferential = 2 * dx - dy;
            int x = p0.x;
        
            for( int y = p0.y; y <= p1.y; y++)
            {
                iBlock->SetPixelValue( x, y, val );
                
                if( slopeDifferential > 0 )
                {
                    x += xStep;
                    slopeDifferential-=(2 * dy);
                }
                slopeDifferential+=(2 * dx);
            }
        }
    }
    
    // ---
    
    
    static void DrawLineAA( TBlock< _SH >*            iBlock
                           , const FPoint             iP0
                           , const FPoint             iP1
                           , const CColor&            iColor
                           , const FPerfStrat&        iPerfStrat
                           , bool                     callInvalidCB )
    {
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        
        auto MaxAlpha = val.GetAlpha();
        
        FPoint p0;
        FPoint p1;
    

        if( ::ULIS::FMath::Abs( iP1.y - iP0.y ) < ::ULIS::FMath::Abs( iP1.x - iP0.x )) //x slope > y slope
        {
            if( iP1.x > iP0.x )
            {
                p0 = iP0;
                p1 = iP1;
            }
            else
            {
                p0 = iP1;
                p1 = iP0;
            }
            
            int dx = p1.x - p0.x;
            int dy = p1.y - p0.y;
            int yStep = 1;
        
            if( dy < 0)
            {
                yStep = -1;
                dy = -dy;
            }
            
            int errMax = -2 * dx + 2 * dy + 1;
            int errMin = 2 * dy - 1;
            int slopeDifferential = 2 * dy - dx;
            int y = p0.y;
        
            for( int x = p0.x; x <= p1.x; x++)
            {
                float alphaTop = (1 - FMath::Abs( ( float( slopeDifferential - errMax ) / float( errMin - errMax ) ) - 0.5 ) ); //Interpolation of slopedifferential between errMin and errMax
                
                val.SetAlpha( MaxAlpha * alphaTop );
                iBlock->SetPixelValue( x, y, val );
                
                val.SetAlpha( MaxAlpha * (1 - alphaTop ) );
                iBlock->SetPixelValue( x, y + yStep, val );

                if( slopeDifferential >= dx )
                {
                    y += yStep;
                    slopeDifferential-=(2 * dx);
                }
                slopeDifferential+=(2 * dy);
            }
        }
        else //y slope > x slope
        {
            if( iP1.y > iP0.y )
            {
                p0 = iP0;
                p1 = iP1;
            }
            else
            {
                p0 = iP1;
                p1 = iP0;
            }
            
            int dx = p1.x - p0.x;
            int dy = p1.y - p0.y;
            int xStep = 1;
        
            if( dx < 0)
            {
                xStep = -1;
                dx = -dx;
            }
            
            int errMax = -2 * dy + 2 * dx + 1;
            int errMin = 2 * dx - 1;
            int slopeDifferential = 2 * dx - dy;
            int x = p0.x;
        
            for( int y = p0.y; y <= p1.y; y++)
            {
                float alphaTop = (1 - FMath::Abs( ( float( slopeDifferential - errMax ) / float( errMin - errMax ) ) - 0.5 ) ); //Interpolation of slopedifferential between errMin and errMax

                val.SetAlpha( MaxAlpha * alphaTop );
                iBlock->SetPixelValue( x, y, val );
                
                val.SetAlpha( MaxAlpha * (1 - alphaTop ) );
                iBlock->SetPixelValue( x + xStep, y, val );
                
                if( slopeDifferential >= dy )
                {
                    x += xStep;
                    slopeDifferential-=(2 * dy);
                }
                slopeDifferential+=(2 * dx);
            }
        }
    }
    
    // ---
    
    
    //You can draw concentric circles with this one. But multiple pixel outline at some part of the circle -> messier result
    static void DrawCircleAndres( TBlock< _SH >*            iBlock
                                 , const FPoint             iCenter
                                 , const int                iRadius
                                 , const CColor&            iColor
                                 , const bool               iFilled
                                 , const FPerfStrat&        iPerfStrat
                                 , bool                     callInvalidCB )
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );

        int x = 0;
        int y = iRadius; //We start from the top of the circle for the first octant
        int diff = iRadius - 1;
        while (y >= x) //We draw 8 octants
        {
            //If 0° is on top and we turn clockwise
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val ); // 0° to 45°
            iBlock->SetPixelValue( iCenter.x + y, iCenter.y - x, val ); // 90° to 45°
            iBlock->SetPixelValue( iCenter.x + y, iCenter.y + x, val ); // 90° to 135°
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val ); // 180° to 135°
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val ); // 180° to 225°
            iBlock->SetPixelValue( iCenter.x - y, iCenter.y + x, val );  // 270° to 225°
            iBlock->SetPixelValue( iCenter.x - y, iCenter.y - x, val ); // 270° to 315°
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val ); // 0° to 315°
            
            if( diff >= ( 2 * x ) )
            {
                if( iFilled )
                {
                    DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x + y, iCenter.y - x ), FPoint( iCenter.x + y, iCenter.y + x ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - y, iCenter.y - x ), FPoint( iCenter.x - y, iCenter.y + x ), iColor, iPerfStrat, callInvalidCB );
                }
                diff -= ( 2 * x + 1 );
                x++;
            }
            else if ( diff < ( 2 * ( iRadius - y ) ) )
            {
                diff += ( 2 * y - 1 );
                y--;
            }
            else
            {
                if( iFilled )
                {
                    DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x + y, iCenter.y - x ), FPoint( iCenter.x + y, iCenter.y + x ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - y, iCenter.y - x ), FPoint( iCenter.x - y, iCenter.y + x ), iColor, iPerfStrat, callInvalidCB );
                }
                diff += (2 * ( y - x - 1 ) );
                y--;
                x++;
            }
        }
        
        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            if( iFilled )
                std::cout << "FilledCircleAndres: elapsed time: " << elapsed_seconds.count() << "s\n";
            else
                std::cout << "CircleAndres: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }
    
    
    
    //You can draw concentric circles with this one. But multiple pixel outline at some part of the circle -> messier result
    static void DrawCircleAndresAA( TBlock< _SH >*            iBlock
                                  , const FPoint             iCenter
                                  , const int                iRadius
                                  , const CColor&            iColor
                                  , const bool               iFilled
                                  , const FPerfStrat&        iPerfStrat
                                  , bool                     callInvalidCB )
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );

        auto MaxAlpha = val.GetAlpha();

        int x = 0;
        int y = iRadius; //We start from the top of the circle for the first octant
        int diff = iRadius - 1;
        int errMax = 2 * (iRadius - 1);
        int errMin = 0;
        while (y >= x) //We draw 8 octants
        {
            float alphaTop = (1 - FMath::Abs( ( float( diff - errMax ) / float( errMin - errMax ) ) ) ); //Interpolation of slopedifferential between errMin and errMax

            val.SetAlpha( MaxAlpha * alphaTop );
            
            //If 0° is on top and we turn clockwise
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val ); // 0° to 45°
            iBlock->SetPixelValue( iCenter.x + y, iCenter.y - x, val ); // 90° to 45°
            iBlock->SetPixelValue( iCenter.x + y, iCenter.y + x, val ); // 90° to 135°
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val ); // 180° to 135°
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val ); // 180° to 225°
            iBlock->SetPixelValue( iCenter.x - y, iCenter.y + x, val );  // 270° to 225°
            iBlock->SetPixelValue( iCenter.x - y, iCenter.y - x, val ); // 270° to 315°
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val ); // 0° to 315°
            
            val.SetAlpha( MaxAlpha * (1 - alphaTop ) );
            
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y + 1, val ); // 0° to 45°
            iBlock->SetPixelValue( iCenter.x + y - 1, iCenter.y - x, val ); // 90° to 45°
            iBlock->SetPixelValue( iCenter.x + y - 1, iCenter.y + x, val ); // 90° to 135°
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y - 1, val ); // 180° to 135°
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y - 1, val ); // 180° to 225°
            iBlock->SetPixelValue( iCenter.x - y + 1, iCenter.y + x, val );  // 270° to 225°
            iBlock->SetPixelValue( iCenter.x - y + 1, iCenter.y - x, val ); // 270° to 315°
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y + 1, val ); // 0° to 315°
            
            if( diff >= ( 2 * x ) )
            {
                if( iFilled )
                {
                    DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x + y, iCenter.y - x ), FPoint( iCenter.x + y, iCenter.y + x ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - y, iCenter.y - x ), FPoint( iCenter.x - y, iCenter.y + x ), iColor, iPerfStrat, callInvalidCB );
                }
                diff -= ( 2 * x + 1 );
                x++;
            }
            else if ( diff < ( 2 * ( iRadius - y ) ) )
            {
                diff += ( 2 * y - 1 );
                y--;
            }
            else
            {
                if( iFilled )
                {
                    DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x + y, iCenter.y - x ), FPoint( iCenter.x + y, iCenter.y + x ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - y, iCenter.y - x ), FPoint( iCenter.x - y, iCenter.y + x ), iColor, iPerfStrat, callInvalidCB );
                }
                diff += (2 * ( y - x - 1 ) );
                y--;
                x++;
            }
        }
        
        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            if( iFilled )
                std::cout << "FilledCircleAndres: elapsed time: " << elapsed_seconds.count() << "s\n";
            else
                std::cout << "CircleAndres: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }
    
    
    //Don't draw concentric circles with this one. But 1 pixel outline all around the circle -> Cleaner result
    static void DrawCircleBresenham(  TBlock< _SH >*           iBlock
                                    , const FPoint             iCenter
                                    , const int                iRadius
                                    , const CColor&            iColor
                                    , const bool               iFilled
                                    , const FPerfStrat&        iPerfStrat
                                    , bool                     callInvalidCB )
    {
        
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );

        int x = 0;
        int y = iRadius;
        int m = 5 - 4 * iRadius;
        while( x <= y )
        {
            //If 0° is on top and we turn clockwise
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val ); // 0° to 45°
            iBlock->SetPixelValue( iCenter.x + y, iCenter.y - x, val ); // 90° to 45°
            iBlock->SetPixelValue( iCenter.x + y, iCenter.y + x, val ); // 90° to 135°
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val ); // 180° to 135°
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val ); // 180° to 225°
            iBlock->SetPixelValue( iCenter.x - y, iCenter.y + x, val );  // 270° to 225°
            iBlock->SetPixelValue( iCenter.x - y, iCenter.y - x, val ); // 270° to 315°
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val ); // 0° to 315°
            
            if( iFilled )
            {
                DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                DrawLine( iBlock, FPoint( iCenter.x + y, iCenter.y - x ), FPoint( iCenter.x + y, iCenter.y + x ), iColor, iPerfStrat, callInvalidCB );
                DrawLine( iBlock, FPoint( iCenter.x - y, iCenter.y - x ), FPoint( iCenter.x - y, iCenter.y + x ), iColor, iPerfStrat, callInvalidCB );
            }
            
            if( m > 0 )
            {
                y--;
                m = m - 8 * y;
            }
            x++;
            m = m + 8 * x + 4;
        }
        
        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            if( iFilled )
                std::cout << "FilledCircleBresen: elapsed time: " << elapsed_seconds.count() << "s\n";
            else
                std::cout << "CircleBresen: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }
    
        // ---
    
    
    //You can draw concentric arcs with this one. But multiple pixel outline at some part of the arc -> messier result
    static void DrawArcAndres(  TBlock< _SH >*            iBlock
                              , const FPoint              iCenter
                              , const int                 iRadius
                              , const int                 iStartDegree
                              , const int                 iEndDegree
                              , const CColor&             iColor
                              , const FPerfStrat&         iPerfStrat
                              , bool                      callInvalidCB )
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        if( iRadius == 0 )
            return;
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        
        int sizeAngleToDraw = (iEndDegree - iStartDegree + 360) % 360; //Positive modulo
        int currentAngle = iStartDegree;
        
        int octantsToDraw[8] = {0, 0, 0, 0, 0 ,0 ,0 ,0 }; // 0: Don't draw the octant. 1: draw fully the octant. 2: draw part of the octant
        int directionToDraw[8][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} ,{0, 0} ,{0, 0} ,{0, 0} }; // 1 clockwise, -1 anti-clockwise, 0 irrelevant, second entry is angle to draw on octant
        
        if( currentAngle % 45 == 0 )
            octantsToDraw[ currentAngle / 45 ] = 1;
        else
        {
            octantsToDraw[ currentAngle / 45 ] = 2;
            directionToDraw[ currentAngle / 45 ][0] = -1;
            directionToDraw[ currentAngle / 45 ][1] = 45 - (currentAngle % 45);
        }

        sizeAngleToDraw -= ( 45 - (iStartDegree % 45) );

        while (sizeAngleToDraw >= 45 )
        {
            currentAngle = ( currentAngle + 45 ) % 360;
            octantsToDraw[ currentAngle / 45] = 1;
            sizeAngleToDraw -= 45;
        }
        
        if( sizeAngleToDraw > 0 )
        {
            currentAngle = ( currentAngle + 45 ) % 360;
            octantsToDraw[ currentAngle / 45] = 2;
            directionToDraw[ currentAngle / 45 ][0] = 1;
            directionToDraw[ currentAngle / 45 ][1] = sizeAngleToDraw;
        }
        
    
        int x = 0; // R * cos(angle) -> angle = acos( x / iRadius )
        int y = iRadius; //We start from the top of the circle for the first octant
        int diff = iRadius - 1;
        while (y >= x) //We draw 8 octants
        {
            double currentAngleOnFirstOctant = -::ULIS::FMath::RadToDeg( std::acos( double(x) / double(iRadius) ) - (PI / 2) );
            
            //If 0° is on top and we turn clockwise // Simple cases
            if( octantsToDraw[0] == 1 ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val ); // 0° to 45°
            if( octantsToDraw[1] == 1 ) iBlock->SetPixelValue( iCenter.x + y, iCenter.y - x, val ); // 90° to 45°
            if( octantsToDraw[2] == 1 ) iBlock->SetPixelValue( iCenter.x + y, iCenter.y + x, val ); // 90° to 135°
            if( octantsToDraw[3] == 1 ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val ); // 180° to 135°
            if( octantsToDraw[4] == 1 ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val ); // 180° to 225°
            if( octantsToDraw[5] == 1 ) iBlock->SetPixelValue( iCenter.x - y, iCenter.y + x, val );  // 270° to 225°
            if( octantsToDraw[6] == 1 ) iBlock->SetPixelValue( iCenter.x - y, iCenter.y - x, val ); // 270° to 315°
            if( octantsToDraw[7] == 1 ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val ); // 0° to 315°
            
            
            // Complex cases
            if( octantsToDraw[0] == 2)
            {
                if ( directionToDraw[0][0] == 1 && currentAngleOnFirstOctant < directionToDraw[0][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                else if ( directionToDraw[0][0] == -1 && currentAngleOnFirstOctant > directionToDraw[0][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
            }
            
            if( octantsToDraw[1] == 2)
            {
                if ( directionToDraw[1][0] == 1 && currentAngleOnFirstOctant > directionToDraw[1][1] ) iBlock->SetPixelValue( iCenter.x + y, iCenter.y - x, val );
                else if ( directionToDraw[1][0] == -1 && currentAngleOnFirstOctant < directionToDraw[1][1] ) iBlock->SetPixelValue( iCenter.x + y, iCenter.y - x, val );
            }

            if( octantsToDraw[2] == 2)
            {
                if ( directionToDraw[2][0] == 1 && currentAngleOnFirstOctant < directionToDraw[2][1] ) iBlock->SetPixelValue( iCenter.x + y, iCenter.y + x, val );
                else if ( directionToDraw[2][0] == -1 && currentAngleOnFirstOctant > directionToDraw[2][1] ) iBlock->SetPixelValue( iCenter.x + y, iCenter.y + x, val );
            }
            
            if( octantsToDraw[3] == 2)
            {
                if ( directionToDraw[3][0] == 1 && currentAngleOnFirstOctant > directionToDraw[3][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val );
                else if ( directionToDraw[3][0] == -1 && currentAngleOnFirstOctant < directionToDraw[3][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val );
            }
            
            if( octantsToDraw[4] == 2)
            {
                if ( directionToDraw[4][0] == 1 && currentAngleOnFirstOctant < directionToDraw[4][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                else if ( directionToDraw[4][0] == -1 && currentAngleOnFirstOctant > directionToDraw[4][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
            }
            
            if( octantsToDraw[5] == 2)
            {
                if ( directionToDraw[5][0] == 1 && currentAngleOnFirstOctant > directionToDraw[5][1] ) iBlock->SetPixelValue( iCenter.x - y, iCenter.y + x, val );
                else if ( directionToDraw[5][0] == -1 && currentAngleOnFirstOctant < directionToDraw[5][1] ) iBlock->SetPixelValue( iCenter.x - y, iCenter.y + x, val );
            }
            
            if( octantsToDraw[6] == 2)
            {
                if ( directionToDraw[6][0] == 1 && currentAngleOnFirstOctant < directionToDraw[6][1] ) iBlock->SetPixelValue( iCenter.x - y, iCenter.y - x, val );
                else if ( directionToDraw[6][0] == -1 && currentAngleOnFirstOctant > directionToDraw[6][1] ) iBlock->SetPixelValue( iCenter.x - y, iCenter.y - x, val );
            }
            
            if( octantsToDraw[7] == 2)
            {
                if ( directionToDraw[7][0] == 1 && currentAngleOnFirstOctant < directionToDraw[7][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val );
                else if ( directionToDraw[7][0] == -1 && currentAngleOnFirstOctant > directionToDraw[7][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val );
            }
            
            
            //Setup for next loop step
            if( diff >= ( 2 * x ) )
            {
                diff -= ( 2 * x + 1 );
                x++;
            }
            else if ( diff < ( 2 * ( iRadius - y ) ) )
            {
                diff += ( 2 * y - 1 );
                y--;
            }
            else
            {
                diff += (2 * ( y - x - 1 ) );
                y--;
                x++;
            }
        }
        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout << "ArcAndres: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }
    
    
    // ---
    
    //Don't draw concentric arcs with this one. But 1 pixel outline all around the arc -> Cleaner result
    static void DrawArcBresenham( TBlock< _SH >*            iBlock
                                , const FPoint              iCenter
                                , const int                 iRadius
                                , const int                 iStartDegree
                                , const int                 iEndDegree
                                , const CColor&             iColor
                                , const FPerfStrat&         iPerfStrat
                                , bool                      callInvalidCB )
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();

        if( iRadius == 0 )
            return;
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        
        int sizeAngleToDraw = (iEndDegree - iStartDegree + 360) % 360; //Positive modulo
        int currentAngle = iStartDegree;
        
        int octantsToDraw[8] = {0, 0, 0, 0, 0 ,0 ,0 ,0 }; // 0: Don't draw the octant. 1: draw fully the octant. 2: draw part of the octant
        int directionToDraw[8][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0} ,{0, 0} ,{0, 0} ,{0, 0} }; // 1 clockwise, -1 anti-clockwise, 0 irrelevant, second entry is angle to draw on octant
        
        if( currentAngle % 45 == 0 )
            octantsToDraw[ currentAngle / 45 ] = 1;
        else
        {
            octantsToDraw[ currentAngle / 45 ] = 2;
            directionToDraw[ currentAngle / 45 ][0] = -1;
            directionToDraw[ currentAngle / 45 ][1] = 45 - (currentAngle % 45);
        }

        sizeAngleToDraw -= ( 45 - (iStartDegree % 45) );

        while (sizeAngleToDraw >= 45 )
        {
            currentAngle = ( currentAngle + 45 ) % 360;
            octantsToDraw[ currentAngle / 45] = 1;
            sizeAngleToDraw -= 45;
        }
        
        if( sizeAngleToDraw > 0 )
        {
            currentAngle = ( currentAngle + 45 ) % 360;
            octantsToDraw[ currentAngle / 45] = 2;
            directionToDraw[ currentAngle / 45 ][0] = 1;
            directionToDraw[ currentAngle / 45 ][1] = sizeAngleToDraw;
        }
        
    
        int x = 0; // R * cos(angle) -> angle = acos( x / iRadius )
        int y = iRadius; //We start from the top of the circle for the first octant
        int m = 5 - 4 * iRadius;
        while ( x <= y ) //We draw 8 octants
        {
            double currentAngleOnFirstOctant = -::ULIS::FMath::RadToDeg( std::acos( double(x) / double(iRadius) ) - (PI / 2) );
            
            //If 0° is on top and we turn clockwise // Simple cases
            if( octantsToDraw[0] == 1 ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val ); // 0° to 45°
            if( octantsToDraw[1] == 1 ) iBlock->SetPixelValue( iCenter.x + y, iCenter.y - x, val ); // 90° to 45°
            if( octantsToDraw[2] == 1 ) iBlock->SetPixelValue( iCenter.x + y, iCenter.y + x, val ); // 90° to 135°
            if( octantsToDraw[3] == 1 ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val ); // 180° to 135°
            if( octantsToDraw[4] == 1 ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val ); // 180° to 225°
            if( octantsToDraw[5] == 1 ) iBlock->SetPixelValue( iCenter.x - y, iCenter.y + x, val );  // 270° to 225°
            if( octantsToDraw[6] == 1 ) iBlock->SetPixelValue( iCenter.x - y, iCenter.y - x, val ); // 270° to 315°
            if( octantsToDraw[7] == 1 ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val ); // 0° to 315°
            
            
            // Complex cases
            if( octantsToDraw[0] == 2)
            {
                if ( directionToDraw[0][0] == 1 && currentAngleOnFirstOctant < directionToDraw[0][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                else if ( directionToDraw[0][0] == -1 && currentAngleOnFirstOctant > directionToDraw[0][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
            }
            
            if( octantsToDraw[1] == 2)
            {
                if ( directionToDraw[1][0] == 1 && currentAngleOnFirstOctant > directionToDraw[1][1] ) iBlock->SetPixelValue( iCenter.x + y, iCenter.y - x, val );
                else if ( directionToDraw[1][0] == -1 && currentAngleOnFirstOctant < directionToDraw[1][1] ) iBlock->SetPixelValue( iCenter.x + y, iCenter.y - x, val );
            }

            if( octantsToDraw[2] == 2)
            {
                if ( directionToDraw[2][0] == 1 && currentAngleOnFirstOctant < directionToDraw[2][1] ) iBlock->SetPixelValue( iCenter.x + y, iCenter.y + x, val );
                else if ( directionToDraw[2][0] == -1 && currentAngleOnFirstOctant > directionToDraw[2][1] ) iBlock->SetPixelValue( iCenter.x + y, iCenter.y + x, val );
            }
            
            if( octantsToDraw[3] == 2)
            {
                if ( directionToDraw[3][0] == 1 && currentAngleOnFirstOctant > directionToDraw[3][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val );
                else if ( directionToDraw[3][0] == -1 && currentAngleOnFirstOctant < directionToDraw[3][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val );
            }
            
            if( octantsToDraw[4] == 2)
            {
                if ( directionToDraw[4][0] == 1 && currentAngleOnFirstOctant < directionToDraw[4][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                else if ( directionToDraw[4][0] == -1 && currentAngleOnFirstOctant > directionToDraw[4][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
            }
            
            if( octantsToDraw[5] == 2)
            {
                if ( directionToDraw[5][0] == 1 && currentAngleOnFirstOctant > directionToDraw[5][1] ) iBlock->SetPixelValue( iCenter.x - y, iCenter.y + x, val );
                else if ( directionToDraw[5][0] == -1 && currentAngleOnFirstOctant < directionToDraw[5][1] ) iBlock->SetPixelValue( iCenter.x - y, iCenter.y + x, val );
            }
            
            if( octantsToDraw[6] == 2)
            {
                if ( directionToDraw[6][0] == 1 && currentAngleOnFirstOctant < directionToDraw[6][1] ) iBlock->SetPixelValue( iCenter.x - y, iCenter.y - x, val );
                else if ( directionToDraw[6][0] == -1 && currentAngleOnFirstOctant > directionToDraw[6][1] ) iBlock->SetPixelValue( iCenter.x - y, iCenter.y - x, val );
            }
            
            if( octantsToDraw[7] == 2)
            {
                if ( directionToDraw[7][0] == 1 && currentAngleOnFirstOctant < directionToDraw[7][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val );
                else if ( directionToDraw[7][0] == -1 && currentAngleOnFirstOctant > directionToDraw[7][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val );
            }
            
            
            if( m > 0 )
            {
                y--;
                m = m - 8 * y;
            }
            x++;
            m = m + 8 * x + 4;
        }
        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout << "ArcBresen: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }
    
    
    // ---
    
    static void InternalGetEllipseAxesPoints(  const int iA
                                             , const int iB
                                             , double iRotationRadians
                                             , FPoint64* ptA
                                             , FPoint64* ptB )
    {
        iRotationRadians = std::fmod( iRotationRadians, PI / 2); // We want ptA in the first quadrant, et ptB in the second. This enables it
        
        ptA->x = std::cos( iRotationRadians ) * iA;
        ptA->y = std::sin( iRotationRadians ) * iA;
        
        ptB->x = std::cos( iRotationRadians + PI / 2 ) * iB;
        ptB->y = std::sin( iRotationRadians + PI / 2 ) * iB;
    }

    
    static void DrawRotatedEllipse(  TBlock< _SH >*           iBlock
                                   , const FPoint             iCenter
                                   , const int                iA
                                   , const int                iB
                                   , const int                iRotationDegrees
                                   , const CColor&            iColor
                                   , const bool               iFilled
                                   , const FPerfStrat&        iPerfStrat
                                   , bool                     callInvalidCB )
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        
        FPoint64 p1;
        FPoint64 p2;
        
        InternalGetEllipseAxesPoints( iA, iB, ::ULIS::FMath::DegToRad( iRotationDegrees ), &p1, &p2);
        
                                                           //               x  y
        std::map< int, std::vector< int > > storagePoints; // storagePoints[x][0]  We have two points for each x on the ellipse: p1(x, y0), p2(x, y1)
                                                           //                 [1]
        
        int64 p1Coeff = (p1.x * p1.x + p1.y * p1.y) * (p1.x * p1.x + p1.y * p1.y);
        int64 p2Coeff = (p2.x * p2.x + p2.y * p2.y) * (p2.x * p2.x + p2.y * p2.y);
        
        int64 A = (p1.x * p1.x) * p2Coeff +
                     (p2.x * p2.x) * p1Coeff;
        
        int64 B = ( p1.x * p1.y ) * p2Coeff +
                     ( p2.x * p2.y ) * p1Coeff;
       
        int64 C = (p1.y * p1.y) * p2Coeff +
                     (p2.y * p2.y) * p1Coeff;
        
        int64 D = p1Coeff *
                     p2Coeff;

        int64 x = -p1.x;
        int64 y = -p1.y;
        
        int64 dx = -(B * p1.x + C * p1.y);
        int64 dy =  A * p1.x + B * p1.y;
        

        //Case 1 ----------------------------
        if( dx == 0 || ::ULIS::FMath::Abs( dy / dx ) >= 1 )
        {
            //Slope = dy/dx //Initial slope to infinite
            while( dx < 0 )
            {
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                y++;
                int64 sigma = A * x * x + 2 * B * x * y + C * y * y - D;
                
                if( sigma < 0)
                {
                    if( iFilled )
                    {
                        storagePoints[x].push_back(y);
                        storagePoints[-x].push_back(-y);
                    }
                    dx -= B;
                    dy += A;
                    x--;
                }
                dx += C;
                dy -= B;
            };
            
            //Slope = dy/dx //Infinite to 1
            while( dx < dy )
            {
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                y++;
                int64 sigma = A * x * x + 2 * B * x * y + C * y * y - D;
                
                if( sigma > 0 )
                {
                    if( iFilled )
                    {
                        storagePoints[x].push_back(y);
                        storagePoints[-x].push_back(-y);
                    }
                    dx += B;
                    dy -= A;
                    x++;
                }
                dx += C;
                dy -= B;
            };
            
            //Slope = dy/dx //1 to 0
            while( dy > 0 )
            {
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );

                if( iFilled )
                {
                    storagePoints[x].push_back(y);
                    storagePoints[-x].push_back(-y);
                }


                x++;
                int64 sigma = A * x * x + 2 * B * x * y + C * y * y - D;
                
                if( sigma < 0 )
                {
                    dx += C;
                    dy -= B;
                    y++;
                }
                dx += B;
                dy -= A;
            };
            
            //Slope = dy/dx //0 to -1
            while( dx > -dy )
            {
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );

                if( iFilled )
                {
                    storagePoints[x].push_back(y);
                    storagePoints[-x].push_back(-y);
                }

                x++;
                int64 sigma = A * x * x + 2 * B * x * y + C * y * y - D;
                
                if( sigma > 0 )
                {
                    dx -= C;
                    dy += B;
                    y--;
                }
                dx += B;
                dy -= A;
            };
            
            //Slope = dy/dx //Continue until y == p1.y, slope always < -1
            while( y > p1.y )
            {
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                y--;
                int64 sigma = A * x * x + 2 * B * x * y + C * y * y - D;
                
                if( sigma < 0 )
                {
                    if( iFilled )
                    {
                        storagePoints[x].push_back(y);
                        storagePoints[-x].push_back(-y);
                    }

                    dx += B;
                    dy -= A;
                    x++;
                }
                dx -= C;
                dy += B;
            };
        }
        //Case 2 -------------------------------
        else
        {
            //Slope = dy/dx //Initial slope to -1
            while( -dx > dy )
            {
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                if( iFilled )
                {
                    storagePoints[x].push_back(y);
                    storagePoints[-x].push_back(-y);
                }
                
                x--;
                int64 sigma = A * x * x + 2 * B * x * y + C * y * y - D;
                
                if( sigma > 0)
                {
                    dx += C;
                    dy -= B;
                    y++;
                }
                dx -= B;
                dy += A;
            };
            
            //Slope = dy/dx //-1 to infinite
            while( dx < 0 )
            {
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                y++;
                int64 sigma = A * x * x + 2 * B * x * y + C * y * y - D;
                
                if( sigma < 0)
                {
                    if( iFilled )
                    {
                        storagePoints[x].push_back(y);
                        storagePoints[-x].push_back(-y);
                    }
                    
                    dx -= B;
                    dy += A;
                    x--;
                }
                dx += C;
                dy -= B;
            };

            //Slope = dy/dx //Infinite to 1
            while( dx < dy )
            {
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                y++;
                int64 sigma = A * x * x + 2 * B * x * y + C * y * y - D;
                
                if( sigma > 0 )
                {
                    if( iFilled )
                    {
                        storagePoints[x].push_back(y);
                        storagePoints[-x].push_back(-y);
                    }
                    
                    dx += B;
                    dy -= A;
                    x++;
                }
                dx += C;
                dy -= B;
            };
            
            //Slope = dy/dx //1 to 0
            while( dy > 0 )
            {
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
        
                if( iFilled )
                {
                    storagePoints[x].push_back(y);
                    storagePoints[-x].push_back(-y);
                }
                
                x++;
                int64 sigma = A * x * x + 2 * B * x * y + C * y * y - D;
                
                if( sigma < 0 )
                {
                    dx += C;
                    dy -= B;
                    y++;
                }
                dx += B;
                dy -= A;
            };
            
            //Slope = dy/dx //Continue until x == p1.x, slope always > -1
            while( x < p1.x )
            {
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                if( iFilled )
                {
                    storagePoints[x].push_back(y);
                    storagePoints[-x].push_back(-y);
                }
                
                x++;
                int64 sigma = A * x * x + 2 * B * x * y + C * y * y - D;
                
                if( sigma > 0 )
                {
                    dx -= C;
                    dy += B;
                    y--;
                }
                dx += B;
                dy -= A;

            };
        }
        
        if( iFilled ) //We fill the ellipse by drawing vertical lines
        {
            for (std::map< int, std::vector< int > >::iterator it=storagePoints.begin(); it!=storagePoints.end(); ++it)
            {
                if( it->second.size() == 2 )
                    DrawLine( iBlock, FPoint( iCenter.x + it->first, iCenter.y - it->second[0] ), FPoint( iCenter.x + it->first, iCenter.y - it->second[1] ), iColor, iPerfStrat, callInvalidCB );
            }
        }

        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            if( iFilled )
                std::cout << "FilledRotatedEllipse: elapsed time: " << elapsed_seconds.count() << "s\n";
            else
                std::cout << "RotatedEllipse: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }
    
    
    
    static void DrawEllipse(  TBlock< _SH >*           iBlock
                            , const FPoint             iCenter
                            , const int                iA
                            , const int                iB
                            , const CColor&            iColor
                            , const bool               iFilled
                            , const FPerfStrat&        iPerfStrat
                            , bool                     callInvalidCB )
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        
        int a2 = iA * iA;
        int b2 = iB * iB;
        int fa2 = 4 * a2;
        int fb2 = 4 * b2;
        int x, y, sigma;
        
        for( x = 0, y = iB, sigma = 2*b2+a2*(1-2*iB) ; b2 * x <= a2 * y; x++ )
        {
            if( iFilled )
            {
                DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
            }
            
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val );
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val );
            
            if( sigma >= 0)
            {
                sigma += fa2 * (1 - y);
                y--;
            }
            sigma += b2*(4 * x + 6);
        }
        
        for( x = iA, y = 0, sigma = 2*a2+b2*(1-2*iA) ; a2 * y <= b2 * x; y++ )
        {
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val );
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val );
            
            if( sigma >= 0)
            {
                if( iFilled )
                {
                    DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerfStrat, callInvalidCB );
                }
                sigma += fb2 * (1 - x);
                x--;

            }
            sigma += a2*(4 * y + 6);
        }
        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            if( iFilled )
                std::cout << "FilledEllipse: elapsed time: " << elapsed_seconds.count() << "s\n";
            else
                std::cout << "Ellipse: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }
    
    // ---
    
    
    static void DrawRectangle( TBlock< _SH >*              iBlock
                                , const FPoint             iTopLeft
                                , const FPoint             iBottomRight
                                , const CColor&            iColor
                                , const bool               iFilled
                                , const FPerfStrat&        iPerfStrat
                                , bool                     callInvalidCB )
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        if( iFilled )
        {
            ::ULIS::FClearFillContext::FillRect( iBlock, iColor, ::ULIS::FRect( iTopLeft.x, iTopLeft.y, ULIS::FMath::Abs( iTopLeft.x - iBottomRight.x ) + 1, ULIS::FMath::Abs( iTopLeft.y - iBottomRight.y ) + 1 ) );
        }
        else
        {
            //Top side
            ::ULIS::FClearFillContext::FillRect( iBlock, iColor, ::ULIS::FRect( iTopLeft.x, iTopLeft.y, ULIS::FMath::Abs( iTopLeft.x - iBottomRight.x ) + 1, 1 ) );
            
            //Bottom side
            ::ULIS::FClearFillContext::FillRect( iBlock, iColor, ::ULIS::FRect( iTopLeft.x, iTopLeft.y + ULIS::FMath::Abs( iTopLeft.y - iBottomRight.y ), ULIS::FMath::Abs( iTopLeft.x - iBottomRight.x ) + 1, 1 ) );
            
            //Left side
            ::ULIS::FClearFillContext::FillRect( iBlock, iColor, ::ULIS::FRect( iTopLeft.x, iTopLeft.y + 1, 1, ULIS::FMath::Abs( iTopLeft.y - iBottomRight.y ) - 1 ) );
            
            //Right side
            ::ULIS::FClearFillContext::FillRect( iBlock, iColor, ::ULIS::FRect( iTopLeft.x + ULIS::FMath::Abs( iTopLeft.x - iBottomRight.x ), iTopLeft.y + 1, 1, ULIS::FMath::Abs( iTopLeft.y - iBottomRight.y ) - 1 ) );
        }
        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            if( iFilled )
                std::cout << "FilledRectangle: elapsed time: " << elapsed_seconds.count() << "s\n";
            else
                std::cout << "Rectangle: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }
    
    
    static void DrawPolygon( TBlock< _SH >*                    iBlock
                                , std::vector< FPoint >&       iPoints
                                , const CColor&                iColor
                                , const bool                   iFilled
                                , const FPerfStrat&            iPerfStrat
                                , bool                         callInvalidCB )
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        if( iPoints.size() < 3 )
            return;
        
        int j = iPoints.size() - 1;
        for( int i = 0; i < iPoints.size(); i++ )
        {
            DrawLine( iBlock, iPoints.at( i ), iPoints.at( j ), iColor, iPerfStrat, callInvalidCB );
            j = i;
        }
        
        
        if( iFilled )
        {
            int maxX = 0;
            int maxY = 0;
            int minX = INT_MAX;
            int minY = INT_MAX;
            
            //Initialization of useful variables
            for( int i = 0; i < iPoints.size(); i++ )
            {
                if( maxX < iPoints[i].x )
                    maxX = iPoints[i].x;
                if( maxY < iPoints[i].y )
                    maxY = iPoints[i].y;
                if( minX > iPoints[i].x )
                    minX = iPoints[i].x;
                if( minY > iPoints[i].y )
                    minY = iPoints[i].y;
            }
            
            //We go through the polygon by scanning it top to bottom
            for (int y = minY; y <= maxY; y++)
            {
                std::vector< int > nodesX;
                int j = iPoints.size() - 1;
                
                for( int i = 0; i < iPoints.size(); i++ )
                {
                    if( ( iPoints[i].y < y && iPoints[j].y >= y ) || ( iPoints[j].y < y && iPoints[i].y >= y ) )
                    {
                        nodesX.push_back( iPoints[i].x  + double( y - iPoints[i].y ) / double( iPoints[j].y - iPoints[i].y ) * (iPoints[j].x - iPoints[i].x ));
                    }
                    j = i;
                }
                
                //Sorting the nodes on X
                int i = 0;
                int size = nodesX.size() - 1;
                while( i < size )
                {
                    if( nodesX[i] > nodesX[i+1] )
                    {
                        int temp = nodesX[i];
                        nodesX[i]=nodesX[i+1];
                        nodesX[i+1] = temp;
                        if( i > 0 )
                            i--;
                    }
                    else
                    {
                        i++;
                    }
                }
                
                //Filling the polygon on line y
                for( i = 0; i < nodesX.size(); i+= 2)
                {
                    if( nodesX[i] > maxX ) break;
                    if( nodesX[i+1] > minX )
                    {
                        if( nodesX[i] < minX )
                            nodesX[i] = minX;
                        if( nodesX[i+1] > maxX )
                            nodesX[i+1] = maxX;
                        
                        DrawLine( iBlock, FPoint( nodesX[i], y), FPoint( nodesX[i+1], y ), iColor, iPerfStrat, callInvalidCB );
                    }
                }
            }
        }
        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            if( iFilled )
                std::cout << "FilledPolygon: elapsed time: " << elapsed_seconds.count() << "s\n";
            else
                std::cout << "Polygon: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }

};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS
