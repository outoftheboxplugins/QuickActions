// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildAutomationExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildAutomationExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> BuildAndSubmit = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BuildAndSubmitToSourceControl.ToSharedRef(), LevelEditorCommands);
	BuildAndSubmit->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "SourceControl.Actions.Submit");
	OutCommands.Emplace(BuildAndSubmit);

	return OutCommands;
}