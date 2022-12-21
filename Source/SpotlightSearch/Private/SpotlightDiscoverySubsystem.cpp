// Fill out your copyright notice in the Description page of Project Settings.

#include "SpotlightDiscoverySubsystem.h"

#include "Interfaces/IMainFrameModule.h"
#include "LevelEditor.h"
#include "LevelEditorActions.h"
#include "MRUFavoritesList.h"
#include "Toolkits/GlobalEditorCommonCommands.h"
#include "WtfHdiTutorialSettings.h"

#define LOCTEXT_NAMESPACE "LevelEditorMenu"

FQuickCommandEntry::FQuickCommandEntry(const TSharedRef<FUICommandInfo>& Command, const TSharedRef<FUICommandList> CommandList)
{
	Icon = Command->GetIcon();

	Title = Command->GetLabel();
	Tooltip = Command->GetDescription();

	const FUIAction* UIAction = CommandList->GetActionForCommand(Command);
	if (ensure(UIAction))
	{
		ExecuteCallback = UIAction->ExecuteAction;
		CanExecuteCallback = UIAction->CanExecuteAction;
	}
}

TArray<FQuickCommandEntry> USpotlightDiscoverySubsystem::GetAllCommands() const
{
	TArray<FQuickCommandEntry> Result;

	GatherCommandsInternal(Result);
	OnDiscoverCommands.Broadcast(Result);

	return Result;
}

void USpotlightDiscoverySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USpotlightDiscoverySubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void USpotlightDiscoverySubsystem::GatherCommandsInternal(TArray<FQuickCommandEntry>& OutCommands) const
{
	PopulateTutorials(OutCommands);
	PopulateMenuEntries(OutCommands);
}
void USpotlightDiscoverySubsystem::PopulateTutorials(TArray<FQuickCommandEntry>& OutCommands) const
{
	const UWtfHdiTutorialSettings* TutorialSettings = GetDefault<UWtfHdiTutorialSettings>();
	if (!TutorialSettings->bIncludeTutorials)
	{
		return;
	}

	for (const FTutorialInfo& Tutorial : TutorialSettings->Tutorials)
	{
		FQuickCommandEntry TutorialEntry;
		TutorialEntry.Title = FText::FromString(Tutorial.Title);
		TutorialEntry.Tooltip = FText::FromString(Tutorial.Description);
		TutorialEntry.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Documentation");
		TutorialEntry.CanExecuteCallback = TDelegate<bool()>::CreateLambda(
			[]()
			{
				return true;
			}
		);
		TutorialEntry.ExecuteCallback = FSimpleDelegate::CreateLambda(
			[Tutorial]()
			{
				FPlatformProcess::LaunchURL(*Tutorial.Url, nullptr, nullptr);
			}
		);

		OutCommands.Emplace(TutorialEntry);
	}
}
void USpotlightDiscoverySubsystem::PopulateMenuEntries(TArray<FQuickCommandEntry>& OutCommands) const
{
	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	IMainFrameModule& MainFrameModule = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	const TSharedRef<FUICommandList> MainFrameCommands = MainFrameModule.GetMainFrameCommandBindings();

	{
		FQuickCommandEntry NewLevel = FQuickCommandEntry(FLevelEditorCommands::Get().NewLevel.ToSharedRef(), LevelEditorCommands);
		OutCommands.Emplace(NewLevel);

		FQuickCommandEntry OpenLevel = FQuickCommandEntry(FLevelEditorCommands::Get().OpenLevel.ToSharedRef(), LevelEditorCommands);
		OutCommands.Emplace(OpenLevel);

		const FMainMRUFavoritesList& MRUFavorites = *MainFrameModule.GetMRUFavoritesList();
		const int32 NumRecent = FMath::Min(MRUFavorites.GetNumItems(), FLevelEditorCommands::Get().OpenRecentFileCommands.Num());
		for (int32 CurrentRecent = 0; CurrentRecent < NumRecent; CurrentRecent++)
		{
			TSharedPtr<FUICommandInfo> OpenRecentFile = FLevelEditorCommands::Get().OpenRecentFileCommands[CurrentRecent];

			if (!MRUFavorites.MRUItemPassesCurrentFilter(CurrentRecent))
			{
				continue;
			}

			const FText RecentMapPath = FText::FromString(MRUFavorites.GetMRUItem(CurrentRecent));
			const FText RecentMapName = FText::FromString(FPaths::GetBaseFilename(RecentMapPath.ToString()));

			const FText Title = FText::Format(LOCTEXT("RecentMapTitle", "Open recent level: {0}"), RecentMapName);
			const FText Tooltip = FText::Format(LOCTEXT("RecentMapTooltip", "Path: {0}"), RecentMapPath);

			FQuickCommandEntry RecentEntry = FQuickCommandEntry(OpenRecentFile.ToSharedRef(), LevelEditorCommands);
			RecentEntry.Title = Title;
			RecentEntry.Tooltip = Tooltip;
			RecentEntry.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "MainFrame.RecentLevels");

			OutCommands.Emplace(RecentEntry);
		}

		// Add a button to add/remove the currently loaded map as a favorite
		if (FLevelEditorActionCallbacks::ToggleFavorite_CanExecute())
		{
			TAttribute<FText> ToggleFavoriteLabel = TAttribute<FText>::CreateLambda(
				[]()
				{
					const FText LevelName = FText::FromString(FPackageName::GetShortName(GWorld->GetOutermost()->GetFName()));
					if (!FLevelEditorActionCallbacks::ToggleFavorite_IsChecked())
					{
						return FText::Format(LOCTEXT("ToggleFavorite_Add", "Add to Favorites: {0}"), LevelName);
					}
					return FText::Format(LOCTEXT("ToggleFavorite_Remove", "Remove from Favorites: {0}"), LevelName);
				}
			);
			FQuickCommandEntry AddOrRemoveLevel = FQuickCommandEntry(FLevelEditorCommands::Get().ToggleFavorite.ToSharedRef(), LevelEditorCommands);
			AddOrRemoveLevel.Title = ToggleFavoriteLabel;
			AddOrRemoveLevel.Tooltip = ToggleFavoriteLabel;
			AddOrRemoveLevel.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "MainFrame.FavoriteLevels");

			OutCommands.Emplace(AddOrRemoveLevel);
		}

		const int32 AllowedFavorites = FMath::Min(MRUFavorites.GetNumFavorites(), FLevelEditorCommands::Get().OpenFavoriteFileCommands.Num());
		for (int32 CurFavoriteIndex = 0; CurFavoriteIndex < AllowedFavorites; ++CurFavoriteIndex)
		{
			TSharedPtr<FUICommandInfo> OpenFavoriteFile = FLevelEditorCommands::Get().OpenFavoriteFileCommands[CurFavoriteIndex];

			const FText FavoriteMapPath = FText::FromString(MRUFavorites.GetFavoritesItem(CurFavoriteIndex));
			const FText FavoriteMapName = FText::FromString(FPaths::GetBaseFilename(FavoriteMapPath.ToString()));

			const FText Title = FText::Format(LOCTEXT("FavoriteMapTitle", "Open favorite level: {0}"), FavoriteMapName);
			const FText Tooltip = FText::Format(LOCTEXT("FavoriteMapTooltip", "Path: {0}"), FavoriteMapPath);

			FQuickCommandEntry FavoriteEntry = FQuickCommandEntry(OpenFavoriteFile.ToSharedRef(), LevelEditorCommands);
			FavoriteEntry.Title = Title;
			FavoriteEntry.Tooltip = Tooltip;
			FavoriteEntry.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "MainFrame.FavoriteLevels");

			OutCommands.Emplace(FavoriteEntry);
		}
	}

	{
		FQuickCommandEntry OpenAsset = FQuickCommandEntry(FGlobalEditorCommonCommands::Get().SummonOpenAssetDialog.ToSharedRef(), MainFrameCommands);
		OutCommands.Emplace(OpenAsset);
	}
}

#undef LOCTEXT_NAMESPACE