// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "QuickMenuExtension.generated.h"

using FExecuteCommandDelegate = TDelegate<void()>;
using FCanExecuteCommandDelegate = TDelegate<bool()>;

struct QUICKMENU_API FQuickCommandEntry
{
	FQuickCommandEntry() = default;
	FQuickCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList);
	FQuickCommandEntry(const FToolMenuEntry& Block, const FToolMenuContext& Context);
	
	virtual ~FQuickCommandEntry() = default;

	TAttribute<FText> Title;
	TAttribute<FText> Tooltip;
	TAttribute<FText> InputText;
	TAttribute<FSlateIcon> Icon;

	FExecuteCommandDelegate ExecuteCallback;
	FCanExecuteCommandDelegate CanExecuteCallback;

	bool IsAllowedToExecute() const;
	FString GetCommandName() const;
	virtual TSharedPtr<SWidget> GetSplitViewWidget() { return {}; };
};

struct QUICKMENU_API FQuickSwitchCommandEntry : FQuickCommandEntry
{
	FQuickSwitchCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList, bool bIsEnabled);
};

/**
 *
 */
UCLASS(Abstract, Blueprintable)
class QUICKMENU_API UQuickMenuExtension : public UObject
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