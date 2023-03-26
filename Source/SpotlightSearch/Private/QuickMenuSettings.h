// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include <Engine/DeveloperSettings.h>

#include "QuickMenuSettings.generated.h"

/**
 *
 */
UCLASS(config = Editor, defaultconfig)
class QUICKMENU_API UQuickMenuSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	// TODO: Spawn widget in the middle of the UE window, not middle of user screen.
	UPROPERTY(EditAnywhere, Category = Customization, config)
	bool bIncludeTutorials = true;

	UPROPERTY(EditAnywhere, Category = Customization, config)
	bool bIncludeSettingSections = true;

	void RegisterRecentCommand(const FString& CommandName);
	const TArray<FString>& GetRecentCommands() const;

protected:
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