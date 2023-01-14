// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "HdiTutorialsExtension.h"

#include "QuickMenuSettings.h"

#define LOCTEXT_NAMESPACE "QuickActions"

TArray<TSharedPtr<FQuickCommandEntry>> UHdiTutorialsExtension::GetCommands(const FToolMenuContext& Context)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UHdiTutorialsExtension::GetCommands);

	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	for (const FTutorialInfo& Tutorial : Tutorials)
	{
		const TSharedPtr<FQuickCommandEntry> TutorialEntry = MakeShared<FQuickCommandEntry>();
		TutorialEntry->Title = FText::FromString(Tutorial.Title);
		TutorialEntry->Tooltip = FText::FromString(Tutorial.Description);
		TutorialEntry->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Documentation");
		TutorialEntry->ExecuteCallback = FSimpleDelegate::CreateLambda(
			[Tutorial]()
			{
				FPlatformProcess::LaunchURL(*Tutorial.Url, nullptr, nullptr);
			}
		);

		OutCommands.Emplace(TutorialEntry);
	}

	return OutCommands;
}

int32 UHdiTutorialsExtension::GetPriority() const
{
	return -100;
}

bool UHdiTutorialsExtension::ShouldShow() const
{
	return GetDefault<UQuickMenuSettings>()->bIncludeTutorials;
}

#undef LOCTEXT_NAMESPACE