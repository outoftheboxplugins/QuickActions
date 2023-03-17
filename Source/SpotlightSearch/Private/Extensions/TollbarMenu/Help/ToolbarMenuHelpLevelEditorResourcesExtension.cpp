// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuHelpLevelEditorResourcesExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuHelpLevelEditorResourcesExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> BrowseDocumentation = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BrowseDocumentation.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(BrowseDocumentation);

	const TSharedPtr<FQuickCommandEntry> BrowseViewportControls = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BrowseViewportControls.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(BrowseViewportControls);

	return OutCommands;
}