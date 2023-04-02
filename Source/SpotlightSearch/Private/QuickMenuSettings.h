// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include <Engine/DeveloperSettings.h>

#include "QuickMenuSettings.generated.h"

/**
 * @brief Editor Settings for Quick Menu behavior customization
 */
UCLASS(config = Editor, defaultconfig)
class QUICKMENU_API UQuickMenuSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * @brief Includes How-do-I tutorials from Mathew Wadstein inside the entries
	 */
	UPROPERTY(EditAnywhere, Category = Customization, config)
	bool bIncludeTutorials = true;
	/**
	 * @brief Includes shortcuts to open specific settings sections inside the entries
	 */
	UPROPERTY(EditAnywhere, Category = Customization, config)
	bool bIncludeSettingSections = true;
	/**
	 * @brief Matching percentage required for an entry to show up as a fuzzy search.
	 */
	UPROPERTY(EditAnywhere, Category = Customization, config, meta = (UIMin = "0.0", UIMax = "100.0"))
	float FuzzySearchMatchPercentage = 75.0f;
	/**
	 * @brief Registers a command on top of the Recent Commands list and saves the config.
	 * @param CommandName Unique name used to identify the command that was executed
	 */
	void RegisterRecentCommand(const FString& CommandName);
	/**
	 * @brief Returns the current list of Recently ran commands
	 * @note Persistent across sessions
	 * @return Ordered list of the most recent ran commands
	 */
	const TArray<FString>& GetRecentCommands() const;

protected:
	/**
	 * @brief Recently executed commands
	 * @note Saved in the config to ensure they are kept across sessions
	 */
	UPROPERTY(EditAnywhere, Category = Customization, config)
	TArray<FString> RecentCommands;
	/**
	 * @brief Maximum number of entries we will display under recent commands
	 */
	UPROPERTY(EditAnywhere, Category = Customization, config)
	int32 MaxRecentCommands = 5;

private:
	// Begin UDeveloperSettings interface
	virtual FName GetContainerName() const override;
	virtual FName GetCategoryName() const override;
	virtual FName GetSectionName() const override;
#if WITH_EDITOR
	virtual FText GetSectionText() const override;
#endif
	// End UDeveloperSettings interface
};