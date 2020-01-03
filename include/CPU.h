// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         CPU.h
* @author       Clement Berthaud
* @brief        This file provides the definition for the FCPU struct.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Core.h"
#include "cpu_x86.h"

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @struct     FCPU
/// @brief      The FCPU struct provides a small wrapper around the FeatureDetector interface.
struct ULIS2_API FCPU
{
public:
    // Construction
    /// @fn         FCPU()
    /// @brief      Default Constructor.
    /// @details    Initializes members by calling the appropriate functions in FeatureDetector.
    FCPU()
    {
        info.detect_host();
    }

public:
    // Public Data Members
    ::FeatureDetector::cpu_x86 info;    ///< public member info of type ::FeatureDetector::cpu_x86, all fields should be initialized by constructor.
};

ULIS2_NAMESPACE_END

