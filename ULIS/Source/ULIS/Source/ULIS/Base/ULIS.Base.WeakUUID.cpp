/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Base.WeakUUID.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Base/ULIS.Base.WeakUUID.h"
#include <iostream>
#include <sstream>
#include <random>

namespace ULIS {
/////////////////////////////////////////////////////
// Weak UUID
//--------------------------------------------------------------------------------------
//----------------------------------------------------- Private Unit Forward Declaration
unsigned char random_char();
std::string generate_hex( const  unsigned  int  len );
//--------------------------------------------------------------------------------------
//---------------------------------------------------------- Private Unit Implementation
unsigned char random_char() {
    return  static_cast< unsigned  char >( rand()%256 );
}


std::string generate_hex( const  unsigned  int  len ) {
    std::stringstream ss;
    for( unsigned  int i = 0; i < len; i++) {
        auto rc = random_char();
        std::stringstream hexstream;
        hexstream << std::hex << int( rc );
        auto hex = hexstream.str(); 
        ss << ( hex.length() < 2 ? '0' + hex : hex );
    }
    return  ss.str();
}


//--------------------------------------------------------------------------------------
//---------------------------------------------------------------- Public Implementation
std::string generate_weak_uuid( const unsigned int len )
{
    return  generate_hex( len );
}


} // namespace ULIS

