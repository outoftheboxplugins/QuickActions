// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "SPackageSelector.h"

void SPackageSelector::Construct(const FArguments& InArgs)
{
	PlatformSuggestions.Emplace(MakeShared<FString>(TEXT("Windows")));
	PlatformSuggestions.Emplace(MakeShared<FString>(TEXT("Linux")));
	PlatformSuggestions.Emplace(MakeShared<FString>(TEXT("Potato")));

	BinarySuggestions.Emplace(MakeShared<FString>(TEXT("Shipping")));
	BinarySuggestions.Emplace(MakeShared<FString>(TEXT("Testing")));
	BinarySuggestions.Emplace(MakeShared<FString>(TEXT("Development")));
	BinarySuggestions.Emplace(MakeShared<FString>(TEXT("DebugGame")));
	BinarySuggestions.Emplace(MakeShared<FString>(TEXT("Debug")));

	TargetSuggestions.Emplace(MakeShared<FString>(TEXT("Client")));
	TargetSuggestions.Emplace(MakeShared<FString>(TEXT("Server")));

	// clang-format off
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			SAssignNew(PlatformListView, SListView< TSharedPtr<FString> >)
			.ListItemsSource(&PlatformSuggestions)
			.SelectionMode(ESelectionMode::Single)
			.OnGenerateRow(this, &SPackageSelector::GenerateRow)	
		]
		+ SVerticalBox::Slot()
		[
			SAssignNew(BinaryListView, SListView< TSharedPtr<FString> >)
			.ListItemsSource(&BinarySuggestions)
			.SelectionMode(ESelectionMode::Single)
			.OnGenerateRow(this, &SPackageSelector::GenerateRow)	
		]
		+ SVerticalBox::Slot()
		[
			SAssignNew(TargetListView, SListView< TSharedPtr<FString> >)
			.ListItemsSource(&TargetSuggestions)
			.SelectionMode(ESelectionMode::Single)
			.OnGenerateRow(this, &SPackageSelector::GenerateRow)	
		]
	];
	// clang-format on

	PlatformListView->SetSelection(PlatformSuggestions[2]);
	BinaryListView->SetSelection(BinarySuggestions[0]);
	TargetListView->SetSelection(TargetSuggestions[1]);
}
TSharedRef<ITableRow> SPackageSelector::GenerateRow(TSharedPtr<FString> Selection, const TSharedRef<STableViewBase>& OwnerTable)
{
	// clang-format off
	return SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
	[
		SNew(STextBlock)
		.Text(FText::FromString(*Selection.Get()))
		.Font(FAppStyle::GetFontStyle("BlueprintEditor.ActionMenu.ContextDescriptionFont"))
	];
	// clang-format on
}