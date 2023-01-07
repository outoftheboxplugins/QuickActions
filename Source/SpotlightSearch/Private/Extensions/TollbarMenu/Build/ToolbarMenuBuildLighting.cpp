// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildLighting.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

#define LOCTEXT_NAMESPACE "QuickActions"

namespace
{
	void ConvertLightingQuality(TAttribute<FText>& QualityText)
	{
		QualityText = FText::Format(LOCTEXT("LightingQuality", "Set lighting quality to: {0}"), QualityText.Get());
	}
} // namespace

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildLighting::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	// TODO: For commands with no icon we should have a default one.
	const TSharedPtr<FQuickCommandEntry> BuildLightingOnly = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BuildLightingOnly.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(BuildLightingOnly);

	TArray<TSharedPtr<FUICommandInfo>> LightQualities;
	LightQualities.Add(FLevelEditorCommands::Get().LightingQuality_Production);
	LightQualities.Add(FLevelEditorCommands::Get().LightingQuality_High);
	LightQualities.Add(FLevelEditorCommands::Get().LightingQuality_Medium);
	LightQualities.Add(FLevelEditorCommands::Get().LightingQuality_Preview);

	for (const TSharedPtr<FUICommandInfo>& LightQuality : LightQualities)
	{
		const TSharedPtr<FQuickCommandEntry> LightQualityCommand = MakeShared<FQuickCommandEntry>(LightQuality.ToSharedRef(), LevelEditorCommands);
		ConvertLightingQuality(LightQualityCommand->Title);
		OutCommands.Emplace(LightQualityCommand);
	}

	// TODO: Add LightingInfo submenu
	// - LightMap Density Rendering options
	// - LightMap Resolution adjustaments
	// - Lighting static mesh info
	// TODO: Add Use Error coloring button
	// TODO: Add Show lightning stats button

	return OutCommands;
}

#undef LOCTEXT_NAMESPACE