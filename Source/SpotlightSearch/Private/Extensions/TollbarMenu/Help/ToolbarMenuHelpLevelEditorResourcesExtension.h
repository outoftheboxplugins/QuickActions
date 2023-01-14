// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuHelpLevelEditorResourcesExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> Help menu -> Level Editor Resources section
 */
UCLASS()
class UToolbarMenuHelpLevelEditorResourcesExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
};