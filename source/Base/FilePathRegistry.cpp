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
#include "Base/String.h"
#include <cppfs/fs.h>
#include <cppfs/FileHandle.h>
#include <cppfs/FilePath.h>
#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>

namespace std {   };
using namespace std;
using namespace cppfs;

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
    mMap.clear();
    std::vector< string > list;
    for( auto it : mLookupPaths ) {
        FileHandle dir = fs::open( it );
        if( ( !dir.exists() ) || ( !dir.isDirectory() ) )
            continue;
        GatherEntriesRecursive( dir, &list );
    }

    for( auto it : list )
        mMap.emplace( CreateName( it ), it );
}


std::string
FFilePathRegistry::GetFilePathForClosestMatchingName( const std::string& iName )
{
    std::string lowercase_name = iName;
    std::transform( lowercase_name.begin(), lowercase_name.end(), lowercase_name.begin(), ::tolower);
    std::vector< std::tuple< int, std::string > > matches;
    for( auto it : mMap ) {
        std::string key = it.first;
        std::string lowercase_key = key;
        std::transform( lowercase_key.begin(), lowercase_key.end(), lowercase_key.begin(), ::tolower);
        int dist = static_cast< int >( LevenshteinDistance( lowercase_name.c_str(), lowercase_name.size(), lowercase_key.c_str(), lowercase_key.size() ) );
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
    std::string dir_path = iDir.path();

    for( auto it : entries ) {
        std::string full_entry_path = dir_path + it;
        FileHandle entry = fs::open( full_entry_path );

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
                oList->push_back( full_entry_path );
        }
    }
}

std::string
FFilePathRegistry::CreateName( const std::string& iFile )
{
    FilePath path( iFile );
    return  path.baseName();
}

ULIS2_NAMESPACE_END

