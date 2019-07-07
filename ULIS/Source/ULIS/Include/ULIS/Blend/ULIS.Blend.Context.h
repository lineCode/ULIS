/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Blend.Context.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Data/ULIS.Data.h"
#include <assert.h>

namespace ULIS {

/////////////////////////////////////////////////////
// eBlendingMode
enum class eBlendingMode : char
{
    kNormal,
    kMultiply
};

/////////////////////////////////////////////////////
// FBlendingContext
class FBlendingContext
{
public:
    // Blend
    // Blends two Blocks
    // Result is stored in-place in iBlockBack
    // Params:
    // iBlockTop: the block on top
    // iBlockBack: the block that receives the blend ( in-place )
    // iMode: the mode
    // iOpacity: the opcaity of iBlockTop
    // x: where is iBlockTop blended on x axis
    // y: where is iBlockTop blended on y axis
    static void Blend( IBlock* iBlockTop, IBlock* iBlockBack, eBlendingMode iMode, float iOpacity = 1.f, int ix = 0, int iy = 0, bool callInvalidCB = true )
    {
        if( iOpacity == 0.f )
            return;

        assert( iOpacity > 0.f && iOpacity <= 1.f );
        assert( iBlockTop->Id() == iBlockBack->Id() );

        FRect back_bb = { 0, 0,     iBlockBack->Width(),    iBlockBack->Height()    };
        FRect top_bb =  { ix, iy,   iBlockTop->Width(),     iBlockTop->Height()     };
        FRect inter_bb = back_bb & top_bb;
        if( inter_bb.Area() <= 0 ) return;

        FPoint shift( -ix, -iy );

        /*
        switch( iBlockBack->GetCVFlag() ) {
            case CV_8UC1:   TBlockBlender< CV_8UC1,     uint8 >::Run( iBlockTop, iBlockBack, iMode, iOpacity * MAX_uint8, inter_bb, shift ); return;
            case CV_8UC4:   TBlockBlender< CV_8UC4,     uint8 >::Run( iBlockTop, iBlockBack, iMode, iOpacity * MAX_uint8, inter_bb, shift ); return;
            case CV_16UC4:  TBlockBlender< CV_16UC4,    float >::Run( iBlockTop, iBlockBack, iMode, iOpacity * MAX_uint16, inter_bb, shift ); return;
            default:        checkf( false, TEXT( "Error" ) ); return;
        }
        */

        if( !callInvalidCB )
            return;

        iBlockBack->Invalidate( inter_bb );
    }


    static void Blend( IBlock* iBlockTop, IBlock* iBlockBack, eBlendingMode iMode, FRect iArea, float iOpacity = 1.f, bool callInvalidCB = true ) {
        /*
        if( iOpacity == 0.f )
            return;

        checkf( iOpacity > 0.f && iOpacity <= 1.f, TEXT( "Bad Opacity Value" ) );
        checkf( iBlockTop->GetFormat() == iBlockBack->GetFormat(), TEXT( "Formats do not match" ) );

        cv::Rect back_bb = cv::Rect( 0, 0, iBlockBack->Width(), iBlockBack->Height() );
        cv::Rect top_bb = cv::Rect( iArea.x, iArea.y, iArea.width, iArea.height );
        cv::Rect inter_bb = back_bb & top_bb;
        bool intersects = inter_bb.area() > 0;
        if( !intersects ) return;
        cv::Point shift( 0, 0 );

        switch( iBlockBack->GetCVFlag() ) {
            case CV_8UC1:   TBlockBlender< CV_8UC1,     uint8 >::Run( iBlockTop, iBlockBack, iMode, iOpacity * MAX_uint8, inter_bb, shift ); return;
            case CV_8UC4:   TBlockBlender< CV_8UC4,     uint8 >::Run( iBlockTop, iBlockBack, iMode, iOpacity * MAX_uint8, inter_bb, shift ); return;
            case CV_16UC4:  TBlockBlender< CV_16UC4,    float >::Run( iBlockTop, iBlockBack, iMode, iOpacity * MAX_uint16, inter_bb, shift ); return;
            default:        checkf( false, TEXT( "Error" ) ); return;
        }

        if( !callInvalidCB )
            return;

        iBlockBack->Invalidate( inter_bb.x,
                               inter_bb.y,
                               inter_bb.x + inter_bb.width,
                               inter_bb.y + inter_bb.height );
                               */
    }
};

} // namespace ULIS