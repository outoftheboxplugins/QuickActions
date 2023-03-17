// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuSelectEmittersExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuSelectEmittersExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	// TODO: Find some icon for all of these

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> SelectMatching = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectMatchingEmitter.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(SelectMatching);

	return Super::GetCommands(Context);
}