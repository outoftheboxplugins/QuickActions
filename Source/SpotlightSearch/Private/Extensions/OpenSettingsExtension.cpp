// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.
// Contributed by: fpwong (https://twitter.com/funcpwong) in BenUI(https://twitter.com/_benui)'s discord

#include "OpenSettingsExtension.h"

#include "ISettingsCategory.h"
#include "ISettingsContainer.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "QuickMenuSettings.h"

#define LOCTEXT_NAMESPACE "QuickActions"

// TODO: Check if the Container.IsValid and Category.IsValid are really necessary

TArray<TSharedPtr<FQuickCommandEntry>> UOpenSettingsExtension::GetCommands(const FToolMenuContext& Context)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UOpenSettingsExtension::GetCommands);

	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

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

			for (const TSharedPtr<ISettingsSection>& Section : AllSections)
			{
				// TODO: When we introduce keywords or matching callbacks all of those values should trigger matches
				const FName ContainerName = Container->GetName();
				const FName CategoryName = Category->GetName();
				const FName SectionName = Section->GetName();

				TSharedPtr<FQuickCommandEntry> OpenSettings = MakeShared<FQuickCommandEntry>();
				OpenSettings->Title = FText::Format(LOCTEXT("OpenSettings", "Open {0}->{1} settings"), Category->GetDisplayName(), Section->GetDisplayName());
				OpenSettings->Tooltip =
					FText::Format(LOCTEXT("OpenSettingsTip", "Open {0}->{1} settings inside the {2} container"), Category->GetDisplayName(), Section->GetDisplayName(), Container->GetDisplayName());
				OpenSettings->Icon = FSlateIcon(FAppStyle::Get().GetStyleSetName(), "Icons.Settings");
				OpenSettings->ExecuteCallback = FSimpleDelegate::CreateLambda(
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

int32 UOpenSettingsExtension::GetPriority() const
{
	return -100;
}

bool UOpenSettingsExtension::ShouldShow() const
{
	return GetDefault<UQuickMenuSettings>()->bIncludeSettingSections;
}

#undef LOCTEXT_NAMESPACE