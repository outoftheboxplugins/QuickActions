// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuFileSaveExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuFileSaveExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* FileMenu = ToolMenus->FindMenu("MainFrame.MainMenu.File");

	FToolMenuSection* SaveSection = FileMenu->FindSection("FileSave");
	for (FToolMenuEntry& Block : SaveSection->Blocks)
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

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	TSharedPtr<FQuickCommandEntry> SaveCurrentLevel = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().Save.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(SaveCurrentLevel);

	TSharedPtr<FQuickCommandEntry> SaveCurrentLevelAs = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SaveAs.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(SaveCurrentLevelAs);

	return OutCommands;
}