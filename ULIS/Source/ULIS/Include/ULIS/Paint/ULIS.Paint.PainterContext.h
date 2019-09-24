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
#include "ULIS/Base/ULIS.Base.PerformanceOptions.h"
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
                         , const FPerformanceOptions&        iPerformanceOptions
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
                           , const FPerformanceOptions&        iPerformanceOptions
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
                                 , const FPerformanceOptions&        iPerformanceOptions
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
                    DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x + y, iCenter.y - x ), FPoint( iCenter.x + y, iCenter.y + x ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - y, iCenter.y - x ), FPoint( iCenter.x - y, iCenter.y + x ), iColor, iPerformanceOptions, callInvalidCB );
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
                    DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x + y, iCenter.y - x ), FPoint( iCenter.x + y, iCenter.y + x ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - y, iCenter.y - x ), FPoint( iCenter.x - y, iCenter.y + x ), iColor, iPerformanceOptions, callInvalidCB );
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
                                  , const FPerformanceOptions&        iPerformanceOptions
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
            float alphaTop = FMath::Abs( ( float( diff - errMax ) / float( errMin - errMax ) ) ); //Interpolation of slopedifferential between errMin and errMax

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
            
            //We anti-aliase towards the exterior of the circle
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y - 1, val ); // 0° to 45°
            iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y - x, val ); // 90° to 45°
            iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y + x, val ); // 90° to 135°
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y + 1, val ); // 180° to 135°
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y + 1, val ); // 180° to 225°
            iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y + x, val );  // 270° to 225°
            iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y - x, val ); // 270° to 315°
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y - 1, val ); // 0° to 315°
            
            if( diff >= ( 2 * x ) )
            {
                if( iFilled )
                {
                    DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x + y, iCenter.y - x ), FPoint( iCenter.x + y, iCenter.y + x ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - y, iCenter.y - x ), FPoint( iCenter.x - y, iCenter.y + x ), iColor, iPerformanceOptions, callInvalidCB );
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
                    DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x + y, iCenter.y - x ), FPoint( iCenter.x + y, iCenter.y + x ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - y, iCenter.y - x ), FPoint( iCenter.x - y, iCenter.y + x ), iColor, iPerformanceOptions, callInvalidCB );
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
                std::cout << "FilledCircleAndresAA: elapsed time: " << elapsed_seconds.count() << "s\n";
            else
                std::cout << "CircleAndresAA: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }
    
    
    //Don't draw concentric circles with this one. But 1 pixel outline all around the circle -> Cleaner result
    static void DrawCircleBresenham(  TBlock< _SH >*           iBlock
                                    , const FPoint             iCenter
                                    , const int                iRadius
                                    , const CColor&            iColor
                                    , const bool               iFilled
                                    , const FPerformanceOptions&        iPerformanceOptions
                                    , bool                     callInvalidCB )
    {
        
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        
        int x = 0;
        int y = iRadius;
        int diff = 5 - 4 * iRadius;
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
                DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                DrawLine( iBlock, FPoint( iCenter.x + y, iCenter.y - x ), FPoint( iCenter.x + y, iCenter.y + x ), iColor, iPerformanceOptions, callInvalidCB );
                DrawLine( iBlock, FPoint( iCenter.x - y, iCenter.y - x ), FPoint( iCenter.x - y, iCenter.y + x ), iColor, iPerformanceOptions, callInvalidCB );
            }
            
            if( diff > 0 )
            {
                y--;
                diff = diff - 8 * y;
            }
            x++;
            diff = diff + 8 * x + 4;
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
    
    //Don't draw concentric circles with this one. But 1 pixel outline all around the circle -> Cleaner result
    static void DrawCircleBresenhamAA(  TBlock< _SH >*           iBlock
                                      , const FPoint             iCenter
                                      , const int                iRadius
                                      , const CColor&            iColor
                                      , const bool               iFilled
                                      , const FPerformanceOptions&        iPerformanceOptions
                                      , bool                     callInvalidCB )
    {
        
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        
        auto MaxAlpha = val.GetAlpha();

        int x = 0;
        int y = iRadius;
        int diff = 5 - 4 * iRadius;
        int errMax = 2 * ( 4 * iRadius - 5 );
        int errMin = 0;
        while( x <= y )
        {
            if( diff > 0 )
            {
                y--;
            }
            
            float alphaTop = 1 - FMath::Abs( ( float( diff - errMax ) / float( errMin - errMax ) ) ); //Interpolation of slopedifferential between errMin and errMax
            
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
            
            //We anti-aliase towards the exterior of the circle
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y - 1, val ); // 0° to 45°
            iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y - x, val ); // 90° to 45°
            iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y + x, val ); // 90° to 135°
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y + 1, val ); // 180° to 135°
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y + 1, val ); // 180° to 225°
            iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y + x, val );  // 270° to 225°
            iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y - x, val ); // 270° to 315°
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y - 1, val ); // 0° to 315°
            
            if( iFilled )
            {
                DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                DrawLine( iBlock, FPoint( iCenter.x + y, iCenter.y - x ), FPoint( iCenter.x + y, iCenter.y + x ), iColor, iPerformanceOptions, callInvalidCB );
                DrawLine( iBlock, FPoint( iCenter.x - y, iCenter.y - x ), FPoint( iCenter.x - y, iCenter.y + x ), iColor, iPerformanceOptions, callInvalidCB );
            }
            
            if( diff > 0 )
            {
                diff = diff - 8 * y;
            }
            x++;
            diff = diff + 8 * x + 4;
        }
        
        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            if( iFilled )
                std::cout << "FilledCircleBresenAA: elapsed time: " << elapsed_seconds.count() << "s\n";
            else
                std::cout << "CircleBresenAA: elapsed time: " << elapsed_seconds.count() << "s\n";
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
                              , const FPerformanceOptions&         iPerformanceOptions
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
    

    //You can draw concentric arcs with this one. But multiple pixel outline at some part of the arc -> messier result
    static void DrawArcAndresAA(  TBlock< _SH >*            iBlock
                                , const FPoint              iCenter
                                , const int                 iRadius
                                , const int                 iStartDegree
                                , const int                 iEndDegree
                                , const CColor&             iColor
                                , const FPerformanceOptions&         iPerformanceOptions
                                , bool                      callInvalidCB )
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        if( iRadius == 0 )
            return;
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        
        auto MaxAlpha = val.GetAlpha();

        
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
        int errMax = 2 * (iRadius - 1);
        int errMin = 0;
        while (y >= x) //We draw 8 octants
        {
            
            float alphaTop = FMath::Abs( ( float( diff - errMax ) / float( errMin - errMax ) ) ); //Interpolation of slopedifferential between errMin and errMax

            val.SetAlpha( MaxAlpha * alphaTop );
            
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
            
    
            val.SetAlpha( MaxAlpha * (1 - alphaTop ) );
            
            //We anti-aliase towards the exterior of the circle
            if( octantsToDraw[0] == 1 ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y - 1, val ); // 0° to 45°
            if( octantsToDraw[1] == 1 ) iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y - x, val ); // 90° to 45°
            if( octantsToDraw[2] == 1 ) iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y + x, val ); // 90° to 135°
            if( octantsToDraw[3] == 1 ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y + 1, val ); // 180° to 135°
            if( octantsToDraw[4] == 1 ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y + 1, val ); // 180° to 225°
            if( octantsToDraw[5] == 1 ) iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y + x, val );  // 270° to 225°
            if( octantsToDraw[6] == 1 ) iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y - x, val ); // 270° to 315°
            if( octantsToDraw[7] == 1 ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y - 1, val ); // 0° to 315°
            
            
            // Complex cases
            if( octantsToDraw[0] == 2)
            {
                if ( directionToDraw[0][0] == 1 && currentAngleOnFirstOctant < directionToDraw[0][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y - 1, val );
                else if ( directionToDraw[0][0] == -1 && currentAngleOnFirstOctant > directionToDraw[0][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y - 1, val );
            }
            
            if( octantsToDraw[1] == 2)
            {
                if ( directionToDraw[1][0] == 1 && currentAngleOnFirstOctant > directionToDraw[1][1] ) iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y - x, val );
                else if ( directionToDraw[1][0] == -1 && currentAngleOnFirstOctant < directionToDraw[1][1] ) iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y - x, val );
            }

            if( octantsToDraw[2] == 2)
            {
                if ( directionToDraw[2][0] == 1 && currentAngleOnFirstOctant < directionToDraw[2][1] ) iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y + x, val );
                else if ( directionToDraw[2][0] == -1 && currentAngleOnFirstOctant > directionToDraw[2][1] ) iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y + x, val );
            }
            
            if( octantsToDraw[3] == 2)
            {
                if ( directionToDraw[3][0] == 1 && currentAngleOnFirstOctant > directionToDraw[3][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y + 1, val );
                else if ( directionToDraw[3][0] == -1 && currentAngleOnFirstOctant < directionToDraw[3][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y + 1, val );
            }
            
            if( octantsToDraw[4] == 2)
            {
                if ( directionToDraw[4][0] == 1 && currentAngleOnFirstOctant < directionToDraw[4][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y + 1, val );
                else if ( directionToDraw[4][0] == -1 && currentAngleOnFirstOctant > directionToDraw[4][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y + 1, val );
            }
            
            if( octantsToDraw[5] == 2)
            {
                if ( directionToDraw[5][0] == 1 && currentAngleOnFirstOctant > directionToDraw[5][1] ) iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y + x, val );
                else if ( directionToDraw[5][0] == -1 && currentAngleOnFirstOctant < directionToDraw[5][1] ) iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y + x, val );
            }
            
            if( octantsToDraw[6] == 2)
            {
                if ( directionToDraw[6][0] == 1 && currentAngleOnFirstOctant < directionToDraw[6][1] ) iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y - x, val );
                else if ( directionToDraw[6][0] == -1 && currentAngleOnFirstOctant > directionToDraw[6][1] ) iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y - x, val );
            }
            
            if( octantsToDraw[7] == 2)
            {
                if ( directionToDraw[7][0] == 1 && currentAngleOnFirstOctant < directionToDraw[7][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y - 1, val );
                else if ( directionToDraw[7][0] == -1 && currentAngleOnFirstOctant > directionToDraw[7][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y - 1, val );
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
            std::cout << "ArcAndresAA: elapsed time: " << elapsed_seconds.count() << "s\n";
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
                                , const FPerformanceOptions&         iPerformanceOptions
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
        int diff = 5 - 4 * iRadius;
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
            
            
            if( diff > 0 )
            {
                y--;
                diff = diff - 8 * y;
            }
            x++;
            diff = diff + 8 * x + 4;
        }
        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout << "ArcBresen: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }
    
    //Don't draw concentric arcs with this one. But 1 pixel outline all around the arc -> Cleaner result
    static void DrawArcBresenhamAA( TBlock< _SH >*            iBlock
                                , const FPoint              iCenter
                                , const int                 iRadius
                                , const int                 iStartDegree
                                , const int                 iEndDegree
                                , const CColor&             iColor
                                , const FPerformanceOptions&         iPerformanceOptions
                                , bool                      callInvalidCB )
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();

        if( iRadius == 0 )
            return;
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        
        auto MaxAlpha = val.GetAlpha();
        
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
        int diff = 5 - 4 * iRadius;
        int errMax = 2 * ( 4 * iRadius - 5 );
        int errMin = 0;
        while ( x <= y ) //We draw 8 octants
        {
            if( diff > 0 )
            {
                y--;
            }
            
            float alphaTop = 1 - FMath::Abs( ( float( diff - errMax ) / float( errMin - errMax ) ) ); //Interpolation of slopedifferential between errMin and errMax

            val.SetAlpha( MaxAlpha * alphaTop );
            
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
            
            val.SetAlpha( MaxAlpha * (1 - alphaTop ) );
            
            //We anti-aliase towards the exterior of the circle
            if( octantsToDraw[0] == 1 ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y - 1, val ); // 0° to 45°
            if( octantsToDraw[1] == 1 ) iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y - x, val ); // 90° to 45°
            if( octantsToDraw[2] == 1 ) iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y + x, val ); // 90° to 135°
            if( octantsToDraw[3] == 1 ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y + 1, val ); // 180° to 135°
            if( octantsToDraw[4] == 1 ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y + 1, val ); // 180° to 225°
            if( octantsToDraw[5] == 1 ) iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y + x, val );  // 270° to 225°
            if( octantsToDraw[6] == 1 ) iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y - x, val ); // 270° to 315°
            if( octantsToDraw[7] == 1 ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y - 1, val ); // 0° to 315°
            

            // Complex cases
            if( octantsToDraw[0] == 2)
            {
                if ( directionToDraw[0][0] == 1 && currentAngleOnFirstOctant < directionToDraw[0][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y - 1, val );
                else if ( directionToDraw[0][0] == -1 && currentAngleOnFirstOctant > directionToDraw[0][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y - 1, val );
            }
            
            if( octantsToDraw[1] == 2)
            {
                if ( directionToDraw[1][0] == 1 && currentAngleOnFirstOctant > directionToDraw[1][1] ) iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y - x, val );
                else if ( directionToDraw[1][0] == -1 && currentAngleOnFirstOctant < directionToDraw[1][1] ) iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y - x, val );
            }

            if( octantsToDraw[2] == 2)
            {
                if ( directionToDraw[2][0] == 1 && currentAngleOnFirstOctant < directionToDraw[2][1] ) iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y + x, val );
                else if ( directionToDraw[2][0] == -1 && currentAngleOnFirstOctant > directionToDraw[2][1] ) iBlock->SetPixelValue( iCenter.x + y + 1, iCenter.y + x, val );
            }
            
            if( octantsToDraw[3] == 2)
            {
                if ( directionToDraw[3][0] == 1 && currentAngleOnFirstOctant > directionToDraw[3][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y + 1, val );
                else if ( directionToDraw[3][0] == -1 && currentAngleOnFirstOctant < directionToDraw[3][1] ) iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y + 1, val );
            }
            
            if( octantsToDraw[4] == 2)
            {
                if ( directionToDraw[4][0] == 1 && currentAngleOnFirstOctant < directionToDraw[4][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y + 1, val );
                else if ( directionToDraw[4][0] == -1 && currentAngleOnFirstOctant > directionToDraw[4][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y + 1, val );
            }
            
            if( octantsToDraw[5] == 2)
            {
                if ( directionToDraw[5][0] == 1 && currentAngleOnFirstOctant > directionToDraw[5][1] ) iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y + x, val );
                else if ( directionToDraw[5][0] == -1 && currentAngleOnFirstOctant < directionToDraw[5][1] ) iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y + x, val );
            }
            
            if( octantsToDraw[6] == 2)
            {
                if ( directionToDraw[6][0] == 1 && currentAngleOnFirstOctant < directionToDraw[6][1] ) iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y - x, val );
                else if ( directionToDraw[6][0] == -1 && currentAngleOnFirstOctant > directionToDraw[6][1] ) iBlock->SetPixelValue( iCenter.x - y - 1, iCenter.y - x, val );
            }
            
            if( octantsToDraw[7] == 2)
            {
                if ( directionToDraw[7][0] == 1 && currentAngleOnFirstOctant < directionToDraw[7][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y + 1, val );
                else if ( directionToDraw[7][0] == -1 && currentAngleOnFirstOctant > directionToDraw[7][1] ) iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y + 1, val );
            }
            
            if( diff > 0 )
            {
                diff = diff - 8 * y;
            }
            x++;
            diff = diff + 8 * x + 4;
        }
        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            std::cout << "ArcBresenAA: elapsed time: " << elapsed_seconds.count() << "s\n";
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
                                   , const FPerformanceOptions&        iPerformanceOptions
                                   , bool                     callInvalidCB )
    {
        if( iRotationDegrees % 180 == 0 )
        {
            DrawEllipse( iBlock, iCenter, iA, iB, iColor, iFilled, iPerformanceOptions, callInvalidCB ); //Don't bother to use the rotated ellipse algorithm if the ellipse is not rotated
            return;
        }
        if( iRotationDegrees % 90 == 0 )
        {
            DrawEllipse( iBlock, iCenter, iB, iA, iColor, iFilled, iPerformanceOptions, callInvalidCB ); //Don't bother to use the rotated ellipse algorithm if the ellipse is not rotated
            return;
        }
        
                                                           //               x  y
        std::map< int, std::vector< int > > storagePoints; // storagePoints[x][0]  We have two points for each x on the ellipse: p1(x, y0), p2(x, y1)
                                                           //                 [1]
        storagePoints[0].push_back( iCenter.x );          // In order to only pass storagePoints in parameter to InternalDrawQuadRationalBezierSeg
        storagePoints[0].push_back( iCenter.y );          // we store the center (useful in this function) at index 0 (we'll know it's there)

        
        int a = iA;
        int b = iB;
        
        float dx = (long)iA*iA;
        float dy = (long)iB*iB;
        float s = std::sin( FMath::DegToRad( iRotationDegrees + 90 ) );
        float dz = (dx - dy) * s;
        dx = std::sqrt( dx - dz * s );
        dy = std::sqrt( dy + dz * s );
        a = dx + 0.5;
        b = dy + 0.5;
        dz = dz * a * b / (dx * dy );
        
        int x0 = iCenter.x - a;
        int y0 = iCenter.y - b;
        int x1 = iCenter.x + a;
        int y1 = iCenter.y + b;
        dz = (4 * dz * cos( FMath::DegToRad( iRotationDegrees + 90 ) ) );
        
        
        dx = x1 - x0;
        dy = y1 - y0;
        float w = dx * dy;
        if( w != 0.0 )
            w = ( w - dz ) / (w + w);
        
        if( w > 1 || w < 0 )
            return;
        
        dx = std::floor( dx * w + 0.5 );
        dy = std::floor( dy * w + 0.5 );
        
        InternalDrawQuadRationalBezierSeg( iBlock, x0, y0 + dy, x0, y0, x0 + dx, y0, 1 - w, iColor, iPerformanceOptions, callInvalidCB, &storagePoints );
        InternalDrawQuadRationalBezierSeg( iBlock, x0, y0 + dy, x0, y1, x1 - dx, y1, w, iColor, iPerformanceOptions, callInvalidCB, &storagePoints );
        InternalDrawQuadRationalBezierSeg( iBlock, x1, y1 - dy, x1, y1, x1 - dx, y1, 1 - w, iColor, iPerformanceOptions, callInvalidCB, &storagePoints );
        InternalDrawQuadRationalBezierSeg( iBlock, x1, y1 - dy, x1, y0, x0 + dx, y0, w, iColor, iPerformanceOptions, callInvalidCB, &storagePoints );
        
        if( iFilled ) //We fill the ellipse by drawing vertical lines
        {
            //We delete the values we stored for the center position
            storagePoints[0].erase( storagePoints[0].begin() );
            storagePoints[0].erase( storagePoints[0].begin() );

            for (std::map< int, std::vector< int > >::iterator it=storagePoints.begin(); it!=storagePoints.end(); ++it)
            {
                if( it->second.size() == 2 )
                {
                    DrawLine( iBlock, FPoint( iCenter.x + it->first, iCenter.y + it->second[0] ), FPoint( iCenter.x + it->first, iCenter.y + it->second[1] ), iColor, iPerformanceOptions, callInvalidCB );
                }
                if( it->second.size() > 2 ) // where we draw more than 2 pixels for a said y
                {
                    int minY = it->second[0];
                    int maxY = it->second[0];
                    for( int i = 1; i < it->second.size(); i++)
                    {
                        if( minY > it->second[i] )
                            minY = it->second[i];

                        if( maxY < it->second[i] )
                            maxY = it->second[i];
                    }
                    DrawLine( iBlock, FPoint( iCenter.x + it->first, iCenter.y + minY ), FPoint( iCenter.x + it->first, iCenter.y + maxY ), iColor, iPerformanceOptions, callInvalidCB );
                }
            }
        }
    }
    

    static void DrawRotatedEllipseAA(  TBlock< _SH >*           iBlock
                                     , const FPoint             iCenter
                                     , const int                iA
                                     , const int                iB
                                     , const int                iRotationDegrees
                                     , const CColor&            iColor
                                     , const bool               iFilled
                                     , const FPerformanceOptions&        iPerformanceOptions
                                     , bool                     callInvalidCB )
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        
        auto MaxAlpha = val.GetAlpha();
        
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
        
        int64 errMax = 0;
        int64 errMin = 2 * (A * x * x + 2 * B * x * (y + 1) + C * (y + 1) * (y + 1) - D);
        
        std::cout << "errMin: " << errMin << " errMax: " << errMax << std::endl;

        //Case 1 ----------------------------
        if( dx == 0 || ::ULIS::FMath::Abs( dy / dx ) >= 1 )
        {
            //Slope = dy/dx //Initial slope to infinite
            while( dx < 0 )
            {
                int64 sigma = A * x * x + 2 * B * x * (y + 1) + C * (y + 1) * (y + 1) - D;
                int step = sigma < 0 ? 1 : -1;
                
                float alphaTop = FMath::Abs( 1 - FMath::Abs( ( float( sigma - errMax ) / float( errMin - errMax ) ) ) ); //Interpolation of slopedifferential between errMin and errMax

                //std::cout << "sigma: " << sigma << " alphaTop: " << alphaTop << std::endl;
                
                val.SetAlpha( MaxAlpha * alphaTop );
                
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                val.SetAlpha( MaxAlpha * ( 1 - alphaTop ) );

                iBlock->SetPixelValue( iCenter.x + x - step, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x + step, iCenter.y + y, val );
                
                y++;
                
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
            
            errMax = 0;
            errMin = 2 * (A * x * x + 2 * B * x * (y + 1) + C * (y + 1) * (y + 1) - D);
            
            std::cout << "errMin: " << errMin << " errMax: " << errMax << std::endl;

            
            //Slope = dy/dx //Infinite to 1
            while( dx < dy )
            {
                int64 sigma = A * x * x + 2 * B * x * (y + 1) + C * (y + 1) * (y + 1) - D;
                int step = sigma < 0 ? 1 : -1;

                float alphaTop = FMath::Abs( 1 - FMath::Abs( ( float( sigma - errMax ) / float( errMin - errMax ) ) ) ); //Interpolation of slopedifferential between errMin and errMax
                
                //std::cout << "sigma: " << sigma << " alphaTop: " << alphaTop << std::endl;
                
                val.SetAlpha( MaxAlpha * alphaTop );
                
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                val.SetAlpha( MaxAlpha * ( 1 - alphaTop ) );

                iBlock->SetPixelValue( iCenter.x + x - step, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x + step, iCenter.y + y, val );
                
                y++;
                
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
            
            errMax = 0;
            errMin = 2 * (A * (x + 1) * (x + 1) + 2 * B * (x + 1) * y + C * y * y - D);
            
            std::cout << "errMin: " << errMin << " errMax: " << errMax << std::endl;
            
            //Slope = dy/dx //1 to 0
            while( dy > 0 )
            {
                int64 sigma = A * (x + 1) * (x + 1) + 2 * B * (x + 1) * y + C * y * y - D;
                int step = sigma < 0 ? 1 : -1;
                
                float alphaTop =  FMath::Abs( 1 - FMath::Abs( ( float( sigma - errMax ) / float( errMin - errMax ) ) ) ); //Interpolation of slopedifferential between errMin and errMax
                
                //std::cout << "sigma: " << sigma << " alphaTop: " << alphaTop << std::endl;
                
                val.SetAlpha( MaxAlpha * alphaTop );
                
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                val.SetAlpha( MaxAlpha * ( 1 - alphaTop ) );

                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y - step, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y + step, val );

                if( iFilled )
                {
                    storagePoints[x].push_back(y);
                    storagePoints[-x].push_back(-y);
                }
                
                x++;
                
                if( sigma < 0 )
                {
                    dx += C;
                    dy -= B;
                    y++;
                }
                dx += B;
                dy -= A;
            };
            
            errMax = 0;
            errMin = 2 * (A * (x + 1) * (x + 1) + 2 * B * (x + 1) * y + C * y * y - D);
            
            std::cout << "errMin: " << errMin << " errMax: " << errMax << std::endl;
            
            //Slope = dy/dx //0 to -1
            while( dx > -dy )
            {
                int64 sigma = A * (x + 1) * (x + 1) + 2 * B * (x + 1) * y + C * y * y - D;
                int step = sigma < 0 ? 1 : -1;
                
                float alphaTop =  FMath::Abs( 1 - FMath::Abs( ( float( sigma - errMax ) / float( errMin - errMax ) ) ) ); //Interpolation of slopedifferential between errMin and errMax
                
                //std::cout << "sigma: " << sigma << " alphaTop: " << alphaTop << std::endl;
                
                val.SetAlpha( MaxAlpha * alphaTop );
                
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                val.SetAlpha( MaxAlpha * ( 1 - alphaTop ) );

                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y - step, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y + step, val );

                if( iFilled )
                {
                    storagePoints[x].push_back(y);
                    storagePoints[-x].push_back(-y);
                }

                x++;
                
                if( sigma > 0 )
                {
                    dx -= C;
                    dy += B;
                    y--;
                }
                dx += B;
                dy -= A;
            };
            
            errMax = 0;
            errMin = 2 * (A * x * x + 2 * B * x * (y - 1) + C * (y - 1) * (y - 1) - D);
            
            std::cout << "errMin: " << errMin << " errMax: " << errMax << std::endl;
            
            //Slope = dy/dx //Continue until y == p1.y, slope always < -1
            while( y > p1.y )
            {
                int64 sigma = A * x * x + 2 * B * x * (y - 1) + C * (y - 1) * (y - 1) - D;
                int step = sigma < 0 ? 1 : -1;
                
                float alphaTop =  FMath::Abs( 1 - FMath::Abs( ( float( sigma - errMax ) / float( errMin - errMax ) ) ) ); //Interpolation of slopedifferential between errMin and errMax
                
                //std::cout << "sigma: " << sigma << " alphaTop: " << alphaTop << std::endl;
                
                val.SetAlpha( MaxAlpha * alphaTop );
                
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                val.SetAlpha( MaxAlpha * ( 1 - alphaTop ) );

                iBlock->SetPixelValue( iCenter.x + x - step, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x + step, iCenter.y + y, val );
                
                y--;
                
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
            errMax = 0;
            errMin = 2 * (A * (x - 1) * (x - 1) + 2 * B * (x - 1) * y + C * y * y - D);
            
            std::cout << "errMin: " << errMin << " errMax: " << errMax << std::endl;
            
            //Slope = dy/dx //Initial slope to -1
            while( -dx > dy )
            {
                int64 sigma = A * (x - 1) * (x - 1) + 2 * B * (x - 1) * y + C * y * y - D;
                int step = sigma < 0 ? 1 : -1;
                
                float alphaTop =  FMath::Abs( 1 - FMath::Abs( ( float( sigma - errMax ) / float( errMin - errMax ) ) ) ); //Interpolation of slopedifferential between errMin and errMax

                //std::cout << "sigma: " << sigma << " alphaTop: " << alphaTop << std::endl;
                
                val.SetAlpha( MaxAlpha * alphaTop );
                
                iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
                val.SetAlpha( MaxAlpha * ( 1 - alphaTop ) );

                iBlock->SetPixelValue( iCenter.x + x - step, iCenter.y - y, val );
                iBlock->SetPixelValue( iCenter.x - x + step, iCenter.y + y, val );
                
                if( iFilled )
                {
                    storagePoints[x].push_back(y);
                    storagePoints[-x].push_back(-y);
                }
                
                x--;

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
                //iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                //iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
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
                //iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                //iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
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
                //iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                //iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
        
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
                //iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val );
                //iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val );
                
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
                    DrawLine( iBlock, FPoint( iCenter.x + it->first, iCenter.y - it->second[0] ), FPoint( iCenter.x + it->first, iCenter.y - it->second[1] ), iColor, iPerformanceOptions, callInvalidCB );
            }
        }

        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            if( iFilled )
                std::cout << "FilledRotatedEllipseAA: elapsed time: " << elapsed_seconds.count() << "s\n";
            else
                std::cout << "RotatedEllipseAA: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }
    
    
    
    static void DrawEllipse(  TBlock< _SH >*           iBlock
                            , const FPoint             iCenter
                            , const int                iA
                            , const int                iB
                            , const CColor&            iColor
                            , const bool               iFilled
                            , const FPerformanceOptions&        iPerformanceOptions
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
                DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
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
                    DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
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
    

    static void DrawEllipseAA(  TBlock< _SH >*           iBlock
                            , const FPoint             iCenter
                            , const int                iA
                            , const int                iB
                            , const CColor&            iColor
                            , const bool               iFilled
                            , const FPerformanceOptions&        iPerformanceOptions
                            , bool                     callInvalidCB )
    {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        
        if( BENCHMARKMODE )
            start = std::chrono::system_clock::now();
        
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        
        auto MaxAlpha = val.GetAlpha();
        
        int a2 = iA * iA;
        int b2 = iB * iB;
        int fa2 = 4 * a2;
        int fb2 = 4 * b2;
        int x, y, sigma;
        
        int errMax = 0;
        int errMin =  2 * (2*a2+b2*(1-2*iA));
        
        
        for( x = iA, y = 0, sigma = 2*a2+b2*(1-2*iA) ; a2 * y <= b2 * x; y++ )
        {
            float alphaTop = 1 - FMath::Abs( ( float( sigma - errMax ) / float( errMin - errMax ) ) ); //Interpolation of slopedifferential between errMin and errMax
            
            int step = sigma < 0 ? 1 : -1;
            
            val.SetAlpha( MaxAlpha * alphaTop );
            
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val ); // 90 to 135 degrees
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val ); // 270 to 225 degrees
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val ); // 90 to 45 degrees
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val ); // 270 to 315 degrees
            
            val.SetAlpha( MaxAlpha * ( 1 - alphaTop ) );

            iBlock->SetPixelValue( iCenter.x + x + step, iCenter.y + y, val ); // 90 to 135 degrees
            iBlock->SetPixelValue( iCenter.x - x - step, iCenter.y + y, val ); // 270 to 225 degrees
            iBlock->SetPixelValue( iCenter.x + x + step, iCenter.y - y, val ); // 90 to 45 degrees
            iBlock->SetPixelValue( iCenter.x - x - step, iCenter.y - y, val ); // 270 to 315 degrees
            
            if( sigma >= 0)
            {
                if( iFilled )
                {
                    if( step == 1 )
                    {
                        DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                        DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                    }
                    else //step = -1, we draw the aliasing on the inside of the ellipse, so we colorize one pixel less
                    {
                        DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y + 1 ), FPoint( iCenter.x + x, iCenter.y + y - 1 ), iColor, iPerformanceOptions, callInvalidCB );
                        DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y + 1 ), FPoint( iCenter.x - x, iCenter.y + y - 1 ), iColor, iPerformanceOptions, callInvalidCB );
                    }
                }
                sigma += fb2 * (1 - x);
                x--;
            }
            sigma += a2*(4 * y + 6);
        }
        
        errMax = 0;
        errMin = 2 * (2*b2+a2*(1-2*iB));
        
        for( x = 0, y = iB, sigma = 2*b2+a2*(1-2*iB) ; b2 * x <= a2 * y; x++ )
        {
            float alphaTop = 1 - FMath::Abs( ( float( sigma - errMax ) / float( errMin - errMax ) ) ); //Interpolation of slopedifferential between errMin and errMax

            val.SetAlpha( MaxAlpha * alphaTop );
            
            int step = sigma <= 0 ? 1 : -1;

            iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y, val ); // 180 to 135 degrees
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y, val ); // 180 to 225 degrees
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y, val ); // 0 to 45 degrees
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y, val ); // 360 to 315 degrees
            
            val.SetAlpha( MaxAlpha * ( 1 - alphaTop ) );

            iBlock->SetPixelValue( iCenter.x + x, iCenter.y + y + step, val ); // 180 to 135 degrees
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y + y + step, val ); // 180 to 225 degrees
            iBlock->SetPixelValue( iCenter.x + x, iCenter.y - y - step, val ); // 0 to 45 degrees
            iBlock->SetPixelValue( iCenter.x - x, iCenter.y - y - step, val ); // 360 to 315 degrees
            
            if( iFilled )
            {
                if( step == 1 )
                {
                    DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y ), FPoint( iCenter.x + x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y ), FPoint( iCenter.x - x, iCenter.y + y ), iColor, iPerformanceOptions, callInvalidCB );
                }
                else //step = -1, we draw the aliasing on the inside of the ellipse, so we colorize one pixel less
                {
                    DrawLine( iBlock, FPoint( iCenter.x + x, iCenter.y - y + 1 ), FPoint( iCenter.x + x, iCenter.y + y - 1 ), iColor, iPerformanceOptions, callInvalidCB );
                    DrawLine( iBlock, FPoint( iCenter.x - x, iCenter.y - y + 1 ), FPoint( iCenter.x - x, iCenter.y + y - 1 ), iColor, iPerformanceOptions, callInvalidCB );
                }
            }
            
            if( sigma >= 0)
            {
                sigma += fa2 * (1 - y);
                y--;
            }
            sigma += b2*(4 * x + 6);
        }

        
        if( BENCHMARKMODE )
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            if( iFilled )
                std::cout << "FilledEllipseAA: elapsed time: " << elapsed_seconds.count() << "s\n";
            else
                std::cout << "EllipseAA: elapsed time: " << elapsed_seconds.count() << "s\n";
            std::cout << "----------------------------- \n";
        }
    }
    
    
    // ---
    
    
    static void DrawRectangle( TBlock< _SH >*              iBlock
                                , const FPoint             iTopLeft
                                , const FPoint             iBottomRight
                                , const CColor&            iColor
                                , const bool               iFilled
                                , const FPerformanceOptions&        iPerformanceOptions
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
                                , const FPerformanceOptions&            iPerformanceOptions
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
            DrawLine( iBlock, iPoints.at( i ), iPoints.at( j ), iColor, iPerformanceOptions, callInvalidCB );
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
                        
                        DrawLine( iBlock, FPoint( nodesX[i], y), FPoint( nodesX[i+1], y ), iColor, iPerformanceOptions, callInvalidCB );
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
    
    
    static void InternalDrawQuadRationalBezierSeg( TBlock< _SH>* iBlock
                                                 , int x0
                                                 , int y0
                                                 , int x1
                                                 , int y1
                                                 , int x2
                                                 , int y2
                                                 , float w
                                                 , const CColor& iColor
                                                 , const FPerformanceOptions& iPerformanceOptions
                                                 , bool callInvalidCB
                                                 , std::map< int, std::vector< int > >* iStoragePoints = NULL)
    {
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );

        int sx = x2-x1, sy = y2-y1;
        double dx = x0-x2, dy = y0-y2, xx = x0-x1, yy = y0-y1;
        double xy = xx*sy+yy*sx, cur = xx*sy-yy*sx, err;
        
        if( xx*sx > 0.0 || yy*sy > 0.0 )
        {
            std::cout << "OUT" << std::endl;
            return;
        }
        
        if (cur != 0.0 && w > 0.0) {
            if (sx*(long)sx+sy*(long)sy > xx*xx+yy*yy) {
                x2 = x0; x0 -= dx; y2 = y0; y0 -= dy; cur = -cur;
            }
            xx = 2.0*(4.0*w*sx*xx+dx*dx);
            yy = 2.0*(4.0*w*sy*yy+dy*dy);
            sx = x0 < x2 ? 1 : -1;
            sy = y0 < y2 ? 1 : -1;
            xy = -2.0*sx*sy*(2.0*w*xy+dx*dy);
            if (cur*sx*sy < 0.0)
            {
                xx = -xx; yy = -yy; xy = -xy; cur = -cur;
            }
            dx = 4.0*w*(x1-x0)*sy*cur+xx/2.0+xy;
            dy = 4.0*w*(y0-y1)*sx*cur+yy/2.0+xy;
            if (w < 0.5 && dy > dx)
            {
                cur = -(w+1.0)/2.0;
                w = sqrt(w);
                xy = 1.0/(w+1.0);
                sx = floor((x0+2.0*w*x1+x2)*xy/2.0+0.5);
                sy = floor((y0+2.0*w*y1+y2)*xy/2.0+0.5);
                dx = floor((w*x1+x0)*xy+0.5);
                dy = floor((y1*w+y0)*xy+0.5);
                InternalDrawQuadRationalBezierSeg( iBlock, x0, y0, dx, dy, sx, sy, cur, iColor, iPerformanceOptions, callInvalidCB, iStoragePoints );
                dx = floor((w*x1+x2)*xy+0.5);
                dy = floor((y1*w+y2)*xy+0.5);
                InternalDrawQuadRationalBezierSeg( iBlock, sx, sy, dx, dy, x2, y2, cur, iColor, iPerformanceOptions, callInvalidCB, iStoragePoints );
                return;
            }
            err = dx+dy-xy;
            do {
                iBlock->SetPixelValue( x0, y0, val );
                if( iStoragePoints )
                {
                    (*iStoragePoints)[ x0 - (*iStoragePoints)[0][0] ].push_back(y0 - (*iStoragePoints)[0][1] );
                }
                if (x0 == x2 && y0 == y2)
                    return;
                x1 = 2 * err > dy; y1 = 2*( err + yy ) < -dy;
                if (2 * err < dx || y1) { y0 += sy; dy += xy; err += dx += xx; }
                if (2 * err > dx || x1) { x0 += sx; dx += xy; err += dy += yy; }
            } while (dy <= xy && dx >= xy);
        }
        DrawLine( iBlock, FPoint( x0, y0 ), FPoint( x2, y2 ), iColor, iPerformanceOptions, callInvalidCB );
        
        if( iStoragePoints )
        {
            if( x0 == x2 && y0 == y2 ) //Corners where we draw a single pixel
            {
                (*iStoragePoints)[ x0 - (*iStoragePoints)[0][0] ].push_back(y0 - (*iStoragePoints)[0][1] );
            }
            else if( y0 == y2 ) //Horizontal lines
            {
                for( int i = x0; i < x2; i++ )
                    (*iStoragePoints)[ i - (*iStoragePoints)[0][0] ].push_back(y0 - (*iStoragePoints)[0][1] );
            }
            //We don't need to take care of vertical lines, since storagePoints is used to fill an ellipse using the exact same type of vertical lines
        }
    }
    
    static void DrawQuadraticBezier( TBlock< _SH>*                   iBlock
                                   , const FPoint&                   iCtrlPt0
                                   , const FPoint&                   iCtrlPt1
                                   , const FPoint&                   iCtrlPt2
                                   , const float                     iWeight
                                   , const CColor&                   iColor
                                   , const FPerformanceOptions&      iPerformanceOptions
                                   , bool                            callInvalidCB )
    {
        int x = iCtrlPt0.x - 2 * iCtrlPt1.x + iCtrlPt2.x;
        int y = iCtrlPt0.y - 2 * iCtrlPt1.y + iCtrlPt2.y;
        double dx = iCtrlPt0.x - iCtrlPt1.x;
        double dy = iCtrlPt0.y - iCtrlPt1.y;
        double dWeight;
        double dt;
        double dq;
        
        FPoint pt0 = iCtrlPt0;
        FPoint pt1 = iCtrlPt1;
        FPoint pt2 = iCtrlPt2;
        
        float weight = iWeight;

        if( weight < 0) //Can't draw a bezier curve with a weight < 0
            return;
        
        if( dx * ( pt2.x - pt1.x ) > 0 )
        {
            if( dy * ( pt2.y - pt1.y ) > 0 )
            {
                if( FMath::Abs( dx * y ) > FMath::Abs( dy * x ) )
                {
                    pt0.x = pt2.x;
                    pt2.x = dx + pt1.x;
                    pt0.y = pt2.y;
                    pt2.y = dy + pt1.y;
                }
            }
            if( pt0.x == pt2.x || weight == 1.0 )
            {
                dt = (pt0.x - pt1.x) / (double)x;
            }
            else
            {
                dq = std::sqrt( 4.0 * weight * weight * ( pt0.x - pt1.x ) * ( pt2.x - pt1.x ) + ( pt2.x - pt0.x ) * (long)( pt2.x - pt0.x ) );
                
                if( pt1.x < pt0.x )
                    dq = -dq;
                
                dt = ( 2.0 * weight * ( pt0.x - pt1.x ) - pt0.x + pt2.x + dq ) / (2.0 * ( 1.0 - weight ) * ( pt2.x - pt0.x ) );
            }
            dq = 1.0 / ( 2.0 * dt * ( 1.0 - dt ) * ( weight - 1.0 ) + 1.0);
            dx = ( dt * dt * ( pt0.x - 2.0 * weight * pt1.x + pt2.x ) + 2.0 * dt * ( weight * pt1.x - pt0.x ) + pt0.x) * dq;
            dy = ( dt * dt * ( pt0.y - 2.0 * weight * pt1.y + pt2.y ) + 2.0 * dt * ( weight * pt1.y - pt0.y ) + pt0.y) * dq;
            dWeight = dt * (weight - 1.0) + 1.0;
            dWeight *= (dWeight * dq);
            weight = ( ( 1.0 - dt ) * ( weight - 1.0 ) + 1.0 ) * std::sqrt(dq);
            x = std::floor( dx + 0.5 );
            y = std::floor( dy + 0.5 );
            dy = ( dx - pt0.x ) * ( pt1.y - pt0.y ) / ( pt1.x - pt0.x ) + pt0.y;
            InternalDrawQuadRationalBezierSeg( iBlock, pt0.x, pt0.y, x, std::floor( dy + 0.5 ), x, y, dWeight, iColor, iPerformanceOptions, callInvalidCB  );
            dy = ( dx - pt2.x ) * ( pt1.y - pt2.y ) / ( pt1.x - pt2.x ) + pt2.y;
            pt1.y = std::floor( dy + 0.5 );
            pt0.x = pt1.x = x;
            pt0.y = y;
            
            std::cout << "1: dx: " << dx << " dy: " << dy << " x0: " << pt0.x << " y0 : " << pt0.y << " x1: " << pt1.x << " y1 : " << pt1.y << " x2: " << pt2.x << " y2 : " << pt2.y <<   std::endl;
        }
        
        if( ( pt0.y - pt1.y ) * (long)( pt2.y - pt1.y ) > 0 )
        {
            if( pt0.y == pt2.y || iWeight == 1.0 )
            {
                dt = ( pt0.y - pt1.y ) / ( pt0.y - 2.0 * pt1.y + pt2.y );
            }
            else
            {
                dq = std::sqrt( 4.0 * weight * weight * ( pt0.y - pt1.y ) * ( pt2.y - pt1.y ) + ( pt2.y - pt0.y ) * (long)( pt2.y - pt0.y ) );
                
                if( pt1.y < pt0.y )
                    dq = -dq;
                
                dt = ( 2.0 * weight * ( pt0.y - pt1.y ) - pt0.y + pt2.y + dq ) / (2.0 * ( 1.0 - weight ) * ( pt2.y - pt0.y ) );
            }
            dq = 1.0 / ( 2.0 * dt * ( 1.0 - dt ) * ( weight - 1.0 ) + 1.0);
            dx = ( dt * dt * ( pt0.x - 2.0 * weight * pt1.x + pt2.x ) + 2.0 * dt * ( weight * pt1.x - pt0.x ) + pt0.x) * dq;
            dy = ( dt * dt * ( pt0.y - 2.0 * weight * pt1.y + pt2.y ) + 2.0 * dt * ( weight * pt1.y - pt0.y ) + pt0.y) * dq;
            dWeight = dt * (weight - 1.0) + 1.0;
            dWeight *= (dWeight * dq);
            weight = ( ( 1.0 - dt ) * ( weight - 1.0 ) + 1.0 ) * std::sqrt(dq);
            x = std::floor( dx + 0.5 );
            y = std::floor( dy + 0.5 );
            dx = ( pt1.x - pt0.x ) * ( dy - pt0.y ) / ( pt1.y - pt0.y ) + pt0.x;
            InternalDrawQuadRationalBezierSeg( iBlock, pt0.x, pt0.y, std::floor( dx + 0.5 ), y, x, y, dWeight, iColor, iPerformanceOptions, callInvalidCB  );
            std::cout << "2Before: dx: " << dx << " dy: " << dy << " x0: " << pt0.x << " y0 : " << pt0.y << " x1: " << pt1.x << " y1 : " << pt1.y << " x2: " << pt2.x << " y2 : " << pt2.y << " x: " << x << " y " << y <<   std::endl;

            dx = ( pt1.x - pt2.x ) * ( dy - pt2.y ) / ( pt1.y - pt2.y ) + pt2.x;
            pt1.x = std::floor( dx + 0.5 );
            pt0.x = x;
            pt0.y = pt1.y = y;
            
            std::cout << "2: dx: " << dx << " dy: " << dy << " x0: " << pt0.x << " y0 : " << pt0.y << " x1: " << pt1.x << " y1 : " << pt1.y << " x2: " << pt2.x << " y2 : " << pt2.y <<   std::endl;
        }
        InternalDrawQuadRationalBezierSeg( iBlock, pt0.x, pt0.y, pt1.x, pt1.y, pt2.x, pt2.y, weight * weight, iColor, iPerformanceOptions, callInvalidCB  );
    }
    
    
    
    static void InternalDrawQuadRationalBezierSegAA( TBlock< _SH>* iBlock
                                                   , int x0
                                                   , int y0
                                                   , int x1
                                                   , int y1
                                                   , int x2
                                                   , int y2
                                                   , float w
                                                   , const CColor& iColor
                                                   , const FPerformanceOptions& iPerformanceOptions
                                                   , bool callInvalidCB)
    {
        TPixelValue< _SH > val = iBlock->PixelValueForColor( iColor );
        auto MaxAlpha = val.GetAlpha();

        int sx = x2-x1, sy = y2-y1;
        double dx = x0-x2, dy = y0-y2, xx = x0-x1, yy = y0-y1;
        double xy = xx*sy+yy*sx, cur = xx*sy-yy*sx, err, ed;
        bool f;
        
        if( xx*sx > 0.0 || yy*sy > 0.0 )
        {
            return;
        }
        
        if (cur != 0.0 && w > 0.0)
        {
            if (sx*(long)sx+sy*(long)sy > xx*xx+yy*yy)
            {
                x2 = x0; x0 -= dx; y2 = y0; y0 -= dy; cur = -cur;
            }
            xx = 2.0*(4.0*w*sx*xx+dx*dx);
            yy = 2.0*(4.0*w*sy*yy+dy*dy);
            sx = x0 < x2 ? 1 : -1;
            sy = y0 < y2 ? 1 : -1;
            xy = -2.0*sx*sy*(2.0*w*xy+dx*dy);
            
            if (cur*sx*sy < 0.0)
            {
                xx = -xx; yy = -yy; xy = -xy; cur = -cur;
            }
            
            dx = 4.0*w*(x1-x0)*sy*cur+xx/2.0+xy;
            dy = 4.0*w*(y0-y1)*sx*cur+yy/2.0+xy;
            
            if (w < 0.5 && dy > dx)
            {
                cur = -(w+1.0)/2.0;
                w = sqrt(w);
                xy = 1.0/(w+1.0);
                sx = floor((x0+2.0*w*x1+x2)*xy/2.0+0.5);
                sy = floor((y0+2.0*w*y1+y2)*xy/2.0+0.5);
                dx = floor((w*x1+x0)*xy+0.5);
                dy = floor((y1*w+y0)*xy+0.5);
                InternalDrawQuadRationalBezierSegAA( iBlock, x0, y0, dx, dy, sx, sy, cur, iColor, iPerformanceOptions, callInvalidCB );
                dx = floor((w*x1+x2)*xy+0.5);
                dy = floor((y1*w+y2)*xy+0.5);
                InternalDrawQuadRationalBezierSegAA( iBlock, sx, sy, dx, dy, x2, y2, cur, iColor, iPerformanceOptions, callInvalidCB );
                return;
            }
            err = dx+dy-xy;
            do
            {
                cur = std::min( dx - xy, xy - dy );
                ed = std::max( dx - xy, xy - dy );
                ed += ( 2 * ed * cur * cur / (4.0 * ed * ed + cur * cur ) );
                x1 = MaxAlpha * ( 1 - FMath::Abs( err - dx - dy + xy ) / ed );
                f = (2 * err + dy) < 0;
                
                if( x1 > MaxAlpha || x1 < 0 )
                    std::cout << "x1: " << x1 << std::endl;

                if( x1 <= MaxAlpha )
                {
                    val.SetAlpha( x1 );
                    iBlock->SetPixelValue( x0, y0, val );
                }

                if( f )
                {
                    if( y0 == y2 )
                        return;
                    if( ( dx - err ) < ed )
                    {
                        float alpha = FMath::Abs( 1 - ( dx - err ) / ed );
                        
                        if( alpha > 1 || alpha < 0 )
                            std::cout << "1: " << alpha << std::endl;
                        
                        val.SetAlpha( MaxAlpha * alpha );
                        iBlock->SetPixelValue( x0 + sx, y0, val );
                    }
                }
            
                if( 2 * err + dx > 0 )
                {
                    if( x0 == x2 )
                        return;
                    if( ( err - dy ) < ed )
                    {
                        float alpha = FMath::Abs( 1 - ( err - dy ) / ed );
                        
                        if( alpha > 1 || alpha < 0 )
                        {
                            std::cout << "2: " << alpha << " x: " << x0 << std::endl;
                        }
                        
                        val.SetAlpha( MaxAlpha * alpha );
                        iBlock->SetPixelValue( x0, y0 + sy, val );
                    }
                    x0 += sx;
                    dx += xy;
                    err += dy += yy;
                }
            
                if( f )
                {
                    y0 += sy;
                    dy += xy;
                    err += dx += xx;
                }
                
            } while (dy < dx);
        }
        DrawLineAA( iBlock, FPoint( x0, y0 ), FPoint( x2, y2 ), iColor, iPerformanceOptions, callInvalidCB );
    }
    
    static void DrawQuadraticBezierAA( TBlock< _SH>*                   iBlock
                                     , const FPoint&                   iCtrlPt0
                                     , const FPoint&                   iCtrlPt1
                                     , const FPoint&                   iCtrlPt2
                                     , const float                     iWeight
                                     , const CColor&                   iColor
                                     , const FPerformanceOptions&      iPerformanceOptions
                                     , bool                            callInvalidCB )
    {
        int x = iCtrlPt0.x - 2 * iCtrlPt1.x + iCtrlPt2.x;
        int y = iCtrlPt0.y - 2 * iCtrlPt1.y + iCtrlPt2.y;
        double dx = iCtrlPt0.x - iCtrlPt1.x;
        double dy = iCtrlPt0.y - iCtrlPt1.y;
        double dWeight;
        double dt;
        double dq;
        
        FPoint pt0 = iCtrlPt0;
        FPoint pt1 = iCtrlPt1;
        FPoint pt2 = iCtrlPt2;
        
        float weight = iWeight;

        if( weight < 0) //Can't draw a bezier curve with a weight < 0
            return;
        
        if( dx * ( pt2.x - pt1.x ) > 0 )
        {
            if( dy * ( pt2.y - pt1.y ) > 0 )
            {
                if( FMath::Abs( dx * y ) > FMath::Abs( dy * x ) )
                {
                    pt0.x = pt2.x;
                    pt2.x = dx + pt1.x;
                    pt0.y = pt2.y;
                    pt2.y = dy + pt1.y;
                }
            }
            if( pt0.x == pt2.x || weight == 1.0 )
            {
                dt = (pt0.x - pt1.x) / (double)x;
            }
            else
            {
                dq = std::sqrt( 4.0 * weight * weight * ( pt0.x - pt1.x ) * ( pt2.x - pt1.x ) + ( pt2.x - pt0.x ) * (long)( pt2.x - pt0.x ) );
                
                if( pt1.x < pt0.x )
                    dq = -dq;
                
                dt = ( 2.0 * weight * ( pt0.x - pt1.x ) - pt0.x + pt2.x + dq ) / (2.0 * ( 1.0 - weight ) * ( pt2.x - pt0.x ) );
            }
            dq = 1.0 / ( 2.0 * dt * ( 1.0 - dt ) * ( weight - 1.0 ) + 1.0);
            dx = ( dt * dt * ( pt0.x - 2.0 * weight * pt1.x + pt2.x ) + 2.0 * dt * ( weight * pt1.x - pt0.x ) + pt0.x) * dq;
            dy = ( dt * dt * ( pt0.y - 2.0 * weight * pt1.y + pt2.y ) + 2.0 * dt * ( weight * pt1.y - pt0.y ) + pt0.y) * dq;
            dWeight = dt * (weight - 1.0) + 1.0;
            dWeight *= (dWeight * dq);
            weight = ( ( 1.0 - dt ) * ( weight - 1.0 ) + 1.0 ) * std::sqrt(dq);
            x = std::floor( dx + 0.5 );
            y = std::floor( dy + 0.5 );
            dy = ( dx - pt0.x ) * ( pt1.y - pt0.y ) / ( pt1.x - pt0.x ) + pt0.y;
            InternalDrawQuadRationalBezierSegAA( iBlock, pt0.x, pt0.y, x, std::floor( dy + 0.5 ), x, y, dWeight, iColor, iPerformanceOptions, callInvalidCB  );
            dy = ( dx - pt2.x ) * ( pt1.y - pt2.y ) / ( pt1.x - pt2.x ) + pt2.y;
            pt1.y = std::floor( dy + 0.5 );
            pt0.x = pt1.x = x;
            pt0.y = y;
            
            std::cout << "1: dx: " << dx << " dy: " << dy << " x0: " << pt0.x << " y0 : " << pt0.y << " x1: " << pt1.x << " y1 : " << pt1.y << " x2: " << pt2.x << " y2 : " << pt2.y <<   std::endl;
        }
        
        if( ( pt0.y - pt1.y ) * (long)( pt2.y - pt1.y ) > 0 )
        {
            if( pt0.y == pt2.y || iWeight == 1.0 )
            {
                dt = ( pt0.y - pt1.y ) / ( pt0.y - 2.0 * pt1.y + pt2.y );
            }
            else
            {
                dq = std::sqrt( 4.0 * weight * weight * ( pt0.y - pt1.y ) * ( pt2.y - pt1.y ) + ( pt2.y - pt0.y ) * (long)( pt2.y - pt0.y ) );
                
                if( pt1.y < pt0.y )
                    dq = -dq;
                
                dt = ( 2.0 * weight * ( pt0.y - pt1.y ) - pt0.y + pt2.y + dq ) / (2.0 * ( 1.0 - weight ) * ( pt2.y - pt0.y ) );
            }
            dq = 1.0 / ( 2.0 * dt * ( 1.0 - dt ) * ( weight - 1.0 ) + 1.0);
            dx = ( dt * dt * ( pt0.x - 2.0 * weight * pt1.x + pt2.x ) + 2.0 * dt * ( weight * pt1.x - pt0.x ) + pt0.x) * dq;
            dy = ( dt * dt * ( pt0.y - 2.0 * weight * pt1.y + pt2.y ) + 2.0 * dt * ( weight * pt1.y - pt0.y ) + pt0.y) * dq;
            dWeight = dt * (weight - 1.0) + 1.0;
            dWeight *= (dWeight * dq);
            weight = ( ( 1.0 - dt ) * ( weight - 1.0 ) + 1.0 ) * std::sqrt(dq);
            x = std::floor( dx + 0.5 );
            y = std::floor( dy + 0.5 );
            dx = ( pt1.x - pt0.x ) * ( dy - pt0.y ) / ( pt1.y - pt0.y ) + pt0.x;
            InternalDrawQuadRationalBezierSegAA( iBlock, pt0.x, pt0.y, std::floor( dx + 0.5 ), y, x, y, dWeight, iColor, iPerformanceOptions, callInvalidCB  );
            std::cout << "2Before: dx: " << dx << " dy: " << dy << " x0: " << pt0.x << " y0 : " << pt0.y << " x1: " << pt1.x << " y1 : " << pt1.y << " x2: " << pt2.x << " y2 : " << pt2.y << " x: " << x << " y " << y <<   std::endl;

            dx = ( pt1.x - pt2.x ) * ( dy - pt2.y ) / ( pt1.y - pt2.y ) + pt2.x;
            pt1.x = std::floor( dx + 0.5 );
            pt0.x = x;
            pt0.y = pt1.y = y;
            
            std::cout << "2: dx: " << dx << " dy: " << dy << " x0: " << pt0.x << " y0 : " << pt0.y << " x1: " << pt1.x << " y1 : " << pt1.y << " x2: " << pt2.x << " y2 : " << pt2.y <<   std::endl;
        }
        InternalDrawQuadRationalBezierSegAA( iBlock, pt0.x, pt0.y, pt1.x, pt1.y, pt2.x, pt2.y, weight * weight, iColor, iPerformanceOptions, callInvalidCB  );
    }
    

    
};

/////////////////////////////////////////////////////
// Undefines
#undef tSpec

} // namespace ULIS
