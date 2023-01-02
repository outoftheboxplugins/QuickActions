// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuWindowLayoutExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuWindowLayoutExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* MainTabFileMenu = ToolMenus->ExtendMenu("MainFrame.MainMenu.Window");
	FToolMenuSection* WindowLayout = MainTabFileMenu->FindSection("WindowLayout");

	for (FToolMenuEntry& Block : WindowLayout->Blocks)
	{
		if (Block.IsSubMenu())
		{
			Block.SubMenuData.ConstructMenu.NewToolMenu
		}
		TSharedPtr<const FUICommandList> OutCommandsList;
		if (const FUIAction* FoundAction = Block.GetActionForCommand(Context, OutCommandsList))
		{
			TSharedPtr<FQuickCommandEntry> MenuEntry = MakeShared<FQuickCommandEntry>();
			MenuEntry->Title = Block.Label;
			MenuEntry->Tooltip = Block.ToolTip;
			MenuEntry->Icon = Block.Icon;
			MenuEntry->CanExecuteCallback = FoundAction->CanExecuteAction;
			MenuEntry->ExecuteCallback = FoundAction->ExecuteAction;

			OutCommands.Emplace(MenuEntry);
		}
	}


	// FToolMenuSection* UserLayout = MainTabFileMenu->FindSection("UserDefaultLayouts");
	// for (FToolMenuEntry& Block : UserLayout->Blocks)
	//{
	//	TSharedPtr<const FUICommandList> OutCommandsList;
	//	if (const FUIAction* FoundAction = Block.GetActionForCommand(Context, OutCommandsList))
	//	{
	//		TSharedPtr<FQuickCommandEntry> MenuEntry = MakeShared<FQuickCommandEntry>();
	//		MenuEntry->Title = Block.Label;
	//		MenuEntry->Tooltip = Block.ToolTip;
	//		MenuEntry->Icon = Block.Icon;
	//		MenuEntry->CanExecuteCallback = FoundAction->CanExecuteAction;
	//		MenuEntry->ExecuteCallback = FoundAction->ExecuteAction;

	//		OutCommands.Emplace(MenuEntry);
	//	}
	//}

	return OutCommands;
}