// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "OpenSettingsExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> Edit menu -> Configuration section
 */
UCLASS()
class UOpenSettingsExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<FQuickCommandEntry> GetCommands() override;
};