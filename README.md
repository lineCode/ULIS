# ULIS2
Unique Library for Imaging Systems

## License
Check LICENSE.md, ULIS2 is not available for commerical use.

## Description

        Cross-Platform C++14 Library
        Build as static or dynamic library
        Very lightweight, good performance
        Generic Digital Image Processing
        Read Write from files for many popular formats
        Image conversions
        Affine Image Transforms
        FX, Convolution, Blur, Noise, ...
        2D Software Rasterizer
        All Standard Pixel Blending Modes
        Many Image Formats, Layouts and Types ( u8, u16, u32, float, double )
        Color Models ( RGB, HSL, HSV, CMY, CMYK, Lab, XYZ, ... )
        Color-Managed Pipelines, Color Space Support With Little-CMS
        Multithreaded optimisations
        SSE4.2 and AVX2 optimisations
        Support for GPU image processing with OpenCL
        Large Tiled Images ( 300000 px * 300000 px)
        Image Pools and Caches for Optimisation

## History
ULIS was first developped by Clément BERTHAUD ( a.k.a Layl or Robot-Fromage ) on his spare-time in December 2018.
It was then developped as part of Praxinos, aiming for robust tools for digital image processing.
ULIS "1.0" was first released internaly for Praxinos at the end of summer 2019, and used in Iliad, a digital painting plugin for UnrealEngine developped by Praxinos.
ULIS "1.0" had a lot of issues. It was hard to maintain and overused template, resulting in terrible binary sizes for the compiled library ( over 200mo for a release build ).
Performance was ok but there was a lot of room for improvments.
The library needed to mature a bit, and the changes to make were so drastic that a separate successor library, ULIS2, was starting development in beginning of January 2020.
ULIS2 was scheduled for release in February 2020, and comes with a much simpler API, drastically reduced compile times and output binary sizes, better performances,
and a lot of additional features such as support for more models, actual support for AVX2 optimisations, color mix, smudge, new blending modes and alpha modes, new interpolation types, etc.
The build framework was also simplified and extended to conform to the typical cmake build process.
Support for GPU image processing with OpenCL was introduced.
Additionally, the library dependencies changed and are now embedded in the repository. The library doesn't rely on preprocessor so much anymore so boost_preprocessor and coal were removed, Qt and OpenCL are now fully optional, and VCL was added for handling SSE / AVX optimisations in a simpler way.

## Software Requirements Specification ( SRS )

        64bit OS Only
        Linux, Windows or MacOS
        CMake
        Git
        C++ compiler with support for C++14 or greater

## Library Dependencies
Dependencies are redistributed directly within the repository under the 3rdparty directory.

        cppfs
        FeatureDetector
        freetype2
        glm
        OpenCL
        Little-CMS
        stb
        VCL ( Agner Fog's Vector Class Library )

Additional Optional library can be used with ULIS2 to test or extend capabilities:

        Qt

## Getting Started

        git clone https://github.com/Praxinos/ULIS2
        mkdir ULIS2_Build
        cd ULIS2_Build
        cmake -G ../ULIS2

Sample scripts are also available in the repository to help with the build process.

## ULIS2 for UnrealEngine ThirdParty Module
A `ULIS2.Build.cs` script is provided within the repository.
ULIS2 GPU capabilities and interop with Direct3D or OpenGL in the context of a generic rendering hardware interface is still a work in progress.

## Examples
Include ULIS2 headers:

        #include <ULIS2>
        using namespace ul2;
        // Ready to go !

Available formats:

        ULIS2_FORMAT_G8         ULIS2_FORMAT_RGB8       ULIS2_FORMAT_ABGR32     ULIS2_FORMAT_HSV8       ULIS2_FORMAT_AVSH32     ULIS2_FORMAT_HSL8  
        ULIS2_FORMAT_GA8        ULIS2_FORMAT_BGR8       ULIS2_FORMAT_ARGB32     ULIS2_FORMAT_VSH8       ULIS2_FORMAT_AHSV32     ULIS2_FORMAT_LSH8  
        ULIS2_FORMAT_AG8        ULIS2_FORMAT_RGBA8      ULIS2_FORMAT_BGRA32     ULIS2_FORMAT_HSVA8      ULIS2_FORMAT_VSHA32     ULIS2_FORMAT_HSLA8 
        ULIS2_FORMAT_G16        ULIS2_FORMAT_ABGR8      ULIS2_FORMAT_RGBF       ULIS2_FORMAT_AVSH8      ULIS2_FORMAT_HSVF       ULIS2_FORMAT_ALSH8 
        ULIS2_FORMAT_GA16       ULIS2_FORMAT_ARGB8      ULIS2_FORMAT_BGRF       ULIS2_FORMAT_AHSV8      ULIS2_FORMAT_VSHF       ULIS2_FORMAT_AHSL8 
        ULIS2_FORMAT_AG16       ULIS2_FORMAT_BGRA8      ULIS2_FORMAT_RGBAF      ULIS2_FORMAT_VSHA8      ULIS2_FORMAT_HSVAF      ULIS2_FORMAT_LSHA8 
        ULIS2_FORMAT_G32        ULIS2_FORMAT_RGB16      ULIS2_FORMAT_ABGRF      ULIS2_FORMAT_HSV16      ULIS2_FORMAT_AVSHF      ULIS2_FORMAT_HSL16 
        ULIS2_FORMAT_GA32       ULIS2_FORMAT_BGR16      ULIS2_FORMAT_ARGBF      ULIS2_FORMAT_VSH16      ULIS2_FORMAT_AHSVF      ULIS2_FORMAT_LSH16 
        ULIS2_FORMAT_AG32       ULIS2_FORMAT_RGBA16     ULIS2_FORMAT_BGRAF      ULIS2_FORMAT_HSVA16     ULIS2_FORMAT_VSHAF      ULIS2_FORMAT_HSLA16
        ULIS2_FORMAT_GF         ULIS2_FORMAT_ABGR16     ULIS2_FORMAT_RGBD       ULIS2_FORMAT_AVSH16     ULIS2_FORMAT_HSVD       ULIS2_FORMAT_ALSH16
        ULIS2_FORMAT_GAF        ULIS2_FORMAT_ARGB16     ULIS2_FORMAT_BGRD       ULIS2_FORMAT_AHSV16     ULIS2_FORMAT_VSHD       ULIS2_FORMAT_AHSL16
        ULIS2_FORMAT_AGF        ULIS2_FORMAT_BGRA16     ULIS2_FORMAT_RGBAD      ULIS2_FORMAT_VSHA16     ULIS2_FORMAT_HSVAD      ULIS2_FORMAT_LSHA16
        ULIS2_FORMAT_GD         ULIS2_FORMAT_RGB32      ULIS2_FORMAT_ABGRD      ULIS2_FORMAT_HSV32      ULIS2_FORMAT_AVSHD      ULIS2_FORMAT_HSL32 
        ULIS2_FORMAT_GAD        ULIS2_FORMAT_BGR32      ULIS2_FORMAT_ARGBD      ULIS2_FORMAT_VSH32      ULIS2_FORMAT_AHSVD      ULIS2_FORMAT_LSH32 
        ULIS2_FORMAT_AGD        ULIS2_FORMAT_RGBA32     ULIS2_FORMAT_BGRAD      ULIS2_FORMAT_HSVA32     ULIS2_FORMAT_VSHAD      ULIS2_FORMAT_HSLA32
                                                                                                                                                   
        ULIS2_FORMAT_HSL8       ULIS2_FORMAT_ALSH32     ULIS2_FORMAT_YUV8       ULIS2_FORMAT_AVUY32     ULIS2_FORMAT_Lab8       ULIS2_FORMAT_AbaL32
        ULIS2_FORMAT_LSH8       ULIS2_FORMAT_AHSL32     ULIS2_FORMAT_VUY8       ULIS2_FORMAT_AYUV32     ULIS2_FORMAT_baL8       ULIS2_FORMAT_ALab32
        ULIS2_FORMAT_HSLA8      ULIS2_FORMAT_LSHA32     ULIS2_FORMAT_YUVA8      ULIS2_FORMAT_VUYA32     ULIS2_FORMAT_LabA8      ULIS2_FORMAT_baLA32
        ULIS2_FORMAT_ALSH8      ULIS2_FORMAT_HSLF       ULIS2_FORMAT_AVUY8      ULIS2_FORMAT_YUVF       ULIS2_FORMAT_AbaL8      ULIS2_FORMAT_LabF  
        ULIS2_FORMAT_AHSL8      ULIS2_FORMAT_LSHF       ULIS2_FORMAT_AYUV8      ULIS2_FORMAT_VUYF       ULIS2_FORMAT_ALab8      ULIS2_FORMAT_baLF  
        ULIS2_FORMAT_LSHA8      ULIS2_FORMAT_HSLAF      ULIS2_FORMAT_VUYA8      ULIS2_FORMAT_YUVAF      ULIS2_FORMAT_baLA8      ULIS2_FORMAT_LabAF 
        ULIS2_FORMAT_HSL16      ULIS2_FORMAT_ALSHF      ULIS2_FORMAT_YUV16      ULIS2_FORMAT_AVUYF      ULIS2_FORMAT_Lab16      ULIS2_FORMAT_AbaLF 
        ULIS2_FORMAT_LSH16      ULIS2_FORMAT_AHSLF      ULIS2_FORMAT_VUY16      ULIS2_FORMAT_AYUVF      ULIS2_FORMAT_baL16      ULIS2_FORMAT_ALabF 
        ULIS2_FORMAT_HSLA16     ULIS2_FORMAT_LSHAF      ULIS2_FORMAT_YUVA16     ULIS2_FORMAT_VUYAF      ULIS2_FORMAT_LabA16     ULIS2_FORMAT_baLAF 
        ULIS2_FORMAT_ALSH16     ULIS2_FORMAT_HSLD       ULIS2_FORMAT_AVUY16     ULIS2_FORMAT_YUVD       ULIS2_FORMAT_AbaL16     ULIS2_FORMAT_LabD  
        ULIS2_FORMAT_AHSL16     ULIS2_FORMAT_LSHD       ULIS2_FORMAT_AYUV16     ULIS2_FORMAT_VUYD       ULIS2_FORMAT_ALab16     ULIS2_FORMAT_baLD  
        ULIS2_FORMAT_LSHA16     ULIS2_FORMAT_HSLAD      ULIS2_FORMAT_VUYA16     ULIS2_FORMAT_YUVAD      ULIS2_FORMAT_baLA16     ULIS2_FORMAT_LabAD 
        ULIS2_FORMAT_HSL32      ULIS2_FORMAT_ALSHD      ULIS2_FORMAT_YUV32      ULIS2_FORMAT_AVUYD      ULIS2_FORMAT_Lab32      ULIS2_FORMAT_AbaLD 
        ULIS2_FORMAT_LSH32      ULIS2_FORMAT_AHSLD      ULIS2_FORMAT_VUY32      ULIS2_FORMAT_AYUVD      ULIS2_FORMAT_baL32      ULIS2_FORMAT_ALabD 
        ULIS2_FORMAT_HSLA32     ULIS2_FORMAT_LSHAD      ULIS2_FORMAT_YUVA32     ULIS2_FORMAT_VUYAD      ULIS2_FORMAT_LabA32     ULIS2_FORMAT_baLAD 
                                                                                                                                                   
        ULIS2_FORMAT_CMY8       ULIS2_FORMAT_AYMC32     ULIS2_FORMAT_CMYK8      ULIS2_FORMAT_KYMCA16    ULIS2_FORMAT_AKYMCF                        
        ULIS2_FORMAT_YMC8       ULIS2_FORMAT_ACMY32     ULIS2_FORMAT_KCMY8      ULIS2_FORMAT_CMYK32     ULIS2_FORMAT_KYMCAF                        
        ULIS2_FORMAT_CMYA8      ULIS2_FORMAT_YMCA32     ULIS2_FORMAT_KYMC8      ULIS2_FORMAT_KCMY32     ULIS2_FORMAT_CMYKD                         
        ULIS2_FORMAT_AYMC8      ULIS2_FORMAT_CMYF       ULIS2_FORMAT_YMCK8      ULIS2_FORMAT_KYMC32     ULIS2_FORMAT_KCMYD                         
        ULIS2_FORMAT_ACMY8      ULIS2_FORMAT_YMCF       ULIS2_FORMAT_CMYKA8     ULIS2_FORMAT_YMCK32     ULIS2_FORMAT_KYMCD                         
        ULIS2_FORMAT_YMCA8      ULIS2_FORMAT_CMYAF      ULIS2_FORMAT_ACMYK8     ULIS2_FORMAT_CMYKA32    ULIS2_FORMAT_YMCKD                         
        ULIS2_FORMAT_CMY16      ULIS2_FORMAT_AYMCF      ULIS2_FORMAT_AKYMC8     ULIS2_FORMAT_ACMYK32    ULIS2_FORMAT_CMYKAD                        
        ULIS2_FORMAT_YMC16      ULIS2_FORMAT_ACMYF      ULIS2_FORMAT_KYMCA8     ULIS2_FORMAT_AKYMC32    ULIS2_FORMAT_ACMYKD                        
        ULIS2_FORMAT_CMYA16     ULIS2_FORMAT_YMCAF      ULIS2_FORMAT_CMYK16     ULIS2_FORMAT_KYMCA32    ULIS2_FORMAT_AKYMCD                        
        ULIS2_FORMAT_AYMC16     ULIS2_FORMAT_CMYD       ULIS2_FORMAT_KCMY16     ULIS2_FORMAT_CMYKF      ULIS2_FORMAT_KYMCAD                        
        ULIS2_FORMAT_ACMY16     ULIS2_FORMAT_YMCD       ULIS2_FORMAT_KYMC16     ULIS2_FORMAT_KCMYF                                                 
        ULIS2_FORMAT_YMCA16     ULIS2_FORMAT_CMYAD      ULIS2_FORMAT_YMCK16     ULIS2_FORMAT_KYMCF                                                 
        ULIS2_FORMAT_CMY32      ULIS2_FORMAT_AYMCD      ULIS2_FORMAT_CMYKA16    ULIS2_FORMAT_YMCKF                                                 
        ULIS2_FORMAT_YMC32      ULIS2_FORMAT_ACMYD      ULIS2_FORMAT_ACMYK16    ULIS2_FORMAT_CMYKAF                                                
        ULIS2_FORMAT_CMYA32     ULIS2_FORMAT_YMCAD      ULIS2_FORMAT_AKYMC16    ULIS2_FORMAT_ACMYKF                                                
                                                                                                                                                   
        ULIS2_FORMAT_XYZ8       ULIS2_FORMAT_AZYX32     ULIS2_FORMAT_Yxy8       ULIS2_FORMAT_AyxY32                                                
        ULIS2_FORMAT_ZYX8       ULIS2_FORMAT_AXYZ32     ULIS2_FORMAT_yxY8       ULIS2_FORMAT_AYxy32                                                
        ULIS2_FORMAT_XYZA8      ULIS2_FORMAT_ZYXA32     ULIS2_FORMAT_YxyA8      ULIS2_FORMAT_yxYA32                                                
        ULIS2_FORMAT_AZYX8      ULIS2_FORMAT_XYZF       ULIS2_FORMAT_AyxY8      ULIS2_FORMAT_YxyF                                                  
        ULIS2_FORMAT_AXYZ8      ULIS2_FORMAT_ZYXF       ULIS2_FORMAT_AYxy8      ULIS2_FORMAT_yxYF                                                  
        ULIS2_FORMAT_ZYXA8      ULIS2_FORMAT_XYZAF      ULIS2_FORMAT_yxYA8      ULIS2_FORMAT_YxyAF                                                 
        ULIS2_FORMAT_XYZ16      ULIS2_FORMAT_AZYXF      ULIS2_FORMAT_Yxy16      ULIS2_FORMAT_AyxYF                                                 
        ULIS2_FORMAT_ZYX16      ULIS2_FORMAT_AXYZF      ULIS2_FORMAT_yxY16      ULIS2_FORMAT_AYxyF                                                 
        ULIS2_FORMAT_XYZA16     ULIS2_FORMAT_ZYXAF      ULIS2_FORMAT_YxyA16     ULIS2_FORMAT_yxYAF                                                 
        ULIS2_FORMAT_AZYX16     ULIS2_FORMAT_XYZD       ULIS2_FORMAT_AyxY16     ULIS2_FORMAT_YxyD                                                  
        ULIS2_FORMAT_AXYZ16     ULIS2_FORMAT_ZYXD       ULIS2_FORMAT_AYxy16     ULIS2_FORMAT_yxYD                                                  
        ULIS2_FORMAT_ZYXA16     ULIS2_FORMAT_XYZAD      ULIS2_FORMAT_yxYA16     ULIS2_FORMAT_YxyAD                                                 
        ULIS2_FORMAT_XYZ32      ULIS2_FORMAT_AZYXD      ULIS2_FORMAT_Yxy32      ULIS2_FORMAT_AyxYD                                                 
        ULIS2_FORMAT_ZYX32      ULIS2_FORMAT_AXYZD      ULIS2_FORMAT_yxY32      ULIS2_FORMAT_AYxyD                                                 
        ULIS2_FORMAT_XYZA32     ULIS2_FORMAT_ZYXAD      ULIS2_FORMAT_YxyA32     ULIS2_FORMAT_yxYAD                                                 

Available blending modes:

        BM_NORMAL           BM_DARKERCOLOR      BM_LINEARLIGHT      BM_DIVIDE
        BM_TOP              BM_LIGHTEN          BM_PINLIGHT         BM_AVERAGE
        BM_BACK             BM_SCREEN           BM_HARDMIX          BM_HUE
        BM_BEHIND           BM_COLORDODGE       BM_PHOENIX          BM_SATURATION
        BM_DISSOLVE         BM_LINEARDODGE      BM_REFLECT          BM_COLOR
        BM_BAYERDITHER8x8   BM_LIGHTERCOLOR     BM_GLOW             BM_LUMINOSITY
        BM_DARKEN           BM_OVERLAY          BM_DIFFERENCE
        BM_MULTIPY          BM_SOFTLIGHT        BM_EXCLUSION
        BM_COLORBURN        BM_HARDLIGHT        BM_ADD
        BM_LINEARBURN       BM_VIVIDLIGHT       BM_SUBSTRACT

Available alpha modes:

        AM_NORMAL           AM_ADD
        AM_ERASE            AM_MUL
        AM_TOP              AM_MIN
        AM_BACK             AM_MAX
        AM_SUB              AM_INVMAX

Create colors in different models:

        FColor color_rgb8_red(      ULIS2_FORMAT_RGB8,  { 255, 0, 0 } );            // Red, constructed from int clamped in range 0-255.
        FColor color_rgba8_blue(    ULIS2_FORMAT_RGBA8, { 0, 0, 255, 127 } );       // Blue with semi transparent alpha information, constructed from int clamped in range 0-255.
        FColor color_rgba8_green(   ULIS2_FORMAT_RGBA8, { 0.f, 1.f, 0.f, 0.5f } );  // Green with semi transparent alpha information, constructed from float scaled to range 0-255
        FColor color_bgraF_red(     ULIS2_FORMAT_RGBAF, { 1.f, 0.f, 0.f, 0.5f } );  // Red with semi transparent alpha information, constructed from float, not clamped.
        FColor color_LabD(          ULIS2_FORMAT_LabD );    // Lab double color, initialized with zero values.
        FColor color_LabF(          ULIS2_FORMAT_LabF );    // Lab float color, initialized with zero values.
        FColor color_HSVAF(         ULIS2_FORMAT_HSVAF );   // HSV float color with alpha information, initialized with zero values.
        FColor color_CMYKA16(       ULIS2_FORMAT_CMYKA16 ); // CMYK 16bit uint color with alpha information, initialized with zero values.
        FColor color_ABGR8(         ULIS2_FORMAT_ABGR8 );   // Rgb 8bit uint color with alpha information, ABGR8888 memory layout, initialized with zero values.
        FColor color_BGRA8(         ULIS2_FORMAT_BGRA8 );   // Rgb 8bit uint color with alpha information, BGRA8888 memory layout, initialized with zero values.
        // etc ...
        FColor color( ULIS2_FORMAT_RGBA8 );
        color.SetR8( 255 );
        color.SetG8( 255 );
        color.SetB8( 255 );
        color.SetA8( 255 );
        // Color will be white.
        // Other accessors can be used too:
        color.SetRF( 0.5 );
        color.SetGF( 0.2 );
        color.SetBF( 0.0 );
        color.SetA8( 1.f );
        // Conversion of any combinations of models can be performed with Conv
        FColor color_RGBA8( ULIS2_FORMAT_RGBA8 );
        FColor color_RGBA16( ULIS2_FORMAT_RGBA16 );
        FColor color_BGRAD( ULIS2_FORMAT_BGRAD );
        FColor color_AbaLF( ULIS2_FORMAT_AbaLF );
        // Src, Dst
        Conv( color_RGBA8, color_RGBA16 );  // perform value conversion from range 0-255 to 0-65535
        Conv( color_RGBA8, color_BGRAD );   // perform layout conversion from RGBA to BGRA and value conversion from range 0-255 to 0.0-1.0
        Conv( color_RGBA8, color_AbaLF );   // perform model conversion and value conversion from RGBA uint8 to Lab float with specified memory layout AbaLffff.
        // etc ...

Get info from pixel colors in different models:

        FPixel rgba8( ULIS2_FORMAT_RGBA8 );
        pixelcolor.BytesPerSample()     // 1
        pixelcolor.Depth()              // 4
        pixelcolor.Format()             // ULIS2_FORMAT_RGBA8
        pixelcolor.Model()              // CM_RGB
        pixelcolor.Type()               // TYPE_UINT8
        pixelcolor.HasAlpha()           // true
        pixelcolor.NumSamples()         // 4
        pixelcolor.NumColorChannels()   // 3

Create and manipulate Images in various formats:

        int         width   = 512;
        int         height  = 512;
        
        // Allocate blocks of size 512x512, with format layout in memory RGBA8888, memory is uninitialized
        FBlock      image_A( width, height, ULIS2_FORMAT_RGBA8 );
        FBlock      image_B( width, height, ULIS2_FORMAT_RGBA8 );
        
        // Create a thread pool with as many threads as supported by the system, and launch these threads
        FThreadPool threadPool;
        
        // Specify performances intent for operations.
        // User may want to not use multithreading or AVX optimisation for benchmark purpose
        FPerf       perfIntent( Perf_MT | Perf_SSE4_2 | Perf_AVX2 );
        
        // Runtime collected information about the system and cpu support for SIMD optimisations
        FCPU        cpuInfo;
        
        // Pixel colors in RGB8
        FColor      colorWhite( ULIS2_FORMAT_RGB8, { 255, 255, 255 } );
        FColor      colorBlack( ULIS2_FORMAT_RGB8, { 0, 0, 0 } );

        // Clear image using performance intent and cpu info, processing in threadpool if intent allows it.
        // The non blocking parameters tells the pool to not wait for completion directly, the user must call it manually.
        // Beware of launching multiple concurrent operations on the same data with non blocking.
        // Here we are clearing different data and waiting for completion afterwards.
        Clear( &threadPool, ULIS2_NONBLOCKING, perfIntent, cpuInfo, &image_A, ULIS2_NOCB );
        Clear( &threadPool, ULIS2_NONBLOCKING, perfIntent, cpuInfo, &image_B, ULIS2_NOCB );
        threadPool.WaitForCompletion();

        // Fill image with specified color, the color can be in any format or model, it will be converted to the image format before filling.
        Fill( &threadPool, ULIS2_NONBLOCKING, perfIntent, cpuInfo, &image_A, colorWhite, ULIS2_NOCB );
        Fill( &threadPool, ULIS2_NONBLOCKING, perfIntent, cpuInfo, &image_B, colorBlack, ULIS2_NOCB );
        threadPool.WaitForCompletion();

        // Blend image_B onto image_A according to the input parameters.
        // A normal blend will be performed with normal alpha at 50% opacity.
        Blend( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, ULIS2_NOSUBPIXEL, &image_B, &image_A, glm::vec2( 0.f ), BM_NORMAL, AM_NORMAL, 0.5f, ULIS2_NOCB );

Full program for rendering simple black text on white background:

        #include <ULIS2>

        int
        main( int argc, char *argv[] )
        {
            FBlock          block( 512, 512, ULIS2_FORMAT_BGRA8 );
            FThreadPool     threadPool;
            FPerf           perfIntent( Perf_Best_CPU );
            FCPU            cpuInfo
            FPixel          white( ULIS2_FORMAT_BGRA8, { 255_u8, 255_u8, 255_u8, 255_u8 } );
            FPixel          black( ULIS2_FORMAT_BGRA8, { 0_u8, 0_u8, 0_u8, 0_u8 } );

            Fill( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, &block, white, ULIS2_NOCB );

            FFontEngine     fontEngine;
            FFontRegistry   fontRegistry;
            fontRegistry.Load( fontEngine );

            FFont font_Arial_Black( fontEngine, fontRegistry, "Arial", "Black" );

            DrawText( &threadPool, ULIS2_BLOCKING, perfIntent, cpuInfo, &block, "Hello World !", glm::vec2( 0.f ), black, font_Arial_Black, 16px, ULIS2_NOCB );

            return  0;
        }

