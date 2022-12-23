// Copyright Out-of-the-Box Plugins 2018-2022. All Rights Reserved.

#pragma once

#include <EditorSubsystem.h>

#include "QuickMenuExtension.h"

#include "QuickMenuDiscoverySubsystem.generated.h"

/**
 *
 */
UCLASS()
class SPOTLIGHTSEARCH_API UQuickMenuDiscoverySubsystem : public UEditorSubsystem
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