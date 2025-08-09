// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "OpenAssetExtension.h"

#include "AssetToolsModule.h"
#include "IAssetTypeActions.h"
#include "QuickMenuSettings.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "ThumbnailRendering/ThumbnailManager.h"

#define LOCTEXT_NAMESPACE "QuickActions"

TArray<TSharedPtr<FQuickCommandEntry>> UOpenAssetExtension::GetCommands(const FQuickCommandContext& Context)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UOpenAssetExtension::GetCommands);

	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	TArray<FAssetData> AllAssets;
	IAssetRegistry* AssetRegistry = IAssetRegistry::Get();
	AssetRegistry->GetAllAssets(AllAssets, true);

	for (const auto& AssetData : AllAssets)
	{
		FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
		TWeakPtr<IAssetTypeActions> AssetTypeActions = AssetToolsModule.Get().GetAssetTypeActionsForClass(AssetData.GetClass());

		if (!AssetTypeActions.Pin() || !AssetTypeActions.Pin()->SupportsOpenedMethod(EAssetTypeActivationOpenedMethod::Edit))
		{
			continue;
		}

		TSharedPtr<FQuickCommandEntry> OpenAsset = MakeShared<FQuickCommandEntry>();
		OpenAsset->Title = FText::Format(LOCTEXT("OpenAsset", "Open {0}"), FText::FromName(AssetData.AssetName));
		OpenAsset->Tooltip = FText::Format(LOCTEXT("OpenAssetTip", "Open the editor for {0}"), FText::FromName(AssetData.PackagePath));

		TSharedRef<FAssetThumbnail> AssetThumbnail = MakeShared<FAssetThumbnail>(AssetData, 64, 64, UThumbnailManager::Get().GetSharedThumbnailPool());
		TSharedRef<SWidget> ThumbnailWidget = AssetThumbnail->MakeThumbnailWidget();
		OpenAsset->CustomIconWidget = ThumbnailWidget;
		
		OpenAsset->ExecuteCallback = FSimpleDelegate::CreateLambda([AssetData]()
		{
			GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(AssetData.ToSoftObjectPath());
		});
		
		OutCommands.Add(OpenAsset);
	}

	return OutCommands;
}

int32 UOpenAssetExtension::GetPriority() const
{
	return -200;
}

bool UOpenAssetExtension::ShouldShow() const
{
	return GetDefault<UQuickMenuSettings>()->bIncludeAssets;
}

#undef LOCTEXT_NAMESPACE