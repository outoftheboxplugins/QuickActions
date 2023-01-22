// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "SPackageSelector.h"

#include <DesktopPlatformModule.h>
#include <GameProjectGenerationModule.h>
#include <IDesktopPlatform.h>
#include <InstalledPlatformInfo.h>
#include <Interfaces/IProjectManager.h>
#include <Interfaces/ITurnkeySupportModule.h>
#include <Settings/ProjectPackagingSettings.h>

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

void SPackageSelector::Construct(const FArguments& InArgs)
{
	for (const TTuple<FName, FDataDrivenPlatformInfo>& Pair : FDataDrivenPlatformInfoRegistry::GetAllPlatformInfos())
	{
		if (!CanPackageForPlatform(Pair))
		{
			continue;
		}

		const FName PlatformName = Pair.Key;
		PlatformSuggestions.Emplace(PlatformName.ToString());
	}

	FGameProjectGenerationModule& GameProjectModule = FModuleManager::LoadModuleChecked<FGameProjectGenerationModule>(TEXT("GameProjectGeneration"));
	const EProjectType ProjectType = GameProjectModule.Get().ProjectHasCodeFiles() ? EProjectType::Code : EProjectType::Content;
	TArray<EProjectPackagingBuildConfigurations> PackagingConfigurations = UProjectPackagingSettings::GetValidPackageConfigurations();
	for (EProjectPackagingBuildConfigurations PackagingConfiguration : PackagingConfigurations)
	{
		const UProjectPackagingSettings::FConfigurationInfo& ConfigurationInfo = UProjectPackagingSettings::ConfigurationInfo[static_cast<int>(PackagingConfiguration)];

		if (FInstalledPlatformInfo::Get().IsValid(TOptional<EBuildTargetType>(), TOptional<FString>(), ConfigurationInfo.Configuration, ProjectType, EInstalledPlatformState::Downloaded))
		{
			BinarySuggestions.Emplace(ConfigurationInfo.Name.ToString());
		}
	}

	FProjectStatus ProjectStatus;
	const bool bHasCode = IProjectManager::Get().QueryStatusForCurrentProject(ProjectStatus) && ProjectStatus.bCodeBasedProject;

	const IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
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
		TargetSuggestions.Emplace(Target.Name);
	}

	// clang-format off
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			GenerateOptions(INVTEXT("Platforms"), PlatformSuggestions, PlatformIndex)	
		]

		+ SVerticalBox::Slot()
		[
			GenerateOptions(INVTEXT("Binary"), BinarySuggestions, BinaryIndex)
		]

		+ SVerticalBox::Slot()
		[
			GenerateOptions(INVTEXT("Target"), TargetSuggestions, TargetIndex)
		]
	];
	// clang-format on

	// TODO: This should come from either a config or a recent configuration selection.
	// PlatformListView->SetSelection(PlatformSuggestions[0]);
	// BinaryListView->SetSelection(BinarySuggestions[0]);
	// TargetListView->SetSelection(TargetSuggestions[0]);
}

TSharedRef<SWidget> SPackageSelector::GenerateOptions(const FText& Category, const TArray<FString>& Options, int32& CategoryIndex)
{
	// clang-format off
	TSharedRef<SVerticalBox> PlatformList = SNew(SVerticalBox);
	PlatformList->AddSlot()
	.AutoHeight()
	[
		SNew(STextBlock)
		.Text(Category)
	];

	for(const FString& Suggestion : Options)
	{
		const int32 CurrentIndex = Options.IndexOfByKey(Suggestion);
		
		PlatformList->AddSlot()
		.AutoHeight()
		[
			SNew(SCheckBox)
			.Style(FAppStyle::Get(), "RadioButton")
			.OnCheckStateChanged_Lambda([&CategoryIndex, CurrentIndex](ECheckBoxState InNewState)
			{
				CategoryIndex = CurrentIndex;
			})
			.IsChecked_Lambda([&CategoryIndex, CurrentIndex]()
			{
				return CategoryIndex == CurrentIndex ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
			})
			[
				SNew(STextBlock)
				.Text(FText::FromString(Suggestion))
			]
		];
	}
	// clang-format on

	return PlatformList;
}
