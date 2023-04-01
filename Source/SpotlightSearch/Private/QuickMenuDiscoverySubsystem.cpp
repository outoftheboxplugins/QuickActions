// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "QuickMenuDiscoverySubsystem.h"

#include <Interfaces/IMainFrameModule.h>

#include "Engine/AssetManager.h"
#include "LevelEditor.h"

TAutoConsoleVariable<FString> CVarQuickActionFilter(TEXT("QuickActions.FilterExtensions"), TEXT(""), TEXT("If set, only extensions with this string in their name will be displayed."));

const TArray<TSharedPtr<FQuickCommandEntry>>& UQuickMenuDiscoverySubsystem::GetAllCommands() const
{
	return DiscoveredCommands;
}

void UQuickMenuDiscoverySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// FLevelEditorModule& LevelEditor = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	// LevelEditor.OnLevelEditorCreated().AddLambda(


	IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));
	MainFrameModule.OnMainFrameCreationFinished().AddLambda(
		[=](TSharedPtr<SWindow>, bool)
		{
			GatherCommandsInternal(DiscoveredCommands);
		}
	);
}

void UQuickMenuDiscoverySubsystem::GatherCommandsInternal(TArray<TSharedPtr<FQuickCommandEntry>>& OutCommands) const
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UQuickMenuDiscoverySubsystem::GatherCommandsInternal);

	TArray<UQuickMenuExtension*> Extensions;

	const FString NameFilterValue = CVarQuickActionFilter.GetValueOnAnyThread();
	for (TObjectIterator<UClass> It; It; ++It)
	{
		const UClass* CurrentClass = (*It);
		const bool bPassesNameFilter = NameFilterValue.IsEmpty() || CurrentClass->GetName().Contains(NameFilterValue);

		if (bPassesNameFilter && CurrentClass->IsChildOf(UQuickMenuExtension::StaticClass()) && !(CurrentClass->HasAnyClassFlags(CLASS_Abstract)))
		{
			UQuickMenuExtension* QuickMenuExtension = Cast<UQuickMenuExtension>(CurrentClass->GetDefaultObject());
			if (QuickMenuExtension->ShouldShow())
			{
				Extensions.Add(QuickMenuExtension);
			}
		}
	}

	Extensions.Sort(
		[](const UQuickMenuExtension& A, const UQuickMenuExtension& B)
		{
			return A.GetPriority() > B.GetPriority();
		}
	);

	IMainFrameModule& MainFrameModule = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	const TSharedPtr<FUICommandList> MainFrameCommands = MainFrameModule.GetMainFrameCommandBindings();

	FToolMenuContext Context;
	Context.AppendCommandList(MainFrameCommands);

	for (UQuickMenuExtension* Extension : Extensions)
	{
		OutCommands.Append(Extension->GetCommands(Context));
	}
}