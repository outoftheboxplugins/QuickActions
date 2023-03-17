// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuHelpApplicationExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuHelpApplicationExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	CollectActionsFromMenuSection(OutCommands, Context, "MainFrame.MainMenu.Help", "HelpApplication");	

	return OutCommands;
}