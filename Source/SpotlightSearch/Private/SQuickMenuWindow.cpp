// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "SQuickMenuWindow.h"

#include <Widgets/Layout/SSeparator.h>

#include "QuickMenuDiscoverySubsystem.h"
#include "QuickMenuHelpers.h"
#include "QuickMenuSettings.h"
#include "QuickMenuStyle.h"

#define LOCTEXT_NAMESPACE "FQuickMenuModule"

// TODO: Show this menu in the middle of the Unreal screen instead of middle of the monitor
// TODO: Reorder functions in here to match the header file order

namespace
{
	int32 PositiveModulo(int32 i, int32 n)
	{
		return (i % n + n) % n;
	}
} // namespace

void SQuickMenuWindow::OnFilterTextChanged(const FText& Text)
{
	FilteredCommands.Empty();

	TArray<FQuickMenuItem> Commands;
	const UQuickMenuDiscoverySubsystem* DiscoverySubsystem = GEditor->GetEditorSubsystem<UQuickMenuDiscoverySubsystem>();
	TArray<TSharedPtr<FQuickCommandEntry>> AllEntries = DiscoverySubsystem->GetAllCommands();
	for (const TSharedPtr<FQuickCommandEntry>& Entry : AllEntries)
	{
		Commands.Emplace(Entry.ToSharedRef());
	}

	TArray<FQuickMenuItem> AvailableCommands = Commands;

	if (Text.IsEmpty())
	{
		const UQuickMenuSettings* Settings = GetDefault<UQuickMenuSettings>();
		const TArray<FString>& RecentCommands = Settings->GetRecentCommands();

		for (const FString& Command : RecentCommands)
		{
			const FQuickMenuItem* FoundCommand = AvailableCommands.FindByPredicate(
				[Command](const FQuickMenuItem& Entry)
				{
					return Entry->GetUniqueCommandName() == Command;
				}
			);

			if (FoundCommand)
			{
				FilteredCommands.Emplace(*FoundCommand);
			}
		}
	}
	else
	{
		// First get all the abbreviations
		for (auto It = AvailableCommands.CreateIterator(); It; ++It)
		{
			FQuickMenuItem Command = *It;
			if (QuickMenuHelpers::IsAbbreviation(Command->GetUniqueCommandName(), Text.ToString()))
			{
				FilteredCommands.Add(*It);
				It.RemoveCurrent();
			}
		}

		// Second get the perfect matches
		for (auto It = AvailableCommands.CreateIterator(); It; ++It)
		{
			FQuickMenuItem Command = *It;
			if (QuickMenuHelpers::IsStartingWith(Command->GetUniqueCommandName(), Text.ToString()))
			{
				FilteredCommands.Add(*It);
				It.RemoveCurrent();
			}
		}

		// Third get fuzzy entries
		for (auto It = AvailableCommands.CreateIterator(); It; ++It)
		{
			FQuickMenuItem Command = *It;
			if (QuickMenuHelpers::IsCloseTo(Command->GetUniqueCommandName(), Text.ToString()))
			{
				FilteredCommands.Add(*It);
				It.RemoveCurrent();
			}
		}
	}

	ListView->RequestListRefresh();
	UpdateSelection(0);
}

void SQuickMenuWindow::Construct(const FArguments& InArgs)
{
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
				.OnTextChanged(this, &SQuickMenuWindow::OnFilterTextChanged)
				.OnKeyDownHandler(this, &SQuickMenuWindow::OnSearchKeyDown)
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
					SAssignNew(ListView, SNonFocusingListView<FQuickMenuItem>)
					.ListItemsSource(&FilteredCommands)
					.OnGenerateRow(this, &SQuickMenuWindow::MakeCommandListItem)
					.ScrollbarVisibility(EVisibility::Collapsed)
					.IsFocusable(false)
				]
			]
		]
	]);
	// clang-format on

	RegisterActiveTimer(0.0f, FWidgetActiveTimerDelegate::CreateSP(this, &SQuickMenuWindow::SetFocusPostConstruct));
}

TSharedRef<ITableRow> SQuickMenuWindow::MakeCommandListItem(FQuickMenuItem Selection, const TSharedRef<STableViewBase>& OwnerTable)
{
	const bool bCanExecute = Selection->IsAllowedToExecute();

	// clang-format off
	return SNew(STableRow<FQuickMenuItem>, OwnerTable)
			.Style(&FQuickMenuStyle::Get().GetWidgetStyle<FTableRowStyle>("ActionMenuRow"))
			.IsEnabled_Lambda([bCanExecute](){return bCanExecute;})
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

FReply SQuickMenuWindow::OnSearchKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
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

FReply SQuickMenuWindow::OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
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

void SQuickMenuWindow::CloseWindow()
{
	// TODO: Prevents this from getting called twice, maybe we should investigate how we can avoid the double call instead.
	if (bWasClosed)
	{
		return;
	}

	bWasClosed = true;
	RequestDestroyWindow();
}

void SQuickMenuWindow::ConfirmSelection()
{
	if (FilteredCommands.IsEmpty())
	{
		// No entries to go through
		return;
	}

	const FQuickMenuItem& CurrentCommand = FilteredCommands[SelectionIndex];
	if (!CurrentCommand->IsAllowedToExecute())
	{
		return;
	}

	UQuickMenuSettings* Settings = GetMutableDefault<UQuickMenuSettings>();
	Settings->RegisterRecentCommand(CurrentCommand->GetUniqueCommandName());

	(void)CurrentCommand->ExecuteCallback.ExecuteIfBound();
	CloseWindow();
}

void SQuickMenuWindow::UpdateSelection(int32 Change)
{
	if (FilteredCommands.IsEmpty())
	{
		return;
	}

	SelectionIndex = PositiveModulo(SelectionIndex + Change, FilteredCommands.Num());

	const FQuickMenuItem& CurrentCommand = FilteredCommands[SelectionIndex];
	ListView->RequestNavigateToItem(CurrentCommand);
	ListView->SetSelection(CurrentCommand);

	const TSharedPtr<SWidget> SplitViewWidget = CurrentCommand->GetSplitViewWidget();

	// TODO: make this padding nicer or find a better solution.
	if (HorizontalBox->NumSlots() > 1)
	{
		HorizontalBox->RemoveSlot(HorizontalBox->GetSlot(1).GetWidget());
	}
	if (SplitViewWidget.IsValid())
	{
		HorizontalBox->InsertSlot(1).Padding(5.0f, 0.0f)[SplitViewWidget.ToSharedRef()];
	}
}

bool SQuickMenuWindow::ShouldShowDescription() const
{
	// TODO: Also create a setting for this.
	const bool bIsAltPressed = FSlateApplication::Get().GetModifierKeys().IsAltDown();
	return bIsAltPressed;
}

bool SQuickMenuWindow::OnIsActiveChanged(const FWindowActivateEvent& ActivateEvent)
{
	if (ActivateEvent.GetActivationType() == FWindowActivateEvent::EA_Deactivate)
	{
		CloseWindow();
	}

	return SWindow::OnIsActiveChanged(ActivateEvent);
}

EActiveTimerReturnType SQuickMenuWindow::SetFocusPostConstruct(double InCurrentTime, float InDeltaTime)
{
	if (EditableText.IsValid())
	{
		FWidgetPath WidgetToFocusPath;
		FSlateApplication::Get().GeneratePathToWidgetUnchecked(EditableText.ToSharedRef(), WidgetToFocusPath);
		FSlateApplication::Get().SetKeyboardFocus(WidgetToFocusPath, EFocusCause::SetDirectly);
		WidgetToFocusPath.GetWindow()->SetWidgetToFocusOnActivate(EditableText);

		// Trigger a text change to filter the selection for an empty search
		OnFilterTextChanged(FText::GetEmpty());

		return EActiveTimerReturnType::Stop;
	}

	return EActiveTimerReturnType::Continue;
}

#undef LOCTEXT_NAMESPACE