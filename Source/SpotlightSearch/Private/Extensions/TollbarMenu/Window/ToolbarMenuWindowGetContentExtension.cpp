// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuWindowGetContentExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuWindowGetContentExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	CollectActionsFromMenuSection(OutCommands, Context, "MainFrame.MainMenu.Window", "GetContent");
	
	return OutCommands;
}