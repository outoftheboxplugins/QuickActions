// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuActorUEToolsExtension.h"

#include <IMergeActorsModule.h>

#include "IMergeActorsTool.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuActorUEToolsExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	IMergeActorsModule& MergeActorsModule = IMergeActorsModule::Get();
	TArray<IMergeActorsTool*> MergeActorTools;
	MergeActorsModule.Get().GetRegisteredMergeActorsTools(MergeActorTools);

	for (IMergeActorsTool* Tool : MergeActorTools)
	{
		const TSharedPtr<FQuickCommandEntry> ToolEntry = MakeShared<FQuickCommandEntry>();
		ToolEntry->Title = Tool->GetToolNameText();
		ToolEntry->Tooltip = Tool->GetTooltipText();
		ToolEntry->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), Tool->GetIconName());
		ToolEntry->CanExecuteCallback = TDelegate<bool()>::CreateLambda(
			[Tool]()
			{
				return Tool->CanMergeFromSelection();
			}
		);
		ToolEntry->ExecuteCallback = FSimpleDelegate::CreateLambda(
			[Tool]()
			{
				Tool->RunMergeFromSelection();
			}
		);

		OutCommands.Add(ToolEntry);
	}

	return OutCommands;
}