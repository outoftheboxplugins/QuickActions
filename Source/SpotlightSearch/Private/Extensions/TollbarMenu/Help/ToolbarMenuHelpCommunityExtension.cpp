// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuHelpCommunityExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuHelpCommunityExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	CollectActionsFromMenuSection(OutCommands, Context, "MainFrame.MainMenu.Help", "Community");	

	return OutCommands;
}