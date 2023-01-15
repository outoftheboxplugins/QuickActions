// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "PackageExtension.generated.h"

/**
 * Creates a quick menu complex entry to quickly package your game on a selected platform & configuration.
 */
UCLASS()
class UPackageExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
};