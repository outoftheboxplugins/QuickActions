// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuHelpCommunityExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuHelpCommunityExtension::GetCommands(const FQuickCommandContext& Context)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UToolbarMenuHelpCommunityExtension::GetCommands);

	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	CollectActionsFromMenuSection(OutCommands, Context, "MainFrame.MainMenu.Help", "Community");	

	return OutCommands;
}