// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildVisibilityExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildVisibilityExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> PrecomputeVisibility = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BuildLightingOnly_VisibilityOnly.ToSharedRef(), LevelEditorCommands);
	PrecomputeVisibility->Icon = FSlateIcon(FAppStyle::Get().GetStyleSetName(), "Icons.Visibility");
	OutCommands.Emplace(PrecomputeVisibility);

	return OutCommands;
}