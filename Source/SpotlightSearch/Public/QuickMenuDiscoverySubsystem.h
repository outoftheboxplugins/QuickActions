// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

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
	TArray<TSharedRef<FQuickCommandEntry>> GetAllCommands() const;

private:
	/**
	 * @brief Loops through all the Extensions to gather all available commands
	 * @param OutCommands Resulting list of all commands
	 */
	void GatherCommandsInternal(TArray<TSharedRef<FQuickCommandEntry>>& OutCommands) const;
};