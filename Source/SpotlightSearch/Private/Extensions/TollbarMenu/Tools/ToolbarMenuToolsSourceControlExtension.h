﻿// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuToolsSourceControlExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> Tools menu -> SourceControl section
 */
UCLASS()
class UToolbarMenuToolsSourceControlExtension : public UQuickMenuExtension 
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FQuickCommandContext& Context) override;
};