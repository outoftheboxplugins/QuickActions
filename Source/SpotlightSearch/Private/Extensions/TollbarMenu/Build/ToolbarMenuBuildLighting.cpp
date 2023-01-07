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

	void ConvertLightingSelection(TAttribute<FText>& SelectionText)
	{
		SelectionText = FText::Format(LOCTEXT("LightingSelection", "Set LightMap resolution selection to: {0}"), SelectionText.Get());
	}

} // namespace

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildLighting::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	// TODO: For commands with no icon we should have a default one.
	const TSharedPtr<FQuickCommandEntry> BuildLightingOnly = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BuildLightingOnly.ToSharedRef(), LevelEditorCommands);
	// TODO: Decide if we should use add or emplace for every OutCommands.
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

	const TSharedPtr<FQuickCommandEntry> LightDensityRenderGreyscale = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().LightingDensity_RenderGrayscale.ToSharedRef(), LevelEditorCommands);
	LightDensityRenderGreyscale->Title = GEngine->bRenderLightMapDensityGrayscale ? NSLOCTEXT("LevelEditorActions", "RenderGrayScaleOn", "Enable Grayscale rendering")
																				  : NSLOCTEXT("LevelEditorActions", "RenderGrayScaleOff", "Disable Grayscale rendering");
	OutCommands.Emplace(LightDensityRenderGreyscale);

	TArray<TSharedPtr<FUICommandInfo>> LightResolutionSelections;
	LightResolutionSelections.Add(FLevelEditorCommands::Get().LightingResolution_CurrentLevel);
	LightResolutionSelections.Add(FLevelEditorCommands::Get().LightingResolution_SelectedLevels);
	LightResolutionSelections.Add(FLevelEditorCommands::Get().LightingResolution_AllLoadedLevels);

	for (const TSharedPtr<FUICommandInfo>& LightResolutionSelection : LightResolutionSelections)
	{
		const TSharedPtr<FQuickCommandEntry> LightResolutionSelectionCommand = MakeShared<FQuickCommandEntry>(LightResolutionSelection.ToSharedRef(), LevelEditorCommands);
		ConvertLightingSelection(LightResolutionSelectionCommand->Title);
		OutCommands.Emplace(LightResolutionSelectionCommand);
	}

	const TSharedPtr<FQuickCommandEntry> LightResolutionSelectedOnly =
		MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().LightingResolution_SelectedObjectsOnly.ToSharedRef(), LevelEditorCommands);
	// LightResolutionSelectedOnly->Title =
	OutCommands.Emplace(LightResolutionSelectedOnly);

	const TSharedPtr<FQuickCommandEntry> LightningStaticMeshInfo = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().LightingStaticMeshInfo.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(LightningStaticMeshInfo);

	// TODO: Add Use Error coloring button
	return OutCommands;
}

#undef LOCTEXT_NAMESPACE