// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuWindowLevelEditorExtension.h"

#include <LevelEditor.h>

#define LOCTEXT_NAMESPACE "QuickActions"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuWindowLevelEditorExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const TSharedPtr<FQuickCommandEntry> CameraShakePreviewer = MakeShared<FQuickCommandEntry>();
	CameraShakePreviewer->Title = LOCTEXT("CameraShakePreviewer", "Camera Shake Previewer");
	CameraShakePreviewer->Tooltip = LOCTEXT("CameraShakePreviewerTooltipText", "Open the camera shake preview panel.");
	CameraShakePreviewer->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelViewport.ToggleActorPilotCameraView");
	CameraShakePreviewer->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("CameraShakePreviewer")));
		}
	);
	OutCommands.Add(CameraShakePreviewer);

	const TSharedPtr<FQuickCommandEntry> Sequencer = MakeShared<FQuickCommandEntry>();
	Sequencer->Title = LOCTEXT("Sequencer", "Sequencer");
	Sequencer->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Cinematics");
	// TODO: Sequence should call this private method to confirm it's allowed to spawn:	SLevelEditor::CanSpawnLevelEditorTab, LevelEditorTabIds::Sequencer
	Sequencer->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("Sequencer")));
		}
	);
	OutCommands.Add(Sequencer);

	const TSharedPtr<FQuickCommandEntry> TakeRecorder = MakeShared<FQuickCommandEntry>();
	TakeRecorder->Title = LOCTEXT("TakeRecorderTab_Label", "Take Recorder");
	TakeRecorder->Tooltip = LOCTEXT("TakeRecorderTab_Tooltip", "Open the main Take Recorder UI.");
	TakeRecorder->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "SequenceRecorder.TabIcon");
	TakeRecorder->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId("TakeRecorder"));
		}
	);
	OutCommands.Add(TakeRecorder);

	const TSharedPtr<FQuickCommandEntry> TakeBrowser = MakeShared<FQuickCommandEntry>();
	TakeBrowser->Title = LOCTEXT("TakesBrowserTab_Label", "Takes Browser");
	TakeBrowser->Tooltip = LOCTEXT("TakeBrowserTab_Tooltip", "Open the Take Browser UI");
	TakeBrowser->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "ContentBrowser.TabIcon");
	TakeBrowser->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId("TakesBrowser"));
		}
	);
	OutCommands.Add(TakeBrowser);

	constexpr int32 NumContentBrowserTabs = 4;
	for (int32 BrowserIdx = 0; BrowserIdx < NumContentBrowserTabs; BrowserIdx++)
	{
		const TSharedPtr<FQuickCommandEntry> ContentBrowserTab = MakeShared<FQuickCommandEntry>();
		ContentBrowserTab->Title = FText::Format(LOCTEXT("ContentBrowserTabNameWithIndex", "Content Browser {0}"), FText::AsNumber(BrowserIdx + 1));
		ContentBrowserTab->Tooltip = LOCTEXT("ContentBrowserMenuTooltipText", "Open a Content Browser tab.");
		ContentBrowserTab->Icon = FSlateIcon(FAppStyle::Get().GetStyleSetName(), "ContentBrowser.TabIcon");
		ContentBrowserTab->ExecuteCallback = FSimpleDelegate::CreateLambda(
			[BrowserIdx]()
			{
				const FName TabID = FName(*FString::Printf(TEXT("ContentBrowserTab%d"), BrowserIdx + 1));
				FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TabID));
			}
		);

		OutCommands.Add(ContentBrowserTab);
	}

	constexpr int32 NumDetailsTabs = 4;
	for (int32 DetailsIdx = 0; DetailsIdx < NumDetailsTabs; DetailsIdx++)
	{
		const TSharedPtr<FQuickCommandEntry> DetailsTab = MakeShared<FQuickCommandEntry>();
		DetailsTab->Title = FText::Format(LOCTEXT("LevelEditorSelectionDetailsWithIndex", "Details {0}"), FText::AsNumber(DetailsIdx + 1));
		DetailsTab->Tooltip = NSLOCTEXT("LevelEditorTabs", "LevelEditorSelectionDetailsTooltip", "Open a Details tab. Use this to view and edit properties of the selected object(s).");
		DetailsTab->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details");
		DetailsTab->ExecuteCallback = FSimpleDelegate::CreateLambda(
			[DetailsIdx]()
			{
				static const FName DetailsTabIdentifiers_LevelEditor[] = {
					"LevelEditorSelectionDetails", "LevelEditorSelectionDetails2", "LevelEditorSelectionDetails3", "LevelEditorSelectionDetails4"};

				const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
				const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
				const FName TabID = DetailsTabIdentifiers_LevelEditor[DetailsIdx];

				LevelEditorTabManager->TryInvokeTab(FTabId(TabID));
			}
		);

		OutCommands.Add(DetailsTab);
	}

	const TSharedPtr<FQuickCommandEntry> ProcessEXR = MakeShared<FQuickCommandEntry>();
	ProcessEXR->Title = LOCTEXT("ImgMediaProcessEXRTabTitle", "Process EXR");
	ProcessEXR->Tooltip = LOCTEXT("ImgMediaProcessEXRTooltipText", "Open the Process EXR tab.");
	ProcessEXR->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Viewports");
	ProcessEXR->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("ImgMediaProcessEXR")));
		}
	);
	OutCommands.Add(ProcessEXR);

	const TSharedPtr<FQuickCommandEntry> BandwidthMonitor = MakeShared<FQuickCommandEntry>();
	BandwidthMonitor->Title = LOCTEXT("ImgMediaBandwidthMonitorTabTitle", "Bandwidth Monitor");
	BandwidthMonitor->Tooltip = LOCTEXT("ImgMediaBandwidthMonitorTooltipText", "Open the bandwidth monitor tab.");
	BandwidthMonitor->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "SequenceRecorder.TabIcon");
	BandwidthMonitor->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("ImgMediaBandwidth")));
		}
	);
	OutCommands.Add(BandwidthMonitor);

	const TSharedPtr<FQuickCommandEntry> GlobalCache = MakeShared<FQuickCommandEntry>();
	GlobalCache->Title = LOCTEXT("ImgMediaGlobalCacheTabTitle", "Global Cache");
	GlobalCache->Tooltip = LOCTEXT("ImgMediaGlobalCacheTooltipText", "Open the global cache tab.");
	GlobalCache->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "SequenceRecorder.TabIcon");
	GlobalCache->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("ImgMediaCache")));
		}
	);
	OutCommands.Add(GlobalCache);

	constexpr int32 NumOutlinerTabs = 4;
	for (int32 OutlinerIdx = 0; OutlinerIdx < NumOutlinerTabs; OutlinerIdx++)
	{
		const TSharedPtr<FQuickCommandEntry> OutlinerTab = MakeShared<FQuickCommandEntry>();
		OutlinerTab->Title = FText::Format(LOCTEXT("LevelEditorSceneOutlinerWithIndex", "Outliner {0}"), FText::AsNumber(OutlinerIdx + 1));
		OutlinerTab->Tooltip =
			NSLOCTEXT("LevelEditorTabs", "LevelEditorSceneOutlinerTooltipText", "Open the Outliner tab, which provides a searchable and filterable list of all actors in the world.");
		OutlinerTab->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Outliner");
		OutlinerTab->ExecuteCallback = FSimpleDelegate::CreateLambda(
			[OutlinerIdx]()
			{
				static const FName OutlinerTabIdentifiers_LevelEditor[] = {"LevelEditorSceneOutliner", "LevelEditorSceneOutliner2", "LevelEditorSceneOutliner3", "LevelEditorSceneOutliner4"};

				const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
				const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
				const FName TabID = OutlinerTabIdentifiers_LevelEditor[OutlinerIdx];

				LevelEditorTabManager->TryInvokeTab(FTabId(TabID));
			}
		);

		OutCommands.Add(OutlinerTab);
	}

	constexpr int32 NumViewportTabs = 4;
	for (int32 ViewportIdx = 0; ViewportIdx < NumViewportTabs; ViewportIdx++)
	{
		const TSharedPtr<FQuickCommandEntry> ViewportTab = MakeShared<FQuickCommandEntry>();
		ViewportTab->Title = FText::Format(LOCTEXT("LevelEditorSceneViewportWithIndex", "Viewport {0}"), FText::AsNumber(ViewportIdx + 1));
		ViewportTab->Tooltip = NSLOCTEXT("LevelEditorTabs", "LevelEditorViewportTooltip", "Open a Viewport tab. Use this to view and edit the current level.");
		ViewportTab->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Viewports");
		ViewportTab->ExecuteCallback = FSimpleDelegate::CreateLambda(
			[ViewportIdx]()
			{
				static const FName ViewportTabIdentifiers_LevelEditor[] = {"LevelEditorViewport", "LevelEditorViewport_Clone1", "LevelEditorViewport_Clone2", "LevelEditorViewport_Clone3"};

				const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
				const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
				const FName TabID = ViewportTabIdentifiers_LevelEditor[ViewportIdx];

				LevelEditorTabManager->TryInvokeTab(FTabId(TabID));
			}
		);

		OutCommands.Add(ViewportTab);
	}

	const TSharedPtr<FQuickCommandEntry> ContentBundles = MakeShared<FQuickCommandEntry>();
	ContentBundles->Title = NSLOCTEXT("LevelEditorTabs", "LevelEditorContentBundleBrowser", "Content Bundles Outliner");
	ContentBundles->Tooltip = NSLOCTEXT("LevelEditorTabs", "LevelEditorContentBundleBrowserTooltipText", "Open the Content Bundles Outliner.");
	ContentBundles->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), TEXT("LevelEditor.Tabs.DataLayers"));
	ContentBundles->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId("ContentBundleBrowser"));
		}
	);
	OutCommands.Add(ContentBundles);

	const TSharedPtr<FQuickCommandEntry> DataLayerOutliner = MakeShared<FQuickCommandEntry>();
	DataLayerOutliner->Title = NSLOCTEXT("LevelEditorTabs", "LevelEditorDataLayerBrowser", "Data Layers Outliner");
	DataLayerOutliner->Tooltip = NSLOCTEXT("LevelEditorTabs", "LevelEditorDataLayerBrowserTooltipText", "Open the Data Layers Outliner.");
	DataLayerOutliner->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.DataLayers");
	DataLayerOutliner->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("LevelEditorDataLayerBrowser")));
		}
	);
	OutCommands.Add(DataLayerOutliner);

	const TSharedPtr<FQuickCommandEntry> WorldPartitionEditor = MakeShared<FQuickCommandEntry>();
	WorldPartitionEditor->Title = NSLOCTEXT("LevelEditorTabs", "WorldPartitionEditor", "World Partition Editor");
	WorldPartitionEditor->Tooltip = NSLOCTEXT("LevelEditorTabs", "WorldPartitionEditorTooltipText", "Open the World Partition Editor.");
	WorldPartitionEditor->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.WorldPartition");
	WorldPartitionEditor->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId("WorldBrowserPartitionEditor"));
		}
	);
	OutCommands.Add(WorldPartitionEditor);

	const TSharedPtr<FQuickCommandEntry> EnvironmentLighting = MakeShared<FQuickCommandEntry>();
	EnvironmentLighting->Title = NSLOCTEXT("LevelEditorTabs", "EnvironmentLightingViewer", "Env. Light Mixer");
	EnvironmentLighting->Tooltip =
		NSLOCTEXT("LevelEditorTabs", "LevelEditorEnvironmentLightingViewerTooltipText", "Open the Environmment Lighting tab to edit all the entities important for world lighting.");
	EnvironmentLighting->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "EditorViewport.ReflectionOverrideMode");
	EnvironmentLighting->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("LevelEditorEnvironmentLightingViewer")));
		}
	);
	OutCommands.Add(EnvironmentLighting);

	const TSharedPtr<FQuickCommandEntry> HierarchicalLODOutliner = MakeShared<FQuickCommandEntry>();
	HierarchicalLODOutliner->Title = NSLOCTEXT("LevelEditorTabs", "LevelEditorHierarchicalLODOutliner", "Hierarchical LOD Outliner");
	HierarchicalLODOutliner->Tooltip = NSLOCTEXT("LevelEditorTabs", "LevelEditorHierarchicalLODOutlinerTooltipText", "Open the Hierarchical LOD Outliner.");
	HierarchicalLODOutliner->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.HLOD");
	HierarchicalLODOutliner->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("LevelEditorHierarchicalLODOutliner")));
		}
	);
	OutCommands.Add(HierarchicalLODOutliner);

	const TSharedPtr<FQuickCommandEntry> Layers = MakeShared<FQuickCommandEntry>();
	Layers->Title = NSLOCTEXT("LevelEditorTabs", "LevelEditorLayerBrowser", "Layers");
	Layers->Tooltip = NSLOCTEXT("LevelEditorTabs", "LevelEditorLayerBrowserTooltipText", "Open the Layers tab. Use this to manage which actors in the world belong to which layers.");
	Layers->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Layers");
	Layers->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("LevelEditorLayerBrowser")));
		}
	);
	OutCommands.Add(Layers);

	const TSharedPtr<FQuickCommandEntry> Levels = MakeShared<FQuickCommandEntry>();
	Levels->Title = NSLOCTEXT("LevelEditorTabs", "WorldBrowserHierarchy", "Levels");
	Levels->Tooltip = NSLOCTEXT("LevelEditorTabs", "WorldBrowserHierarchyTooltipText", "Open the Levels tab. Use this to manage the levels in the current project.");
	Levels->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.WorldBrowser");
	Levels->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("WorldBrowserHierarchy")));
		}
	);
	OutCommands.Add(Levels);

	const TSharedPtr<FQuickCommandEntry> LightMixer = MakeShared<FQuickCommandEntry>();
	LightMixer->Title = LOCTEXT("LightMixerTabLabel", "Light Mixer");
	LightMixer->Tooltip = LOCTEXT("OpenLightMixerEditorTooltip", "Open Light Mixer");
	LightMixer->Icon = FSlateIcon(FName(TEXT("LightMixer")), "LightMixer.ToolbarButton", "LightMixer.ToolbarButton.Small");
	LightMixer->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("LightMixerToolkit")));
		}
	);
	OutCommands.Add(LightMixer);

	const TSharedPtr<FQuickCommandEntry> PlaceActor = MakeShared<FQuickCommandEntry>();
	PlaceActor->Title = NSLOCTEXT("LevelEditorTabs", "PlacementBrowser", "Place Actors");
	PlaceActor->Tooltip = NSLOCTEXT("LevelEditorTabs", "PlacementBrowserTooltipText", "Actor Placement Browser");
	PlaceActor->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.PlacementBrowser");
	PlaceActor->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("PlacementBrowser")));
		}
	);
	OutCommands.Add(PlaceActor);

	const TSharedPtr<FQuickCommandEntry> VariantManager = MakeShared<FQuickCommandEntry>();
	VariantManager->Title = LOCTEXT("VariantManagerMainTab", "Variant Manager");
	VariantManager->Icon = FSlateIcon(FName(TEXT("VariantManagerEditorStyle")), "VariantManager.Icon");
	VariantManager->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("VariantManager_VariantManagerMain")));
		}
	);
	OutCommands.Add(VariantManager);

	const TSharedPtr<FQuickCommandEntry> WorldSettings = MakeShared<FQuickCommandEntry>();
	WorldSettings->Title = NSLOCTEXT("LevelEditorTabs", "WorldSettings", "World Settings");
	WorldSettings->Tooltip = NSLOCTEXT("LevelEditorTabs", "WorldSettingsTooltipText", "Open the World Settings tab, in which global properties of the level can be viewed and edited.");
	WorldSettings->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.WorldProperties.Tab");
	WorldSettings->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("WorldSettingsTab")));
		}
	);
	OutCommands.Add(WorldSettings);

	return OutCommands;
}

#undef LOCTEXT_NAMESPACE