// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuToolsInstrumentationExtension.h"

#include <LevelEditor.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuToolsInstrumentationExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const TSharedPtr<FQuickCommandEntry> BlueprintDebugger = MakeShared<FQuickCommandEntry>();
	BlueprintDebugger->Title = NSLOCTEXT("BlueprintDebugger", "TabTitle", "Blueprint Debugger");
	BlueprintDebugger->Tooltip = NSLOCTEXT("BlueprintDebugger", "TooltipText", "Open the Blueprint Debugger tab.");
	BlueprintDebugger->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "BlueprintDebugger.TabIcon");
	BlueprintDebugger->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("BlueprintDebugger")));
		}
	);
	OutCommands.Add(BlueprintDebugger);

	const TSharedPtr<FQuickCommandEntry> CollisionAnalyzer = MakeShared<FQuickCommandEntry>();
	CollisionAnalyzer->Title = NSLOCTEXT("CollisionAnalyzerModule", "TabTitle", "Collision Analyzer");
	CollisionAnalyzer->Tooltip = NSLOCTEXT("CollisionAnalyzerModule", "TooltipText", "Open the Collision Analyzer tab.");
	CollisionAnalyzer->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "CollisionAnalyzer.TabIcon");
	CollisionAnalyzer->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("CollisionAnalyzerApp")));
		}
	);
	OutCommands.Add(CollisionAnalyzer);

	const TSharedPtr<FQuickCommandEntry> DebugTools = MakeShared<FQuickCommandEntry>();
	DebugTools->Title = NSLOCTEXT("Toolbox", "DebugTools", "Debug Tools");
	DebugTools->Tooltip = NSLOCTEXT("Toolbox", "DebugToolsTooltipText", "Open the Debug Tools tab.");
	DebugTools->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Debug");
	DebugTools->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("DebugTools")));
		}
	);
	OutCommands.Add(DebugTools);

	const TSharedPtr<FQuickCommandEntry> Modules = MakeShared<FQuickCommandEntry>();
	Modules->Title = NSLOCTEXT("Toolbox", "Modules", "Modules");
	Modules->Tooltip = NSLOCTEXT("Toolbox", "ModulesTooltipText", "Open the Modules tab.");
	Modules->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Modules");
	Modules->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("Modules")));
		}
	);
	OutCommands.Add(Modules);

	const TSharedPtr<FQuickCommandEntry> NiagaraDebugger = MakeShared<FQuickCommandEntry>();
	NiagaraDebugger->Title = NSLOCTEXT("UnrealEditor", "NiagaraDebuggerTab", "Niagara Debugger");
	NiagaraDebugger->Tooltip = NSLOCTEXT("UnrealEditor", "NiagaraDebuggerTooltipText", "Open the Niagara Debugger Tab.");
	NiagaraDebugger->Icon = FSlateIcon(FName(TEXT("NiagaraEditorStyle")), "Tab.Debugger");
	NiagaraDebugger->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("NiagaraDebugger")));
		}
	);
	OutCommands.Add(NiagaraDebugger);

	const TSharedPtr<FQuickCommandEntry> PixelInspector = MakeShared<FQuickCommandEntry>();
	PixelInspector->Title = NSLOCTEXT("LevelEditorTabs", "LevelEditorPixelInspector", "Pixel Inspector");
	PixelInspector->Tooltip = NSLOCTEXT("LevelEditorTabs", "LevelEditorPixelInspectorTooltipText", "Open the viewport pixel inspector tool.");
	PixelInspector->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "PixelInspector.TabIcon");
	PixelInspector->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("LevelEditorPixelInspector")));
		}
	);
	OutCommands.Add(PixelInspector);

	const TSharedPtr<FQuickCommandEntry> StylusInputDebugger = MakeShared<FQuickCommandEntry>();
	StylusInputDebugger->Title = NSLOCTEXT("FStylusInputModule", "DebugTabTitle", "Stylus Input Debug");
	StylusInputDebugger->Tooltip = NSLOCTEXT("FStylusInputModule", "DebugTabTooltip", "Debug panel to display current values of stylus inputs.");
	StylusInputDebugger->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "StylusInputDebug.TabIcon");
	StylusInputDebugger->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("StylusInputDebug")));
		}
	);
	OutCommands.Add(StylusInputDebugger);

	const TSharedPtr<FQuickCommandEntry> VisualLogger = MakeShared<FQuickCommandEntry>();
	VisualLogger->Title = NSLOCTEXT("LogVisualizerApp", "TabTitle", "Visual Logger");
	VisualLogger->Tooltip = NSLOCTEXT("LogVisualizerApp", "TooltipText", "Opens Visual Logger tool.");
	VisualLogger->Icon = FSlateIcon(FName(TEXT("LogVisualizerStyle")), "LogVisualizerApp.TabIcon");
	VisualLogger->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("VisualLogger")));
		}
	);
	OutCommands.Add(VisualLogger);

	const TSharedPtr<FQuickCommandEntry> WidgetReflector = MakeShared<FQuickCommandEntry>();
	WidgetReflector->Title = NSLOCTEXT("FSlateReflectorModuleImpl", "WidgetReflectorTitle", "Widget Reflector");
	WidgetReflector->Tooltip = NSLOCTEXT("FSlateReflectorModuleImpl", "WidgetReflectorTooltipText", "Open the Widget Reflector tab.");
	WidgetReflector->Icon = FSlateIcon(FName(TEXT("WidgetReflectorStyleStyle")), "WidgetReflector.TabIcon");
	WidgetReflector->InputText = FInputChord(FInputChord(EModifierKey::Shift | EModifierKey::Control, EKeys::W)).GetInputText();
	WidgetReflector->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("WidgetReflector")));
		}
	);
	OutCommands.Add(WidgetReflector);

	const TSharedPtr<FQuickCommandEntry> ProfileDataVisualizer = MakeShared<FQuickCommandEntry>();
	ProfileDataVisualizer->Title = NSLOCTEXT("ProfileVisualizerModule", "TabTitle", "Profile Data Visualizer");
	ProfileDataVisualizer->Tooltip = NSLOCTEXT("ProfileVisualizerModule", "TooltipText", "Open the Profile Data Visualizer tab.");
	ProfileDataVisualizer->Icon = FSlateIcon(FAppStyle::Get().GetStyleSetName(), "Profiler.Tab");
	ProfileDataVisualizer->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("VisualizerSpawnPoint")));
		}
	);
	OutCommands.Add(ProfileDataVisualizer);

	const TSharedPtr<FQuickCommandEntry> TraceDataFiltering = MakeShared<FQuickCommandEntry>();
	TraceDataFiltering->Title = NSLOCTEXT("FTraceInsightsModule", "FilteringTabTitle", "Trace Data Filtering");
	TraceDataFiltering->Tooltip = NSLOCTEXT("FTraceInsightsModule", "FilteringTabTooltip", "Opens the Trace Data Filtering tab, allows for setting Trace Channel states");
	TraceDataFiltering->Icon = FSlateIcon(FName(TEXT("EventFilter")), "EventFilter.TabIcon");
	TraceDataFiltering->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("TraceDataFiltering")));
		}
	);
	OutCommands.Add(TraceDataFiltering);

	const TSharedPtr<FQuickCommandEntry> AssetAudit = MakeShared<FQuickCommandEntry>();
	AssetAudit->Title = NSLOCTEXT("AssetManagerEditor", "AssetAuditTitle", "Asset Audit");
	AssetAudit->Tooltip = NSLOCTEXT("AssetManagerEditor", "AssetAuditTooltip", "Open Asset Audit window, allows viewing detailed information about assets.");
	AssetAudit->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Audit");
	AssetAudit->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("AssetAudit")));
		}
	);
	OutCommands.Add(AssetAudit);

	const TSharedPtr<FQuickCommandEntry> MaterialAnalyzer = MakeShared<FQuickCommandEntry>();
	MaterialAnalyzer->Title = NSLOCTEXT("MaterialAnalyzer", "TabTitle", "Material Analyzer");
	MaterialAnalyzer->Tooltip = NSLOCTEXT("MaterialAnalyzer", "TooltipText", "Opens Material Analyzer tool.");
	MaterialAnalyzer->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "MaterialEditor.ToggleMaterialStats.Tab");
	MaterialAnalyzer->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("MaterialAnalyzer")));
		}
	);
	OutCommands.Add(MaterialAnalyzer);

	const TSharedPtr<FQuickCommandEntry> Statistics = MakeShared<FQuickCommandEntry>();
	Statistics->Title = NSLOCTEXT("LevelEditorTabs", "LevelEditorStatsViewer", "Statistics");
	Statistics->Tooltip = NSLOCTEXT("LevelEditorTabs", "LevelEditorStatsViewerTooltipText", "Open the Statistics tab, in order to see data pertaining to lighting, textures and primitives.");
	Statistics->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.StatsViewer");
	Statistics->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
			const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
			LevelEditorTabManager->TryInvokeTab(FTabId(TEXT("LevelEditorStatsViewer")));
		}
	);
	OutCommands.Add(Statistics);

	const TSharedPtr<FQuickCommandEntry> VirtualAssets = MakeShared<FQuickCommandEntry>();
	VirtualAssets->Title = NSLOCTEXT("VirtualizationEditor", "VirtualAssetsStatisticsTabTitle", "Virtual Assets");
	VirtualAssets->Tooltip = NSLOCTEXT("VirtualizationEditor", "VirtualAssetsStatisticsTabToolTipText", "Virtual Assets  Statistics");
	VirtualAssets->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "DerivedData.Cache.Statistics");
	VirtualAssets->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("VirtualAssetsStatistics")));
		}
	);
	OutCommands.Add(VirtualAssets);

	const TSharedPtr<FQuickCommandEntry> DeviceManager = MakeShared<FQuickCommandEntry>();
	DeviceManager->Title = NSLOCTEXT("FDeviceManagerModule", "DeviceManagerTabTitle", "Device Manager");
	DeviceManager->Tooltip = NSLOCTEXT("FDeviceManagerModule", "DeviceManagerTooltipText", "View and manage connected devices.");
	DeviceManager->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "DeviceDetails.TabIcon");
	DeviceManager->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("DeviceManager")));
		}
	);
	OutCommands.Add(DeviceManager);

	const TSharedPtr<FQuickCommandEntry> DeviceProfiles = MakeShared<FQuickCommandEntry>();
	DeviceProfiles->Title = NSLOCTEXT("DeviceProfileEditor", "DeviceProfileEditorTitle", "Device Profiles");
	DeviceProfiles->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "DeviceDetails.Tabs.ProfileEditor");
	DeviceProfiles->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("DeviceProfileEditor")));
		}
	);
	OutCommands.Add(DeviceProfiles);

	return OutCommands;
}