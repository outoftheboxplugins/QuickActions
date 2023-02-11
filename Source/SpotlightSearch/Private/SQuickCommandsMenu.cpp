// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "SQuickCommandsMenu.h"

#include <Widgets/Layout/SSeparator.h>

#include "QuickMenuStyle.h"
#include "Styling/StyleColors.h"

#define LOCTEXT_NAMESPACE "FQuickMenuModule"

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

	const UQuickMenuDiscoverySubsystem* DiscoverySubsystem = GEditor->GetEditorSubsystem<UQuickMenuDiscoverySubsystem>();
	for (const auto& Command : Commands)
	{
		if (DiscoverySubsystem->ShouldDisplayCommand(Text.ToString(), Command))
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

	// clang-format off
	SWindow::Construct(SWindow::FArguments()
	.Style(&FAppStyle::Get().GetWidgetStyle<FWindowStyle>("NotificationWindow"))
	.CreateTitleBar(false)
	.SizingRule(ESizingRule::FixedSize)
	.ClientSize(FVector2D(680.f, 430.f))
	.SupportsMaximize(false)
	.SupportsMinimize(false)
	.IsPopupWindow(true)
	[
		SNew(SVerticalBox)

		+SVerticalBox::Slot()
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

			+SHorizontalBox::Slot()
			.FillWidth(1.0)
			.VAlign(VAlign_Center)
			[
				SAssignNew(EditableText, SEditableText)
				.OnTextChanged(this, &SQuickCommandsMenu::OnFilterTextChanged)
				.OnKeyDownHandler(this, &SQuickCommandsMenu::OnSearchKeyDown)
				.Style(&FQuickMenuStyle::Get().GetWidgetStyle<FEditableTextStyle>("ActionMenuSearchTextStyle"))
			]
		]

		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SSeparator)
			.Thickness(1)
			.SeparatorImage(FAppStyle::Get().GetBrush("Menu.Separator"))
		]

		+SVerticalBox::Slot()
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
				.Padding(5.0f, 0.0f)
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
	const bool bCanExecute = Selection->IsAllowedToExecute();

	// clang-format off
	return SNew(STableRow<TSharedRef<FQuickCommandEntry>>, OwnerTable)
			.Style(&FQuickMenuStyle::Get().GetWidgetStyle<FTableRowStyle>("ActionMenuRow"))
			.IsEnabled_Lambda([bCanExecute](){return bCanExecute;})
			.ToolTipText(Selection->Tooltip)
			[
				SNew(SHorizontalBox)

				+SHorizontalBox::Slot()
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

				+SHorizontalBox::Slot()
				.VAlign(VAlign_Fill)
				.Padding(0)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					.FillHeight(1.0f)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.TextStyle(FAppStyle::Get(), "PlacementBrowser.Asset.Name")
						.Text(Selection->Title)
					]
					+SVerticalBox::Slot()
					[
						SNew(STextBlock)
						.TextStyle(FAppStyle::Get(), "ContentBrowser.ClassFont")
						.Visibility_Lambda([this]{ return ShouldShowDescription() ? EVisibility::Visible : EVisibility::Collapsed; })
						.Text(Selection->Tooltip)
					]
				]

				+SHorizontalBox::Slot()
				.Padding(8.0f, 4.f)
				.AutoWidth()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Bottom)
				[
					SNew(STextBlock)
					.TextStyle(FAppStyle::Get(), "Menu.Keybinding")
					.Text(Selection->InputText)
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
		// TODO: make this padding nicer or find a better solution.
		HorizontalBox->InsertSlot(1).Padding(5.0f, 0.0f)[SplitViewWidget.ToSharedRef()];
	}
}
bool SQuickCommandsMenu::ShouldShowDescription() const
{
	// TODO: Also create a setting for this.
	const bool bIsAltPressed = FSlateApplication::Get().GetModifierKeys().IsAltDown();
	return bIsAltPressed;
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
	// TODO: Is this function even needed?
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