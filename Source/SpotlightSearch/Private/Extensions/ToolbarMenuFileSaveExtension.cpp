// Copyright Out-of-the-Box Plugins 2018-2021. All Rights Reserved.

#include "ToolbarMenuFileSaveExtension.h"

#include <Interfaces/IMainFrameModule.h>

namespace
{
	void GatherActionsFromMenuSection(TArray<FQuickCommandEntry>& OutEntries, FToolMenuSection& Section, TSharedRef<FUICommandList> CommandList)
	{
	}
} // namespace

TArray<FQuickCommandEntry> UToolbarMenuFileSaveExtension::GetCommands()
{
	TArray<FQuickCommandEntry> OutCommands;

	IMainFrameModule& MainFrameModule = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	TSharedPtr<const FUICommandList> MainFrameCommands = MainFrameModule.GetMainFrameCommandBindings();

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* FileMenu = ToolMenus->FindMenu("MainFrame.MainMenu.File");

	FToolMenuSection* SaveSection = FileMenu->FindSection("FileSave");
	for (FToolMenuEntry& Block : SaveSection->Blocks)
	{
		// NOTE: the FileSave block has no command list assigned, we temporarily assign the MainFrame list to access the FUIAction and revert it afterwards
		Block.SetCommandList(MainFrameCommands);
		if (const FUIAction* FoundAction = Block.GetActionForCommand(SaveSection->Context, MainFrameCommands))
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