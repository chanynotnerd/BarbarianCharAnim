// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RemakeCharacterAnim : ModuleRules
{
	public RemakeCharacterAnim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
