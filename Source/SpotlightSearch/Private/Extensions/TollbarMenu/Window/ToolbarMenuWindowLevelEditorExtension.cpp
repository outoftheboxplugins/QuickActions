// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuWindowLevelEditorExtension.h"

#include <LevelEditor.h>

#define LOCTEXT_NAMESPACE "QuickActions"

TArray<FQuickCommandEntry> UToolbarMenuWindowLevelEditorExtension::GetCommands()
{
	TArray<FQuickCommandEntry> OutCommands;

	FQuickCommandEntry CameraShakePreviewer;
	CameraShakePreviewer.Title = LOCTEXT("CameraShakePreviewer", "Camera Shake Previewer");
	CameraShakePreviewer.Tooltip = LOCTEXT("CameraShakePreviewerTooltipText", "Open the camera shake preview panel.");
	CameraShakePreviewer.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelViewport.ToggleActorPilotCameraView");
	CameraShakePreviewer.ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("CameraShakePreviewer")));
		}
	);
	OutCommands.Add(CameraShakePreviewer);

	FQuickCommandEntry Sequencer;
	Sequencer.Title = LOCTEXT("Sequencer", "Sequencer");
	Sequencer.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Cinematics");
	// TODO: Sequence should call this private method to confirm it's allowed to spawn:	SLevelEditor::CanSpawnLevelEditorTab, LevelEditorTabIds::Sequencer
	Sequencer.ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("Sequencer")));
		}
	);
	OutCommands.Add(Sequencer);

	return OutCommands;
}

#undef LOCTEXT_NAMESPACE