// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuActorActorOptionsExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> Actor menu -> ActorOptions section
 */
UCLASS()
class UToolbarMenuActorActorOptionsExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
};
