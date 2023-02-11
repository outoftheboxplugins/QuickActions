// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuSelectHierarchyExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuSelectHierarchyExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	// TODO: Find some icon for all of these

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> ImmediateChildren = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectImmediateChildren.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(ImmediateChildren);

	const TSharedPtr<FQuickCommandEntry> AllChildren = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectAllDescendants.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(AllChildren);

	return Super::GetCommands(Context);
}