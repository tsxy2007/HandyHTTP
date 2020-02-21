// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


using UnrealBuildTool;

public class HandyHTTP : ModuleRules
{
    public HandyHTTP(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "Public/HandyHTTP.h";


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
               "Public/Client"
            }
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "HTTP"
				// ... add other public dependencies that you statically link with here ...
			}
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
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
