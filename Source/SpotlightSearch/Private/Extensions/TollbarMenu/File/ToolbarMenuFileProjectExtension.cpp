// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuFileProjectExtension.h"

TArray<FQuickCommandEntry> UToolbarMenuFileProjectExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<FQuickCommandEntry> OutCommands;

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* MainTabFileMenu = ToolMenus->ExtendMenu("MainFrame.MainTabMenu.File");
	FToolMenuSection* ProjectSection = MainTabFileMenu->FindSection("FileProject");

	for (FToolMenuEntry& Block : ProjectSection->Blocks)
	{
		TSharedPtr<const FUICommandList> OutCommandsList;
		if (const FUIAction* FoundAction = Block.GetActionForCommand(Context, OutCommandsList))
		{
			FQuickCommandEntry MenuEntry;
			MenuEntry.Title = Block.Label;
			MenuEntry.Tooltip = Block.ToolTip;
			MenuEntry.Icon = Block.Icon;
			MenuEntry.CanExecuteCallback = FoundAction->CanExecuteAction;
			MenuEntry.ExecuteCallback = FoundAction->ExecuteAction;

			OutCommands.Emplace(MenuEntry);
		}
	}

	return OutCommands;
}