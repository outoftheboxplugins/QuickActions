// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuFileExitExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuFileExitExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	CollectActionsFromMenuSection(OutCommands, Context, "MainFrame.MainTabMenu.File", "Exit");	
	
	return OutCommands;
}