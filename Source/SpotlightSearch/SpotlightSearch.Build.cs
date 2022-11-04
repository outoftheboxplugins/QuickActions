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
				"DeveloperSettings",
				"EditorStyle",
				"Engine",
				"InputCore",
				"LevelEditor",
				"MainFrame", 
				"Slate",
				"SlateCore",
				"ToolMenus",
				"ToolWidgets", 
				"UnrealEd", 
				"EditorSubsystem",
		});
	}
}
