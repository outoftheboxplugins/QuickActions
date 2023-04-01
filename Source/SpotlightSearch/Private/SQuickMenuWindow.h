// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include <Widgets/SCompoundWidget.h>

#include "QuickMenuExtension.h"
#include "SNonFocusingListView.h"

/**
 * @brief A dialog similar to Spotlight Search. It contains a textbox to filter items on top and a list of filtered actions below
 */
class SQuickMenuWindow : public SWindow
{
public:
	SLATE_BEGIN_ARGS(SQuickMenuWindow) {}

	SLATE_END_ARGS()

	/**
	 * Constructs the quick menu window
	 */
	void Construct(const FArguments& InArgs);

	/**
	 * @brief Callback executed when the filter textbox content is changed
	 * @param Text current text we should filter for
	 */
	void OnFilterTextChanged(const FText& Text);


private:
	// Begin SWindow interface.
	virtual bool OnIsActiveChanged(const FWindowActivateEvent& ActivateEvent) override;
	virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	// End SWindow interface.

	/**
	 * @brief Used to focus the filter textbox immediately following construction
	 */
	EActiveTimerReturnType SetFocusPostConstruct(double InCurrentTime, float InDeltaTime);

	TSharedRef<ITableRow> MakeShowWidget(TSharedRef<FQuickCommandEntry> Selection, const TSharedRef<STableViewBase>& OwnerTable);

	FReply OnSearchKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);
	void CloseWindow();
	void ConfirmSelection();
	void UpdateSelection(int32 Change);
	bool ShouldShowDescription() const;


	int32 SelectionIndex = 0;
	TSharedPtr<SEditableText> EditableText;
	TSharedPtr<SHorizontalBox> HorizontalBox;
	TSharedPtr<SNonFocusingListView<TSharedRef<FQuickCommandEntry>>> ListView;
	TArray<TSharedRef<FQuickCommandEntry>> Commands;
	TArray<TSharedRef<FQuickCommandEntry>> FilteredCommands;

	bool bWasClosed = false;
};
