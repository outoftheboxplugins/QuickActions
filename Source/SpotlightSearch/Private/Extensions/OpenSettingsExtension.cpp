// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "OpenSettingsExtension.h"

#include "ISettingsCategory.h"
#include "ISettingsContainer.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"

#define LOCTEXT_NAMESPACE "QuickActions"

// TODO: Check if the Container.IsValid and Category.IsValid are really necessary

TArray<FQuickCommandEntry> UOpenSettingsExtension::GetCommands()
{
	TArray<FQuickCommandEntry> OutCommands;

	// Courtesy of fpwong#1209 on BenUI's disocrd
	ISettingsModule& SettingsModule = FModuleManager::LoadModuleChecked<ISettingsModule>("Settings");
	TArray<FName> AllContainers;
	SettingsModule.GetContainerNames(AllContainers);
	for (auto ContainerIt : AllContainers)
	{
		TSharedPtr<ISettingsContainer> Container = SettingsModule.GetContainer(ContainerIt);
		if (!Container.IsValid())
		{
			continue;
		}

		TArray<TSharedPtr<ISettingsCategory>> AllCategories;
		Container->GetCategories(AllCategories);

		for (TSharedPtr<ISettingsCategory> Category : AllCategories)
		{
			if (!Category.IsValid())
			{
				continue;
			}

			TArray<TSharedPtr<ISettingsSection>> AllSections;
			Category->GetSections(AllSections);

			for (const TSharedPtr<ISettingsSection> Section : AllSections)
			{
				// TODO: When we introduce keywords or matching callbacks all of those values should trigger matches
				const FName ContainerName = Container->GetName();
				const FName CategoryName = Category->GetName();
				const FName SectionName = Section->GetName();

				FQuickCommandEntry OpenSettings;
				OpenSettings.Title = FText::Format(LOCTEXT("OpenSettings", "Open {0}-{0} settings"), Category->GetDisplayName(), Section->GetDisplayName());
				OpenSettings.Tooltip =
					FText::Format(LOCTEXT("OpenSettingsTip", "Open {0}-{1} settings modal inside {2}"), Category->GetDisplayName(), Section->GetDisplayName(), Container->GetDisplayName());
				OpenSettings.Icon = FSlateIcon(FAppStyle::Get().GetStyleSetName(), "Icons.Settings");
				OpenSettings.ExecuteCallback = FSimpleDelegate::CreateLambda(
					[ContainerName, CategoryName, SectionName]()
					{
						FModuleManager::LoadModuleChecked<ISettingsModule>("Settings").ShowViewer(ContainerName, CategoryName, SectionName);
					}
				);

				OutCommands.Add(OpenSettings);
			}
		}
	}

	return OutCommands;
}

#undef LOCTEXT_NAMESPACE