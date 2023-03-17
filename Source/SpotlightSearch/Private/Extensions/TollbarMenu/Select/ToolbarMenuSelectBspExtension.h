// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuSelectBspExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> Select menu -> BSP section
 */
UCLASS()
class UToolbarMenuSelectBspExtension : public UQuickMenuExtension 
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
};
