// Fill out your copyright notice in the Description page of Project Settings.

#include "QuickMenuDiscoverySubsystem.h"

#include <Interfaces/IMainFrameModule.h>

#define LOCTEXT_NAMESPACE "LevelEditorMenu"

FQuickCommandEntry::FQuickCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList)
{
	Title = Command->GetLabel();
	Tooltip = Command->GetDescription();
	Icon = Command->GetIcon();

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

TArray<TSharedPtr<FQuickCommandEntry>> UQuickMenuDiscoverySubsystem::GetAllCommands() const
{
	TArray<TSharedPtr<FQuickCommandEntry>> Result;

	GatherCommandsInternal(Result);
	OnDiscoverCommands.Broadcast(Result);

	return Result;
}

void UQuickMenuDiscoverySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UQuickMenuDiscoverySubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UQuickMenuDiscoverySubsystem::GatherCommandsInternal(TArray<TSharedPtr<FQuickCommandEntry>>& OutCommands) const
{
	TArray<UQuickMenuExtension*> Extensions;
	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* CurrentClass = (*It);

		if (CurrentClass->IsChildOf(UQuickMenuExtension::StaticClass()) && !(CurrentClass->HasAnyClassFlags(CLASS_Abstract)))
		{
			UQuickMenuExtension* QuickMenuExtension = Cast<UQuickMenuExtension>(CurrentClass->GetDefaultObject());
			if (QuickMenuExtension->ShouldShow())
			{
				Extensions.Add(QuickMenuExtension);
			}
		}
	}

	Extensions.Sort(
		[](const UQuickMenuExtension& A, const UQuickMenuExtension& B)
		{
			return A.GetPriority() > B.GetPriority();
		}
	);

	IMainFrameModule& MainFrameModule = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	const TSharedPtr<FUICommandList> MainFrameCommands = MainFrameModule.GetMainFrameCommandBindings();

	FToolMenuContext Context;
	Context.AppendCommandList(MainFrameCommands);

	for (UQuickMenuExtension* Extension : Extensions)
	{
		OutCommands.Append(Extension->GetCommands(Context));
	}
	PopulateMenuEntries(OutCommands);
}

void UQuickMenuDiscoverySubsystem::PopulateMenuEntries(TArray<TSharedPtr<FQuickCommandEntry>>& OutCommands) const
{
}

#undef LOCTEXT_NAMESPACE