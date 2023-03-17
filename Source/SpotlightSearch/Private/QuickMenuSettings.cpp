// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "QuickMenuSettings.h"

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