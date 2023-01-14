// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuHelpSupportExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuHelpSupportExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;
	
	CollectActionsFromMenuSection(OutCommands, Context, "MainFrame.MainMenu.Help", "Support");	

	return OutCommands;
}