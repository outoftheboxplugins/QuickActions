﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "HdiTutorialsExtensions.h"

#include "WtfHdiTutorialSettings.h"

#define LOCTEXT_NAMESPACE "QuickActions"

TArray<FQuickCommandEntry> UHdiTutorialsExtensions::GetCommands()
{
	TArray<FQuickCommandEntry> OutCommands;
	const UWtfHdiTutorialSettings* TutorialSettings = GetDefault<UWtfHdiTutorialSettings>();

	FQuickCommandEntry ToggleTutorials;
	ToggleTutorials.Title = TutorialSettings->bIncludeTutorials ? LOCTEXT("DisableTutorials", "Disable Tutorials") : LOCTEXT("EnableTutorials", "Enable Tutorials");
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
			GetMutableDefault<UWtfHdiTutorialSettings>()->ToggleIncludeTutorials();
		}
	);

	OutCommands.Emplace(ToggleTutorials);

	if (!TutorialSettings->bIncludeTutorials)
	{
		return OutCommands;
	}

	for (const FTutorialInfo& Tutorial : TutorialSettings->Tutorials)
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

	return OutCommands;
}
int32 UHdiTutorialsExtensions::GetPriority() const
{
	return -100;
}

#undef LOCTEXT_NAMESPACE