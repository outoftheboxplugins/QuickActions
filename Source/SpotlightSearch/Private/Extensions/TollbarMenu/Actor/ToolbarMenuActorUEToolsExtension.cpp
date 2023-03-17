// Fill out your copyright notice in the Description page of Project Settings.


#include <IMergeActorsModule.h>

#include "IMergeActorsTool.h"
#include "ToolbarMenuActorUEToolsExtension.h"

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