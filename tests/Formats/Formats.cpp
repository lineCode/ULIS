// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS3
*__________________
*
* @file         Formats.cpp
* @author       Clement Berthaud
* @brief        Formats application for ULIS3.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS3>
using namespace ::ul3;

int main( int argc, char *argv[] ) {
    std::cout << "G8        : " << ULIS3_FORMAT_G8      << std::endl;
    std::cout << "GA8       : " << ULIS3_FORMAT_GA8     << std::endl;
    std::cout << "AG8       : " << ULIS3_FORMAT_AG8     << std::endl;
    std::cout << "G16       : " << ULIS3_FORMAT_G16     << std::endl;
    std::cout << "GA16      : " << ULIS3_FORMAT_GA16    << std::endl;
    std::cout << "AG16      : " << ULIS3_FORMAT_AG16    << std::endl;
    std::cout << "G32       : " << ULIS3_FORMAT_G32     << std::endl;
    std::cout << "GA32      : " << ULIS3_FORMAT_GA32    << std::endl;
    std::cout << "AG32      : " << ULIS3_FORMAT_AG32    << std::endl;
    std::cout << "GF        : " << ULIS3_FORMAT_GF      << std::endl;
    std::cout << "GAF       : " << ULIS3_FORMAT_GAF     << std::endl;
    std::cout << "AGF       : " << ULIS3_FORMAT_AGF     << std::endl;
    std::cout << "GD        : " << ULIS3_FORMAT_GD      << std::endl;
    std::cout << "GAD       : " << ULIS3_FORMAT_GAD     << std::endl;
    std::cout << "AGD       : " << ULIS3_FORMAT_AGD     << std::endl;
    std::cout << "RGB8      : " << ULIS3_FORMAT_RGB8    << std::endl;
    std::cout << "BGR8      : " << ULIS3_FORMAT_BGR8    << std::endl;
    std::cout << "RGBA8     : " << ULIS3_FORMAT_RGBA8   << std::endl;
    std::cout << "ABGR8     : " << ULIS3_FORMAT_ABGR8   << std::endl;
    std::cout << "ARGB8     : " << ULIS3_FORMAT_ARGB8   << std::endl;
    std::cout << "BGRA8     : " << ULIS3_FORMAT_BGRA8   << std::endl;
    std::cout << "RGB16     : " << ULIS3_FORMAT_RGB16   << std::endl;
    std::cout << "BGR16     : " << ULIS3_FORMAT_BGR16   << std::endl;
    std::cout << "RGBA16    : " << ULIS3_FORMAT_RGBA16  << std::endl;
    std::cout << "ABGR16    : " << ULIS3_FORMAT_ABGR16  << std::endl;
    std::cout << "ARGB16    : " << ULIS3_FORMAT_ARGB16  << std::endl;
    std::cout << "BGRA16    : " << ULIS3_FORMAT_BGRA16  << std::endl;
    std::cout << "RGB32     : " << ULIS3_FORMAT_RGB32   << std::endl;
    std::cout << "BGR32     : " << ULIS3_FORMAT_BGR32   << std::endl;
    std::cout << "RGBA32    : " << ULIS3_FORMAT_RGBA32  << std::endl;
    std::cout << "ABGR32    : " << ULIS3_FORMAT_ABGR32  << std::endl;
    std::cout << "ARGB32    : " << ULIS3_FORMAT_ARGB32  << std::endl;
    std::cout << "BGRA32    : " << ULIS3_FORMAT_BGRA32  << std::endl;
    std::cout << "RGBF      : " << ULIS3_FORMAT_RGBF    << std::endl;
    std::cout << "BGRF      : " << ULIS3_FORMAT_BGRF    << std::endl;
    std::cout << "RGBAF     : " << ULIS3_FORMAT_RGBAF   << std::endl;
    std::cout << "ABGRF     : " << ULIS3_FORMAT_ABGRF   << std::endl;
    std::cout << "ARGBF     : " << ULIS3_FORMAT_ARGBF   << std::endl;
    std::cout << "BGRAF     : " << ULIS3_FORMAT_BGRAF   << std::endl;
    std::cout << "RGBD      : " << ULIS3_FORMAT_RGBD    << std::endl;
    std::cout << "BGRD      : " << ULIS3_FORMAT_BGRD    << std::endl;
    std::cout << "RGBAD     : " << ULIS3_FORMAT_RGBAD   << std::endl;
    std::cout << "ABGRD     : " << ULIS3_FORMAT_ABGRD   << std::endl;
    std::cout << "ARGBD     : " << ULIS3_FORMAT_ARGBD   << std::endl;
    std::cout << "BGRAD     : " << ULIS3_FORMAT_BGRAD   << std::endl;
    std::cout << "HSV8      : " << ULIS3_FORMAT_HSV8    << std::endl;
    std::cout << "VSH8      : " << ULIS3_FORMAT_VSH8    << std::endl;
    std::cout << "HSVA8     : " << ULIS3_FORMAT_HSVA8   << std::endl;
    std::cout << "AVSH8     : " << ULIS3_FORMAT_AVSH8   << std::endl;
    std::cout << "AHSV8     : " << ULIS3_FORMAT_AHSV8   << std::endl;
    std::cout << "VSHA8     : " << ULIS3_FORMAT_VSHA8   << std::endl;
    std::cout << "HSV16     : " << ULIS3_FORMAT_HSV16   << std::endl;
    std::cout << "VSH16     : " << ULIS3_FORMAT_VSH16   << std::endl;
    std::cout << "HSVA16    : " << ULIS3_FORMAT_HSVA16  << std::endl;
    std::cout << "AVSH16    : " << ULIS3_FORMAT_AVSH16  << std::endl;
    std::cout << "AHSV16    : " << ULIS3_FORMAT_AHSV16  << std::endl;
    std::cout << "VSHA16    : " << ULIS3_FORMAT_VSHA16  << std::endl;
    std::cout << "HSV32     : " << ULIS3_FORMAT_HSV32   << std::endl;
    std::cout << "VSH32     : " << ULIS3_FORMAT_VSH32   << std::endl;
    std::cout << "HSVA32    : " << ULIS3_FORMAT_HSVA32  << std::endl;
    std::cout << "AVSH32    : " << ULIS3_FORMAT_AVSH32  << std::endl;
    std::cout << "AHSV32    : " << ULIS3_FORMAT_AHSV32  << std::endl;
    std::cout << "VSHA32    : " << ULIS3_FORMAT_VSHA32  << std::endl;
    std::cout << "HSVF      : " << ULIS3_FORMAT_HSVF    << std::endl;
    std::cout << "VSHF      : " << ULIS3_FORMAT_VSHF    << std::endl;
    std::cout << "HSVAF     : " << ULIS3_FORMAT_HSVAF   << std::endl;
    std::cout << "AVSHF     : " << ULIS3_FORMAT_AVSHF   << std::endl;
    std::cout << "AHSVF     : " << ULIS3_FORMAT_AHSVF   << std::endl;
    std::cout << "VSHAF     : " << ULIS3_FORMAT_VSHAF   << std::endl;
    std::cout << "HSVD      : " << ULIS3_FORMAT_HSVD    << std::endl;
    std::cout << "VSHD      : " << ULIS3_FORMAT_VSHD    << std::endl;
    std::cout << "HSVAD     : " << ULIS3_FORMAT_HSVAD   << std::endl;
    std::cout << "AVSHD     : " << ULIS3_FORMAT_AVSHD   << std::endl;
    std::cout << "AHSVD     : " << ULIS3_FORMAT_AHSVD   << std::endl;
    std::cout << "VSHAD     : " << ULIS3_FORMAT_VSHAD   << std::endl;
    std::cout << "HSL8      : " << ULIS3_FORMAT_HSL8    << std::endl;
    std::cout << "LSH8      : " << ULIS3_FORMAT_LSH8    << std::endl;
    std::cout << "HSLA8     : " << ULIS3_FORMAT_HSLA8   << std::endl;
    std::cout << "ALSH8     : " << ULIS3_FORMAT_ALSH8   << std::endl;
    std::cout << "AHSL8     : " << ULIS3_FORMAT_AHSL8   << std::endl;
    std::cout << "LSHA8     : " << ULIS3_FORMAT_LSHA8   << std::endl;
    std::cout << "HSL16     : " << ULIS3_FORMAT_HSL16   << std::endl;
    std::cout << "LSH16     : " << ULIS3_FORMAT_LSH16   << std::endl;
    std::cout << "HSLA16    : " << ULIS3_FORMAT_HSLA16  << std::endl;
    std::cout << "ALSH16    : " << ULIS3_FORMAT_ALSH16  << std::endl;
    std::cout << "AHSL16    : " << ULIS3_FORMAT_AHSL16  << std::endl;
    std::cout << "LSHA16    : " << ULIS3_FORMAT_LSHA16  << std::endl;
    std::cout << "HSL32     : " << ULIS3_FORMAT_HSL32   << std::endl;
    std::cout << "LSH32     : " << ULIS3_FORMAT_LSH32   << std::endl;
    std::cout << "HSLA32    : " << ULIS3_FORMAT_HSLA32  << std::endl;
    std::cout << "ALSH32    : " << ULIS3_FORMAT_ALSH32  << std::endl;
    std::cout << "AHSL32    : " << ULIS3_FORMAT_AHSL32  << std::endl;
    std::cout << "LSHA32    : " << ULIS3_FORMAT_LSHA32  << std::endl;
    std::cout << "HSLF      : " << ULIS3_FORMAT_HSLF    << std::endl;
    std::cout << "LSHF      : " << ULIS3_FORMAT_LSHF    << std::endl;
    std::cout << "HSLAF     : " << ULIS3_FORMAT_HSLAF   << std::endl;
    std::cout << "ALSHF     : " << ULIS3_FORMAT_ALSHF   << std::endl;
    std::cout << "AHSLF     : " << ULIS3_FORMAT_AHSLF   << std::endl;
    std::cout << "LSHAF     : " << ULIS3_FORMAT_LSHAF   << std::endl;
    std::cout << "HSLD      : " << ULIS3_FORMAT_HSLD    << std::endl;
    std::cout << "LSHD      : " << ULIS3_FORMAT_LSHD    << std::endl;
    std::cout << "HSLAD     : " << ULIS3_FORMAT_HSLAD   << std::endl;
    std::cout << "ALSHD     : " << ULIS3_FORMAT_ALSHD   << std::endl;
    std::cout << "AHSLD     : " << ULIS3_FORMAT_AHSLD   << std::endl;
    std::cout << "LSHAD     : " << ULIS3_FORMAT_LSHAD   << std::endl;
    std::cout << "CMY8      : " << ULIS3_FORMAT_CMY8    << std::endl;
    std::cout << "YMC8      : " << ULIS3_FORMAT_YMC8    << std::endl;
    std::cout << "CMYA8     : " << ULIS3_FORMAT_CMYA8   << std::endl;
    std::cout << "AYMC8     : " << ULIS3_FORMAT_AYMC8   << std::endl;
    std::cout << "ACMY8     : " << ULIS3_FORMAT_ACMY8   << std::endl;
    std::cout << "YMCA8     : " << ULIS3_FORMAT_YMCA8   << std::endl;
    std::cout << "CMY16     : " << ULIS3_FORMAT_CMY16   << std::endl;
    std::cout << "YMC16     : " << ULIS3_FORMAT_YMC16   << std::endl;
    std::cout << "CMYA16    : " << ULIS3_FORMAT_CMYA16  << std::endl;
    std::cout << "AYMC16    : " << ULIS3_FORMAT_AYMC16  << std::endl;
    std::cout << "ACMY16    : " << ULIS3_FORMAT_ACMY16  << std::endl;
    std::cout << "YMCA16    : " << ULIS3_FORMAT_YMCA16  << std::endl;
    std::cout << "CMY32     : " << ULIS3_FORMAT_CMY32   << std::endl;
    std::cout << "YMC32     : " << ULIS3_FORMAT_YMC32   << std::endl;
    std::cout << "CMYA32    : " << ULIS3_FORMAT_CMYA32  << std::endl;
    std::cout << "AYMC32    : " << ULIS3_FORMAT_AYMC32  << std::endl;
    std::cout << "ACMY32    : " << ULIS3_FORMAT_ACMY32  << std::endl;
    std::cout << "YMCA32    : " << ULIS3_FORMAT_YMCA32  << std::endl;
    std::cout << "CMYF      : " << ULIS3_FORMAT_CMYF    << std::endl;
    std::cout << "YMCF      : " << ULIS3_FORMAT_YMCF    << std::endl;
    std::cout << "CMYAF     : " << ULIS3_FORMAT_CMYAF   << std::endl;
    std::cout << "AYMCF     : " << ULIS3_FORMAT_AYMCF   << std::endl;
    std::cout << "ACMYF     : " << ULIS3_FORMAT_ACMYF   << std::endl;
    std::cout << "YMCAF     : " << ULIS3_FORMAT_YMCAF   << std::endl;
    std::cout << "CMYD      : " << ULIS3_FORMAT_CMYD    << std::endl;
    std::cout << "YMCD      : " << ULIS3_FORMAT_YMCD    << std::endl;
    std::cout << "CMYAD     : " << ULIS3_FORMAT_CMYAD   << std::endl;
    std::cout << "AYMCD     : " << ULIS3_FORMAT_AYMCD   << std::endl;
    std::cout << "ACMYD     : " << ULIS3_FORMAT_ACMYD   << std::endl;
    std::cout << "YMCAD     : " << ULIS3_FORMAT_YMCAD   << std::endl;
    std::cout << "CMYK8     : " << ULIS3_FORMAT_CMYK8   << std::endl;
    std::cout << "KCMY8     : " << ULIS3_FORMAT_KCMY8   << std::endl;
    std::cout << "KYMC8     : " << ULIS3_FORMAT_KYMC8   << std::endl;
    std::cout << "YMCK8     : " << ULIS3_FORMAT_YMCK8   << std::endl;
    std::cout << "CMYKA8    : " << ULIS3_FORMAT_CMYKA8  << std::endl;
    std::cout << "ACMYK8    : " << ULIS3_FORMAT_ACMYK8  << std::endl;
    std::cout << "AKYMC8    : " << ULIS3_FORMAT_AKYMC8  << std::endl;
    std::cout << "KYMCA8    : " << ULIS3_FORMAT_KYMCA8  << std::endl;
    std::cout << "CMYK16    : " << ULIS3_FORMAT_CMYK16  << std::endl;
    std::cout << "KCMY16    : " << ULIS3_FORMAT_KCMY16  << std::endl;
    std::cout << "KYMC16    : " << ULIS3_FORMAT_KYMC16  << std::endl;
    std::cout << "YMCK16    : " << ULIS3_FORMAT_YMCK16  << std::endl;
    std::cout << "CMYKA16   : " << ULIS3_FORMAT_CMYKA16 << std::endl;
    std::cout << "ACMYK16   : " << ULIS3_FORMAT_ACMYK16 << std::endl;
    std::cout << "AKYMC16   : " << ULIS3_FORMAT_AKYMC16 << std::endl;
    std::cout << "KYMCA16   : " << ULIS3_FORMAT_KYMCA16 << std::endl;
    std::cout << "CMYK32    : " << ULIS3_FORMAT_CMYK32  << std::endl;
    std::cout << "KCMY32    : " << ULIS3_FORMAT_KCMY32  << std::endl;
    std::cout << "KYMC32    : " << ULIS3_FORMAT_KYMC32  << std::endl;
    std::cout << "YMCK32    : " << ULIS3_FORMAT_YMCK32  << std::endl;
    std::cout << "CMYKA32   : " << ULIS3_FORMAT_CMYKA32 << std::endl;
    std::cout << "ACMYK32   : " << ULIS3_FORMAT_ACMYK32 << std::endl;
    std::cout << "AKYMC32   : " << ULIS3_FORMAT_AKYMC32 << std::endl;
    std::cout << "KYMCA32   : " << ULIS3_FORMAT_KYMCA32 << std::endl;
    std::cout << "CMYKF     : " << ULIS3_FORMAT_CMYKF   << std::endl;
    std::cout << "KCMYF     : " << ULIS3_FORMAT_KCMYF   << std::endl;
    std::cout << "KYMCF     : " << ULIS3_FORMAT_KYMCF   << std::endl;
    std::cout << "YMCKF     : " << ULIS3_FORMAT_YMCKF   << std::endl;
    std::cout << "CMYKAF    : " << ULIS3_FORMAT_CMYKAF  << std::endl;
    std::cout << "ACMYKF    : " << ULIS3_FORMAT_ACMYKF  << std::endl;
    std::cout << "AKYMCF    : " << ULIS3_FORMAT_AKYMCF  << std::endl;
    std::cout << "KYMCAF    : " << ULIS3_FORMAT_KYMCAF  << std::endl;
    std::cout << "CMYKD     : " << ULIS3_FORMAT_CMYKD   << std::endl;
    std::cout << "KCMYD     : " << ULIS3_FORMAT_KCMYD   << std::endl;
    std::cout << "KYMCD     : " << ULIS3_FORMAT_KYMCD   << std::endl;
    std::cout << "YMCKD     : " << ULIS3_FORMAT_YMCKD   << std::endl;
    std::cout << "CMYKAD    : " << ULIS3_FORMAT_CMYKAD  << std::endl;
    std::cout << "ACMYKD    : " << ULIS3_FORMAT_ACMYKD  << std::endl;
    std::cout << "AKYMCD    : " << ULIS3_FORMAT_AKYMCD  << std::endl;
    std::cout << "KYMCAD    : " << ULIS3_FORMAT_KYMCAD  << std::endl;
    std::cout << "YUV8      : " << ULIS3_FORMAT_YUV8    << std::endl;
    std::cout << "VUY8      : " << ULIS3_FORMAT_VUY8    << std::endl;
    std::cout << "YUVA8     : " << ULIS3_FORMAT_YUVA8   << std::endl;
    std::cout << "AVUY8     : " << ULIS3_FORMAT_AVUY8   << std::endl;
    std::cout << "AYUV8     : " << ULIS3_FORMAT_AYUV8   << std::endl;
    std::cout << "VUYA8     : " << ULIS3_FORMAT_VUYA8   << std::endl;
    std::cout << "YUV16     : " << ULIS3_FORMAT_YUV16   << std::endl;
    std::cout << "VUY16     : " << ULIS3_FORMAT_VUY16   << std::endl;
    std::cout << "YUVA16    : " << ULIS3_FORMAT_YUVA16  << std::endl;
    std::cout << "AVUY16    : " << ULIS3_FORMAT_AVUY16  << std::endl;
    std::cout << "AYUV16    : " << ULIS3_FORMAT_AYUV16  << std::endl;
    std::cout << "VUYA16    : " << ULIS3_FORMAT_VUYA16  << std::endl;
    std::cout << "YUV32     : " << ULIS3_FORMAT_YUV32   << std::endl;
    std::cout << "VUY32     : " << ULIS3_FORMAT_VUY32   << std::endl;
    std::cout << "YUVA32    : " << ULIS3_FORMAT_YUVA32  << std::endl;
    std::cout << "AVUY32    : " << ULIS3_FORMAT_AVUY32  << std::endl;
    std::cout << "AYUV32    : " << ULIS3_FORMAT_AYUV32  << std::endl;
    std::cout << "VUYA32    : " << ULIS3_FORMAT_VUYA32  << std::endl;
    std::cout << "YUVF      : " << ULIS3_FORMAT_YUVF    << std::endl;
    std::cout << "VUYF      : " << ULIS3_FORMAT_VUYF    << std::endl;
    std::cout << "YUVAF     : " << ULIS3_FORMAT_YUVAF   << std::endl;
    std::cout << "AVUYF     : " << ULIS3_FORMAT_AVUYF   << std::endl;
    std::cout << "AYUVF     : " << ULIS3_FORMAT_AYUVF   << std::endl;
    std::cout << "VUYAF     : " << ULIS3_FORMAT_VUYAF   << std::endl;
    std::cout << "YUVD      : " << ULIS3_FORMAT_YUVD    << std::endl;
    std::cout << "VUYD      : " << ULIS3_FORMAT_VUYD    << std::endl;
    std::cout << "YUVAD     : " << ULIS3_FORMAT_YUVAD   << std::endl;
    std::cout << "AVUYD     : " << ULIS3_FORMAT_AVUYD   << std::endl;
    std::cout << "AYUVD     : " << ULIS3_FORMAT_AYUVD   << std::endl;
    std::cout << "VUYAD     : " << ULIS3_FORMAT_VUYAD   << std::endl;
    std::cout << "Lab8      : " << ULIS3_FORMAT_Lab8    << std::endl;
    std::cout << "baL8      : " << ULIS3_FORMAT_baL8    << std::endl;
    std::cout << "LabA8     : " << ULIS3_FORMAT_LabA8   << std::endl;
    std::cout << "AbaL8     : " << ULIS3_FORMAT_AbaL8   << std::endl;
    std::cout << "ALab8     : " << ULIS3_FORMAT_ALab8   << std::endl;
    std::cout << "baLA8     : " << ULIS3_FORMAT_baLA8   << std::endl;
    std::cout << "Lab16     : " << ULIS3_FORMAT_Lab16   << std::endl;
    std::cout << "baL16     : " << ULIS3_FORMAT_baL16   << std::endl;
    std::cout << "LabA16    : " << ULIS3_FORMAT_LabA16  << std::endl;
    std::cout << "AbaL16    : " << ULIS3_FORMAT_AbaL16  << std::endl;
    std::cout << "ALab16    : " << ULIS3_FORMAT_ALab16  << std::endl;
    std::cout << "baLA16    : " << ULIS3_FORMAT_baLA16  << std::endl;
    std::cout << "Lab32     : " << ULIS3_FORMAT_Lab32   << std::endl;
    std::cout << "baL32     : " << ULIS3_FORMAT_baL32   << std::endl;
    std::cout << "LabA32    : " << ULIS3_FORMAT_LabA32  << std::endl;
    std::cout << "AbaL32    : " << ULIS3_FORMAT_AbaL32  << std::endl;
    std::cout << "ALab32    : " << ULIS3_FORMAT_ALab32  << std::endl;
    std::cout << "baLA32    : " << ULIS3_FORMAT_baLA32  << std::endl;
    std::cout << "LabF      : " << ULIS3_FORMAT_LabF    << std::endl;
    std::cout << "baLF      : " << ULIS3_FORMAT_baLF    << std::endl;
    std::cout << "LabAF     : " << ULIS3_FORMAT_LabAF   << std::endl;
    std::cout << "AbaLF     : " << ULIS3_FORMAT_AbaLF   << std::endl;
    std::cout << "ALabF     : " << ULIS3_FORMAT_ALabF   << std::endl;
    std::cout << "baLAF     : " << ULIS3_FORMAT_baLAF   << std::endl;
    std::cout << "LabD      : " << ULIS3_FORMAT_LabD    << std::endl;
    std::cout << "baLD      : " << ULIS3_FORMAT_baLD    << std::endl;
    std::cout << "LabAD     : " << ULIS3_FORMAT_LabAD   << std::endl;
    std::cout << "AbaLD     : " << ULIS3_FORMAT_AbaLD   << std::endl;
    std::cout << "ALabD     : " << ULIS3_FORMAT_ALabD   << std::endl;
    std::cout << "baLAD     : " << ULIS3_FORMAT_baLAD   << std::endl;
    std::cout << "XYZ8      : " << ULIS3_FORMAT_XYZ8    << std::endl;
    std::cout << "ZYX8      : " << ULIS3_FORMAT_ZYX8    << std::endl;
    std::cout << "XYZA8     : " << ULIS3_FORMAT_XYZA8   << std::endl;
    std::cout << "AZYX8     : " << ULIS3_FORMAT_AZYX8   << std::endl;
    std::cout << "AXYZ8     : " << ULIS3_FORMAT_AXYZ8   << std::endl;
    std::cout << "ZYXA8     : " << ULIS3_FORMAT_ZYXA8   << std::endl;
    std::cout << "XYZ16     : " << ULIS3_FORMAT_XYZ16   << std::endl;
    std::cout << "ZYX16     : " << ULIS3_FORMAT_ZYX16   << std::endl;
    std::cout << "XYZA16    : " << ULIS3_FORMAT_XYZA16  << std::endl;
    std::cout << "AZYX16    : " << ULIS3_FORMAT_AZYX16  << std::endl;
    std::cout << "AXYZ16    : " << ULIS3_FORMAT_AXYZ16  << std::endl;
    std::cout << "ZYXA16    : " << ULIS3_FORMAT_ZYXA16  << std::endl;
    std::cout << "XYZ32     : " << ULIS3_FORMAT_XYZ32   << std::endl;
    std::cout << "ZYX32     : " << ULIS3_FORMAT_ZYX32   << std::endl;
    std::cout << "XYZA32    : " << ULIS3_FORMAT_XYZA32  << std::endl;
    std::cout << "AZYX32    : " << ULIS3_FORMAT_AZYX32  << std::endl;
    std::cout << "AXYZ32    : " << ULIS3_FORMAT_AXYZ32  << std::endl;
    std::cout << "ZYXA32    : " << ULIS3_FORMAT_ZYXA32  << std::endl;
    std::cout << "XYZF      : " << ULIS3_FORMAT_XYZF    << std::endl;
    std::cout << "ZYXF      : " << ULIS3_FORMAT_ZYXF    << std::endl;
    std::cout << "XYZAF     : " << ULIS3_FORMAT_XYZAF   << std::endl;
    std::cout << "AZYXF     : " << ULIS3_FORMAT_AZYXF   << std::endl;
    std::cout << "AXYZF     : " << ULIS3_FORMAT_AXYZF   << std::endl;
    std::cout << "ZYXAF     : " << ULIS3_FORMAT_ZYXAF   << std::endl;
    std::cout << "XYZD      : " << ULIS3_FORMAT_XYZD    << std::endl;
    std::cout << "ZYXD      : " << ULIS3_FORMAT_ZYXD    << std::endl;
    std::cout << "XYZAD     : " << ULIS3_FORMAT_XYZAD   << std::endl;
    std::cout << "AZYXD     : " << ULIS3_FORMAT_AZYXD   << std::endl;
    std::cout << "AXYZD     : " << ULIS3_FORMAT_AXYZD   << std::endl;
    std::cout << "ZYXAD     : " << ULIS3_FORMAT_ZYXAD   << std::endl;
    std::cout << "Yxy8      : " << ULIS3_FORMAT_Yxy8    << std::endl;
    std::cout << "yxY8      : " << ULIS3_FORMAT_yxY8    << std::endl;
    std::cout << "YxyA8     : " << ULIS3_FORMAT_YxyA8   << std::endl;
    std::cout << "AyxY8     : " << ULIS3_FORMAT_AyxY8   << std::endl;
    std::cout << "AYxy8     : " << ULIS3_FORMAT_AYxy8   << std::endl;
    std::cout << "yxYA8     : " << ULIS3_FORMAT_yxYA8   << std::endl;
    std::cout << "Yxy16     : " << ULIS3_FORMAT_Yxy16   << std::endl;
    std::cout << "yxY16     : " << ULIS3_FORMAT_yxY16   << std::endl;
    std::cout << "YxyA16    : " << ULIS3_FORMAT_YxyA16  << std::endl;
    std::cout << "AyxY16    : " << ULIS3_FORMAT_AyxY16  << std::endl;
    std::cout << "AYxy16    : " << ULIS3_FORMAT_AYxy16  << std::endl;
    std::cout << "yxYA16    : " << ULIS3_FORMAT_yxYA16  << std::endl;
    std::cout << "Yxy32     : " << ULIS3_FORMAT_Yxy32   << std::endl;
    std::cout << "yxY32     : " << ULIS3_FORMAT_yxY32   << std::endl;
    std::cout << "YxyA32    : " << ULIS3_FORMAT_YxyA32  << std::endl;
    std::cout << "AyxY32    : " << ULIS3_FORMAT_AyxY32  << std::endl;
    std::cout << "AYxy32    : " << ULIS3_FORMAT_AYxy32  << std::endl;
    std::cout << "yxYA32    : " << ULIS3_FORMAT_yxYA32  << std::endl;
    std::cout << "YxyF      : " << ULIS3_FORMAT_YxyF    << std::endl;
    std::cout << "yxYF      : " << ULIS3_FORMAT_yxYF    << std::endl;
    std::cout << "YxyAF     : " << ULIS3_FORMAT_YxyAF   << std::endl;
    std::cout << "AyxYF     : " << ULIS3_FORMAT_AyxYF   << std::endl;
    std::cout << "AYxyF     : " << ULIS3_FORMAT_AYxyF   << std::endl;
    std::cout << "yxYAF     : " << ULIS3_FORMAT_yxYAF   << std::endl;
    std::cout << "YxyD      : " << ULIS3_FORMAT_YxyD    << std::endl;
    std::cout << "yxYD      : " << ULIS3_FORMAT_yxYD    << std::endl;
    std::cout << "YxyAD     : " << ULIS3_FORMAT_YxyAD   << std::endl;
    std::cout << "AyxYD     : " << ULIS3_FORMAT_AyxYD   << std::endl;
    std::cout << "AYxyD     : " << ULIS3_FORMAT_AYxyD   << std::endl;
    std::cout << "yxYAD     : " << ULIS3_FORMAT_yxYAD   << std::endl;
    return  0;
}

