// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuSelectGeometryCollectionExtension.h"

#include <GeometryCollection/GeometryCollectionSelectionCommands.h>
#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuSelectGeometryCollectionExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	// TODO: Find some icon for all of these

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> SelectAllGeometry = MakeShared<FQuickCommandEntry>(FGeometryCollectionSelectionCommands::Get().SelectAllGeometry.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(SelectAllGeometry);

	const TSharedPtr<FQuickCommandEntry> SelectNone = MakeShared<FQuickCommandEntry>(FGeometryCollectionSelectionCommands::Get().SelectNone.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(SelectNone);

	const TSharedPtr<FQuickCommandEntry> SelectInverse = MakeShared<FQuickCommandEntry>(FGeometryCollectionSelectionCommands::Get().SelectInverseGeometry.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(SelectInverse);

	return Super::GetCommands(Context);
}