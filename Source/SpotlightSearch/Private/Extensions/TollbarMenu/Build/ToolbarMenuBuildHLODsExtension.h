// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuBuildHLODsExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> Build menu -> Hierarchical LODS section
 */
UCLASS()
class UToolbarMenuBuildHLODsExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
};