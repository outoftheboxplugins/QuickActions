// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 *
 */
class SPOTLIGHTSEARCH_API SPackageSelector : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPackageSelector) {}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TArray<FString> PlatformSuggestions;
	int32 PlatformIndex = 0;
	
	TArray<FString> BinarySuggestions;
	int32 BinaryIndex = 0;
	
	TArray<FString> TargetSuggestions;
	int32 TargetIndex = 0;

	TSharedRef<SWidget> GenerateOptions(const FText& Category, const TArray<FString>& Options, int32& CategoryIndex);

	void StartPackage();
};