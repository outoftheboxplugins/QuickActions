// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuFileSaveExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuFileSaveExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	CollectActionsFromMenuSection(OutCommands, Context, "MainFrame.MainMenu.File", "FileSave");	
	
	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	TSharedPtr<FQuickCommandEntry> SaveCurrentLevel = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().Save.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(SaveCurrentLevel);

	TSharedPtr<FQuickCommandEntry> SaveCurrentLevelAs = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SaveAs.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(SaveCurrentLevelAs);

	return OutCommands;
}