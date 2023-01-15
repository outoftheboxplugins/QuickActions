// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "QuickMenuExtension.generated.h"

struct FQuickCommandEntry
{
	// TODO: Check if we need to default the move constructor as well
	FQuickCommandEntry() = default;
	FQuickCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList);
	FQuickCommandEntry(const FToolMenuEntry& Block, const FToolMenuContext& Context);
	virtual ~FQuickCommandEntry() = default;

	TAttribute<FText> Title;
	TAttribute<FText> Tooltip;
	TAttribute<FSlateIcon> Icon;

	FSimpleDelegate ExecuteCallback;
	// TODO: Change this delegate type to something nice like: FCanExecuteAction
	TDelegate<bool()> CanExecuteCallback;

	bool IsAllowedToExecute() const;
	virtual TSharedPtr<SWidget> GetSplitViewWidget() { return {}; };
};

struct FQuickSwitchCommandEntry : FQuickCommandEntry
{
	FQuickSwitchCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList, bool bIsEnabled);
};

/**
 *
 */
UCLASS(Abstract, Blueprintable)
class SPOTLIGHTSEARCH_API UQuickMenuExtension : public UObject
{
	GENERATED_BODY()

public:
	// TODO: Create a blueprint friendly version of this
	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) { return {}; }

	// Bigger priority will be show before. Lower priority will show up after
	virtual int32 GetPriority() const { return 0; }

	virtual bool ShouldShow() const { return true; }

protected:
	void CollectActionsFromMenuSection(TArray<TSharedPtr<FQuickCommandEntry>>& OutCommands, const FToolMenuContext& Context, FName MenuName, FName SectionName) const;
};