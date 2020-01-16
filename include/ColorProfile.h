// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ColorProfile.h
* @author       Clement Berthaud
* @brief        This file provides declaration for the FColorProfile class.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include "Illuminants.h"
#include "lcms2.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// DefaultProfiles
namespace DefaultProfiles
{
    static const std::string sRGB                = "sRGB";
    static const std::string AdobeRGB_compat     = "AdobeRGB_compat";
    static const std::string Lab_D65             = "Lab_D65";
    static const std::string Lab_D50             = "Lab_D50";
    static const std::string XYZ                 = "XYZ";
    static const std::string Grey_Gamma2_2_D65   = "Grey_Gamma2.2_D65";
    static const std::string Default_CMYK        = "Default_CMYK";
};

/////////////////////////////////////////////////////
// FColorProfile
class ULIS2_API FColorProfile
{
public:
    // Construction / Destruction
    FColorProfile( const std::string& iName, cmsHPROFILE iProfile );
    ~FColorProfile();

public:
    // Public API
    eColorModel         Model() const;
    bool                IsModelSupported( eColorModel iModel ) const;
    const std::string&  Name() const;
    cmsHPROFILE         ProfileHandle();

private:
    // Private Data
    cmsHPROFILE     mProfile;
    eColorModel     mModel;
    std::string     mName;
};

ULIS2_NAMESPACE_END

