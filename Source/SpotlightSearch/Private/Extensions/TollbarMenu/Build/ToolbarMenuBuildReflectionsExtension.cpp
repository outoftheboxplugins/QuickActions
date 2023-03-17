// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildReflectionsExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildReflectionsExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> BuildReflectionCaptures = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BuildReflectionCapturesOnly.ToSharedRef(), LevelEditorCommands);
	BuildReflectionCaptures->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.SceneCaptureComponent");
	OutCommands.Emplace(BuildReflectionCaptures);

	return OutCommands;
}