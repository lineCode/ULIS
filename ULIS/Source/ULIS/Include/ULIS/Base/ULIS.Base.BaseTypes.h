/**
*
*   ULIS
*__________________
*
* @file     ULIS.Base.BaseTypes.h
* @author   Clement Berthaud
* @brief    This file provides some usefull shorthand typedefs.
*/
#pragma once
#include <stdint.h>

namespace ULIS {
/////////////////////////////////////////////////////
// Shorthand typedefs within ULIS namespace
typedef  uint8_t    uint8;
typedef  uint16_t   uint16;
typedef  uint32_t   uint32;
typedef  uint64_t   uint64;
typedef  int8_t     int8;
typedef  int16_t    int16;
typedef  int32_t    int32;
typedef  int64_t    int64;

/////////////////////////////////////////////////////
// Callback Typedefs
class IBlock;
typedef void (*fpInvalidateFunction)( IBlock* /*data*/, void* /*info*/, const FRect& /*rect*/ );

} // namespace ULIS

