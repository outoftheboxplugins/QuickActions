// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "SQuickCommandsMenu.h"

#include <Widgets/Layout/SSeparator.h>

#include "Brushes/SlateRoundedBoxBrush.h"
#include "Styling/StyleColors.h"

#define LOCTEXT_NAMESPACE "FSpotlightSearchModule"

namespace
{
	int32 PositiveModulo(int32 i, int32 n)
	{
		return (i % n + n) % n;
	}
} // namespace

void SQuickCommandsMenu::OnFilterTextChanged(const FText& Text)
{
	FilteredCommands.Empty();

	for (const auto& Command : Commands)
	{
		FString CommandTitle = Command->Title.Get().ToString();
		if (Text.IsEmpty() || CommandTitle.Contains(Text.ToString()))
		{
			FilteredCommands.Add(Command);
		}
	}

	ListView->RequestListRefresh();
	UpdateSelection(0);
}

void SQuickCommandsMenu::Construct(const FArguments& InArgs)
{
	UQuickMenuDiscoverySubsystem* DiscoverySubsystem = GEditor->GetEditorSubsystem<UQuickMenuDiscoverySubsystem>();
	TArray<TSharedPtr<FQuickCommandEntry>> AllEntries = DiscoverySubsystem->GetAllCommands();
	for (const TSharedPtr<FQuickCommandEntry>& Entry : AllEntries)
	{
		Commands.Emplace(Entry.ToSharedRef());
	}

	static FEditableTextStyle EditableTextBoxStyle = FCoreStyle::Get().GetWidgetStyle<FEditableTextStyle>("NormalEditableText");
	EditableTextBoxStyle.SetFont(FCoreStyle::GetDefaultFontStyle("Bold", 18));

	// static FWindowStyle WindowStyle = FCoreStyle::Get().GetWidgetStyle<FWindowStyle>("Window");
	// WindowStyle.SetBackgroundBrush(FSlateColorBrush(FStyleColors::Recessed))
	// 	.SetBorderBrush(FSlateRoundedBoxBrush(FStyleColors::Recessed, 2.0f, FStyleColors::WindowBorder, 2.0f))
	// 	.SetOutlineBrush(FSlateRoundedBoxBrush(FStyleColors::Recessed, 2.0f, FStyleColors::InputOutline, 1.0f))
	// 	.SetChildBackgroundBrush(FSlateColorBrush(FStyleColors::Recessed))
	// 	.SetCornerRadius(36)
	// 	.SetBorderPadding(FMargin(3.0f, 3.0f, 3.0f, 3.0f));

	static FWindowStyle WindowStyle = FAppStyle::Get().GetWidgetStyle<FWindowStyle>("NotificationWindow");

	// clang-format off
	SWindow::Construct(SWindow::FArguments()
	                   .Style(&WindowStyle)
	                   .CreateTitleBar(false)
	                   .SizingRule(ESizingRule::FixedSize)
	                   .ClientSize(FVector2D(680.f, 430.f))
	                   .SupportsMaximize(false)
	                   .SupportsMinimize(false)
	                   .IsPopupWindow(true)
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		  .AutoHeight()
		  .HAlign(HAlign_Fill)
		  .Padding(15)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .AutoWidth()
			  .Padding(2.0f, 2.0f, 6.0f, 2.0f)
			[
				SNew(SBox)
				.WidthOverride(30)
				.HeightOverride(30)
				[
					SNew(SImage)
					.Image(FAppStyle::GetBrush("Icons.Search"))
				]
			]

			+ SHorizontalBox::Slot()
			  .FillWidth(1.0)
			  .VAlign(VAlign_Center)
			[
				SAssignNew(EditableText, SEditableText)
				.OnTextChanged(this, &SQuickCommandsMenu::OnFilterTextChanged)
				.OnKeyDownHandler(this, &SQuickCommandsMenu::OnSearchKeyDown)
				.Style(&EditableTextBoxStyle)
			]
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SSeparator)
			.Thickness(1)
			.SeparatorImage(FAppStyle::Get().GetBrush("Menu.Separator"))
		]

		+ SVerticalBox::Slot()
		  .FillHeight(1)
		  .Padding(15)
		  .HAlign(HAlign_Fill)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("Docking.Tab.ContentAreaBrush"))
			.Padding(1.0)
			[
				SAssignNew(HorizontalBox, SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(10.0f, 0.0f)
				[
					SAssignNew(ListView, SQuickCommandsListView)
					.ListItemsSource(&FilteredCommands)
					.OnGenerateRow(this, &SQuickCommandsMenu::MakeShowWidget)
					.ScrollbarVisibility(EVisibility::Collapsed)
					.IsFocusable(false)
				]
			]
		]
	]);
	// clang-format on

	RegisterActiveTimer(0.0f, FWidgetActiveTimerDelegate::CreateSP(this, &SQuickCommandsMenu::SetFocusPostConstruct));
}

TSharedRef<ITableRow> SQuickCommandsMenu::MakeShowWidget(TSharedRef<FQuickCommandEntry> Selection, const TSharedRef<STableViewBase>& OwnerTable)
{
	static FTableRowStyle TableRowStyle = FCoreStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row");
	TableRowStyle.SetEvenRowBackgroundBrush(FSlateNoResource())
		.SetEvenRowBackgroundHoveredBrush(FSlateRoundedBoxBrush(FStyleColors::Panel, 4.0f))
		.SetOddRowBackgroundBrush(FSlateNoResource())
		.SetOddRowBackgroundHoveredBrush(FSlateRoundedBoxBrush(FStyleColors::Panel, 4.0f))
		.SetSelectorFocusedBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::Select, 1.0f))
		.SetActiveBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::Select, 1.0f))
		.SetActiveHoveredBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::Select, 1.0f))
		.SetInactiveBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::SelectInactive, 1.0f))
		.SetInactiveHoveredBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::SelectInactive, 1.0f))
		.SetTextColor(FStyleColors::Foreground)
		.SetActiveHighlightedBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::Select, 1.0f))
		.SetSelectedTextColor(FStyleColors::Foreground);

	const bool bCanExecute = Selection->IsAllowedToExecute();

	// clang-format off
	return SNew(STableRow<TSharedRef<FQuickCommandEntry>>, OwnerTable)
			.Style(&TableRowStyle)
			.IsEnabled_Lambda([bCanExecute](){return bCanExecute;})
	       [
		       SNew(SHorizontalBox)

		       + SHorizontalBox::Slot()
		       .Padding(8.0f, 4.f)
		       .AutoWidth()
		       .HAlign(HAlign_Center)
		       .VAlign(VAlign_Center)
		       [
			       SNew(SBox)
					.WidthOverride(30)
					.HeightOverride(30)
			       [
				       SNew(SImage)
				       .Image(Selection->Icon.Get().GetIcon()) 
			       ]
		       ]

		       + SHorizontalBox::Slot()
		       .VAlign(VAlign_Fill)
		       .Padding(0)
		       [
			       SNew(SHorizontalBox)
			       + SHorizontalBox::Slot()
			       .Padding(9, 0, 0, 1)
			       .VAlign(VAlign_Center)
			       [
						SNew(STextBlock)
						.TextStyle(FAppStyle::Get(), "PlacementBrowser.Asset.Name")
						.Text(Selection->Title)
			       ]
		       ]
	       ];
	// clang-format on
}

FReply SQuickCommandsMenu::OnSearchKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Down)
	{
		UpdateSelection(1);
		return FReply::Handled();
	}
	if (InKeyEvent.GetKey() == EKeys::Up)
	{
		UpdateSelection(-1);
		return FReply::Handled();
	}

	return FReply::Unhandled();
}
FReply SQuickCommandsMenu::OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Enter)
	{
		ConfirmSelection();
		return FReply::Handled();
	}
	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		CloseWindow();
		return FReply::Handled();
	}

	return SWindow::OnPreviewKeyDown(MyGeometry, InKeyEvent);
}

void SQuickCommandsMenu::CloseWindow()
{
	// TODO: Prevents this from getting called twice, maybe we should investigate how we can avoid the double call instead.
	if (bWasClosed)
	{
		return;
	}

	bWasClosed = true;
	RequestDestroyWindow();
}

void SQuickCommandsMenu::ConfirmSelection()
{
	if (FilteredCommands.IsEmpty())
	{
		// No entries to go through
		return;
	}

	const TSharedRef<FQuickCommandEntry>& CurrentCommand = FilteredCommands[SelectionIndex];
	if (!CurrentCommand->IsAllowedToExecute())
	{
		return;
	}

	(void)CurrentCommand->ExecuteCallback.ExecuteIfBound();
	CloseWindow();
}

void SQuickCommandsMenu::UpdateSelection(int32 Change)
{
	if (FilteredCommands.IsEmpty())
	{
		// No entries to go through
		return;
	}

	SelectionIndex = PositiveModulo(SelectionIndex + Change, FilteredCommands.Num());

	const TSharedRef<FQuickCommandEntry>& CurrentCommand = FilteredCommands[SelectionIndex];
	ListView->RequestNavigateToItem(CurrentCommand);
	ListView->SetSelection(CurrentCommand);

	const TSharedPtr<SWidget> SplitViewWidget = CurrentCommand->GetSplitViewWidget();

	if (HorizontalBox->NumSlots() > 1)
	{
		HorizontalBox->RemoveSlot(HorizontalBox->GetSlot(1).GetWidget());
	}
	if (SplitViewWidget.IsValid())
	{
		HorizontalBox->InsertSlot(1)[SplitViewWidget.ToSharedRef()];
	}
}

bool SQuickCommandsMenu::OnIsActiveChanged(const FWindowActivateEvent& ActivateEvent)
{
	if (ActivateEvent.GetActivationType() == FWindowActivateEvent::EA_Deactivate)
	{
		CloseWindow();
	}

	return SWindow::OnIsActiveChanged(ActivateEvent);
}

EActiveTimerReturnType SQuickCommandsMenu::SetFocusPostConstruct(double InCurrentTime, float InDeltaTime)
{
	if (EditableText.IsValid())
	{
		FWidgetPath WidgetToFocusPath;
		FSlateApplication::Get().GeneratePathToWidgetUnchecked(EditableText.ToSharedRef(), WidgetToFocusPath);
		FSlateApplication::Get().SetKeyboardFocus(WidgetToFocusPath, EFocusCause::SetDirectly);
		WidgetToFocusPath.GetWindow()->SetWidgetToFocusOnActivate(EditableText);
		return EActiveTimerReturnType::Stop;
	}

	return EActiveTimerReturnType::Continue;
}
#undef LOCTEXT_NAMESPACE