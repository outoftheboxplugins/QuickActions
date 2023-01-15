// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "PackageExtension.h"

#include <DesktopPlatformModule.h>
#include <GameProjectGenerationModule.h>
#include <IDesktopPlatform.h>
#include <InstalledPlatformInfo.h>
#include <Interfaces/IProjectManager.h>
#include <Interfaces/ITurnkeySupportModule.h>
#include <Settings/ProjectPackagingSettings.h>

#include "SPackageSelector.h"

namespace
{
	FSlateIcon GetPlatformIcon(FName IniPlatformName)
	{
		return FSlateIcon(FAppStyle::Get().GetStyleSetName(), FDataDrivenPlatformInfoRegistry::GetPlatformInfo(IniPlatformName).GetIconStyleName(EPlatformIconSize::Large));
	}

	bool CanPackageForPlatform(const TTuple<FName, FDataDrivenPlatformInfo>& PlatformInfo)
	{
		const FName& PlatformName = PlatformInfo.Key;
		const FDataDrivenPlatformInfo& PlatformData = PlatformInfo.Value;

		FProjectStatus ProjectStatus;
		const bool bProjectStatusIsValid = IProjectManager::Get().QueryStatusForCurrentProject(ProjectStatus);

		if (PlatformData.bIsFakePlatform || PlatformData.bEnabledForUse == false)
		{
			return false;
		}

		if (FDataDrivenPlatformInfoRegistry::IsPlatformHiddenFromUI(PlatformName))
		{
			return false;
		}

		if (!FDataDrivenPlatformInfoRegistry::HasCompiledSupportForPlatform(PlatformName, FDataDrivenPlatformInfoRegistry::EPlatformNameType::Ini))
		{
			return false;
		}

		if (bProjectStatusIsValid && !ProjectStatus.IsTargetPlatformSupported(PlatformName))
		{
			return false;
		}

		if (ITurnkeySupportModule::Get().GetSdkInfo(PlatformName, false).Status != ETurnkeyPlatformSdkStatus::Valid)
		{
			return false;
		}

		return true;
	}
} // namespace

FQuickPackageCommandEntry::FQuickPackageCommandEntry() : FQuickCommandEntry()
{
	Title = INVTEXT("Package");
}
TSharedPtr<SWidget> FQuickPackageCommandEntry::GetSplitViewWidget()
{
	return SNew(SPackageSelector);
}

TArray<TSharedPtr<FQuickCommandEntry>> UPackageExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	OutCommands.Emplace(MakeShared<FQuickPackageCommandEntry>());

	return OutCommands;

	for (const TTuple<FName, FDataDrivenPlatformInfo>& Pair : FDataDrivenPlatformInfoRegistry::GetAllPlatformInfos())
	{
		if (!CanPackageForPlatform(Pair))
		{
			continue;
		}

		const FName PlatformName = Pair.Key;
		FGameProjectGenerationModule& GameProjectModule = FModuleManager::LoadModuleChecked<FGameProjectGenerationModule>(TEXT("GameProjectGeneration"));
		EProjectType ProjectType = GameProjectModule.Get().ProjectHasCodeFiles() ? EProjectType::Code : EProjectType::Content;
		TArray<EProjectPackagingBuildConfigurations> PackagingConfigurations = UProjectPackagingSettings::GetValidPackageConfigurations();
		for (EProjectPackagingBuildConfigurations PackagingConfiguration : PackagingConfigurations)
		{
			const UProjectPackagingSettings::FConfigurationInfo& ConfigurationInfo = UProjectPackagingSettings::ConfigurationInfo[static_cast<int>(PackagingConfiguration)];

			if (FInstalledPlatformInfo::Get().IsValid(TOptional<EBuildTargetType>(), TOptional<FString>(), ConfigurationInfo.Configuration, ProjectType, EInstalledPlatformState::Downloaded))
			{
				FProjectStatus ProjectStatus;
				bool bHasCode = IProjectManager::Get().QueryStatusForCurrentProject(ProjectStatus) && ProjectStatus.bCodeBasedProject;

				IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
				TArray<FTargetInfo> Targets = bHasCode ? DesktopPlatform->GetTargetsForCurrentProject() : DesktopPlatform->GetTargetsForProject(FString());

				Targets.Sort(
					[](const FTargetInfo& A, const FTargetInfo& B)
					{
						return A.Name < B.Name;
					}
				);

				const TArray<FTargetInfo> ValidTargets = Targets.FilterByPredicate(
					[](const FTargetInfo& Target)
					{
						return Target.Type == EBuildTargetType::Game || Target.Type == EBuildTargetType::Client || Target.Type == EBuildTargetType::Server;
					}
				);

				for (const FTargetInfo& Target : ValidTargets)
				{
					const TSharedPtr<FQuickCommandEntry> PlatformEntry = MakeShared<FQuickCommandEntry>();
					PlatformEntry->Title = FText::Format(INVTEXT("{0} - {1} - {2}"), FText::FromString(PlatformName.ToString()), ConfigurationInfo.Name, FText::FromString(Target.Name));
					PlatformEntry->Icon = GetPlatformIcon(PlatformName);

					OutCommands.Emplace(PlatformEntry);
				}
			}
		}
	}

	return OutCommands;
}