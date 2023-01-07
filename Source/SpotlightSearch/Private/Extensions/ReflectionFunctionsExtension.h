// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ReflectionFunctionsExtension.generated.h"

/**
 * Creates a quick menu entry for each UFUNCTION with the meta tag QuickActionEntry
 *
 * Example usage:
 *
 *		// Example tooltip
 *		UFUNCTION(meta = (QuickActionEntry))
 *		void ExampleFunction();
 */
UCLASS()
class UReflectionFunctionsExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;

	// Example tooltip
	UFUNCTION(meta = (QuickActionEntry))
	void ExampleFunction();
};