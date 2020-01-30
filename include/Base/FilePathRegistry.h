// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         FilePathRegistry.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FFilePathRegistry class.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Base/Core.h"
#include <unordered_map>
#include <vector>
namespace cppfs { class FileHandle; }

ULIS2_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FFilePathRegistry
/// @brief      The FFilePathRegistry class provides a mean of storing and manipulating file paths registry with filters.
class ULIS2_API FFilePathRegistry
{
public:
    // Construction / Destruction
    virtual ~FFilePathRegistry();
    FFilePathRegistry();

public:
    // Public API
    const std::vector< std::string >& GetLookupPaths() const;
    const std::vector< std::string >& GetFilters() const;
    void AddLookupPath( const std::string& iPath );
    void AddLookupPaths( const std::vector< std::string >& iPaths );
    void AddFilter( const std::string& iFilter );
    void AddFilters( const std::vector< std::string >& iFilters );
    void Parse();
    std::string GetFilePathForClosestMatchingName( const std::string& iName );
    std::string GetFilePathForExactMatchingName( const std::string& iName );
    const std::unordered_map< std::string, std::string >& GetMap() const;

private:
    // Private API
    void GatherEntriesRecursive( const cppfs::FileHandle& iDir, std::vector< std::string >* oList );
    virtual std::string CreateName( const std::string& iFile );

private:
    // Private Data Members
    std::vector< std::string > mLookupPaths;
    std::vector< std::string > mFilters;
    std::unordered_map< std::string, std::string > mMap; // < Name, Path >
};

ULIS2_NAMESPACE_END

