// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuHelpSupportExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuHelpSupportExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* FileMenu = ToolMenus->FindMenu("MainFrame.MainMenu.Help");

	FToolMenuSection* SupportSection = FileMenu->FindSection("Support");
	for (FToolMenuEntry& Block : SupportSection->Blocks)
	{
		TSharedPtr<const FUICommandList> OutCommandsList;
		if (const FUIAction* FoundAction = Block.GetActionForCommand(Context, OutCommandsList))
		{
			const TSharedPtr<FQuickCommandEntry> MenuEntry = MakeShared<FQuickCommandEntry>();
			MenuEntry->Title = Block.Label;
			MenuEntry->Tooltip = Block.ToolTip;
			MenuEntry->Icon = Block.Icon;
			MenuEntry->CanExecuteCallback = FoundAction->CanExecuteAction;
			MenuEntry->ExecuteCallback = FoundAction->ExecuteAction;

			OutCommands.Emplace(MenuEntry);
		}
	}

	return OutCommands;
}