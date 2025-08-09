// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "OpenAssetExtension.generated.h"

/**
 * Creates a quick menu entry for each Asset to open it directly.
 */
UCLASS()
class UOpenAssetExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FQuickCommandContext& Context) override;
	virtual int32 GetPriority() const override;
	virtual bool ShouldShow() const override;
};