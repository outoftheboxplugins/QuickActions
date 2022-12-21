// Copyright Out-of-the-Box Plugins 2018-2022. All Rights Reserved.

#pragma once

#include "EditorSubsystem.h"
#include "SpotlightDiscoverySubsystem.generated.h"

struct FQuickCommandEntry
{
	// TODO: Check if we need to default the move constructor as well
	FQuickCommandEntry() = default;
	FQuickCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList);

	TAttribute<FText> Title;
	TAttribute<FText> Tooltip;

	FSlateIcon Icon;

	FSimpleDelegate ExecuteCallback;
	// TODO: Change this delegate type to something nice like: FCanExecuteAction
	TDelegate<bool()> CanExecuteCallback;
};

/**
 *
 */
UCLASS()
class SPOTLIGHTSEARCH_API USpotlightDiscoverySubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	TMulticastDelegate<void(TArray<FQuickCommandEntry>& OutCommands)> OnDiscoverCommands;

	TArray<FQuickCommandEntry> GetAllCommands() const;

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void GatherCommandsInternal(TArray<FQuickCommandEntry>& OutCommands) const;

	// TODO: The populate commands should be refactored into classes similar to UCheatManagerExtensions and automatically gather
	void PopulateTutorials(TArray<FQuickCommandEntry>& OutCommands) const;
	void PopulateMenuEntries(TArray<FQuickCommandEntry>& OutCommands) const;
};
