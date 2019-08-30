/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Coçnfig.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#ifndef NDEBUG
    #define ULIS_DEBUG
#elif // !NDEBUG
    #define ULIS_RELEASE
#endif // !NDEBUG

#ifdef ULIS_DEBUG
    //#define ULIS_DEBUG_TYPE_STR_SYMBOL_ENABLED
#endif // ULIS_DEBUG
