// Copyright Out-of-the-Box Plugins 2018-2022. All Rights Reserved.

#pragma once

#include <EditorSubsystem.h>

#include "QuickMenuExtension.h"

#include "QuickMenuDiscoverySubsystem.generated.h"

/**
 *
 */
UCLASS()
class QUICKMENU_API UQuickMenuDiscoverySubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	TMulticastDelegate<void(TArray<TSharedPtr<FQuickCommandEntry>>& OutCommands)> OnDiscoverCommands;

	TArray<TSharedPtr<FQuickCommandEntry>> GetAllCommands() const;
	bool ShouldDisplayCommand(const FString& InputPattern, const TSharedPtr<FQuickCommandEntry>& Command) const;

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void GatherCommandsInternal(TArray<TSharedPtr<FQuickCommandEntry>>& OutCommands) const;

	void PopulateMenuEntries(TArray<TSharedPtr<FQuickCommandEntry>>& OutCommands) const;
};