// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuBuildAutomationExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> Build menu -> Automation section
 */
UCLASS()
class UToolbarMenuBuildAutomationExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
};