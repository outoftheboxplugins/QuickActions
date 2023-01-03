// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuToolsSourceControlExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuToolsSourceControlExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const TSharedPtr<FQuickCommandEntry> ViewChangelists = MakeShared<FQuickCommandEntry>();
	ViewChangelists->Title = NSLOCTEXT("SourceControlWindows", "ChangelistsTabTitle", "View Changelists");
	ViewChangelists->Tooltip = NSLOCTEXT("SourceControlWindows", "ChangelistsTabTooltip", "Opens a dialog displaying current changelists.");
	ViewChangelists->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "SourceControl.ChangelistsTab");
	ViewChangelists->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("SourceControlChangelists")));
		}
	);
	OutCommands.Add(ViewChangelists);

	return OutCommands;
}