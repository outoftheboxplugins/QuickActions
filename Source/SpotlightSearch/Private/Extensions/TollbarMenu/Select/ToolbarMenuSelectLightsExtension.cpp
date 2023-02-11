// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuSelectLightsExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuSelectLightsExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	// TODO: Find some icon for all of these

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> RelevantLights = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectRelevantLights.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(RelevantLights);

	const TSharedPtr<FQuickCommandEntry> AllLights = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectAllLights.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(AllLights);

	const TSharedPtr<FQuickCommandEntry> LightsExceedingOverlap = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SelectStationaryLightsExceedingOverlap.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(LightsExceedingOverlap);

	return Super::GetCommands(Context);
}