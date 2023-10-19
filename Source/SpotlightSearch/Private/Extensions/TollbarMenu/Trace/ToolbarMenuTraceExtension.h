// Copyright Nesting Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuickMenuExtension.h"
#include "ToolbarMenuTraceExtension.generated.h"

/**
 * 
 */
UCLASS()
class QUICKMENU_API UToolbarMenuTraceExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

public:
	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FQuickCommandContext& Context) override;
};
