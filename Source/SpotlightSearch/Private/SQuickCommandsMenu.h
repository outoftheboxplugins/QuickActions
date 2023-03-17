// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "SQuickCommandsListView.h"

#include <Widgets/SCompoundWidget.h>

class SQuickCommandsMenu : public SWindow
{
public:
	SLATE_BEGIN_ARGS(SQuickCommandsMenu)
	{
	}

	SLATE_END_ARGS()

	void OnFilterTextChanged(const FText& Text);
	void Construct(const FArguments& InArgs);

private:
	TSharedRef<ITableRow> MakeShowWidget(TSharedRef<FQuickCommandEntry> Selection, const TSharedRef<STableViewBase>& OwnerTable);

	EActiveTimerReturnType SetFocusPostConstruct(double InCurrentTime, float InDeltaTime);
	TSharedPtr<SEditableText> EditableText;

private:
	FReply OnSearchKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);
	virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	void CloseWindow();
	void ConfirmSelection();
	void UpdateSelection(int32 Change);
	bool ShouldShowDescription() const;

	virtual bool OnIsActiveChanged(const FWindowActivateEvent& ActivateEvent) override;

	int32 SelectionIndex = 0;
	TSharedPtr<SHorizontalBox> HorizontalBox;
	TSharedPtr<SQuickCommandsListView> ListView;
	TArray<TSharedRef<FQuickCommandEntry>> Commands;
	TArray<TSharedRef<FQuickCommandEntry>> FilteredCommands;
	
	bool bWasClosed = false;
};
