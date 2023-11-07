// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuFileExitExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuFileExitExtension::GetCommands(const FQuickCommandContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

#if !PLATFORM_MAC // Handled by app's menu in menu bar
	CollectActionsFromMenuSection(OutCommands, Context, "MainFrame.MainTabMenu.File", "Exit");
#endif

	return OutCommands;
}