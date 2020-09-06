// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS
*__________________
*
* @file         OldThreadInterface.cpp
* @author       Clement Berthaud
* @brief        This file provides the definitions for the OldThreadInterface entry points.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Thread/OldThreadInterface.h"
#include "Thread/OldThreadPool.h"

ULIS_NAMESPACE_BEGIN

FOldThreadPool*
XCreateOldThreadPool( uint32 iCount ) {
    return  new  FOldThreadPool( iCount );
}


void
XDeleteOldThreadPool( FOldThreadPool* iOldThreadPool ) {
    ULIS_ASSERT( iOldThreadPool, "Invalid Input Arg" );
    iOldThreadPool->WaitForCompletion();
    delete  iOldThreadPool;
}


void
Fence( FOldThreadPool& iPool ) {
    iPool.WaitForCompletion();
}


void
SetNumWorkers( FOldThreadPool& iPool, uint32 iValue ) {
    iPool.SetNumWorkers( iValue );
}


uint32
GetProcessed( FOldThreadPool& iPool ) {
    return  iPool.GetProcessed();
}


uint32
GetNumWorkers( FOldThreadPool& iPool ) {
    return  iPool.GetNumWorkers();
}


uint32
MaxWorkers() {
    return  FOldThreadPool::MaxWorkers();
}


ULIS_NAMESPACE_END

