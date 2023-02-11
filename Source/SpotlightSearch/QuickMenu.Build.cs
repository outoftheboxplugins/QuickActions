using UnrealBuildTool;

public class QuickMenu : ModuleRules
{
	public QuickMenu(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
				"Core",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
				"CoreUObject",
				"DeveloperSettings",
				"EditorStyle",
				"EditorSubsystem", 
				"Engine",
				"InputCore",
				"Landscape",
				"LevelEditor",
				"MainFrame", 
				"Slate",
				"SlateCore",
				"ToolMenus",
				"ToolWidgets", 
				"UndoHistoryEditor",
				"UnrealEd", 
		});
	}
}
