/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.AlignedMemory.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include <cstdlib>

namespace ULIS {
/////////////////////////////////////////////////////
// TAlignedMemory
template< typename T, size_t alignement >
class TAlignedMemory
{
public:
    // Construction / Destruction
    TAlignedMemory()
        : raw               ( nullptr )
        , ptr               ( nullptr )
        , allocated_size    ( 0 )
        , pad_left          ( 0 )
        , pad_right         ( 0 )
    {}

    ~TAlignedMemory()
    {
        if( raw ) delete[] raw;
    }

public:
    // Public API
    void Allocate( size_t size_bytes )
    {
        size_t offset       = alignement - 1;
        allocated_size      = size_bytes;
        pad_right           = ( alignement - ( size_bytes & offset ) ) & offset;
        size_t total        = offset + size_bytes + pad_right;
        raw = new uint8[ total ];

        size_t memloc_raw_start = (size_t)raw;
        pad_left = ( alignement - ( memloc_raw_start & offset ) ) & offset;
        ptr = raw + pad_left;
    }

    size_t  Alignment   () const { return  alignement;              }
    size_t  Waste       () const { return  pad_left + pad_right;    }
    T*      Ptr         () const { return  ptr;                     }
    size_t  RawStart    () const { return  (size_t)raw;             }
    size_t  RawEnd      () const { return  (size_t)raw;             }
    size_t  DataStart   () const { return  (size_t)raw + pad_left;  }
    size_t  DataEnd     () const { return  (size_t)raw - pad_right; }

private:
    // Private Data
    T*      raw;
    T*      ptr;
    size_t  allocated_size;
    size_t  pad_left;
    size_t  pad_right;
};


} // namespace ULIS

