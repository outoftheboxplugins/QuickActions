// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "OpenSettingsExtension.generated.h"

/**
 * Creates a quick menu entry for each Settings section to open it directly.
 */
UCLASS()
class UOpenSettingsExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
	virtual int32 GetPriority() const override;
	virtual bool ShouldShow() const override;
};