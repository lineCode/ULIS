// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         FilePathRegistry.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FFilePathRegistry class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Base/FilePathRegistry.h"
#include <cppfs/FilePath.h>
#include <cppfs/FileHandle.h>
#include <cppfs/windows/LocalFileHandle.h>
#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>

namespace std {   };
using namespace std;
using namespace cppfs;

size_t
LevenshteinDistance( const char* s, size_t n, const char* t, size_t m )
{
   ++n; ++m;
   size_t* d = new size_t[n * m];
   memset(d, 0, sizeof(size_t) * n * m);
   for( size_t i = 1, im = 0; i < m; ++i, ++im ) {
      for( size_t j = 1, jn = 0; j < n; ++j, ++jn ) {
         if( s[jn] == t[im] ) {
            d[(i * n) + j] = d[((i - 1) * n) + (j - 1)];
         } else {
            d[(i * n) + j] = min(d[(i - 1) * n + j] + 1,        /* A deletion. */
                             min(d[i * n + (j - 1)] + 1,        /* An insertion. */
                             d[(i - 1) * n + (j - 1)] + 1));    /* A substitution. */
         }
      }
   }
   size_t r = d[n * m - 1];
   delete [] d;
   return  r;
}

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
// FFilePathRegistry
//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction
FFilePathRegistry::~FFilePathRegistry()
{
}


FFilePathRegistry::FFilePathRegistry()
{
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Public API
const std::vector< std::string >&
FFilePathRegistry::GetLookupPaths() const
{
    return  mLookupPaths;
}


const std::vector< std::string >&
FFilePathRegistry::GetFilters() const
{
    return  mFilters;
}


void
FFilePathRegistry::AddLookupPath( const std::string& iPath )
{
    mLookupPaths.push_back( iPath );
}


void
FFilePathRegistry::AddLookupPaths( const std::vector< std::string >& iPaths )
{
    for( auto it : iPaths )
        mLookupPaths.push_back( it );
}


void
FFilePathRegistry::AddFilter( const std::string& iFilter )
{
    mFilters.push_back( iFilter );
}


void
FFilePathRegistry::AddFilters( const std::vector< std::string >& iFilters )
{
    for( auto it : iFilters )
        mFilters.push_back( it );
}


void
FFilePathRegistry::Parse()
{
    std::vector< string > list;
    for( auto it : mLookupPaths ) {
        FileHandle dir;
        dir.open( it );
        if( ( !dir.exists() ) || ( !dir.isDirectory() ) )
            continue;
        GatherEntriesRecursive( dir, &list );
    }

    for( auto it : list )
        mMap.try_emplace( CreateName( it ), it );
}


std::string
FFilePathRegistry::GetFilePathForClosestMatchingName( const std::string& iName )
{
    std::vector< std::tuple< int, std::string > > matches;
    for( auto it : mMap ) {
        std::string key = it.first;
        int dist = LevenshteinDistance( iName.c_str(), iName.size(), key.c_str(), key.size() );
        matches.push_back( std::tuple< int, std::string >( dist, key ) );
    }
    std::sort( matches.begin(), matches.end() );
    return  GetFilePathForExactMatchingName( get< 1 >( matches[0] ) );
}


std::string
FFilePathRegistry::GetFilePathForExactMatchingName( const std::string& iName )
{
    if( mMap.find( iName ) == mMap.end() ) {
        return  "";
    } else {
        return  mMap.at( iName );
    }
}


const std::unordered_map< std::string, std::string >&
FFilePathRegistry::GetMap() const
{
    return  mMap;
}

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Private API
void
FFilePathRegistry::GatherEntriesRecursive( const cppfs::FileHandle& iDir, std::vector< std::string >* oList )
{
    std::vector< std::string > entries = iDir.listFiles();

    for( auto it : entries ) {
        FileHandle entry;
        entry.open( it );

        if( entry.isDirectory() )
            GatherEntriesRecursive( entry, oList );

        if( entry.isFile() ) {
            FilePath path( entry.path() );
            std::string ext = path.extension();
            bool match = false;
            for( auto filter : mFilters ) {
                if( ext == filter )
                    match = true;
            }

            if( match )
                oList->push_back( it );
        }
    }
}

std::string
FFilePathRegistry::CreateName( const std::string& iFile )
{
    FilePath path( iFile );
    return  path.fileName();
}

ULIS2_NAMESPACE_END

