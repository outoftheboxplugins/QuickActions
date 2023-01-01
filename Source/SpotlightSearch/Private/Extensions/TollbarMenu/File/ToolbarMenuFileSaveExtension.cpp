// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuFileSaveExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<FQuickCommandEntry> UToolbarMenuFileSaveExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<FQuickCommandEntry> OutCommands;

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* FileMenu = ToolMenus->FindMenu("MainFrame.MainMenu.File");

	FToolMenuSection* SaveSection = FileMenu->FindSection("FileSave");
	for (FToolMenuEntry& Block : SaveSection->Blocks)
	{
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

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	FQuickCommandEntry SaveCurrentLevel = FQuickCommandEntry(FLevelEditorCommands::Get().Save.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(SaveCurrentLevel);

	FQuickCommandEntry SaveCurrentLevelAs = FQuickCommandEntry(FLevelEditorCommands::Get().SaveAs.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(SaveCurrentLevelAs);

	return OutCommands;
}