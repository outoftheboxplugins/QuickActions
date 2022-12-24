// Copyright Out-of-the-Box Plugins 2018-2021. All Rights Reserved.

#include "ToolbarMenuEditEditExtension.h"

#include <Framework/Commands/GenericCommands.h>
#include <Interfaces/IMainFrameModule.h>

TArray<FQuickCommandEntry> UToolbarMenuEditEditExtension::GetCommands()
{
	TArray<FQuickCommandEntry> OutCommands;

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* MainTabEditMenu = ToolMenus->ExtendMenu("LevelEditor.MainMenu.Edit");
	FToolMenuSection* EditSection = MainTabEditMenu->FindSection("EditMain");

	return OutCommands;

	for (FToolMenuEntry& Block : EditSection->Blocks)
	{
		TSharedPtr<const FUICommandList> EmptyList;
		const FUIAction* Action = Block.GetActionForCommand(EditSection->Context, EmptyList);

		FQuickCommandEntry NewEntry;

		NewEntry.Title = Block.Label;
		NewEntry.Tooltip = Block.ToolTip;
		NewEntry.Icon = Block.Icon;
		NewEntry.CanExecuteCallback = Action->CanExecuteAction;
		NewEntry.ExecuteCallback = Action->ExecuteAction;

		OutCommands.Add(NewEntry);
	}


	// IMainFrameModule& MainFrameModule = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	// TSharedRef<FUICommandList> MainFrameCommands = MainFrameModule.GetMainFrameCommandBindings();

	// FQuickCommandEntry Cut = FQuickCommandEntry(FGenericCommands::Get().Cut.ToSharedRef(), MainFrameCommands);
	// OutCommands.Add(Cut);

	// FQuickCommandEntry Copy = FQuickCommandEntry(FGenericCommands::Get().Copy.ToSharedRef(), MainFrameCommands);
	// OutCommands.Add(Copy);

	// FQuickCommandEntry Paste = FQuickCommandEntry(FGenericCommands::Get().Paste.ToSharedRef(), MainFrameCommands);
	// OutCommands.Add(Paste);

	// FQuickCommandEntry Duplicate = FQuickCommandEntry(FGenericCommands::Get().Duplicate.ToSharedRef(), MainFrameCommands);
	// OutCommands.Add(Duplicate);

	// FQuickCommandEntry Delete = FQuickCommandEntry(FGenericCommands::Get().Delete.ToSharedRef(), MainFrameCommands);
	// OutCommands.Add(Delete);

	return OutCommands;
}