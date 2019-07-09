/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.CRC32.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Base/ULIS.Base.CRC32.h"

namespace ULIS {
/////////////////////////////////////////////////////
// CRC32
uint32 CRC32( const unsigned char *data, int length ) {
   int i = 0;
   int j = 0;
   unsigned int byte = 0;
   unsigned int crc = 0;
   unsigned int mask = 0;

   i = 0;
   crc = 0xFFFFFFFF;
   while( i < length ) {
      byte = data[i];
      crc = crc ^ byte;
      for (j = 7; j >= 0; j--) {
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
      }
      i = i + 1;
   }
   return ~crc;
}


} // namespace ULIS

