// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuSelectBspExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuSelectBspExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	// TODO: Find some icon for all of these

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> AllAdditiveBrushes = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectAllAddditiveBrushes.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(AllAdditiveBrushes);

	const TSharedPtr<FQuickCommandEntry> AllSubtractiveBrushes = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectAllSubtractiveBrushes.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(AllSubtractiveBrushes);

	const TSharedPtr<FQuickCommandEntry> AllSurfaces = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectAllSurfaces.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(AllSurfaces);

	return Super::GetCommands(Context);
}