// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "SPackageSelector.h"

void SPackageSelector::Construct(const FArguments& InArgs)
{
	SuggestionsList.Add(MakeShared<FString>(TEXT("da")));
	SuggestionsList.Add(MakeShared<FString>(TEXT("da")));
	SuggestionsList.Add(MakeShared<FString>(TEXT("da")));
	SuggestionsList.Add(MakeShared<FString>(TEXT("da")));
	SuggestionsList.Add(MakeShared<FString>(TEXT("da")));
	SuggestionsList.Add(MakeShared<FString>(TEXT("da")));

	// clang-format off
	ChildSlot
	[
		SAssignNew(SuggestionListView, SListView< TSharedPtr<FString> >)
		.ListItemsSource(&SuggestionsList)
		.SelectionMode(ESelectionMode::Single)
		.OnGenerateRow(this, &SPackageSelector::GenerateRow)	
	];
	// clang-format on
}
TSharedRef<ITableRow> SPackageSelector::GenerateRow(TSharedPtr<FString> Selection, const TSharedRef<STableViewBase>& OwnerTable)
{
	// clang-format off
	return SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
	[
		SNew(STextBlock)
		.Text(FText::FromString(*Selection.Get()))
	];
	// clang-format on
}