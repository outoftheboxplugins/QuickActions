// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuToolsSourceControlExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuToolsSourceControlExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* MainTabFileMenu = ToolMenus->ExtendMenu("MainFrame.MainMenu.Tools");
	FToolMenuSection* SourceControlSection = MainTabFileMenu->FindSection("Source Control");

	// TODO: This is missing the entries from the dynamic section (Connect to source control + Change source control settings)
	for (FToolMenuEntry& Block : SourceControlSection->Blocks)
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