/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Access.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Interface/ULIS.Interface.Decl.h"

namespace ULIS { class IBlock; }

namespace ULIS {

class PixelValueAutoCastChecked
{
private:
    const IBlock* block;
    int x, y;

public:
    PixelValueAutoCastChecked( const IBlock* iBlock, int iX, int iY )
        : block( iBlock )
        , x( iX )
        , y( iY )
    {}

    template< typename T > operator T()
    {
        assert( block->Id() == T::TypeId() );
        return  ((::ULIS::TBlock< T::TypeId() >*)block)->PixelValue( x, y );
    }
};

} // namespace ULIS

