using UnrealBuildTool;

public class SpotlightSearch : ModuleRules
{
	public SpotlightSearch(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
				"Core",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
				"CoreUObject",
				"DesktopPlatform",
				"DeveloperSettings",
				"EditorStyle",
				"EditorSubsystem", 
				"Engine",
				"GameProjectGeneration", 
				"InputCore",
				"Landscape",
				"LevelEditor",
				"MainFrame", 
				"Projects",
				"Slate",
				"SlateCore",
				"TargetDeviceServices", 
				"ToolMenus",
				"ToolWidgets", 
				"TurnkeySupport",
				"UndoHistoryEditor",
				"UnrealEd", 
				"DeveloperToolSettings",
		});
	}
}
