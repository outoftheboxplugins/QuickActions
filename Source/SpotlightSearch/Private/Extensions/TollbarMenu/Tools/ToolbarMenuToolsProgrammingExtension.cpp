// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuToolsProgrammingExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuToolsProgrammingExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* MainTabFileMenu = ToolMenus->ExtendMenu("MainFrame.MainMenu.Tools");
	FToolMenuSection* ProgrammingSection = MainTabFileMenu->FindSection("Programming");

	for (FToolMenuEntry& Block : ProgrammingSection->Blocks)
	{
		if (Block.Label.Get().IsEmpty() || Block.IsSubMenu())
		{
			continue;
		}

		const TSharedPtr<FQuickCommandEntry> BlockCommand = MakeShared<FQuickCommandEntry>(Block, Context);
		OutCommands.Emplace(BlockCommand);
	}

	return OutCommands;
}