// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Test.cpp
* @author       Clement Berthaud
* @brief        Test application for ULIS2.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS2>
using namespace ::ul2;

int
main()
{
    FPixel pixel( ULIS2_FORMAT_RGBA8 );
    std::cout << "pixel.BytesPerSample()    : " << (int)pixel.BytesPerSample()     << std::endl;
    std::cout << "pixel.Depth()             : " << (int)pixel.Depth()              << std::endl;
    std::cout << "pixel.Format()            : " << (int)pixel.Format()             << std::endl;
    std::cout << "pixel.HasAlpha()          : " << (int)pixel.HasAlpha()           << std::endl;
    std::cout << "pixel.Model()             : " << (int)pixel.Model()              << std::endl;
    std::cout << "pixel.NumColorChannels()  : " << (int)pixel.NumColorChannels()   << std::endl;
    std::cout << "pixel.NumSamples()        : " << (int)pixel.NumSamples()         << std::endl;
    std::cout << "pixel.Reversed()          : " << (int)pixel.Reversed()           << std::endl;
    std::cout << "pixel.Swapped()           : " << (int)pixel.Swapped()            << std::endl;
    std::cout << "pixel.Type()              : " << (int)pixel.Type()               << std::endl;
    uint8& R = pixel.GetRef< uint8 >( RGB_R );
    uint8& G = pixel.GetRef< uint8 >( RGB_G );
    uint8& B = pixel.GetRef< uint8 >( RGB_B );
    uint8& A = pixel.GetRef< uint8 >( RGB_A );
    R = 255; G = 20; B = 127; A = 220;

    uint8 _r = pixel.R8();
    uint8 _g = pixel.G8();
    uint8 _b = pixel.B8();
    uint8 _a = pixel.A8();
    auto dummy = 0;
}

