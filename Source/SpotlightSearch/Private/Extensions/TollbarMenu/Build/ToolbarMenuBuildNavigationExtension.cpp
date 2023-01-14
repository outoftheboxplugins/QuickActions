// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildNavigationExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildNavigationExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> BuildPaths = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BuildPathsOnly.ToSharedRef(), LevelEditorCommands);
	BuildPaths->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "ShowFlagsMenu.Navigation");
	OutCommands.Emplace(BuildPaths);

	return OutCommands;
}