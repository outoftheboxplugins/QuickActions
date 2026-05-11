// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuHelpSupportExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuHelpSupportExtension::GetCommands(const FQuickCommandContext& Context)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UToolbarMenuHelpSupportExtension::GetCommands);

	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;
	
	CollectActionsFromMenuSection(OutCommands, Context, "MainFrame.MainMenu.Help", "Support");	

	return OutCommands;
}