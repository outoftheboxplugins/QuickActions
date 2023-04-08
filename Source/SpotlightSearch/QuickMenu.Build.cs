// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

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
				"GeometryCollectionEditor", 
				"InputCore",
				"Landscape",
				"LevelEditor",
				"MainFrame", 
				"Projects",
				"Slate",
				"SlateCore",
				"ToolMenus",
				"ToolWidgets", 
				"UndoHistoryEditor",
				"UnrealEd", 
				"MergeActors", 
		});
	}
}
