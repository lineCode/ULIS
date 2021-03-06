// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         OldThreadPool.h
* @author       Clement Berthaud
* @brief        This file provides the dispatch to include thread pool if supported
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

#ifdef ULIS_COMPILED_WITH_THREAD_SUPPORT
#include "Thread/OldThreadPool_imp.ipp"
#else
#include "Thread/OldThreadPool_dummy.ipp"
#endif
