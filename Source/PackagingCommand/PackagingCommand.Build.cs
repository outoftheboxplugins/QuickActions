using UnrealBuildTool;

public class PackagingCommand : ModuleRules
{
    public PackagingCommand(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
				"DesktopPlatform",
				"DeveloperToolSettings",
				"LauncherServices",
				"Projects",
				"TargetDeviceServices", 
				"TurnkeySupport",
                "CoreUObject",
                "Engine",
                "GameProjectGeneration", 
                "GeometryCollectionEditor",
                "LevelEditor",
                "Slate",
                "SlateCore", 
                "SpotlightSearch",
                "TurnkeyIO",
                "UATHelper",
                "UnrealEd",
                "Zen",
            }
        );
    }
}
