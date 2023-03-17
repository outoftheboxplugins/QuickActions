// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuToolsToolsExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuToolsToolsExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;
	constexpr int32 NumFindInBlueprintsTabs = 4;
	for (int32 FindIdx = 0; FindIdx < NumFindInBlueprintsTabs; FindIdx++)
	{
		const TSharedPtr<FQuickCommandEntry> FindInBlueprintsTab = MakeShared<FQuickCommandEntry>();
		FindInBlueprintsTab->Title = FText::Format(NSLOCTEXT("FindInBlueprintManager", "GlobalFindResultsDisplayName", "Find in Blueprints {0}"), FText::AsNumber(FindIdx + 1));
		FindInBlueprintsTab->Tooltip = NSLOCTEXT("FindInBlueprintManager", "GlobalFindResultsMenuTooltipText", "Find references to functions, events and variables in all Blueprints.");
		FindInBlueprintsTab->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "BlueprintEditor.FindInBlueprints.MenuIcon");
		FindInBlueprintsTab->ExecuteCallback = FSimpleDelegate::CreateLambda(
			[FindIdx]()
			{
				const FName TabID = FName(*FString::Printf(TEXT("GlobalFindResults_%02d"), FindIdx + 1));
				FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TabID));
			}
		);

		OutCommands.Add(FindInBlueprintsTab);
	}

	const TSharedPtr<FQuickCommandEntry> CppHeaderPreview = MakeShared<FQuickCommandEntry>();
	CppHeaderPreview->Title = NSLOCTEXT("BlueprintHeaderViewApp", "TabTitle", "C++ Header Preview");
	CppHeaderPreview->Tooltip = NSLOCTEXT("BlueprintHeaderViewApp", "TooltipText", "Displays a Blueprint Class in C++ Header format.");
	CppHeaderPreview->Icon = FSlateIcon(FName(TEXT("HeaderViewStyle")), "Icons.HeaderView");
	CppHeaderPreview->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("BlueprintHeaderViewApp")));
		}
	);
	OutCommands.Add(CppHeaderPreview);

	const TSharedPtr<FQuickCommandEntry> CacheStatistics = MakeShared<FQuickCommandEntry>();
	CacheStatistics->Title = NSLOCTEXT("DerivedDataEditor", "DerivedDataCacheStatisticsTabTitle", "Cache Statistics");
	CacheStatistics->Tooltip = NSLOCTEXT("DerivedDataEditor", "DerivedDataCacheStatisticsTabToolTipText", "Derived Data Cache Statistics");
	CacheStatistics->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "DerivedData.Cache.Statistics");
	CacheStatistics->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("DerivedDataCacheStatistics")));
		}
	);
	OutCommands.Add(CacheStatistics);

	const TSharedPtr<FQuickCommandEntry> ClassViewer = MakeShared<FQuickCommandEntry>();
	ClassViewer->Title = NSLOCTEXT("ClassViewerApp", "TabTitle", "Class Viewer");
	ClassViewer->Tooltip = NSLOCTEXT("ClassViewerApp", "TooltipText", "Displays all classes that exist within this project.");
	ClassViewer->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassViewer.TabIcon");
	ClassViewer->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("ClassViewerApp")));
		}
	);
	OutCommands.Add(ClassViewer);

	const TSharedPtr<FQuickCommandEntry> CsvToSvg = MakeShared<FQuickCommandEntry>();
	CsvToSvg->Title = NSLOCTEXT("CSVtoSVGApp", "TabTitle", "CSV to SVG");
	CsvToSvg->Tooltip = NSLOCTEXT("CSVtoSVGApp", "TooltipText", "Tool for generating vector line graphs from comma-separated value files generated from CSV profiles.");
	CsvToSvg->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.UserDefinedStruct");
	CsvToSvg->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("CSVtoSVGApp")));
		}
	);
	OutCommands.Add(CsvToSvg);

	const TSharedPtr<FQuickCommandEntry> LocalizationDashboard = MakeShared<FQuickCommandEntry>();
	LocalizationDashboard->Title = NSLOCTEXT("LocalizationDashboard", "MainTabTitle", "Localization Dashboard");
	LocalizationDashboard->Tooltip = NSLOCTEXT("LocalizationDashboard", "LocalizationDashboardToolTip", "Open the Localization Dashboard for this Project.");
	LocalizationDashboard->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LocalizationDashboard.MenuIcon");
	LocalizationDashboard->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("LocalizationDashboard")));
		}
	);
	OutCommands.Add(LocalizationDashboard);

	const TSharedPtr<FQuickCommandEntry> MergeActors = MakeShared<FQuickCommandEntry>();
	MergeActors->Title = NSLOCTEXT("MergeActorsModule", "TabTitle", "Merge Actors");
	MergeActors->Tooltip = NSLOCTEXT("MergeActorsModule", "TooltipText", "Open the Merge Actors tab.");
	MergeActors->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "MergeActors.TabIcon");
	MergeActors->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("MergeActors")));
		}
	);
	OutCommands.Add(MergeActors);

	const TSharedPtr<FQuickCommandEntry> NaniteTools = MakeShared<FQuickCommandEntry>();
	NaniteTools->Title = NSLOCTEXT("NaniteToolsApp", "TabTitle", "Nanite Tools");
	NaniteTools->Tooltip = NSLOCTEXT("NaniteToolsApp", "TooltipText", "Tools for auditing and optimizing Nanite assets.");
	NaniteTools->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.UserDefinedStruct");
	NaniteTools->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("NaniteToolsApp")));
		}
	);
	OutCommands.Add(NaniteTools);

	const TSharedPtr<FQuickCommandEntry> ProjectLauncher = MakeShared<FQuickCommandEntry>();
	ProjectLauncher->Title = NSLOCTEXT("FProjectLauncherModule", "ProjectLauncherTabTitle", "Project Launcher");
	ProjectLauncher->Tooltip = NSLOCTEXT("FProjectLauncherModule", "ProjectLauncherTooltipText", "Open the Project Launcher tab.");
	ProjectLauncher->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Launcher.TabIcon");
	ProjectLauncher->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("ProjectLauncher")));
		}
	);
	OutCommands.Add(ProjectLauncher);

	const TSharedPtr<FQuickCommandEntry> ResourceUsage = MakeShared<FQuickCommandEntry>();
	ResourceUsage->Title = NSLOCTEXT("DerivedDataEditor", "DerivedDataResourceUsageTabTitle", "Resource Usage");
	ResourceUsage->Tooltip = NSLOCTEXT("DerivedDataEditor", "DerivedDataResourceUsageTabToolTipText", "Derived Data Resource Usage");
	ResourceUsage->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "DerivedData.ResourceUsage");
	ResourceUsage->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("DerivedDataResourceUsage")));
		}
	);
	OutCommands.Add(ResourceUsage);

	const TSharedPtr<FQuickCommandEntry> SessionFrontend = MakeShared<FQuickCommandEntry>();
	SessionFrontend->Title = NSLOCTEXT("FSessionFrontendModule", "FrontendTabTitle", "Session Frontend");
	SessionFrontend->Tooltip = NSLOCTEXT("FSessionFrontendModule", "FrontendTooltipText", "Open the Session Frontend tab.");
	SessionFrontend->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "SessionFrontEnd.TabIcon");
	SessionFrontend->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("SessionFrontend")));
		}
	);
	OutCommands.Add(SessionFrontend);

	const TSharedPtr<FQuickCommandEntry> StructViewer = MakeShared<FQuickCommandEntry>();
	StructViewer->Title = NSLOCTEXT("StructViewerApp", "TabTitle", "Struct Viewer");
	StructViewer->Tooltip = NSLOCTEXT("StructViewerApp", "TooltipText", "Displays all structs that exist within this project.");
	StructViewer->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.UserDefinedStruct");
	StructViewer->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("StructViewerApp")));
		}
	);
	OutCommands.Add(StructViewer);


	return OutCommands;
}