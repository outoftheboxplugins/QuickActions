// Copyright Out-of-the-Box Plugins 2018-2022. All Rights Reserved.

#pragma once

#include <EditorSubsystem.h>

#include "QuickMenuExtension.h"

#include "QuickMenuDiscoverySubsystem.generated.h"

/**
 * Keeps a cached list of available commands up-to-date at all times to be used by any possible consumers.
 */
UCLASS()
class QUICKMENU_API UQuickMenuDiscoverySubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	/**
	 * @brief Gets an up-to-date list of all currently available commands
	 * @return List of Commands available
	 */
	const TArray<TSharedPtr<FQuickCommandEntry>>& GetAllCommands() const;

private:
	// Begin UEditorSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End UEditorSubsystem interface

	/**
	 * @brief Loops through all the Extensions to gather all available commands
	 * @param OutCommands Resulting list of all commands
	 */
	void GatherCommandsInternal(TArray<TSharedPtr<FQuickCommandEntry>>& OutCommands) const;
	/**
	 * @brief Cached array of all commands we discovered on startup so menu spawn time are lower
	 */
	TArray<TSharedPtr<FQuickCommandEntry>> DiscoveredCommands;
};