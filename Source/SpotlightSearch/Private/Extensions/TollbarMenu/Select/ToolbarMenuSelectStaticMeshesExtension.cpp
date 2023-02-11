// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuSelectStaticMeshesExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuSelectStaticMeshesExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	// TODO: Find some icon for all of these

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> SelectSameClass = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectStaticMeshesOfSameClass.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(SelectSameClass);

	const TSharedPtr<FQuickCommandEntry> SelectAllClass = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectStaticMeshesAllClasses.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(SelectSameClass);

	return Super::GetCommands(Context);
}