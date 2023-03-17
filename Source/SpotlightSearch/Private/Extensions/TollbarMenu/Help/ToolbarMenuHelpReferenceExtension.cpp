// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuHelpReferenceExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuHelpReferenceExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;
	
	CollectActionsFromMenuSection(OutCommands, Context, "MainFrame.MainMenu.Help", "Reference");	

	return OutCommands;
}