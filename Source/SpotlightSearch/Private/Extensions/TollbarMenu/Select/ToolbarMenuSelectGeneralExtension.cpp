// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuSelectGeneralExtension.h"

#include <EditorViewportCommands.h>
#include <Framework/Commands/GenericCommands.h>
#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuSelectGeneralExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	// TODO: Find some icon for all of these

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> SelectAll = MakeShared<FQuickCommandEntry>(FGenericCommands::Get().SelectAll.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(SelectAll);

	const TSharedPtr<FQuickCommandEntry> SelectNone = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectNone.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(SelectNone);

	const TSharedPtr<FQuickCommandEntry> InvertSelect = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectNone.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(InvertSelect);

	const TSharedPtr<FQuickCommandEntry> SelectAllOfClass = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectAllActorsOfSameClass.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(SelectAllOfClass);

	const TSharedPtr<FQuickCommandEntry> FocusSelected = MakeShared<FQuickCommandEntry>(FEditorViewportCommands::Get().FocusViewportToSelection.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(FocusSelected);

	return OutCommands;
}