// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuHelpReferenceExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuHelpReferenceExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* FileMenu = ToolMenus->FindMenu("MainFrame.MainMenu.Help");

	FToolMenuSection* ReferenceSection = FileMenu->FindSection("Reference");
	for (FToolMenuEntry& Block : ReferenceSection->Blocks)
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