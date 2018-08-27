// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PsReplayKit : ModuleRules
{
    static bool bCompileReplayKit;
	static bool bAvailable;

	public PsReplayKit(ReadOnlyTargetRules Target) : base(Target)
	{
        // #define REPLAYKIT_ENABLE
        bCompileReplayKit = true;
		bAvailable = Target.Platform == UnrealTargetPlatform.IOS;

		PublicDefinitions.Add("WITH_REPLAYKIT=" + (bCompileReplayKit && bAvailable ? "1" : "0"));
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"PsReplayKit/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Engine",
				"CoreUObject"
				// ... add private dependencies that you statically link with here ...
			}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		if (bCompileReplayKit == true)
		{
			if(Target.Platform == UnrealTargetPlatform.IOS)
			{
				PublicFrameworks.AddRange(
					new string[]
					{
						"CoreTelephony",
						"SystemConfiguration",
						"UIKit",
						"Foundation",
						"CoreGraphics",
						"MobileCoreServices",
						"StoreKit",
						"CFNetwork",
						"CoreData",
						"Security",
						"CoreLocation",
						"WatchConnectivity",
						"MediaPlayer",
						"CoreFoundation"
					}
				);
			}
		}
	}
}
