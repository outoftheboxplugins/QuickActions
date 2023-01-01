// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuEditEditExtension.h"

#include <Framework/Commands/GenericCommands.h>
#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<FQuickCommandEntry> UToolbarMenuEditEditExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<FQuickCommandEntry> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	FQuickCommandEntry Cut = FQuickCommandEntry(FGenericCommands::Get().Cut.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(Cut);

	FQuickCommandEntry Copy = FQuickCommandEntry(FGenericCommands::Get().Copy.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(Copy);

	FQuickCommandEntry Paste = FQuickCommandEntry(FGenericCommands::Get().Paste.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(Paste);

	FQuickCommandEntry Duplicate = FQuickCommandEntry(FGenericCommands::Get().Duplicate.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(Duplicate);

	FQuickCommandEntry Delete = FQuickCommandEntry(FGenericCommands::Get().Delete.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(Delete);

	return OutCommands;
}