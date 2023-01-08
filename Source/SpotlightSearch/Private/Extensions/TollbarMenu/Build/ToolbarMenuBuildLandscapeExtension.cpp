// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildLandscapeExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildLandscapeExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> BuildAllLandscape = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BuildAllLandscape.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(BuildAllLandscape);

	return OutCommands;
}