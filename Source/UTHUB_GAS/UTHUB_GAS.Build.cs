// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UTHUB_GAS : ModuleRules
{
	public UTHUB_GAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" });
        
        PrivateDependencyModuleNames.Add("GameplayAbilities");
        PrivateDependencyModuleNames.Add("GameplayTasks");
        
        PublicIncludePaths.Add(ModuleDirectory + "/Public");
	}
}
