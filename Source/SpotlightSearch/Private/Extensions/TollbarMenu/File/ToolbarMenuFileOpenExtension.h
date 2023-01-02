// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuFileOpenExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> File menu -> Open section
 */
UCLASS()
class UToolbarMenuFileOpenExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
};