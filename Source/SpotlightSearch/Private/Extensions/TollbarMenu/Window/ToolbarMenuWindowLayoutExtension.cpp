// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuWindowLayoutExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuWindowLayoutExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* MainTabFileMenu = ToolMenus->ExtendMenu("MainFrame.MainMenu.Window");
	FToolMenuSection* WindowLayoutSection = MainTabFileMenu->FindSection("WindowLayout");

	for (FToolMenuEntry& Block : WindowLayoutSection->Blocks)
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