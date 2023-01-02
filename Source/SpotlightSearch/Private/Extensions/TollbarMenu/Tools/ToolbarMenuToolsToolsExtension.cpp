// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuToolsToolsExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuToolsToolsExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;
	constexpr int32 NumFindInBlueprintsTabs = 4;
	for (int32 FindIdx = 0; FindIdx < NumFindInBlueprintsTabs; FindIdx++)
	{
		const TSharedPtr<FQuickCommandEntry> FindInBlueprintsTab = MakeShared<FQuickCommandEntry>();
		FindInBlueprintsTab->Title = FText::Format(NSLOCTEXT("FindInBlueprintManager", "GlobalFindResultsDisplayName", "Find in Blueprints {0}"), FText::AsNumber(FindIdx + 1));
		FindInBlueprintsTab->Tooltip = NSLOCTEXT("FindInBlueprintManager", "GlobalFindResultsMenuTooltipText", "Find references to functions, events and variables in all Blueprints.");
		FindInBlueprintsTab->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "BlueprintEditor.FindInBlueprints.MenuIcon");
		FindInBlueprintsTab->ExecuteCallback = FSimpleDelegate::CreateLambda(
			[FindIdx]()
			{
				const FName TabID = FName(*FString::Printf(TEXT("GlobalFindResults_%02d"), FindIdx + 1));
				FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TabID));
			}
		);

		OutCommands.Add(FindInBlueprintsTab);
	}

	return OutCommands;
}