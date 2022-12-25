// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "HdiTutorialsExtension.h"

#include "QuickMenuSettings.h"

#define LOCTEXT_NAMESPACE "QuickActions"

TArray<FQuickCommandEntry> UHdiTutorialsExtension::GetCommands()
{
	const bool bIsShowingTutorials = GetDefault<UQuickMenuSettings>()->bIncludeTutorials;

	TArray<FQuickCommandEntry> OutCommands;

	FQuickCommandEntry ToggleTutorials;
	ToggleTutorials.Title = bIsShowingTutorials ? LOCTEXT("DisableTutorials", "Disable Tutorials") : LOCTEXT("EnableTutorials", "Enable Tutorials");
	ToggleTutorials.Tooltip = LOCTEXT("ToggleTutorials", "Toggles the tutorials showing in the menu");
	ToggleTutorials.Icon = FSlateIcon(FAppStyle::Get().GetStyleSetName(), "Icons.Settings");
	ToggleTutorials.CanExecuteCallback = TDelegate<bool()>::CreateLambda(
		[]()
		{
			return true;
		}
	);
	ToggleTutorials.ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			GetMutableDefault<UQuickMenuSettings>()->ToggleIncludeTutorials();
		}
	);

	OutCommands.Emplace(ToggleTutorials);

	if (bIsShowingTutorials)
	{
		for (const FTutorialInfo& Tutorial : Tutorials)
		{
			FQuickCommandEntry TutorialEntry;
			TutorialEntry.Title = FText::FromString(Tutorial.Title);
			TutorialEntry.Tooltip = FText::FromString(Tutorial.Description);
			TutorialEntry.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Documentation");
			TutorialEntry.CanExecuteCallback = TDelegate<bool()>::CreateLambda(
				[]()
				{
					return true;
				}
			);
			TutorialEntry.ExecuteCallback = FSimpleDelegate::CreateLambda(
				[Tutorial]()
				{
					FPlatformProcess::LaunchURL(*Tutorial.Url, nullptr, nullptr);
				}
			);

			OutCommands.Emplace(TutorialEntry);
		}
	}

	return OutCommands;
}

int32 UHdiTutorialsExtension::GetPriority() const
{
	return -100;
}

#undef LOCTEXT_NAMESPACE