# ULIS2
Unique Library for Imaging Systems

## Description
        Cross-Platform C++14 Library
        Generic Digital Image Processing
        2D Software Rasterizer
        All Standard Pixel Blending Modes
        Many Image Formats, Layouts and Types ( u8, u16, u32, float, double )
        Color Models ( RGB, HSL, HSV, CMY, CMYK, Lab, XYZ, ... )
        Color-Managed Pipelines, Color Space Support With Little-CMS
        Everything Multithreaded
        SIMD SSE Extensions For Common Heavy Pixel Operations
        Big Images, Tiled Images ( 300000 px * 300000 px)
        Image Pools and Caches for Optimisation

## Software Requirements Specification ( SRS )
        64bit OS Only
        Linux, Windows or MacOS
        CMake ( 3.11+ )
        Git ( 2.17+ )
        C++ compiler with support for C++14 or greater

## Supported Compilers
        MinGW x64
        Clang LLVM
        MSVC
        GNU GCC

## [Optional] Enforcing a x64 toolchain
For Windows MSVC, ensure these global environment variables are set when launching an MSVC build environment:

        _IsNativeEnvironment            true
        PreferredToolArchitecture       x64

## Library Dependencies
        glm           ( https://github.com/g-truc/glm )
        Little-CMS    ( https://github.com/Robot-Fromage/Little-CMS )
Note: my Little-CMS fork provides a CMakeLists.

## Officially Supported IDEs
        Windows: VisualStudio 2017, 2019
        MacOS: XCode
        Linux: SublimeText

## Getting Started
        git clone git@pro.github.com:Praxinos/ULIS2.git
        cd ULIS2
        #Windows:         call    Setup.bat
        #MacOS / Linux :  sh      Setup.sh

You should see the following files appear in the repository root:

        #Windows:
            MinGW_Makefile_GCC_Config.cmake
            VisualStudio_Solution_CLANG_LLVM_Config.cmake
            VisualStudio_Solution_MSVC_Config.cmake
        #MacOS / Linux:
            SublimeText_Project_GNU_GCC_Config.cmake
            Xcode_Config.cmake

The contents of these files should look like this:

        SET( ULIS2_BUILD_SHARED              OFF )
        SET( ULIS2_BUILD_TESTS               ON )
        SET( ULIS2_BUILD_GUIS                OFF )
        SET( ULIS2_QT_CMAKE_PATH             "default" )
        SET( ULIS2_GLM_INCLUDE_PATH          "default" )
        SET( ULIS2_LCMS2_INCLUDE_PATH        "default" )
        SET( ULIS2_LCMS2_DEBUG_LIB_PATH      "default" )
        SET( ULIS2_LCMS2_RELEASE_LIB_PATH    "default" )

Make sure you cloned the dependencies and built them if needed. You can then copy the path for the requested components. All paths should use forward slashes on all OS, even Windows MacOS and Linux. All paths should have a trailing forward slash too. `ULIS_QT_CMAKE_PATH` is optional and can remain to `"default"`, in that case `ULIS_BUILD_GUIS` should remain `OFF`too. Make sure you fill the path for the config file of your compiler / IDE of choice, and that components you use were built with the same compiler. The building process of the dependencies will not be detailled here, it is left for the user to figure out, although most dependencies are header-only and i provide a CMakeLists in order to build Little-CMS easily, which can also be found in the Scripts folder of ULIS2.

Helper Scripts are also available in the repository to clone and build the dependencies automatically, embeded withing the repository.

Here is an example of a fully configured config.cmake file:

        SET( ULIS2_BUILD_SHARED              OFF )
        SET( ULIS2_BUILD_TESTS               ON )
        SET( ULIS2_BUILD_GUIS                ON )
        SET( ULIS2_QT_CMAKE_PATH             "C:/Qt/5.12.2/msvc2017_64/lib/cmake/" )
        SET( ULIS2_GLM_INCLUDE_PATH          "C:/Users/WorkStation/work/glm_distribution/glm/" )
        SET( ULIS2_LCMS2_INCLUDE_PATH        "C:/Users/WorkStation/work/Little-CMS_MSVC_distribution/include/" )
        SET( ULIS2_LCMS2_DEBUG_LIB_PATH      "C:/Users/WorkStation/work/Little-CMS_MSVC_distribution/lcms2d.lib" )
        SET( ULIS2_LCMS2_RELEASE_LIB_PATH    "C:/Users/WorkStation/work/Little-CMS_MSVC_distribution/lcms2.lib" )

When you're done you should launch the appropriate script according to your configuration:

        Generate_MinGW_Makefile_GCC.bat
        Generate_VisualStudio_Solution_CLANG_LLVM.bat
        Generate_VisualStudio_Solution_MSVC.bat
        Generate_SublimeText_Project_GNU_GCC.sh
        Generate_Xcode.sh

The generated project files will be found under `ULIS2/Generated_*/` where you fill find solution files according to your config.
Project files are git-ignored and are never commited.

## ULIS2 for UnrealEngine ThirdParty Module
A `ULIS2.Build.cs` script is provided with the repo, as well as a `FullBuildUE4_*` script for easy one-click build. In order to include ULIS2 as a third party module for UE4 you can copy the Redist folder with the build.cs file and put them together in a ULIS2 directory under ThirdParty in your UnrealEngine setup, wether it is a custom build, C++ project or Plugin.

## Additional Notes
On Linux, the provided scripts generate the CMake makefiles for SublimeText solutions, you can install the free demo or paid version of SublimeText in order to enjoy it.

The CMake makefiles will work with wathever generator you chose.
On MacOS the provided scripts generate solutions for Xcode only, however you should be able to use other generators too.

On Windows, the provided scripts generate solutions for VisualStudio using either MSVC or Clang LLVM. There is also a script for MinGW GCC which will produce MinGW makefiles.

If you wish to use `Qt` you should download it ( OpenSource Qt versions 5.10+ ) from the official website, either pre-built for Windows MSVC or MinGW or Linux GCC or for MacOS Clang, or build it from source.
On Windows, using VisualStudio you should download the VS plugin `Qt VisualStudio Tools`.

If you wish to use Clang LLVM VisualStudio solution generator, you should download the VS plugin `LLVM Compiler Toolchain`.

If you wish to use the `MinGW GCC` generator with Qt and test GUIS enabled, you should make sure that the MinGW GCC version available from PATH is the one provided with the Qt version you downloaded, or that Qt was built with the GCC version you are using.
