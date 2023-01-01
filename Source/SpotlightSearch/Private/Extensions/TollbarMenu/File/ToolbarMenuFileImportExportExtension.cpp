// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuFileImportExportExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<FQuickCommandEntry> UToolbarMenuFileImportExportExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<FQuickCommandEntry> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	FQuickCommandEntry ImportScene = FQuickCommandEntry(FLevelEditorCommands::Get().ImportScene.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(ImportScene);

	FQuickCommandEntry ExportAll = FQuickCommandEntry(FLevelEditorCommands::Get().ExportAll.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(ExportAll);

	FQuickCommandEntry ExportSelected = FQuickCommandEntry(FLevelEditorCommands::Get().ExportSelected.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(ExportSelected);

	return OutCommands;
}