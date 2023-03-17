// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuEditEditExtension.h"

#include <Framework/Commands/GenericCommands.h>
#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuEditEditExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> Cut = MakeShared<FQuickCommandEntry>(FGenericCommands::Get().Cut.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(Cut);

	const TSharedPtr<FQuickCommandEntry> Copy = MakeShared<FQuickCommandEntry>(FGenericCommands::Get().Copy.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(Copy);

	const TSharedPtr<FQuickCommandEntry> Paste = MakeShared<FQuickCommandEntry>(FGenericCommands::Get().Paste.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(Paste);

	const TSharedPtr<FQuickCommandEntry> Duplicate = MakeShared<FQuickCommandEntry>(FGenericCommands::Get().Duplicate.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(Duplicate);

	const TSharedPtr<FQuickCommandEntry> Delete = MakeShared<FQuickCommandEntry>(FGenericCommands::Get().Delete.ToSharedRef(), LevelEditorCommands);
	OutCommands.Add(Delete);

	return OutCommands;
}