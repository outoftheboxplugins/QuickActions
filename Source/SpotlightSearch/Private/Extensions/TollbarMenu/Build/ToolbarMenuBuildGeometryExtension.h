// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuBuildGeometryExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> Build menu -> Geometry section
 */
UCLASS()
class UToolbarMenuBuildGeometryExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
};