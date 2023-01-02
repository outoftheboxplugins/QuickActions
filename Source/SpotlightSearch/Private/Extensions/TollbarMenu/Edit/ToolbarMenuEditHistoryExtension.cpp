// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuEditHistoryExtension.h"

#include <Framework/Commands/GenericCommands.h>
#include <IUndoHistoryEditorModule.h>
#include <Interfaces/IMainFrameModule.h>

#define LOCTEXT_NAMESPACE "QuickActions"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuEditHistoryExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	IMainFrameModule& MainFrameModule = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	TSharedRef<FUICommandList> MainFrameCommands = MainFrameModule.GetMainFrameCommandBindings();

	const TSharedPtr<FQuickCommandEntry> Undo = MakeShared<FQuickCommandEntry>(FGenericCommands::Get().Undo.ToSharedRef(), MainFrameCommands);
	OutCommands.Add(Undo);

	const TSharedPtr<FQuickCommandEntry> Redo = MakeShared<FQuickCommandEntry>(FGenericCommands::Get().Redo.ToSharedRef(), MainFrameCommands);
	OutCommands.Add(Redo);

	const TSharedPtr<FQuickCommandEntry> UndoHistory = MakeShared<FQuickCommandEntry>();
	UndoHistory->Title = LOCTEXT("UndoHistoryTabTitle", "Undo History");
	UndoHistory->Tooltip = LOCTEXT("UndoHistoryTooltipText", "View the entire undo history.");
	UndoHistory->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "UndoHistory.TabIcon");
	UndoHistory->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			IUndoHistoryEditorModule::Get().ExecuteOpenUndoHistory();
		}
	);
	OutCommands.Add(UndoHistory);

	return OutCommands;
}

#undef LOCTEXT_NAMESPACE