// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuFileImportExportExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuFileImportExportExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> ImportScene = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().ImportScene.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(ImportScene);

	const TSharedPtr<FQuickCommandEntry> ExportAll = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().ExportAll.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(ExportAll);

	const TSharedPtr<FQuickCommandEntry> ExportSelected = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().ExportSelected.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(ExportSelected);

	return OutCommands;
}