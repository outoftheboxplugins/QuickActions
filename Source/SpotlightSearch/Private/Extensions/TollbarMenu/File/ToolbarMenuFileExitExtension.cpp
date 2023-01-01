// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuFileExitExtension.h"

#include <Interfaces/IMainFrameModule.h>

TArray<FQuickCommandEntry> UToolbarMenuFileExitExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<FQuickCommandEntry> OutCommands;

	IMainFrameModule& MainFrameModule = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	TSharedPtr<const FUICommandList> MainFrameCommands = MainFrameModule.GetMainFrameCommandBindings();

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* MainTabFileMenu = ToolMenus->ExtendMenu("MainFrame.MainTabMenu.File");
	FToolMenuSection* ExitSection = MainTabFileMenu->FindSection("Exit");

	for (FToolMenuEntry& Block : ExitSection->Blocks)
	{
		// NOTE: the block has no command list assigned, we temporarily assign the MainFrame list to access the FUIAction and revert it afterwards
		Block.SetCommandList(MainFrameCommands);
		if (const FUIAction* FoundAction = Block.GetActionForCommand(ExitSection->Context, MainFrameCommands))
		{
			FQuickCommandEntry MenuEntry;
			MenuEntry.Title = Block.Label;
			MenuEntry.Tooltip = Block.ToolTip;
			MenuEntry.Icon = Block.Icon;
			MenuEntry.CanExecuteCallback = FoundAction->CanExecuteAction;
			MenuEntry.ExecuteCallback = FoundAction->ExecuteAction;

			OutCommands.Emplace(MenuEntry);
		}
		Block.SetCommandList({});
	}

	return OutCommands;
}