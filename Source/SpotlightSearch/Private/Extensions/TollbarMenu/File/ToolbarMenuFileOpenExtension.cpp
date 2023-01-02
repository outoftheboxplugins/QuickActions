// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuFileOpenExtension.h"

#include <Interfaces/IMainFrameModule.h>
#include <LevelEditor.h>
#include <LevelEditorActions.h>
#include <MRUFavoritesList.h>
#include <Toolkits/GlobalEditorCommonCommands.h>

#define LOCTEXT_NAMESPACE "QuickActions"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuFileOpenExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	IMainFrameModule& MainFrameModule = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	const TSharedRef<FUICommandList> MainFrameCommands = MainFrameModule.GetMainFrameCommandBindings();

	const TSharedPtr<FQuickCommandEntry> NewLevel = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().NewLevel.ToSharedRef(), LevelEditorCommands);
	OutCommands.Emplace(NewLevel);

	const TSharedPtr<FQuickCommandEntry> OpenLevel = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().OpenLevel.ToSharedRef(), LevelEditorCommands);
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

		const TSharedPtr<FQuickCommandEntry> RecentEntry = MakeShared<FQuickCommandEntry>(OpenRecentFile.ToSharedRef(), LevelEditorCommands);
		RecentEntry->Title = Title;
		RecentEntry->Tooltip = Tooltip;
		RecentEntry->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "MainFrame.RecentLevels");

		OutCommands.Emplace(RecentEntry);
	}

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
		const TSharedPtr<FQuickCommandEntry> AddOrRemoveLevel = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().ToggleFavorite.ToSharedRef(), LevelEditorCommands);
		AddOrRemoveLevel->Title = ToggleFavoriteLabel;
		AddOrRemoveLevel->Tooltip = ToggleFavoriteLabel;
		AddOrRemoveLevel->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "MainFrame.FavoriteLevels");

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

		const TSharedPtr<FQuickCommandEntry> FavoriteEntry = MakeShared<FQuickCommandEntry>(OpenFavoriteFile.ToSharedRef(), LevelEditorCommands);
		FavoriteEntry->Title = Title;
		FavoriteEntry->Tooltip = Tooltip;
		FavoriteEntry->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "MainFrame.FavoriteLevels");

		OutCommands.Emplace(FavoriteEntry);
	}

	const TSharedPtr<FQuickCommandEntry> OpenAsset = MakeShared<FQuickCommandEntry>(FGlobalEditorCommonCommands::Get().SummonOpenAssetDialog.ToSharedRef(), MainFrameCommands);
	OutCommands.Emplace(OpenAsset);


	return OutCommands;
}

#undef LOCTEXT_NAMESPACE