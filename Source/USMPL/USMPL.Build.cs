// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class USMPL: ModuleRules
{
	public USMPL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"USMPL/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"USMPL/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "ProceduralMeshComponent",
                "ROSIntegration",
				// ... add other public dependencies that you statically link with here ...
			}
			);


        string PluginPath = Path.GetFullPath(ModuleDirectory);
        string csmpl_lib_path = Environment.GetEnvironmentVariable("CSMPL_LIB_PATH");
        string julia_dir = Environment.GetEnvironmentVariable("JULIA_DIR");

        //RuntimeDependencies.Add(new RuntimeDependency("C:\\Users\\nsaini\\Documents\\Unreal Projects\\SMPLPluginTest_18\\Binaries\\Win64\\csmpl.dll"));
        RuntimeDependencies.Add(new RuntimeDependency(csmpl_lib_path));

        //Julia
        PublicAdditionalLibraries.Add(Path.Combine(julia_dir,"lib","libjulia.dll.a"));
        PublicAdditionalLibraries.Add(Path.Combine(julia_dir,"lib","libopenlibm.dll.a"));

        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
