// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "QuickMenuExtension.h"

#define LOCTEXT_NAMESPACE "QuickActions"

FQuickCommandEntry::FQuickCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList)
{
	Title = Command->GetLabel();
	Tooltip = Command->GetDescription();
	InputText = Command->GetInputText();
	Icon = Command->GetIcon();

	// TODO: Refactor this to take in a context and use InContext.GetActionForCommand(Command, OutCommandList);
	const FUIAction* UIAction = CommandList->GetActionForCommand(Command);
	if (ensure(UIAction))
	{
		ExecuteCallback = UIAction->ExecuteAction;
		CanExecuteCallback = UIAction->CanExecuteAction;
	}
}

FQuickCommandEntry::FQuickCommandEntry(const FToolMenuEntry& Block, const FToolMenuContext& Context)
{
	Title = Block.Label;
	Tooltip = Block.ToolTip;
	Icon = Block.Icon;

	TSharedPtr<const FUICommandList> OutCommandsList;

	const FUIAction* FoundAction = Block.GetActionForCommand(Context, OutCommandsList);
	if (ensure(FoundAction))
	{
		CanExecuteCallback = FoundAction->CanExecuteAction;
		ExecuteCallback = FoundAction->ExecuteAction;
	}
}

bool FQuickCommandEntry::IsAllowedToExecute() const
{
	if (!CanExecuteCallback.IsBound())
	{
		return true;
	}

	return CanExecuteCallback.Execute();
}
FString FQuickCommandEntry::GetCommandName() const
{
	return Title.Get().ToString();
}

FString FQuickCommandEntry::GetUniqueCommandName() const
{
	return FMD5::HashAnsiString(*GetCommandName());
}

FQuickSwitchCommandEntry::FQuickSwitchCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList, bool bIsEnabled) : FQuickCommandEntry(Command, CommandList)
{
	SwitchTitle = Title;

	const FText ActionPrefix = bIsEnabled ? LOCTEXT("Disable", "Disable:") : LOCTEXT("Enable", "Enable:");
	Title = FText::Format(INVTEXT("{0} {1}"), ActionPrefix, Title.Get());

	// TODO: Find a better icon for this. Hopefully a custom one.
	Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), bIsEnabled ? "FBXIcon.ReimportCompareRemoved" : "FBXIcon.ReimportCompareAdd");
}

FString FQuickSwitchCommandEntry::GetUniqueCommandName() const
{
	const FString UniqueSwitchTitle = SwitchTitle.Get().ToString();
	return FMD5::HashAnsiString(*UniqueSwitchTitle);
}

void UQuickMenuExtension::CollectActionsFromMenuSection(TArray<TSharedPtr<FQuickCommandEntry>>& OutCommands, const FToolMenuContext& Context, FName MenuName, FName SectionName) const
{
	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* FileMenu = ToolMenus->FindMenu(MenuName);

	FToolMenuSection* Section = FileMenu->FindSection(SectionName);
	for (FToolMenuEntry& Block : Section->Blocks)
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
}

#undef LOCTEXT_NAMESPACE