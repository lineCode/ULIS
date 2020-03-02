// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         CoreInternal.h
* @author       Clement Berthaud
* @brief        This file provides internal core definitions for the ULIS2 library.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Platform.h"
#include <cstring>
#include <iostream>
#include <memory>

/////////////////////////////////////////////////////
// Define Namespaces
#define ULIS2_NAMESPACE_NAME        ULIS2
#define ULIS2_SHORT_NAMESPACE_NAME  ul2
#define ULIS2_NAMESPACE_BEGIN       namespace ULIS2_NAMESPACE_NAME {
#define ULIS2_NAMESPACE_END         }
#define ULIS2_FDECL_CLASS( i )      ULIS2_NAMESPACE_BEGIN class i ; ULIS2_NAMESPACE_END
#define ULIS2_FDECL_STRUCT( i )     ULIS2_NAMESPACE_BEGIN struct i ; ULIS2_NAMESPACE_END
namespace ULIS2_NAMESPACE_NAME {}
namespace ULIS2_SHORT_NAMESPACE_NAME = ULIS2_NAMESPACE_NAME;

/////////////////////////////////////////////////////
// Version Specification
#define ULIS2_VERSION_MAJOR      2
#define ULIS2_VERSION_MINOR      0
#define ULIS2_VERSION_MAJOR_STR  "2"
#define ULIS2_VERSION_MINOR_STR  "0"

/////////////////////////////////////////////////////
// Crash Behaviours
#define ULIS2_CRASH              *((volatile int*)0) = 0
#define ULIS2_CRASH_DELIBERATE   ULIS2_CRASH
#define ULIS2_CRASH_TODO         ULIS2_CRASH
#define ULIS2_CRASH_CHECK        ULIS2_CRASH

/////////////////////////////////////////////////////
// Assert Behaviours
#ifdef ULIS2_DEBUG
    #define ULIS2_ASSERT( cond, log )  if( !( cond ) ) { std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << " " << "Assertion failed:" << log << std::endl; ULIS2_CRASH; }
#else
    #define ULIS2_ASSERT( cond, log )
#endif

#define ULIS2_WARNING( cond, log )  if( !( cond ) ) { std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << " " <<  "Warning: " << log << std::endl; }
#define ULIS2_ERROR( cond, log )    if( !( cond ) ) { std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << " " << "Error: " << log << std::endl; ULIS2_CRASH; }
#define ULIS2_FAIL( log )           { std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << " " << "Error: " << log << std::endl; ULIS2_CRASH; }
#define ULIS2_FAIL_RET( log, ret )  { std::cout << __FILE__ << " " << __FUNCTION__ << " " << __LINE__ << " " << "Error: " << log << std::endl; ULIS2_CRASH; } return  ret;

/////////////////////////////////////////////////////
// Named booleans literals
#define ULIS2_PASS          true
#define ULIS2_BLOCKING      true
#define ULIS2_NONBLOCKING   false
#define ULIS2_CALLCB        true
#define ULIS2_NOCB          false
#define ULIS2_AA            true
#define ULIS2_NOAA          false

