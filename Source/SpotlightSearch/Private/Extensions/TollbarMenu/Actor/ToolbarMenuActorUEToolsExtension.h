﻿// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuActorUEToolsExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> Actor menu -> UE Tools section
 */
UCLASS()
class UToolbarMenuActorUEToolsExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FQuickCommandContext& Context) override;
};
