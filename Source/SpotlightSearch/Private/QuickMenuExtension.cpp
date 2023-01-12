// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "QuickMenuExtension.h"

#define LOCTEXT_NAMESPACE "QuickActions"

FQuickCommandEntry::FQuickCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList)
{
	Title = Command->GetLabel();
	Tooltip = Command->GetDescription();
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
	// TODO: Consider if we should ensure FoundAction similar to the constructor above
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

FQuickSwitchCommandEntry::FQuickSwitchCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList, bool bIsEnabled) : FQuickCommandEntry(Command, CommandList)
{
	const FText ActionPrefix = bIsEnabled ? LOCTEXT("Disable", "Disable:") : LOCTEXT("Enable", "Enable:");
	Title = FText::Format(INVTEXT("{0} {1}"), ActionPrefix, Title.Get());
	Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), bIsEnabled ? "FBXIcon.ReimportCompareRemoved" : "FBXIcon.ReimportCompareAdd");
}

#undef LOCTEXT_NAMESPACE