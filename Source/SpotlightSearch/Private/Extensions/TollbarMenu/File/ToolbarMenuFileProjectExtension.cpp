// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuFileProjectExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuFileProjectExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	CollectActionsFromMenuSection(OutCommands, Context, "MainFrame.MainTabMenu.File", "FileProject");	
	
	return OutCommands;
}