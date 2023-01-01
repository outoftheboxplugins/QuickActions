// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuWindowGetContentExtension.h"

#include <Interfaces/IMainFrameModule.h>

TArray<FQuickCommandEntry> UToolbarMenuWindowGetContentExtension::GetCommands()
{
	TArray<FQuickCommandEntry> OutCommands;

	IMainFrameModule& MainFrameModule = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	TSharedPtr<FUICommandList> MainFrameCommands = MainFrameModule.GetMainFrameCommandBindings();

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* MainTabFileMenu = ToolMenus->ExtendMenu("MainFrame.MainMenu.Window");
	FToolMenuSection* ContentSection = MainTabFileMenu->FindSection("GetContent");

	FToolMenuContext Context;
	Context.AppendCommandList(MainFrameCommands);

	for (FToolMenuEntry& Block : ContentSection->Blocks)
	{
		// TODO: This only works for the open Marketplace button, not for the Quixel bridge
		// NOTE: the block has no command list assigned, we temporarily assign the MainFrame list to access the FUIAction and revert it afterwards
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