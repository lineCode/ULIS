// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ProfileRegistry.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FProfileRegistry class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include "Color/ColorProfile.h"
#include <unordered_map>

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FProfileRegistry
class ULIS2_API FProfileRegistry
{
public:
    // Construction / Destruction
    FProfileRegistry();
    ~FProfileRegistry();

public:
    // Public API
    FColorProfile* GetProfile( const std::string iKey ) const;
    std::string DefaultProfileNameForModel( eColorModel iModel ) const;
    FColorProfile* GetDefaultProfileForModel( eColorModel iModel ) const;

private:
    // Private Data
    std::unordered_map< std::string, FColorProfile* > mLockedSoftwareProfiles;
    std::unordered_map< std::string, FColorProfile* > mFileBasedProfiles;
};

ULIS2_NAMESPACE_END

