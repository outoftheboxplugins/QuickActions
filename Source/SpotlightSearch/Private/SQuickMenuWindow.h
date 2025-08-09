// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"
#include "SNonFocusingListView.h"

using FQuickMenuItem = TSharedRef<FQuickCommandEntry>;

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

private:
	// Begin SWindow interface.
	virtual bool OnIsActiveChanged(const FWindowActivateEvent& ActivateEvent) override;
	virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	// End SWindow interface.
	/**
	 * @brief Used to focus the filter textbox immediately following construction
	 */
	EActiveTimerReturnType SetFocusPostConstruct(double InCurrentTime, float InDeltaTime);
	/**
	 * TODO: Research if this and OnPreviewKeyDown can be merged together
	 * @brief Callback executed when a key is pressed while the textbox if focused
	 */
	FReply OnSearchKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);
	/**
	 * @brief Callback executed when the filter textbox content is changed
	 * @param Text current text we should filter for
	 */
	void OnFilterTextChanged(const FText& Text);
	/**
	 * @brief Filters out the recently ran commands from AvailableActions and constructs a list of them in OutResult
	 * @param AvailableActions Input list we will remove the matching commands from
	 * @param OutResult Output list we will add the matching commands to
	 */
	void GetRecentCommands(TArray<FQuickMenuItem>& AvailableActions, TArray<FQuickMenuItem>& OutResult);
	/**
	 * Callback executed when the QuickMenu settings -> WindowSize property is changed
	 */
	void OnWindowSizeSettingsChanged(FVector2D NewSize);
	/**
	 * @brief Filters out the commands with matching abbreviations from AvailableActions and constructs a list of them in OutResult
	 * @param AvailableActions Input list we will remove the matching commands from
	 * @param OutResult Output list we will add the matching commands to
	 * @param FilterText String we will use to perform to perform the filtering
	 */
	void GetAbbreviationsCommands(TArray<FQuickMenuItem>& AvailableActions, TArray<FQuickMenuItem>& OutResult, const FString& FilterText) const;
	/**
	 * @brief Filters out the commands with perfect matches from AvailableActions and constructs a list of them in OutResult
	 * @param AvailableActions Input list we will remove the matching commands from
	 * @param OutResult Output list we will add the matching commands to
	 * @param FilterText String we will use to perform to perform the filtering
	 */
	void GetPerfectMatchesCommands(TArray<FQuickMenuItem>& AvailableActions, TArray<FQuickMenuItem>& OutResult, const FString& FilterText) const;
	/**
	 * @brief Filters out the commands with fuzzy matches from AvailableActions and constructs a list of them in OutResult
	 * @param AvailableActions Input list we will remove the matching commands from
	 * @param OutResult Output list we will add the matching commands to
	 * @param FilterText String we will use to perform to perform the filtering
	 */
	void GetFuzzyMatchesCommands(TArray<FQuickMenuItem>& AvailableActions, TArray<FQuickMenuItem>& OutResult, const FString& FilterText) const;
	/**
	 * @brief Callback executed when a command entry is initialized by the ListView
	 * @param QuickCommandEntry The command entry that was initialized
	 * @param TableRow The row that was initialized in the ListView
	 */
	void OnEntryInitialized(TSharedRef<FQuickCommandEntry> QuickCommandEntry, const TSharedRef<ITableRow>& TableRow);
	/**
	 * @brief Generates the entry for a ListView based on a QuickCommandEntry
	 */
	TSharedRef<ITableRow> MakeCommandListItem(FQuickMenuItem Selection, const TSharedRef<STableViewBase>& OwnerTable);
	/**
	 * @brief Callback executed when an item in the list is clicked with the mouse
	 */
	void OnItemClicked(FQuickMenuItem QuickCommandEntry);
	/**
	 * @brief Trys to execute the currently hovered (arrow key selection) command 
	 */
	void ConfirmSelection();
	/**
	 * @brief Validates a command can be executed and if the test passes, runs the command
	 */
	void TryExecuteCommand(const FQuickMenuItem& CurrentCommand);
	/**
	 * @brief Moves the current selection up for down based on the input
	 * @param Change the number of entries we should move up (negative values) or down (positive values)
	 * @note Loops around if number is below 0 or exceeds max
	 */
	void UpdateSelection(int32 Change);
	/**
	 * @brief Determine if the command entries should display an explanatory tooltip below
	 * @return true if the description should be visible, false otherwise
	 */
	bool ShouldShowDescription() const;
	/**
	 * @brief Closes this dialog window making sure the destroy gets trigger only once.
	 */
	void CloseWindow();
	/**
	 * @brief Index of the currently selected command in the list.
	 */
	int32 SelectionIndex = 0;
	/**
	 * @brief Textbox shown on top to allow filtering of the commands below
	 */
	TSharedPtr<SEditableText> EditableText;
	/**
	 * @brief Layout container to display commands which require a split view
	 */
	TSharedPtr<SHorizontalBox> HorizontalBox;
	/**
	 * @brief ListView containing all the commands available after filtering
	 */
	TSharedPtr<SNonFocusingListView<FQuickMenuItem>> ListView;
	/**
	 * @brief List of all commands available to the users before filtering (fetched only once during construction)
	 */
	TArray<FQuickMenuItem> AvailableCommands;
	/**
	 * @brief List of commands available to the users after filtering
	 */
	TArray<FQuickMenuItem> FilteredCommands;
	/**
	 * @brief Whether the destroy was already initiated for this widget
	 */
	bool bWasClosed = false;
};