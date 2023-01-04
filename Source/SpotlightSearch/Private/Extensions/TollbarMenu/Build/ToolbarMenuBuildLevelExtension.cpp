// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildLevelExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildLevelExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	// TODO: For commands with no icon we should have a default one.
	const TSharedPtr<FQuickCommandEntry> Build = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().Build.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(Build);

	return OutCommands;
}