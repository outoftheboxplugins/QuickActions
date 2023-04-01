// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "QuickMenuSettings.h"

void UQuickMenuSettings::RegisterRecentCommand(const FString& CommandName)
{
	// Remove from the list so we can re-add it on top
	RecentCommands.Remove(CommandName);
	RecentCommands.EmplaceAt(0, CommandName);

	// Prevent the array from storing more items than the user intended
	RecentCommands.SetNum(MaxRecentCommands);

	SaveConfig();
}

const TArray<FString>& UQuickMenuSettings::GetRecentCommands() const
{
	return RecentCommands;
}

FName UQuickMenuSettings::GetContainerName() const
{
	return TEXT("Editor");
}

FName UQuickMenuSettings::GetCategoryName() const
{
	return TEXT("Out-of-the-Box Plugins");
}

FName UQuickMenuSettings::GetSectionName() const
{
	return TEXT("Quick Menu");
}

#if WITH_EDITOR
FText UQuickMenuSettings::GetSectionText() const
{
	const FName DisplaySectionName = GetSectionName();
	return FText::FromName(DisplaySectionName);
}
#endif