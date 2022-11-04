// Copyright Out-of-the-Box Plugins 2018-2022. All Rights Reserved.

#pragma once

#include "EditorSubsystem.h"

#include "SpotlightDiscoverySubsystem.generated.h"

struct FQuickCommandEntry
{
	FQuickCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList);

	TAttribute<FText> Title;
	TAttribute<FText> Tooltip;

	FSlateIcon Icon;

	FSimpleDelegate ExecuteCallback;
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
};
