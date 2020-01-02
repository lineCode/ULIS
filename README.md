# ULIS2
Unique Library for Imaging Systems

## Description
        - Cross-Platform C++14 Library
        - Generic Digital Image Processing
        - 2D Software Rasterizer
        - All Standard Pixel Blending Modes
        - Many Image Formats, Layouts and Types ( u8, u16, u32, float, double )
        - Color Models ( RGB, HSL, HSV, CMY, CMYK, Lab, XYZ, ... )
        - Color-Managed Pipelines, Color Space Support With Little-CMS
        - Everything Multithreaded
        - SIMD SSE Extensions For Common Heavy Pixel Operations
        - Big Images, Tiled Images ( 300000 px * 300000 px)
        - Image Pools and Caches for Optimisation

## Software Requirements Specification ( SRS )
        - 64bit OS Only
        - Linux, Windows or MacOS
        - CMake ( 3.11+ )
        - Git ( 2.17+ )
        - C++ compiler with support for C++14 or greater

## Library Dependencies
Dependencies are provided as custom shaped redistributions with the repository under the 3rdparty directory.

        - glm
        - Little-CMS

## Getting Started
        - git clone https://github.com/Praxinos/ULIS2
        - mkdir ULIS2_Build
        - cd ULIS2_Build
        - cmake -G ../ULIS2

Sample scripts are also available in the repository to help with the build process.

## ULIS2 for UnrealEngine ThirdParty Module
A `ULIS2.Build.cs` script is provided within the repository.
