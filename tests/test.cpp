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
    FPixel pixel( ULIS2_FORMAT_BGRAF );
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
    auto R = pixel.GetRef< float >( RGB_R );
    auto G = pixel.GetRef< float >( RGB_G );
    auto B = pixel.GetRef< float >( RGB_B );
    auto A = pixel.GetRef< float >( RGB_A );
    R = 255; G = 20; B = 127; A = 220;

    float _r = pixel.RF();
    float _g = pixel.GF();
    float _b = pixel.BF();
    float _a = pixel.AF();
    auto dummy = 0;
}

