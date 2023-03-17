// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildLevelExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildLevelExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> Build = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().Build.ToSharedRef(), LevelEditorCommands);
	Build->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "PlayWorld.Simulate");
	OutCommands.Emplace(Build);

	return OutCommands;
}