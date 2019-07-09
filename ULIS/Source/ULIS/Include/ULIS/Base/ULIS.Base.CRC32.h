/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.CRC32.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.BaseTypes.h"

namespace ULIS {
/////////////////////////////////////////////////////
// CRC32
// Simple CRC32 computation for hashing purposes
uint32 CRC32( const unsigned char *data, int length );
} // namespace ULIS

