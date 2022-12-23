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

	void PopulateMenuEntries(TArray<FQuickCommandEntry>& OutCommands) const;
};