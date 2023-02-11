// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"
#include "SPackageSelector.h"

#include "PackageExtension.generated.h"

struct FQuickPackageCommandEntry : FQuickCommandEntry
{
	FQuickPackageCommandEntry();

	virtual TSharedPtr<SWidget> GetSplitViewWidget() override;

	TSharedRef<SPackageSelector> SplitViewWidget;
};


/**
 * Creates a quick menu complex entry to quickly package your game on a selected platform & configuration.
 */
UCLASS()
class UPackageExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
};