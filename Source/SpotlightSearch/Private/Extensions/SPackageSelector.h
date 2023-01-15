// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SPackageOptionListView : public SListView<TSharedPtr<FString>>
{
protected:
	virtual TOptional<bool> OnQueryShowFocus(const EFocusCause InFocusCause) const override;
};
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

	TSharedRef<ITableRow> GenerateRow(TSharedPtr<FString> Selection, const TSharedRef<STableViewBase>& OwnerTable);

	TSharedPtr<SListView<TSharedPtr<FString>>> PlatformListView;
	TArray<TSharedPtr<FString>> PlatformSuggestions;

	TSharedPtr<SListView<TSharedPtr<FString>>> BinaryListView;
	TArray<TSharedPtr<FString>> BinarySuggestions;

	TSharedPtr<SListView<TSharedPtr<FString>>> TargetListView;
	TArray<TSharedPtr<FString>> TargetSuggestions;
};