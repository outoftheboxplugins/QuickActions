// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuSelectSkeletalMeshesExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuSelectSkeletalMeshesExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	// TODO: Find some icon for all of these

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> SelectSameClass = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectSkeletalMeshesOfSameClass.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(SelectSameClass);

	const TSharedPtr<FQuickCommandEntry> SelectAllClasses = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectSkeletalMeshesAllClasses.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(SelectAllClasses);

	return Super::GetCommands(Context);
}