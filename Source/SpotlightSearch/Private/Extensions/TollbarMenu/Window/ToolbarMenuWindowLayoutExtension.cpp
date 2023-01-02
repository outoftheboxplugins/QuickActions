// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuWindowLayoutExtension.h"

namespace
{
	TSharedPtr<FQuickCommandEntry> BlockToCommand(const FToolMenuEntry& Block, const FToolMenuContext& Context)
	{
		TSharedPtr<FQuickCommandEntry> MenuEntry = MakeShared<FQuickCommandEntry>();
		TSharedPtr<const FUICommandList> OutCommandsList;
		if (const FUIAction* FoundAction = Block.GetActionForCommand(Context, OutCommandsList))
		{
			MenuEntry->Title = Block.Label;
			MenuEntry->Tooltip = Block.ToolTip;
			MenuEntry->Icon = Block.Icon;
			MenuEntry->CanExecuteCallback = FoundAction->CanExecuteAction;
			MenuEntry->ExecuteCallback = FoundAction->ExecuteAction;
		}
		return MenuEntry;
	}
} // namespace

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuWindowLayoutExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* MainTabFileMenu = ToolMenus->ExtendMenu("MainFrame.MainMenu.Window");
	FToolMenuSection* WindowLayout = MainTabFileMenu->FindSection("WindowLayout");

	for (FToolMenuEntry& Block : WindowLayout->Blocks)
	{
		OutCommands.Emplace(BlockToCommand(Block, Context));
	}

	return OutCommands;
}