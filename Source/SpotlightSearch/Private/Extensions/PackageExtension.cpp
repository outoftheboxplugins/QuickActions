// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "PackageExtension.h"

#include <InstalledPlatformInfo.h>
#include <Interfaces/IProjectManager.h>
#include <Interfaces/ITurnkeySupportModule.h>
#include <Settings/ProjectPackagingSettings.h>

#include "GameProjectGenerationModule.h"

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

TArray<TSharedPtr<FQuickCommandEntry>> UPackageExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

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
				const TSharedPtr<FQuickCommandEntry> PlatformEntry = MakeShared<FQuickCommandEntry>();
				PlatformEntry->Title = FText::Format(INVTEXT("{0} - {1}"), FText::FromString(PlatformName.ToString()), ConfigurationInfo.Name);
				PlatformEntry->Icon = GetPlatformIcon(PlatformName);

				OutCommands.Emplace(PlatformEntry);
			}
		}
	}

	return OutCommands;
}