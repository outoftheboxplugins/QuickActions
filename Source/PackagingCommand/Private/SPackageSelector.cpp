// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "SPackageSelector.h"

#include <DesktopPlatformModule.h>
#include <GameProjectGenerationModule.h>
#include <IDesktopPlatform.h>
#include <InstalledPlatformInfo.h>
#include <Interfaces/IProjectManager.h>
#include <Interfaces/ITurnkeySupportModule.h>
#include <Settings/ProjectPackagingSettings.h>

#include "AnalyticsEventAttribute.h"
#include "DerivedDataCache/Public/DerivedDataCacheInterface.h"
#include "ITurnkeyIOModule.h"
#include "IUATHelperModule.h"
#include "PlatformInfo.h"
#include "ZenServerInterface.h"

namespace
{
	bool DoesProjectHaveCode()
	{
		FGameProjectGenerationModule& GameProjectModule = FModuleManager::LoadModuleChecked<FGameProjectGenerationModule>(TEXT("GameProjectGeneration"));
		return GameProjectModule.Get().ProjectHasCodeFiles();
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

	FString GetProjectPathForTurnkey()
	{
		if (FPaths::IsProjectFilePathSet())
		{
			return FPaths::ConvertRelativePathToFull(FPaths::GetProjectFilePath());
		}
		if (FApp::HasProjectName())
		{
			FString ProjectPath = FPaths::ProjectDir() / FApp::GetProjectName() + TEXT(".uproject");
			if (FPaths::FileExists(ProjectPath))
			{
				return ProjectPath;
			}
			ProjectPath = FPaths::RootDir() / FApp::GetProjectName() / FApp::GetProjectName() + TEXT(".uproject");
			if (FPaths::FileExists(ProjectPath))
			{
				return ProjectPath;
			}
		}
		return FString();
	}

	UProjectPackagingSettings* GetPackagingSettingsForPlatform(FName IniPlatformName)
	{
		FString PlatformString = IniPlatformName.ToString();
		UProjectPackagingSettings* PackagingSettings = nullptr;
		for (TObjectIterator<UProjectPackagingSettings> Itr; Itr; ++Itr)
		{
			if (Itr->GetConfigPlatform() == PlatformString)
			{
				PackagingSettings = *Itr;
				break;
			}
		}
		if (PackagingSettings == nullptr)
		{
			PackagingSettings = NewObject<UProjectPackagingSettings>(GetTransientPackage());
			// Prevent object from being GCed.
			PackagingSettings->AddToRoot();
			// make sure any changes to DefaultGame are updated in this class
			PackagingSettings->LoadSettingsForPlatform(PlatformString);
		}

		return PackagingSettings;
	}

	// extern LAUNCHERSERVICES_API bool HasPromotedTarget(const TCHAR* BaseDir, const TCHAR* TargetName, const TCHAR* Platform, EBuildConfiguration Configuration, const TCHAR* Architecture);
	bool ShouldBuildProject(UProjectPackagingSettings* PackagingSettings, const ITargetPlatform* TargetPlatform)
	{
		const UProjectPackagingSettings::FConfigurationInfo& ConfigurationInfo = UProjectPackagingSettings::ConfigurationInfo[(int)PackagingSettings->BuildConfiguration];

		// Get the target to build
		const FTargetInfo* Target = PackagingSettings->GetBuildTargetInfo();

		// Only build if the user elects to do so
		bool bBuild = false;
		if (PackagingSettings->Build == EProjectPackagingBuild::Always)
		{
			bBuild = true;
		}
		else if (PackagingSettings->Build == EProjectPackagingBuild::Never)
		{
			bBuild = false;
		}
		else if (PackagingSettings->Build == EProjectPackagingBuild::IfProjectHasCode)
		{
			bBuild = true;
			if (FApp::GetEngineIsPromotedBuild())
			{
				FString BaseDir;

				// Get the target name
				FString TargetName;
				if (Target == nullptr)
				{
					TargetName = TEXT("UnrealGame");
				}
				else
				{
					TargetName = Target->Name;
				}

				// Get the directory containing the receipt for this target, depending on whether the project needs to be built or not
				FString ProjectDir = FPaths::GetPath(FPaths::GetProjectFilePath());
				if (Target != nullptr && FPaths::IsUnderDirectory(Target->Path, ProjectDir))
				{
					UE_LOG(LogTemp, Log, TEXT("Selected target: %s"), *Target->Name);
					BaseDir = ProjectDir;
				}
				else
				{
					FText Reason;

					if (TargetPlatform->RequiresTempTarget(DoesProjectHaveCode(), ConfigurationInfo.Configuration, false, Reason))
					{
						UE_LOG(LogTemp, Log, TEXT("Project requires temp target (%s)"), *Reason.ToString());
						BaseDir = ProjectDir;
					}
					else
					{
						UE_LOG(LogTemp, Log, TEXT("Project does not require temp target"));
						BaseDir = FPaths::EngineDir();
					}
				}

				// Check if the receipt is for a matching promoted target
				FString UBTPlatformName = TargetPlatform->GetTargetPlatformInfo().DataDrivenPlatformInfo->UBTPlatformString;

				// extern LAUNCHERSERVICES_API bool HasPromotedTarget(const TCHAR* BaseDir, const TCHAR* TargetName, const TCHAR* Platform, EBuildConfiguration Configuration, const TCHAR*
				// Architecture); if (HasPromotedTarget(*BaseDir, *TargetName, *UBTPlatformName, ConfigurationInfo.Configuration, nullptr))
				{
					bBuild = false;
				}
			}
		}
		else if (PackagingSettings->Build == EProjectPackagingBuild::IfEditorWasBuiltLocally)
		{
			bBuild = !FApp::GetEngineIsPromotedBuild();
		}

		return bBuild;
	}
} // namespace


void SPackageSelector::StartPackage()
{
	FName IniPlatformName = FName(PlatformSuggestions[PlatformIndex]);

	// Copied over form CookOrPackage TurnkeySupportModule
	TArray<FAnalyticsEventAttribute> AnalyticsParamArray;

	// get a in-memory defaults which will have the user-settings, like the per-platform config/target platform stuff
	UProjectPackagingSettings* AllPlatformPackagingSettings = GetMutableDefault<UProjectPackagingSettings>();

	// installed builds only support standard Game type builds (not Client, Server, etc) so instead of looking up a setting that the user can't set,
	// always use the base PlatformInfo for Game builds, which will be named the same as the platform itself
	const PlatformInfo::FTargetPlatformInfo* PlatformInfo = nullptr;
	if (FApp::IsInstalled())
	{
		PlatformInfo = PlatformInfo::FindPlatformInfo(IniPlatformName);
	}
	else
	{
		PlatformInfo = PlatformInfo::FindPlatformInfo(AllPlatformPackagingSettings->GetTargetFlavorForPlatform(IniPlatformName));
	}
	// this is unexpected to be able to happen, but it could if there was a bad value saved in the UProjectPackagingSettings - if this trips, we should handle errors
	check(PlatformInfo != nullptr);

	const FString UBTPlatformString = PlatformInfo->DataDrivenPlatformInfo->UBTPlatformString;
	const FString ProjectPath = GetProjectPathForTurnkey();

	// force a save of dirty packages before proceeding to run UAT
	// this may delete UProjectPackagingSettings , don't hold it across this call
	// FTurnkeyEditorSupport::SaveAll();

	// get all the helper objects
	UProjectPackagingSettings* PackagingSettings = GetPackagingSettingsForPlatform(IniPlatformName);

	// basic BuildCookRun params we always want
	FString BuildCookRunParams = FString::Printf(TEXT("-nop4 -utf8output %s -cook "), TEXT("-nocompileeditor -skipbuildeditor"));


	// set locations to engine and project
	if (!ProjectPath.IsEmpty())
	{
		BuildCookRunParams += FString::Printf(TEXT(" -project=\"%s\""), *ProjectPath);
	}

	bool bIsProjectBuildTarget = false;
	const FTargetInfo* BuildTargetInfo = AllPlatformPackagingSettings->GetBuildTargetInfoForPlatform(IniPlatformName, bIsProjectBuildTarget);

	// Only add the -Target=... argument for code projects. Content projects will return UnrealGame/UnrealClient/UnrealServer here, but
	// may need a temporary target generated to enable/disable plugins. Specifying -Target in these cases will cause packaging to fail,
	// since it'll have a different name.
	if (BuildTargetInfo && bIsProjectBuildTarget)
	{
		BuildCookRunParams += FString::Printf(TEXT(" -target=%s"), *BuildTargetInfo->Name);
	}

	// let the editor add options (-unrealexe in particular)
	{
		FString Options;
		Options += FString::Printf(TEXT(" -unrealexe=\"%s\""), *FUnrealEdMisc::Get().GetExecutableForCommandlets());
		BuildCookRunParams += FString::Printf(TEXT(" %s"), *Options);
	}

	// set the platform we are preparing content for
	{
		BuildCookRunParams += FString::Printf(TEXT(" -platform=%s"), *UBTPlatformString);
	}

	// Append any extra UAT flags specified for this platform flavor
	if (!PlatformInfo->UATCommandLine.IsEmpty())
	{
		BuildCookRunParams += FString::Printf(TEXT(" %s"), *PlatformInfo->UATCommandLine);
	}

	// optional settings
	if (PackagingSettings->bSkipEditorContent)
	{
		BuildCookRunParams += TEXT(" -SkipCookingEditorContent");
	}
	if (FDerivedDataCacheInterface* DDC = TryGetDerivedDataCache())
	{
		const TCHAR* GraphName = DDC->GetGraphName();
		if (FCString::Strcmp(GraphName, DDC->GetDefaultGraphName()))
		{
			BuildCookRunParams += FString::Printf(TEXT(" -DDC=%s"), DDC->GetGraphName());
		}
	}
	if (FApp::IsEngineInstalled())
	{
		BuildCookRunParams += TEXT(" -installed");
	}

	if (PackagingSettings->bUseZenStore)
	{
#if WITH_EDITOR && UE_WITH_ZEN
		static UE::Zen::FScopeZenService TurnkeyStaticZenService;
#endif
		BuildCookRunParams += TEXT(" -zenstore");
	}

	// gather analytics
	const ITargetPlatform* TargetPlatform = GetTargetPlatformManager()->FindTargetPlatform(PlatformInfo->Name);
	TargetPlatform->GetPlatformSpecificProjectAnalytics(AnalyticsParamArray);

	// per mode settings
	FText ContentPrepDescription;
	FText ContentPrepTaskName;
	const FSlateBrush* ContentPrepIcon = nullptr;

	ContentPrepDescription = INVTEXT("Packaging project");
	ContentPrepTaskName = INVTEXT("Packaging");
	ContentPrepIcon = FAppStyle::Get().GetBrush(TEXT("MainFrame.PackageProject"));

	// let the user pick a target directory
	if (AllPlatformPackagingSettings->StagingDirectory.Path.IsEmpty())
	{
		AllPlatformPackagingSettings->StagingDirectory.Path = FPaths::ProjectDir();
	}

	FString OutFolderName;

	if (!FDesktopPlatformModule::Get()->OpenDirectoryDialog(
			FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr), INVTEXT("Package project...").ToString(), AllPlatformPackagingSettings->StagingDirectory.Path, OutFolderName
		))
	{
		return;
	}

	AllPlatformPackagingSettings->StagingDirectory.Path = OutFolderName;
	AllPlatformPackagingSettings->SaveConfig();


	BuildCookRunParams += TEXT(" -stage -archive -package");

	if (ShouldBuildProject(PackagingSettings, TargetPlatform))
	{
		BuildCookRunParams += TEXT(" -build");
	}

	if (PackagingSettings->FullRebuild)
	{
		BuildCookRunParams += TEXT(" -clean");
	}

	// Pak file(s) must be used when using container file(s)
	PackagingSettings->UsePakFile |= PackagingSettings->bUseIoStore;

	if (PackagingSettings->UsePakFile)
	{
		BuildCookRunParams += TEXT(" -pak");
		if (PackagingSettings->bUseIoStore)
		{
			BuildCookRunParams += TEXT(" -iostore");
		}

		if (PackagingSettings->bCompressed)
		{
			BuildCookRunParams += TEXT(" -compressed");
		}
	}

	if (PackagingSettings->IncludePrerequisites)
	{
		BuildCookRunParams += TEXT(" -prereqs");
	}

	if (!PackagingSettings->ApplocalPrerequisitesDirectory.Path.IsEmpty())
	{
		BuildCookRunParams += FString::Printf(TEXT(" -applocaldirectory=\"%s\""), *(PackagingSettings->ApplocalPrerequisitesDirectory.Path));
	}
	else if (PackagingSettings->IncludeAppLocalPrerequisites)
	{
		BuildCookRunParams += TEXT(" -applocaldirectory=\"$(EngineDir)/Binaries/ThirdParty/AppLocalDependencies\"");
	}

	BuildCookRunParams += FString::Printf(TEXT(" -archivedirectory=\"%s\""), *AllPlatformPackagingSettings->StagingDirectory.Path);

	if (PackagingSettings->ForDistribution)
	{
		BuildCookRunParams += TEXT(" -distribution");
	}

	if (PackagingSettings->bGenerateChunks)
	{
		BuildCookRunParams += TEXT(" -manifests");
	}

	// Whether to include the crash reporter.
	if (PackagingSettings->IncludeCrashReporter && PlatformInfo->DataDrivenPlatformInfo->bCanUseCrashReporter)
	{
		BuildCookRunParams += TEXT(" -CrashReporter");
	}

	if (PackagingSettings->bBuildHttpChunkInstallData)
	{
		BuildCookRunParams += FString::Printf(
			TEXT(" -manifests -createchunkinstall -chunkinstalldirectory=\"%s\" -chunkinstallversion=%s"),
			*(PackagingSettings->HttpChunkInstallDataDirectory.Path),
			*(PackagingSettings->HttpChunkInstallDataVersion)
		);
	}

	EProjectPackagingBuildConfigurations BuildConfig = AllPlatformPackagingSettings->GetBuildConfigurationForPlatform(IniPlatformName);

	const UProjectPackagingSettings::FConfigurationInfo& ConfigurationInfo = UProjectPackagingSettings::ConfigurationInfo[(int)BuildConfig];
	if (BuildTargetInfo)
	{
		if (BuildTargetInfo->Type == EBuildTargetType::Client)
		{
			BuildCookRunParams += FString::Printf(TEXT(" -client -clientconfig=%s"), LexToString(ConfigurationInfo.Configuration));
		}
		else if (BuildTargetInfo->Type == EBuildTargetType::Server)
		{
			BuildCookRunParams += FString::Printf(TEXT(" -server -noclient -serverconfig=%s"), LexToString(ConfigurationInfo.Configuration));
		}
		else
		{
			BuildCookRunParams += FString::Printf(TEXT(" -clientconfig=%s"), LexToString(ConfigurationInfo.Configuration));
		}
	}

	if (ConfigurationInfo.Configuration == EBuildConfiguration::Shipping && !PackagingSettings->IncludeDebugFiles)
	{
		BuildCookRunParams += TEXT(" -nodebuginfo");
	}

	FString TurnkeyParams = FString::Printf(TEXT("-command=VerifySdk -platform=%s -UpdateIfNeeded %s"), *UBTPlatformString, *ITurnkeyIOModule::Get().GetUATParams());
	if (!ProjectPath.IsEmpty())
	{
		TurnkeyParams.Appendf(TEXT(" -project=\"%s\""), *ProjectPath);
	}

	FString CommandLine;
	if (!ProjectPath.IsEmpty())
	{
		CommandLine.Appendf(TEXT(" -ScriptsForProject=\"%s\" "), *ProjectPath);
	}
	CommandLine.Appendf(TEXT("Turnkey %s BuildCookRun %s"), *TurnkeyParams, *BuildCookRunParams);

	IUATHelperModule::Get().CreateUatTask(CommandLine, PlatformInfo->DisplayName, ContentPrepDescription, ContentPrepTaskName, ContentPrepIcon, &AnalyticsParamArray);
}

void SPackageSelector::Construct(const FArguments& InArgs)
{
	InitPackagingData();

	TArray<FString> PlatformOptions;
	for (const auto& Platform : PlatformSuggestions)
	{
		PlatformOptions.Emplace(Platform.ToString());
	}

	TArray<FString> BinaryOptions;
	for (const auto& Binary : BinarySuggestions)
	{
		const UProjectPackagingSettings::FConfigurationInfo& ConfigurationInfo = UProjectPackagingSettings::ConfigurationInfo[static_cast<int>(Binary)];
		BinaryOptions.Emplace(ConfigurationInfo.Name.ToString());
	}

	TArray<FString> TargetOptions;
	for (const auto& Target : TargetSuggestions)
	{
		TargetOptions.Emplace(Target.Name);
	}

	// clang-format off
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			GenerateOptionsWidget(INVTEXT("Platforms"), PlatformOptions, PlatformIndex)	
		]

		+ SVerticalBox::Slot()
		[
			GenerateOptionsWidget(INVTEXT("Binary"), BinaryOptions, BinaryIndex)
		]

		+ SVerticalBox::Slot()
		[
			GenerateOptionsWidget(INVTEXT("Target"), TargetOptions, TargetIndex)
		]
	];
	// clang-format on
}

void SPackageSelector::InitPackagingData()
{
	// TODO: The default values should come from either a config or a recent configuration selection.

	// Platforms
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
	}


	// Binaries
	{
		const EProjectType ProjectType = DoesProjectHaveCode() ? EProjectType::Code : EProjectType::Content;
		for (EProjectPackagingBuildConfigurations PackagingConfiguration : UProjectPackagingSettings::GetValidPackageConfigurations())
		{
			const UProjectPackagingSettings::FConfigurationInfo& ConfigurationInfo = UProjectPackagingSettings::ConfigurationInfo[static_cast<int>(PackagingConfiguration)];

			if (FInstalledPlatformInfo::Get().IsValid(TOptional<EBuildTargetType>(), TOptional<FString>(), ConfigurationInfo.Configuration, ProjectType, EInstalledPlatformState::Downloaded))
			{
				BinarySuggestions.Emplace(PackagingConfiguration);
			}
		}
	}

	// Targets
	{
		FProjectStatus ProjectStatus;
		const bool bHasCode = IProjectManager::Get().QueryStatusForCurrentProject(ProjectStatus) && ProjectStatus.bCodeBasedProject;

		const IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
		TArray<FTargetInfo> Targets = bHasCode ? DesktopPlatform->GetTargetsForCurrentProject() : DesktopPlatform->GetTargetsForProject({});

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
			TargetSuggestions.Emplace(Target);
		}
	}
}

TSharedRef<SWidget> SPackageSelector::GenerateOptionsWidget(const FText& Category, const TArray<FString>& Options, int32& CategoryIndex) const
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
