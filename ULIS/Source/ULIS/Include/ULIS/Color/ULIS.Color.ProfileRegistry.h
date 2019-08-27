/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Color.ProfileRegistry.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Color/ULIS.Color.ColorProfile.h"
#include <unordered_map>
#include <string>

namespace ULIS {
/////////////////////////////////////////////////////
// FProfileRegistry
class FProfileRegistry
{
public:
    // Construction / Destruction
    FProfileRegistry();
    ~FProfileRegistry();

public:
    // Public API
    FColorProfile* GetProfile( const std::string iKey );
    std::string DefaultProfileNameForModel( e_cm iModel );
    FColorProfile* GetDefaultProfileForModel( e_cm iModel );

private:
    // Private Data
    std::unordered_map< std::string, FColorProfile* > mLockedSoftwareProfiles;
    std::unordered_map< std::string, FColorProfile* > mFileBasedProfiles;
};


} // namespace ULIS
