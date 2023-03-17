// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildLightingExtension.h"

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

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildLightingExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	// TODO: Decide if we should use add or emplace for every OutCommands.
	const TSharedPtr<FQuickCommandEntry> BuildLightingOnly = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BuildLightingOnly.ToSharedRef(), LevelEditorCommands);
	BuildLightingOnly->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "PlacementBrowser.Icons.Lights");
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
		LightQualityCommand->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "PlacementBrowser.Icons.Lights");
		OutCommands.Emplace(LightQualityCommand);
	}

	const bool bRenderGrayscale = FLevelEditorActionCallbacks::IsLightingDensityRenderGrayscaleChecked();
	const TSharedPtr<FQuickSwitchCommandEntry> RenderGrayscale =
		MakeShared<FQuickSwitchCommandEntry>(FLevelEditorCommands::Get().LightingDensity_RenderGrayscale.ToSharedRef(), LevelEditorCommands, bRenderGrayscale);
	OutCommands.Emplace(RenderGrayscale);

	TArray<TSharedPtr<FUICommandInfo>> LightResolutionSelections;
	LightResolutionSelections.Add(FLevelEditorCommands::Get().LightingResolution_CurrentLevel);
	LightResolutionSelections.Add(FLevelEditorCommands::Get().LightingResolution_SelectedLevels);
	LightResolutionSelections.Add(FLevelEditorCommands::Get().LightingResolution_AllLoadedLevels);

	for (const TSharedPtr<FUICommandInfo>& LightResolutionSelection : LightResolutionSelections)
	{
		const TSharedPtr<FQuickCommandEntry> LightResolutionSelectionCommand = MakeShared<FQuickCommandEntry>(LightResolutionSelection.ToSharedRef(), LevelEditorCommands);
		ConvertLightingSelection(LightResolutionSelectionCommand->Title);
		LightResolutionSelectionCommand->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "PlacementBrowser.Icons.Lights");
		OutCommands.Emplace(LightResolutionSelectionCommand);
	}

	const bool bSelectedObjectsOnly = FLevelEditorActionCallbacks::IsLightingResolutionSelectedObjectsOnlyChecked();
	const TSharedPtr<FQuickSwitchCommandEntry> SelectedObjectsOnly =
		MakeShared<FQuickSwitchCommandEntry>(FLevelEditorCommands::Get().LightingResolution_SelectedObjectsOnly.ToSharedRef(), LevelEditorCommands, bSelectedObjectsOnly);
	OutCommands.Emplace(SelectedObjectsOnly);

	const TSharedPtr<FQuickCommandEntry> LightningStaticMeshInfo = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().LightingStaticMeshInfo.ToSharedRef(), LevelEditorCommands);
	LightningStaticMeshInfo->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "PlacementBrowser.Icons.Lights");
	OutCommands.Emplace(LightningStaticMeshInfo);

	const bool bErrorColoring = FLevelEditorActionCallbacks::LightingBuildOptions_UseErrorColoring_IsChecked();
	const TSharedPtr<FQuickSwitchCommandEntry> LightBuildErrorColoring =
		MakeShared<FQuickSwitchCommandEntry>(FLevelEditorCommands::Get().LightingBuildOptions_UseErrorColoring.ToSharedRef(), LevelEditorCommands, bErrorColoring);
	OutCommands.Emplace(LightBuildErrorColoring);

	const bool bShowStats = FLevelEditorActionCallbacks::LightingBuildOptions_ShowLightingStats_IsChecked();
	const TSharedPtr<FQuickSwitchCommandEntry> ShowStats =
		MakeShared<FQuickSwitchCommandEntry>(FLevelEditorCommands::Get().LightingBuildOptions_ShowLightingStats.ToSharedRef(), LevelEditorCommands, bShowStats);
	OutCommands.Emplace(ShowStats);

	return OutCommands;
}

#undef LOCTEXT_NAMESPACE