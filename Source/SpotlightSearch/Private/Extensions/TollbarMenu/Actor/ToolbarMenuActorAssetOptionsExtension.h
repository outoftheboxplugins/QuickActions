// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuActorAssetOptionsExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> Actor menu -> Asset Options section
 */
UCLASS()
class UToolbarMenuActorAssetOptionsExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
};
