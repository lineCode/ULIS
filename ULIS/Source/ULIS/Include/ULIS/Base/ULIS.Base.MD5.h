/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Data.Pixel.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include <string>
#include <cstring>
#include "ULIS/Base/ULIS.Base.BaseTypes.h"

namespace ULIS {

// Class for simple FMD5 computation for hash purpose
// Based on reference implementation of RFC 1321
class FMD5
{
public:
    // Construction
    FMD5();
    FMD5( const std::string& text );
    FMD5( const uint8* data, int length );

private:
    // Private Internals
    void Init();
    void Transform( const unsigned char block[64] );

public:
    // Public API
    void Update( const unsigned char buf[], uint32 length );
    void Update( const char buf[], uint32 length );
    FMD5& Finalize();
    std::string Hexdigest() const;

private:
    // Private logic
    static void Decode( uint32 output[], const unsigned char input[], uint32 len );
    static void Encode( unsigned char output[], const uint32 input[], uint32 len );
    static inline uint32 F( uint32 x, uint32 y, uint32 z );
    static inline uint32 G( uint32 x, uint32 y, uint32 z );
    static inline uint32 H( uint32 x, uint32 y, uint32 z  );
    static inline uint32 I( uint32 x, uint32 y, uint32 z );
    static inline uint32 Rotate( uint32 x, int n );
    static inline void FF( uint32& a, uint32 b, uint32 c, uint32 d, uint32 x, uint32 s, uint32 ac );
    static inline void GG( uint32& a, uint32 b, uint32 c, uint32 d, uint32 x, uint32 s, uint32 ac );
    static inline void HH( uint32& a, uint32 b, uint32 c, uint32 d, uint32 x, uint32 s, uint32 ac );
    static inline void II( uint32& a, uint32 b, uint32 c, uint32 d, uint32 x, uint32 s, uint32 ac );

private:
    // Private Data
    bool finalized;
    unsigned char buffer[64];
    uint32 count[2];
    uint32 state[4];
    unsigned char digest[16];
};


// Accessibility util
std::string MD5( const std::string str );
std::string MD5( const uint8* data, int length );

} // namespace ULIS

