// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuBuildVerificationExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> Build menu -> Verification section
 */
UCLASS()
class UToolbarMenuBuildVerificationExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
};