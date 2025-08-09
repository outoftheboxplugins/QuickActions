// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "SQuickMenuWindow.h"

#include <Widgets/Layout/SSeparator.h>

#include "QuickMenuDiscoverySubsystem.h"
#include "QuickMenuHelpers.h"
#include "QuickMenuSettings.h"
#include "QuickMenuStyle.h"
#include "HAL/PlatformApplicationMisc.h"

#define LOCTEXT_NAMESPACE "FQuickMenuModule"

// TODO: Show this menu in the middle of the Unreal screen instead of middle of the monitor

namespace
{
	int32 PositiveModulo(int32 i, int32 n)
	{
		return (i % n + n) % n;
	}
} // namespace

void SQuickMenuWindow::Construct(const FArguments& InArgs)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(SQuickMenuWindow::Construct);

	UQuickMenuSettings* Settings = GetMutableDefault<UQuickMenuSettings>();

	const UQuickMenuDiscoverySubsystem* DiscoverySubsystem = GEditor->GetEditorSubsystem<UQuickMenuDiscoverySubsystem>();
	AvailableCommands = DiscoverySubsystem->GetAllCommands();

	// clang-format off
	SWindow::Construct(SWindow::FArguments()
	.Style(&FAppStyle::Get().GetWidgetStyle<FWindowStyle>("NotificationWindow"))
	.CreateTitleBar(false)
	.ClientSize(Settings->WindowSize)
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
				// TODO: The horizontal box is needed for split view widgets, currently this solution is horrible, needs to be refactored 
				SAssignNew(HorizontalBox, SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(5.0f, 0.0f)
				[
					SAssignNew(ListView, SNonFocusingListView<FQuickMenuItem>)
					.ListItemsSource(&FilteredCommands)
					.OnGenerateRow(this, &SQuickMenuWindow::MakeCommandListItem)
					.OnEntryInitialized(this, &SQuickMenuWindow::OnEntryInitialized)
					.ScrollbarVisibility(EVisibility::Collapsed)
					.IsFocusable(false)
					.OnMouseButtonClick(this, &SQuickMenuWindow::OnItemClicked)
				]
			]
		]
	]);
	// clang-format on

	Settings->OnWindowSizeChanged.AddSP(this, &SQuickMenuWindow::OnWindowSizeSettingsChanged); 

	RegisterActiveTimer(0.0f, FWidgetActiveTimerDelegate::CreateSP(this, &SQuickMenuWindow::SetFocusPostConstruct));
}

bool SQuickMenuWindow::OnIsActiveChanged(const FWindowActivateEvent& ActivateEvent)
{
	if (ActivateEvent.GetActivationType() == FWindowActivateEvent::EA_Deactivate)
	{
		CloseWindow();
	}

	return SWindow::OnIsActiveChanged(ActivateEvent);
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

void SQuickMenuWindow::OnFilterTextChanged(const FText& Text)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(SQuickMenuWindow::OnFilterTextChanged);

	TArray<FQuickMenuItem> LocalCommands = AvailableCommands;
	FilteredCommands.Empty();

	if(Text.IsEmpty())
	{
		const UQuickMenuSettings* Settings = GetDefault<UQuickMenuSettings>();
		if(Settings->bShowAllOptionsWhenEmpty)
		{
			FilteredCommands = LocalCommands;
		}
		else
		{
			GetRecentCommands(LocalCommands, FilteredCommands);
		}
	}
	else
	{
		const FString& FilterText = Text.ToString();
		GetAbbreviationsCommands(LocalCommands, FilteredCommands, FilterText);
		GetPerfectMatchesCommands(LocalCommands, FilteredCommands, FilterText);
		GetFuzzyMatchesCommands(LocalCommands, FilteredCommands, FilterText);
	}

	ListView->RequestListRefresh();
	UpdateSelection(0);
}

void SQuickMenuWindow::GetRecentCommands(TArray<FQuickMenuItem>& AvailableActions, TArray<FQuickMenuItem>& OutResult)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(SQuickMenuWindow::GetRecentCommands);

	const UQuickMenuSettings* Settings = GetDefault<UQuickMenuSettings>();
	const TArray<FString>& RecentCommands = Settings->GetRecentCommands();

	for (const FString& Command : RecentCommands)
	{
		if (Command.IsEmpty())
		{
			continue;
		}

		const int32 CommandIndex = AvailableActions.IndexOfByPredicate(
			[Command](const FQuickMenuItem& Entry)
			{
				return Entry->GetUniqueCommandName() == Command;
			}
		);

		if (CommandIndex != INDEX_NONE)
		{
			OutResult.Emplace(AvailableActions[CommandIndex]);
			AvailableActions.RemoveAt(CommandIndex);
		}
	}
}

void SQuickMenuWindow::OnWindowSizeSettingsChanged(FVector2D NewSize)
{
	const float DPIScale = FPlatformApplicationMisc::GetDPIScaleFactorAtPoint(0, 0);
	const FVector2D ScaledSize = GetWindowSizeFromClientSize(NewSize * DPIScale, DPIScale);
	Resize(ScaledSize);

	const FSlateRect AutoCenterRect = FSlateApplicationBase::Get().GetPreferredWorkArea();

	const FVector2D DisplayTopLeft( AutoCenterRect.Left, AutoCenterRect.Top );
	const FVector2D DisplaySize( AutoCenterRect.Right - AutoCenterRect.Left, AutoCenterRect.Bottom - AutoCenterRect.Top );

	const FVector2D ScreenCenter = DisplayTopLeft + (DisplaySize - ScaledSize) * 0.5f;
	MoveWindowTo(ScreenCenter);
}

void SQuickMenuWindow::GetAbbreviationsCommands(TArray<FQuickMenuItem>& AvailableActions, TArray<FQuickMenuItem>& OutResult, const FString& FilterText) const
{
	for (auto It = AvailableActions.CreateIterator(); It; ++It)
	{
		const FQuickMenuItem& Command = *It;
		if (QuickMenuHelpers::IsAbbreviation(Command->GetCommandName(), FilterText))
		{
			OutResult.Add(*It);
			It.RemoveCurrent();
		}
	}
}

void SQuickMenuWindow::GetPerfectMatchesCommands(TArray<FQuickMenuItem>& AvailableActions, TArray<FQuickMenuItem>& OutResult, const FString& FilterText) const
{
	for (auto It = AvailableActions.CreateIterator(); It; ++It)
	{
		const FQuickMenuItem& Command = *It;
		if (QuickMenuHelpers::IsPotentialMatchTo(Command->GetCommandName(), FilterText))
		{
			OutResult.Add(*It);
			It.RemoveCurrent();
		}
	}
}

void SQuickMenuWindow::GetFuzzyMatchesCommands(TArray<FQuickMenuItem>& AvailableActions, TArray<FQuickMenuItem>& OutResult, const FString& FilterText) const
{
	const UQuickMenuSettings* Settings = GetDefault<UQuickMenuSettings>();
	const float MinimumMatchPercentage = Settings->FuzzySearchMatchPercentage;

	TMap<FQuickMenuItem, float> GoodMatches;
	for (auto It = AvailableActions.CreateIterator(); It; ++It)
	{
		const FQuickMenuItem& Command = *It;
		const float MatchScore = QuickMenuHelpers::GetMatchPercentage(Command->GetCommandName(), FilterText);
		if (MatchScore > MinimumMatchPercentage)
		{
			GoodMatches.Emplace(Command, MatchScore);
			It.RemoveCurrent();
		}
	}

	GoodMatches.ValueSort(TGreater<float>());
	for (const auto& Match : GoodMatches)
	{
		OutResult.Emplace(Match.Key);
	}
}

void SQuickMenuWindow::OnEntryInitialized(TSharedRef<FQuickCommandEntry> QuickCommandEntry, const TSharedRef<ITableRow>& TableRow)
{
	QuickCommandEntry->OnItemScrolledIntoView.ExecuteIfBound();
}

TSharedRef<ITableRow> SQuickMenuWindow::MakeCommandListItem(FQuickMenuItem Selection, const TSharedRef<STableViewBase>& OwnerTable)
{
	const bool bCanExecute = Selection->IsAllowedToExecute();

	TSharedPtr<SWidget> Icon;
	if (Selection->CustomIconWidget.IsSet())
	{
		Icon = Selection->CustomIconWidget.Get();
	}
	else
	{
		Icon = SNew(SImage).Image(Selection->Icon.Get().GetIcon());
	}

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
						Icon.ToSharedRef()
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

void SQuickMenuWindow::OnItemClicked(FQuickMenuItem QuickCommandEntry)
{
	TryExecuteCommand(QuickCommandEntry);
}

void SQuickMenuWindow::TryExecuteCommand(const FQuickMenuItem& CurrentCommand)
{
	if (!CurrentCommand->IsAllowedToExecute())
	{
		return;
	}

	UQuickMenuSettings* Settings = GetMutableDefault<UQuickMenuSettings>();
	Settings->RegisterRecentCommand(CurrentCommand->GetUniqueCommandName());

	(void)CurrentCommand->ExecuteCallback.ExecuteIfBound();
	CloseWindow();
}

void SQuickMenuWindow::ConfirmSelection()
{
	if (FilteredCommands.IsEmpty())
	{
		// No entries to go through
		return;
	}

	const FQuickMenuItem& CurrentCommand = FilteredCommands[SelectionIndex];
	TryExecuteCommand(CurrentCommand);
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

#undef LOCTEXT_NAMESPACE