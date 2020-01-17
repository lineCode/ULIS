// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         ColorProfile.cpp
* @author       Clement Berthaud
* @brief        This file provides definition for the FColorProfile class.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "ColorProfile.h"
#include "ModelCompat.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FColorProfile
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FColorProfile::FColorProfile( const std::string& iName, cmsHPROFILE iProfile )
    : mProfile( iProfile )
    , mModel( ModelFromColorSpaceSignature( cmsGetColorSpace( iProfile ) ) )
    , mName( iName )
{
}


FColorProfile::~FColorProfile()
{
    cmsCloseProfile( mProfile );
    mProfile = nullptr;
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
eColorModel
FColorProfile::Model()  const
{
    return  mModel;
}


bool
FColorProfile::IsModelSupported( eColorModel iModel ) const
{
    return  ModelCompatFallback( iModel ) == mModel;
}


const std::string&
FColorProfile::Name() const
{
    return  mName;
}


cmsHPROFILE
FColorProfile::ProfileHandle()
{
    return  mProfile;
}

ULIS2_NAMESPACE_END

