// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
using System;
using System.IO;
using UnrealBuildTool;

public class ULIS : ModuleRules
{
    public string GetRootPath()
    {
        //Assuming Source/ThirdParty/ULIS/
        return Path.GetFullPath( Path.Combine( ModuleDirectory, "../../.." ) );
    }

    private string CopyToBinaries(string Filepath, ReadOnlyTargetRules Target)
    {
        string BinariesDir      = Path.Combine( GetRootPath(), "Binaries", Target.Platform.ToString() );
        string Filename         = Path.GetFileName( Filepath );
        string FullBinariesDir  = Path.GetFullPath( BinariesDir );

        if( !Directory.Exists( FullBinariesDir ) ) {
            Directory.CreateDirectory( FullBinariesDir );
        }

        string FullExistingPath = Path.Combine( FullBinariesDir, Filename );
        File.Copy( Filepath, Path.Combine( FullBinariesDir, Filename ), true);
        return FullExistingPath;
    }

    public ULIS( ReadOnlyTargetRules Target ) : base( Target )
    {
        Type = ModuleType.External;
        if (Target.Platform == UnrealTargetPlatform.Win64 ||
            Target.Platform == UnrealTargetPlatform.Win32 )
        {
            string IncludeBase  = Path.GetFullPath( Path.Combine( ModuleDirectory, "redist", "include" ) );
            string LibBase      = Path.GetFullPath( Path.Combine( ModuleDirectory, "redist", "lib" ) );
            string BinBase      = Path.GetFullPath( Path.Combine( ModuleDirectory, "redist", "bin" ) );
            string ULIS_Name = "ULIS3";
            string ULIS_LibName = ULIS_Name + ".lib";
            string ULIS_DLLName = ULIS_Name + ".dll";

            PublicSystemIncludePaths.Add( Path.Combine( IncludeBase, ULIS_Name) );
            PublicAdditionalLibraries.Add( Path.Combine( LibBase, ULIS_LibName ) );

            PublicDefinitions.Add("ULIS3_DYNAMIC_LIBRARY");

            string pluginDLLPath = Path.Combine( BinBase, ULIS_DLLName );
            string binariesPath = CopyToBinaries( pluginDLLPath, Target );
            System.Console.WriteLine( "Using " + ULIS_Name +" DLL: " + binariesPath );
            RuntimeDependencies.Add( binariesPath );
        }
        else if ( Target.Platform == UnrealTargetPlatform.Mac )
        {
            string IncludeBase  = Path.GetFullPath( Path.Combine( ModuleDirectory, "redist", "include" ) );
            string BinBase      = Path.GetFullPath( Path.Combine( ModuleDirectory, "redist", "bin" ) );
            string ULIS_Name = "ULIS3";
            string ULIS_DylibName = ULIS_Name + ".dylib";
            string pluginDylibPath = Path.Combine( BinBase, ULIS_DylibName );

            PublicSystemIncludePaths.Add( Path.Combine( IncludeBase, ULIS_Name) );
            PublicAdditionalLibraries.Add( pluginDylibPath );

            PublicDefinitions.Add("ULIS3_DYNAMIC_LIBRARY");

            string binariesPath = CopyToBinaries( pluginDylibPath, Target );
            System.Console.WriteLine( "Using " + ULIS_Name +" DYLIB: " + binariesPath );
            RuntimeDependencies.Add( binariesPath );
        }
    }
}

