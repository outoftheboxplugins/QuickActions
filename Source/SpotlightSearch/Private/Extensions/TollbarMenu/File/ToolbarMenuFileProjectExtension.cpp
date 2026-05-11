// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuFileProjectExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuFileProjectExtension::GetCommands(const FQuickCommandContext& Context)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UToolbarMenuFileProjectExtension::GetCommands);

	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	CollectActionsFromMenuSection(OutCommands, Context, "MainFrame.MainTabMenu.File", "FileProject");	
	
	return OutCommands;
}