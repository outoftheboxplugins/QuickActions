// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildGeometryExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildGeometryExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> BuildGeometry = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BuildGeometryOnly.ToSharedRef(), LevelEditorCommands);
	BuildGeometry->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.box-perspective");
	OutCommands.Emplace(BuildGeometry);

	const TSharedPtr<FQuickCommandEntry> BuildGeometryCurrent = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BuildGeometryOnly_OnlyCurrentLevel.ToSharedRef(), LevelEditorCommands);
	BuildGeometryCurrent->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.box-perspective");
	OutCommands.Emplace(BuildGeometryCurrent);

	return OutCommands;
}