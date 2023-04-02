// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "QuickMenuExtension.generated.h"

using FExecuteCommandDelegate = TDelegate<void()>;
using FCanExecuteCommandDelegate = TDelegate<bool()>;

/**
 * @brief Base class for all entries displayed in the quick commands menu
 */
struct QUICKMENU_API FQuickCommandEntry
{
	FQuickCommandEntry() = default;
	FQuickCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList);
	FQuickCommandEntry(const FToolMenuEntry& Block, const FToolMenuContext& Context);

	virtual ~FQuickCommandEntry() = default;

	/**
	 * @brief Text displayed as the entry name in the command list
	 */
	TAttribute<FText> Title;
	/**
	 * @brief Text displayed when more information about the command is required
	 */
	TAttribute<FText> Tooltip;
	/**
	 * @brief Text displayed as the command shortcut
	 */
	TAttribute<FText> InputText;
	/**
	 * @brief Icon displayed as the entry icon in the command list
	 */
	TAttribute<FSlateIcon> Icon;

	/**
	 * @brief Callback executed when we want to execute this action
	 */
	FExecuteCommandDelegate ExecuteCallback;
	/**
	 * @brief Callback executed to determine if we are allowed to execute this action
	 * @note If the callback is not bound, we are always allowed to execute the action
	 */
	FCanExecuteCommandDelegate CanExecuteCallback;

	/**
	 * @brief Evaluates the current command state to determine if we are allowed to execute the command now.
	 * @return true if we can execute the command now, false otherwise
	 */
	bool IsAllowedToExecute() const;
	/**
	 * @brief Name to be displayed for this command's menu entry
	 */
	FString GetCommandName() const;
	/**
	 * @brief Creates a unique identifier for this command, persistent across multiple menu instances and editor launches
	 * @return Unique identifier for this command
	 */
	virtual FString GetUniqueCommandName() const;
	/**
	 * @brief Allows derived classes to construct an additional widget to be displayed in a split view when the command is highlighted
	 * @return The Widget to display in a split view or nullptr
	 */
	virtual TSharedPtr<SWidget> GetSplitViewWidget() { return {}; }
};

/**
 * @brief Class specialized in displaying simple on/off toggle switches as commands
 */
struct QUICKMENU_API FQuickSwitchCommandEntry : FQuickCommandEntry
{
	FQuickSwitchCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList, bool bIsEnabled);

private:
	// Begin FQuickCommandEntry interface
	virtual FString GetUniqueCommandName() const override;
	// End FQuickCommandEntry interface

	/**
	 * @brief Original Title of the switch command so we can have a consistent name even if the switch is flipped
	 * @example "Enable: High Quality Shadows" and "Disable: High Quality Shadows" should have the same Switch Tite: "High Quality Shadows"
	 */
	TAttribute<FText> SwitchTitle;
};

/**
 * Aids in finding QuickAction menu entries when we are collecting them in a composition pattern
 */
UCLASS(Abstract, Blueprintable)
class QUICKMENU_API UQuickMenuExtension : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief Generates the commands this collector wants to add to the final list
	 * @param Context Context we are building the list in (TODO: Document this parameter better)
	 * @return List of the commands generated
	 */
	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) { return {}; }
	/**
	 * @brief Determines the order in which the commands found by this extension will be placed in the list
	 * @note Bigger priority will be show before. Lower priority will show up after
	 * @return Integer denoting order.
	 */
	virtual int32 GetPriority() const { return 0; }
	/**
	 * @brief Determines if we want or not to display the actions found by this collector
	 * @return true if we want to show them, false otherwise
	 */
	virtual bool ShouldShow() const { return true; }

protected:
	// TODO: Should we consider moving this to a helper class since it doesn't use any member functions/variables?
	/**
	 * @brief Automatically collects the commands from a menu section
	 * @param OutCommands Commands generated from the menu section
	 * @param Context Context we are building this menu into
	 * @param MenuName Name of the menu we want to collect the section from
	 * @param SectionName Name of the section we want to collect the actions from
	 */
	void CollectActionsFromMenuSection(TArray<TSharedPtr<FQuickCommandEntry>>& OutCommands, const FToolMenuContext& Context, FName MenuName, FName SectionName) const;
};