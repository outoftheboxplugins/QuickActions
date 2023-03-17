// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuBuildPackedLevelActorExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> Build menu -> Packed Level Actor section
 */
UCLASS()
class UToolbarMenuBuildPackedLevelActorExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
	virtual bool ShouldShow() const override;
};