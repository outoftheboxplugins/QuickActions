// Copyright Out-of-the-Box Plugins 2018-2021. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuFileProjectExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> File menu -> Project section
 */
UCLASS()
class UToolbarMenuFileProjectExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<FQuickCommandEntry> GetCommands() override;
};