// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildVerificationExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildVerificationExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> MapCheck = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().MapCheck.ToSharedRef(), LevelEditorCommands);
	MapCheck->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Validate");
	OutCommands.Emplace(MapCheck);

	return OutCommands;
}