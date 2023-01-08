// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildHLODsExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildHLODsExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> BuildHLODs = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BuildHLODs.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(BuildHLODs);

	return OutCommands;
}