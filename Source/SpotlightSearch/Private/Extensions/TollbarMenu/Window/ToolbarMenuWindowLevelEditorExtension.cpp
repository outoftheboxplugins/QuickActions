﻿// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

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

	FQuickCommandEntry TakeRecorder;
	TakeRecorder.Title = LOCTEXT("TakeRecorderTab_Label", "Take Recorder");
	TakeRecorder.Tooltip = LOCTEXT("TakeRecorderTab_Tooltip", "Open the main Take Recorder UI.");
	TakeRecorder.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "SequenceRecorder.TabIcon");
	TakeRecorder.ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId("TakeRecorder"));
		}
	);
	OutCommands.Add(TakeRecorder);

	FQuickCommandEntry TakeBrowser;
	TakeBrowser.Title = LOCTEXT("TakesBrowserTab_Label", "Takes Browser");
	TakeBrowser.Tooltip = LOCTEXT("TakeBrowserTab_Tooltip", "Open the Take Browser UI");
	TakeBrowser.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "ContentBrowser.TabIcon");
	TakeBrowser.ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId("TakesBrowser"));
		}
	);
	OutCommands.Add(TakeBrowser);

	return OutCommands;
}

#undef LOCTEXT_NAMESPACE