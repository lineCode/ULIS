// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         test.cpp
* @author       Clement Berthaud
* @brief        Test application for ULIS2.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS2>
//#include <CL/cl.hpp>
//#include <vectorclass.h>
using namespace ::ul2;

int
main()
{
    std::cout << "ULIS2_FORMAT_G8      " << " = " << (int)( ULIS2_FORMAT_G8     ) << std::endl;
    std::cout << "ULIS2_FORMAT_GA8     " << " = " << (int)( ULIS2_FORMAT_GA8    ) << std::endl;
    std::cout << "ULIS2_FORMAT_AG8     " << " = " << (int)( ULIS2_FORMAT_AG8    ) << std::endl;
    std::cout << "ULIS2_FORMAT_G16     " << " = " << (int)( ULIS2_FORMAT_G16    ) << std::endl;
    std::cout << "ULIS2_FORMAT_GA16    " << " = " << (int)( ULIS2_FORMAT_GA16   ) << std::endl;
    std::cout << "ULIS2_FORMAT_AG16    " << " = " << (int)( ULIS2_FORMAT_AG16   ) << std::endl;
    std::cout << "ULIS2_FORMAT_G32     " << " = " << (int)( ULIS2_FORMAT_G32    ) << std::endl;
    std::cout << "ULIS2_FORMAT_GA32    " << " = " << (int)( ULIS2_FORMAT_GA32   ) << std::endl;
    std::cout << "ULIS2_FORMAT_AG32    " << " = " << (int)( ULIS2_FORMAT_AG32   ) << std::endl;
    std::cout << "ULIS2_FORMAT_GF      " << " = " << (int)( ULIS2_FORMAT_GF     ) << std::endl;
    std::cout << "ULIS2_FORMAT_GAF     " << " = " << (int)( ULIS2_FORMAT_GAF    ) << std::endl;
    std::cout << "ULIS2_FORMAT_AGF     " << " = " << (int)( ULIS2_FORMAT_AGF    ) << std::endl;
    std::cout << "ULIS2_FORMAT_GD      " << " = " << (int)( ULIS2_FORMAT_GD     ) << std::endl;
    std::cout << "ULIS2_FORMAT_GAD     " << " = " << (int)( ULIS2_FORMAT_GAD    ) << std::endl;
    std::cout << "ULIS2_FORMAT_AGD     " << " = " << (int)( ULIS2_FORMAT_AGD    ) << std::endl;
    std::cout << "ULIS2_FORMAT_RGB8    " << " = " << (int)( ULIS2_FORMAT_RGB8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_BGR8    " << " = " << (int)( ULIS2_FORMAT_BGR8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_RGBA8   " << " = " << (int)( ULIS2_FORMAT_RGBA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ABGR8   " << " = " << (int)( ULIS2_FORMAT_ABGR8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ARGB8   " << " = " << (int)( ULIS2_FORMAT_ARGB8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_BGRA8   " << " = " << (int)( ULIS2_FORMAT_BGRA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_RGB16   " << " = " << (int)( ULIS2_FORMAT_RGB16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_BGR16   " << " = " << (int)( ULIS2_FORMAT_BGR16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_RGBA16  " << " = " << (int)( ULIS2_FORMAT_RGBA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ABGR16  " << " = " << (int)( ULIS2_FORMAT_ABGR16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ARGB16  " << " = " << (int)( ULIS2_FORMAT_ARGB16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_BGRA16  " << " = " << (int)( ULIS2_FORMAT_BGRA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_RGB32   " << " = " << (int)( ULIS2_FORMAT_RGB32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_BGR32   " << " = " << (int)( ULIS2_FORMAT_BGR32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_RGBA32  " << " = " << (int)( ULIS2_FORMAT_RGBA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ABGR32  " << " = " << (int)( ULIS2_FORMAT_ABGR32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ARGB32  " << " = " << (int)( ULIS2_FORMAT_ARGB32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_BGRA32  " << " = " << (int)( ULIS2_FORMAT_BGRA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_RGBF    " << " = " << (int)( ULIS2_FORMAT_RGBF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_BGRF    " << " = " << (int)( ULIS2_FORMAT_BGRF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_RGBAF   " << " = " << (int)( ULIS2_FORMAT_RGBAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ABGRF   " << " = " << (int)( ULIS2_FORMAT_ABGRF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ARGBF   " << " = " << (int)( ULIS2_FORMAT_ARGBF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_BGRAF   " << " = " << (int)( ULIS2_FORMAT_BGRAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_RGBD    " << " = " << (int)( ULIS2_FORMAT_RGBD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_BGRD    " << " = " << (int)( ULIS2_FORMAT_BGRD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_RGBAD   " << " = " << (int)( ULIS2_FORMAT_RGBAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ABGRD   " << " = " << (int)( ULIS2_FORMAT_ABGRD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ARGBD   " << " = " << (int)( ULIS2_FORMAT_ARGBD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_BGRAD   " << " = " << (int)( ULIS2_FORMAT_BGRAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSV8    " << " = " << (int)( ULIS2_FORMAT_HSV8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_VSH8    " << " = " << (int)( ULIS2_FORMAT_VSH8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSVA8   " << " = " << (int)( ULIS2_FORMAT_HSVA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AVSH8   " << " = " << (int)( ULIS2_FORMAT_AVSH8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AHSV8   " << " = " << (int)( ULIS2_FORMAT_AHSV8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_VSHA8   " << " = " << (int)( ULIS2_FORMAT_VSHA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSV16   " << " = " << (int)( ULIS2_FORMAT_HSV16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_VSH16   " << " = " << (int)( ULIS2_FORMAT_VSH16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSVA16  " << " = " << (int)( ULIS2_FORMAT_HSVA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AVSH16  " << " = " << (int)( ULIS2_FORMAT_AVSH16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AHSV16  " << " = " << (int)( ULIS2_FORMAT_AHSV16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_VSHA16  " << " = " << (int)( ULIS2_FORMAT_VSHA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSV32   " << " = " << (int)( ULIS2_FORMAT_HSV32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_VSH32   " << " = " << (int)( ULIS2_FORMAT_VSH32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSVA32  " << " = " << (int)( ULIS2_FORMAT_HSVA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AVSH32  " << " = " << (int)( ULIS2_FORMAT_AVSH32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AHSV32  " << " = " << (int)( ULIS2_FORMAT_AHSV32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_VSHA32  " << " = " << (int)( ULIS2_FORMAT_VSHA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSVF    " << " = " << (int)( ULIS2_FORMAT_HSVF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_VSHF    " << " = " << (int)( ULIS2_FORMAT_VSHF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSVAF   " << " = " << (int)( ULIS2_FORMAT_HSVAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AVSHF   " << " = " << (int)( ULIS2_FORMAT_AVSHF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AHSVF   " << " = " << (int)( ULIS2_FORMAT_AHSVF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_VSHAF   " << " = " << (int)( ULIS2_FORMAT_VSHAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSVD    " << " = " << (int)( ULIS2_FORMAT_HSVD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_VSHD    " << " = " << (int)( ULIS2_FORMAT_VSHD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSVAD   " << " = " << (int)( ULIS2_FORMAT_HSVAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AVSHD   " << " = " << (int)( ULIS2_FORMAT_AVSHD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AHSVD   " << " = " << (int)( ULIS2_FORMAT_AHSVD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_VSHAD   " << " = " << (int)( ULIS2_FORMAT_VSHAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSL8    " << " = " << (int)( ULIS2_FORMAT_HSL8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_LSH8    " << " = " << (int)( ULIS2_FORMAT_LSH8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSLA8   " << " = " << (int)( ULIS2_FORMAT_HSLA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ALSH8   " << " = " << (int)( ULIS2_FORMAT_ALSH8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AHSL8   " << " = " << (int)( ULIS2_FORMAT_AHSL8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_LSHA8   " << " = " << (int)( ULIS2_FORMAT_LSHA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSL16   " << " = " << (int)( ULIS2_FORMAT_HSL16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_LSH16   " << " = " << (int)( ULIS2_FORMAT_LSH16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSLA16  " << " = " << (int)( ULIS2_FORMAT_HSLA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ALSH16  " << " = " << (int)( ULIS2_FORMAT_ALSH16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AHSL16  " << " = " << (int)( ULIS2_FORMAT_AHSL16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_LSHA16  " << " = " << (int)( ULIS2_FORMAT_LSHA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSL32   " << " = " << (int)( ULIS2_FORMAT_HSL32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_LSH32   " << " = " << (int)( ULIS2_FORMAT_LSH32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSLA32  " << " = " << (int)( ULIS2_FORMAT_HSLA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ALSH32  " << " = " << (int)( ULIS2_FORMAT_ALSH32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AHSL32  " << " = " << (int)( ULIS2_FORMAT_AHSL32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_LSHA32  " << " = " << (int)( ULIS2_FORMAT_LSHA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSLF    " << " = " << (int)( ULIS2_FORMAT_HSLF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_LSHF    " << " = " << (int)( ULIS2_FORMAT_LSHF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSLAF   " << " = " << (int)( ULIS2_FORMAT_HSLAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ALSHF   " << " = " << (int)( ULIS2_FORMAT_ALSHF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AHSLF   " << " = " << (int)( ULIS2_FORMAT_AHSLF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_LSHAF   " << " = " << (int)( ULIS2_FORMAT_LSHAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSLD    " << " = " << (int)( ULIS2_FORMAT_HSLD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_LSHD    " << " = " << (int)( ULIS2_FORMAT_LSHD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_HSLAD   " << " = " << (int)( ULIS2_FORMAT_HSLAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ALSHD   " << " = " << (int)( ULIS2_FORMAT_ALSHD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AHSLD   " << " = " << (int)( ULIS2_FORMAT_AHSLD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_LSHAD   " << " = " << (int)( ULIS2_FORMAT_LSHAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMY8    " << " = " << (int)( ULIS2_FORMAT_CMY8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMC8    " << " = " << (int)( ULIS2_FORMAT_YMC8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYA8   " << " = " << (int)( ULIS2_FORMAT_CMYA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYMC8   " << " = " << (int)( ULIS2_FORMAT_AYMC8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ACMY8   " << " = " << (int)( ULIS2_FORMAT_ACMY8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMCA8   " << " = " << (int)( ULIS2_FORMAT_YMCA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMY16   " << " = " << (int)( ULIS2_FORMAT_CMY16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMC16   " << " = " << (int)( ULIS2_FORMAT_YMC16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYA16  " << " = " << (int)( ULIS2_FORMAT_CMYA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYMC16  " << " = " << (int)( ULIS2_FORMAT_AYMC16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ACMY16  " << " = " << (int)( ULIS2_FORMAT_ACMY16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMCA16  " << " = " << (int)( ULIS2_FORMAT_YMCA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMY32   " << " = " << (int)( ULIS2_FORMAT_CMY32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMC32   " << " = " << (int)( ULIS2_FORMAT_YMC32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYA32  " << " = " << (int)( ULIS2_FORMAT_CMYA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYMC32  " << " = " << (int)( ULIS2_FORMAT_AYMC32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ACMY32  " << " = " << (int)( ULIS2_FORMAT_ACMY32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMCA32  " << " = " << (int)( ULIS2_FORMAT_YMCA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYF    " << " = " << (int)( ULIS2_FORMAT_CMYF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMCF    " << " = " << (int)( ULIS2_FORMAT_YMCF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYAF   " << " = " << (int)( ULIS2_FORMAT_CMYAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYMCF   " << " = " << (int)( ULIS2_FORMAT_AYMCF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ACMYF   " << " = " << (int)( ULIS2_FORMAT_ACMYF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMCAF   " << " = " << (int)( ULIS2_FORMAT_YMCAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYD    " << " = " << (int)( ULIS2_FORMAT_CMYD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMCD    " << " = " << (int)( ULIS2_FORMAT_YMCD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYAD   " << " = " << (int)( ULIS2_FORMAT_CMYAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYMCD   " << " = " << (int)( ULIS2_FORMAT_AYMCD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ACMYD   " << " = " << (int)( ULIS2_FORMAT_ACMYD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMCAD   " << " = " << (int)( ULIS2_FORMAT_YMCAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYK8   " << " = " << (int)( ULIS2_FORMAT_CMYK8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_KCMY8   " << " = " << (int)( ULIS2_FORMAT_KCMY8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_KYMC8   " << " = " << (int)( ULIS2_FORMAT_KYMC8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMCK8   " << " = " << (int)( ULIS2_FORMAT_YMCK8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYKA8  " << " = " << (int)( ULIS2_FORMAT_CMYKA8 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ACMYK8  " << " = " << (int)( ULIS2_FORMAT_ACMYK8 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AKYMC8  " << " = " << (int)( ULIS2_FORMAT_AKYMC8 ) << std::endl;
    std::cout << "ULIS2_FORMAT_KYMCA8  " << " = " << (int)( ULIS2_FORMAT_KYMCA8 ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYK16  " << " = " << (int)( ULIS2_FORMAT_CMYK16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_KCMY16  " << " = " << (int)( ULIS2_FORMAT_KCMY16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_KYMC16  " << " = " << (int)( ULIS2_FORMAT_KYMC16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMCK16  " << " = " << (int)( ULIS2_FORMAT_YMCK16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYKA16 " << " = " << (int)( ULIS2_FORMAT_CMYKA16) << std::endl;
    std::cout << "ULIS2_FORMAT_ACMYK16 " << " = " << (int)( ULIS2_FORMAT_ACMYK16) << std::endl;
    std::cout << "ULIS2_FORMAT_AKYMC16 " << " = " << (int)( ULIS2_FORMAT_AKYMC16) << std::endl;
    std::cout << "ULIS2_FORMAT_KYMCA16 " << " = " << (int)( ULIS2_FORMAT_KYMCA16) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYK32  " << " = " << (int)( ULIS2_FORMAT_CMYK32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_KCMY32  " << " = " << (int)( ULIS2_FORMAT_KCMY32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_KYMC32  " << " = " << (int)( ULIS2_FORMAT_KYMC32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMCK32  " << " = " << (int)( ULIS2_FORMAT_YMCK32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYKA32 " << " = " << (int)( ULIS2_FORMAT_CMYKA32) << std::endl;
    std::cout << "ULIS2_FORMAT_ACMYK32 " << " = " << (int)( ULIS2_FORMAT_ACMYK32) << std::endl;
    std::cout << "ULIS2_FORMAT_AKYMC32 " << " = " << (int)( ULIS2_FORMAT_AKYMC32) << std::endl;
    std::cout << "ULIS2_FORMAT_KYMCA32 " << " = " << (int)( ULIS2_FORMAT_KYMCA32) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYKF   " << " = " << (int)( ULIS2_FORMAT_CMYKF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_KCMYF   " << " = " << (int)( ULIS2_FORMAT_KCMYF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_KYMCF   " << " = " << (int)( ULIS2_FORMAT_KYMCF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMCKF   " << " = " << (int)( ULIS2_FORMAT_YMCKF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYKAF  " << " = " << (int)( ULIS2_FORMAT_CMYKAF ) << std::endl;
    std::cout << "ULIS2_FORMAT_ACMYKF  " << " = " << (int)( ULIS2_FORMAT_ACMYKF ) << std::endl;
    std::cout << "ULIS2_FORMAT_AKYMCF  " << " = " << (int)( ULIS2_FORMAT_AKYMCF ) << std::endl;
    std::cout << "ULIS2_FORMAT_KYMCAF  " << " = " << (int)( ULIS2_FORMAT_KYMCAF ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYKD   " << " = " << (int)( ULIS2_FORMAT_CMYKD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_KCMYD   " << " = " << (int)( ULIS2_FORMAT_KCMYD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_KYMCD   " << " = " << (int)( ULIS2_FORMAT_KYMCD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YMCKD   " << " = " << (int)( ULIS2_FORMAT_YMCKD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_CMYKAD  " << " = " << (int)( ULIS2_FORMAT_CMYKAD ) << std::endl;
    std::cout << "ULIS2_FORMAT_ACMYKD  " << " = " << (int)( ULIS2_FORMAT_ACMYKD ) << std::endl;
    std::cout << "ULIS2_FORMAT_AKYMCD  " << " = " << (int)( ULIS2_FORMAT_AKYMCD ) << std::endl;
    std::cout << "ULIS2_FORMAT_KYMCAD  " << " = " << (int)( ULIS2_FORMAT_KYMCAD ) << std::endl;
    std::cout << "ULIS2_FORMAT_YUV8    " << " = " << (int)( ULIS2_FORMAT_YUV8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_VUY8    " << " = " << (int)( ULIS2_FORMAT_VUY8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_YUVA8   " << " = " << (int)( ULIS2_FORMAT_YUVA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AVUY8   " << " = " << (int)( ULIS2_FORMAT_AVUY8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYUV8   " << " = " << (int)( ULIS2_FORMAT_AYUV8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_VUYA8   " << " = " << (int)( ULIS2_FORMAT_VUYA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YUV16   " << " = " << (int)( ULIS2_FORMAT_YUV16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_VUY16   " << " = " << (int)( ULIS2_FORMAT_VUY16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YUVA16  " << " = " << (int)( ULIS2_FORMAT_YUVA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AVUY16  " << " = " << (int)( ULIS2_FORMAT_AVUY16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYUV16  " << " = " << (int)( ULIS2_FORMAT_AYUV16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_VUYA16  " << " = " << (int)( ULIS2_FORMAT_VUYA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_YUV32   " << " = " << (int)( ULIS2_FORMAT_YUV32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_VUY32   " << " = " << (int)( ULIS2_FORMAT_VUY32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YUVA32  " << " = " << (int)( ULIS2_FORMAT_YUVA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AVUY32  " << " = " << (int)( ULIS2_FORMAT_AVUY32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYUV32  " << " = " << (int)( ULIS2_FORMAT_AYUV32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_VUYA32  " << " = " << (int)( ULIS2_FORMAT_VUYA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_YUVF    " << " = " << (int)( ULIS2_FORMAT_YUVF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_VUYF    " << " = " << (int)( ULIS2_FORMAT_VUYF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_YUVAF   " << " = " << (int)( ULIS2_FORMAT_YUVAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AVUYF   " << " = " << (int)( ULIS2_FORMAT_AVUYF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYUVF   " << " = " << (int)( ULIS2_FORMAT_AYUVF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_VUYAF   " << " = " << (int)( ULIS2_FORMAT_VUYAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YUVD    " << " = " << (int)( ULIS2_FORMAT_YUVD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_VUYD    " << " = " << (int)( ULIS2_FORMAT_VUYD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_YUVAD   " << " = " << (int)( ULIS2_FORMAT_YUVAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AVUYD   " << " = " << (int)( ULIS2_FORMAT_AVUYD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYUVD   " << " = " << (int)( ULIS2_FORMAT_AYUVD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_VUYAD   " << " = " << (int)( ULIS2_FORMAT_VUYAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_Lab8    " << " = " << (int)( ULIS2_FORMAT_Lab8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_baL8    " << " = " << (int)( ULIS2_FORMAT_baL8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_LabA8   " << " = " << (int)( ULIS2_FORMAT_LabA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AbaL8   " << " = " << (int)( ULIS2_FORMAT_AbaL8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ALab8   " << " = " << (int)( ULIS2_FORMAT_ALab8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_baLA8   " << " = " << (int)( ULIS2_FORMAT_baLA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_Lab16   " << " = " << (int)( ULIS2_FORMAT_Lab16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_baL16   " << " = " << (int)( ULIS2_FORMAT_baL16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_LabA16  " << " = " << (int)( ULIS2_FORMAT_LabA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AbaL16  " << " = " << (int)( ULIS2_FORMAT_AbaL16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ALab16  " << " = " << (int)( ULIS2_FORMAT_ALab16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_baLA16  " << " = " << (int)( ULIS2_FORMAT_baLA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_Lab32   " << " = " << (int)( ULIS2_FORMAT_Lab32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_baL32   " << " = " << (int)( ULIS2_FORMAT_baL32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_LabA32  " << " = " << (int)( ULIS2_FORMAT_LabA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AbaL32  " << " = " << (int)( ULIS2_FORMAT_AbaL32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ALab32  " << " = " << (int)( ULIS2_FORMAT_ALab32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_baLA32  " << " = " << (int)( ULIS2_FORMAT_baLA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_LabF    " << " = " << (int)( ULIS2_FORMAT_LabF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_baLF    " << " = " << (int)( ULIS2_FORMAT_baLF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_LabAF   " << " = " << (int)( ULIS2_FORMAT_LabAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AbaLF   " << " = " << (int)( ULIS2_FORMAT_AbaLF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ALabF   " << " = " << (int)( ULIS2_FORMAT_ALabF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_baLAF   " << " = " << (int)( ULIS2_FORMAT_baLAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_LabD    " << " = " << (int)( ULIS2_FORMAT_LabD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_baLD    " << " = " << (int)( ULIS2_FORMAT_baLD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_LabAD   " << " = " << (int)( ULIS2_FORMAT_LabAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AbaLD   " << " = " << (int)( ULIS2_FORMAT_AbaLD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ALabD   " << " = " << (int)( ULIS2_FORMAT_ALabD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_baLAD   " << " = " << (int)( ULIS2_FORMAT_baLAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_XYZ8    " << " = " << (int)( ULIS2_FORMAT_XYZ8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_ZYX8    " << " = " << (int)( ULIS2_FORMAT_ZYX8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_XYZA8   " << " = " << (int)( ULIS2_FORMAT_XYZA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AZYX8   " << " = " << (int)( ULIS2_FORMAT_AZYX8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AXYZ8   " << " = " << (int)( ULIS2_FORMAT_AXYZ8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ZYXA8   " << " = " << (int)( ULIS2_FORMAT_ZYXA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_XYZ16   " << " = " << (int)( ULIS2_FORMAT_XYZ16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ZYX16   " << " = " << (int)( ULIS2_FORMAT_ZYX16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_XYZA16  " << " = " << (int)( ULIS2_FORMAT_XYZA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AZYX16  " << " = " << (int)( ULIS2_FORMAT_AZYX16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AXYZ16  " << " = " << (int)( ULIS2_FORMAT_AXYZ16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ZYXA16  " << " = " << (int)( ULIS2_FORMAT_ZYXA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_XYZ32   " << " = " << (int)( ULIS2_FORMAT_XYZ32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ZYX32   " << " = " << (int)( ULIS2_FORMAT_ZYX32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_XYZA32  " << " = " << (int)( ULIS2_FORMAT_XYZA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AZYX32  " << " = " << (int)( ULIS2_FORMAT_AZYX32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AXYZ32  " << " = " << (int)( ULIS2_FORMAT_AXYZ32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_ZYXA32  " << " = " << (int)( ULIS2_FORMAT_ZYXA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_XYZF    " << " = " << (int)( ULIS2_FORMAT_XYZF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_ZYXF    " << " = " << (int)( ULIS2_FORMAT_ZYXF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_XYZAF   " << " = " << (int)( ULIS2_FORMAT_XYZAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AZYXF   " << " = " << (int)( ULIS2_FORMAT_AZYXF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AXYZF   " << " = " << (int)( ULIS2_FORMAT_AXYZF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ZYXAF   " << " = " << (int)( ULIS2_FORMAT_ZYXAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_XYZD    " << " = " << (int)( ULIS2_FORMAT_XYZD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_ZYXD    " << " = " << (int)( ULIS2_FORMAT_ZYXD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_XYZAD   " << " = " << (int)( ULIS2_FORMAT_XYZAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AZYXD   " << " = " << (int)( ULIS2_FORMAT_AZYXD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AXYZD   " << " = " << (int)( ULIS2_FORMAT_AXYZD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_ZYXAD   " << " = " << (int)( ULIS2_FORMAT_ZYXAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_Yxy8    " << " = " << (int)( ULIS2_FORMAT_Yxy8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_yxY8    " << " = " << (int)( ULIS2_FORMAT_yxY8   ) << std::endl;
    std::cout << "ULIS2_FORMAT_YxyA8   " << " = " << (int)( ULIS2_FORMAT_YxyA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AyxY8   " << " = " << (int)( ULIS2_FORMAT_AyxY8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYxy8   " << " = " << (int)( ULIS2_FORMAT_AYxy8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_yxYA8   " << " = " << (int)( ULIS2_FORMAT_yxYA8  ) << std::endl;
    std::cout << "ULIS2_FORMAT_Yxy16   " << " = " << (int)( ULIS2_FORMAT_Yxy16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_yxY16   " << " = " << (int)( ULIS2_FORMAT_yxY16  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YxyA16  " << " = " << (int)( ULIS2_FORMAT_YxyA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AyxY16  " << " = " << (int)( ULIS2_FORMAT_AyxY16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYxy16  " << " = " << (int)( ULIS2_FORMAT_AYxy16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_yxYA16  " << " = " << (int)( ULIS2_FORMAT_yxYA16 ) << std::endl;
    std::cout << "ULIS2_FORMAT_Yxy32   " << " = " << (int)( ULIS2_FORMAT_Yxy32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_yxY32   " << " = " << (int)( ULIS2_FORMAT_yxY32  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YxyA32  " << " = " << (int)( ULIS2_FORMAT_YxyA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AyxY32  " << " = " << (int)( ULIS2_FORMAT_AyxY32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYxy32  " << " = " << (int)( ULIS2_FORMAT_AYxy32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_yxYA32  " << " = " << (int)( ULIS2_FORMAT_yxYA32 ) << std::endl;
    std::cout << "ULIS2_FORMAT_YxyF    " << " = " << (int)( ULIS2_FORMAT_YxyF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_yxYF    " << " = " << (int)( ULIS2_FORMAT_yxYF   ) << std::endl;
    std::cout << "ULIS2_FORMAT_YxyAF   " << " = " << (int)( ULIS2_FORMAT_YxyAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AyxYF   " << " = " << (int)( ULIS2_FORMAT_AyxYF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYxyF   " << " = " << (int)( ULIS2_FORMAT_AYxyF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_yxYAF   " << " = " << (int)( ULIS2_FORMAT_yxYAF  ) << std::endl;
    std::cout << "ULIS2_FORMAT_YxyD    " << " = " << (int)( ULIS2_FORMAT_YxyD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_yxYD    " << " = " << (int)( ULIS2_FORMAT_yxYD   ) << std::endl;
    std::cout << "ULIS2_FORMAT_YxyAD   " << " = " << (int)( ULIS2_FORMAT_YxyAD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AyxYD   " << " = " << (int)( ULIS2_FORMAT_AyxYD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_AYxyD   " << " = " << (int)( ULIS2_FORMAT_AYxyD  ) << std::endl;
    std::cout << "ULIS2_FORMAT_yxYAD   " << " = " << (int)( ULIS2_FORMAT_yxYAD  ) << std::endl;































    /*
    FBlock blockA( 256, 256, ULIS2_FORMAT_ARGB8 );
    FBlock blockB( 256, 256, ULIS2_FORMAT_ARGB8 );
    FThreadPool pool;
    FPerf       perf( Perf_Lowest );
    Blend( &pool, ULIS2_BLOCKING, &blockA, &blockB, glm::vec2( 0 ), BM_HUE, AM_NORMAL, 1.f, perf, ULIS2_CALL_CB );
    */

    /*
    // OpenCL
    //get all platforms (drivers)
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    if(all_platforms.size()==0){
        std::cout<<" No platforms found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Platform default_platform=all_platforms[0];
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";

     //get default device of the default platform
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(all_devices.size()==0){
        std::cout<<" No devices found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Device default_device=all_devices[0];
    std::cout<< "Num devices: "<<all_devices.size()<<"\n";
    std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";

    cl::Context context({default_device});
    cl::Program::Sources sources;

    // kernel calculates for each element C=A+B
    std::string kernel_code =
            "   void kernel simple_add(global const int* A, global const int* B, global int* C){    "
            "       C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];                    "
            "   }                                                                                   ";
    sources.push_back({kernel_code.c_str(),kernel_code.length()});

    cl::Program program(context,sources);
    if(program.build({default_device})!=CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        exit(1);
    }

    // create buffers on the device
    cl::Buffer buffer_A( context,CL_MEM_READ_WRITE,sizeof(int)*10 );
    cl::Buffer buffer_B( context,CL_MEM_READ_WRITE,sizeof(int)*10 );
    cl::Buffer buffer_C( context,CL_MEM_READ_WRITE,sizeof(int)*10 );

    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};

    //create queue to which we will push commands for the device.
    cl::CommandQueue queue(context,default_device);
    //write arrays A and B to the device
    queue.enqueueWriteBuffer(buffer_A,CL_TRUE,0,sizeof(int)*10,A);
    queue.enqueueWriteBuffer(buffer_B,CL_TRUE,0,sizeof(int)*10,B);

    cl::make_kernel< cl::Buffer, cl::Buffer, cl::Buffer > simple_add( cl::Kernel( program, "simple_add" ) );
    cl::EnqueueArgs eargs(queue, cl::NullRange, cl::NDRange(10), cl::NullRange);
    simple_add(eargs, buffer_A, buffer_B, buffer_C).wait();

    int C[10];
    //read result C from the device to array C
    queue.enqueueReadBuffer(buffer_C,CL_TRUE,0,sizeof(int)*10,C);

    std::cout<<" result: \n";
    for(int i=0;i<10;i++){
        std::cout<<C[i]<< " " << std::endl;
    }

    cl_int err;
    cl::size_t< 3 > origin;
    cl::size_t< 3 > region;
    region[0] = 256;
    region[1] = 256;
    cl::Image2D resource( context, CL_MEM_USE_HOST_PTR, { CL_RGBA, CL_FLOAT }, 256, 256, 0, block.DataPtr(), &err );
    std::cout << err << std::endl;
    std::cout << resource.getInfo< CL_MEM_SIZE >( &err ) << std::endl;
    std::cout << err << std::endl;
    auto _dummy = 0;
    */
    return  0;
}

