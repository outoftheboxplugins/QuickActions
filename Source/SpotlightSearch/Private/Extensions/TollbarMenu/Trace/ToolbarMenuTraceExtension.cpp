// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuTraceExtension.h"

#include "IUATHelperModule.h"
#include "MessageLogModule.h"

/*
 * @Note: The only reason this file seems complicated
 * is because everything's UnrealInsight launcher related
 * is in private directories and unnaccessible from outside
 * We've just copied everything relevant here
 *
 * At the end of the day, it's just launching a process
 */

class FLogMessageOnGameThreadTask
{
public:
	FLogMessageOnGameThreadTask(const FText& InMessage)
		: Message(InMessage)
	{}

	FORCEINLINE TStatId GetStatId() const { RETURN_QUICK_DECLARE_CYCLE_STAT(FLogMessageOnGameThreadTask, STATGROUP_TaskGraphTasks); }
	ENamedThreads::Type GetDesiredThread() { return ENamedThreads::Type::GameThread; }
	static ESubsequentsMode::Type GetSubsequentsMode() { return ESubsequentsMode::TrackSubsequents; }

	void LogMessage(const FText& InMessage)
	{
		const FName LogListingName = TEXT("UnrealInsights");
		
		FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
		if (!MessageLogModule.IsRegisteredLogListing(LogListingName))
		{
			MessageLogModule.RegisterLogListing(LogListingName, NSLOCTEXT("FUnrealInsightsLauncher", "UnrealInsights", "Unreal Insights"));
		}
	
		FMessageLog ReportMessageLog(LogListingName);
		TSharedRef<FTokenizedMessage> TokenizedMessage = FTokenizedMessage::Create(EMessageSeverity::Error, InMessage);
		ReportMessageLog.AddMessage(TokenizedMessage);
		ReportMessageLog.Notify();
	}
	
	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
	{
		LogMessage(Message);
	}

private:
	FText Message;
};

static void StartUnrealInsights(const FString& Path, const FString& Parameters);

static FString GetInsightsApplicationPath() // Copied from UnrealInsightsLauncher since it's private
{
	FString Path = FPlatformProcess::GenerateApplicationPath(TEXT("UnrealInsights"), EBuildConfiguration::Development);
	return FPaths::ConvertRelativePathToFull(Path);
}

static void TryBuildUnrealInsightsExe(const FString& Path, const FString& LaunchParameters)
{
	UE_LOG(LogTemp, Log, TEXT("Could not find the Unreal Insights executable: %s. Attempting to build UnrealInsights."), *Path);

	FString Arguments;
#if PLATFORM_WINDOWS
	FText PlatformName = NSLOCTEXT("FUnrealInsightsLauncher", "PlatformName_Windows", "Windows");
	Arguments = TEXT("BuildTarget -Target=UnrealInsights -Platform=Win64");
#elif PLATFORM_MAC
	FText PlatformName = NSLOCTEXT("FUnrealInsightsLauncher", "PlatformName_Mac", "Mac");
	Arguments = TEXT("BuildTarget -Target=UnrealInsights -Platform=Mac");
#elif PLATFORM_LINUX
	FText PlatformName = NSLOCTEXT("FUnrealInsightsLauncher", "PlatformName_Linux", "Linux");
	Arguments = TEXT("BuildTarget -Target=UnrealInsights -Platform=Linux");
#endif

	IUATHelperModule::Get().CreateUatTask(Arguments, PlatformName, NSLOCTEXT("FUnrealInsightsLauncher", "BuildingUnrealInsights", "Building Unreal Insights"),
		NSLOCTEXT("FUnrealInsightsLauncher", "BuildUnrealInsightsTask", "Build Unreal Insights Task"), FAppStyle::GetBrush(TEXT("MainFrame.CookContent")), nullptr, [Path, LaunchParameters](FString Result, double Time)
		{
			if (Result.Equals(TEXT("Completed")))
			{
#if PLATFORM_MAC
				// On Mac we genereate the path again so that it includes the newly built executable.
				FString NewPath = GetInsightsApplicationPath();
				StartUnrealInsights(NewPath, LaunchParameters);
#else
				StartUnrealInsights(Path, LaunchParameters);
#endif
			}
		});
}

static void StartUnrealInsights(const FString& Path, const FString& Parameters = TEXT(""))
{
	if (!FPaths::FileExists(Path))
	{
		TryBuildUnrealInsightsExe(Path, Parameters);
		return;
	}
	
	constexpr bool bLaunchDetached = true;
	constexpr bool bLaunchHidden = false;
	constexpr bool bLaunchReallyHidden = false;

	uint32 ProcessID = 0;
	const int32 PriorityModifier = 0;

	const TCHAR* OptionalWorkingDirectory = nullptr;

	void* PipeWriteChild = nullptr;
	void* PipeReadChild = nullptr;
	FProcHandle Handle = FPlatformProcess::CreateProc(*Path, *Parameters, bLaunchDetached, bLaunchHidden, bLaunchReallyHidden, &ProcessID, PriorityModifier, OptionalWorkingDirectory, PipeWriteChild, PipeReadChild);

	if (Handle.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Launched Unreal Insights executable: %s %s"), *Path, *Parameters);
	}
	else
	{
		const FText	MessageBoxTextFmt = NSLOCTEXT("FUnrealInsightsLauncher", "ExecutableNotFound_TextFmt", "Could not start Unreal Insights executable at path: {0}");
		const FText MessageBoxText = FText::Format(MessageBoxTextFmt, FText::FromString(Path));
		TGraphTask<FLogMessageOnGameThreadTask>::CreateTask().ConstructAndDispatchWhenReady(MessageBoxText);
	}
}

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuTraceExtension::GetCommands(const FQuickCommandContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const TSharedPtr<FQuickCommandEntry> UnrealInsight = MakeShared<FQuickCommandEntry>();
	UnrealInsight->Title = NSLOCTEXT("FUnrealInsightsLauncher", "OpenInsightsLabel", "Unreal Insights (Session Browser)");
	UnrealInsight->Tooltip = NSLOCTEXT("FUnrealInsightsLauncher", "OpenInsightsTooltip", "Launch the Unreal Insights Session Browser.");
	UnrealInsight->Icon = FSlateIcon("EditorTraceUtilitiesStyle", "Icons.UnrealInsights.Menu");
	UnrealInsight->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			StartUnrealInsights(GetInsightsApplicationPath());
		});
	OutCommands.Emplace(UnrealInsight);
	
	return OutCommands;
}