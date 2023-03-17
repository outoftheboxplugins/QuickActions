// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuActorAssetOptionsExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

#include "Selection.h"
#include "Styling/SlateIconFinder.h"
#include "Toolkits/GlobalEditorCommonCommands.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuActorAssetOptionsExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	TArray<UObject*> ReferencedAssets;
	GEditor->GetReferencedAssetsForEditorSelection(ReferencedAssets);

	const FSlateIcon AssetIcon = ReferencedAssets.Num() == 1 ? FSlateIconFinder::FindIconForClass(ReferencedAssets[0]->GetClass()) : FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.Default");

	const TSharedPtr<FQuickCommandEntry> Find = MakeShared<FQuickCommandEntry>(FGlobalEditorCommonCommands::Get().FindInContentBrowser.ToSharedRef(), LevelEditorModule.GetGlobalLevelEditorActions());
	OutCommands.Add(Find);

	if (ReferencedAssets.Num() == 0)
	{
		const TSharedPtr<FQuickCommandEntry> Edit = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().EditAsset.ToSharedRef(), LevelEditorCommands);
		Edit->Icon = AssetIcon;

		OutCommands.Add(Edit);
	}
	else if (ReferencedAssets.Num() == 1)
	{
		UObject* Asset = ReferencedAssets[0];
		const FString AssetLabel = Cast<AActor>(Asset) ? Cast<AActor>(Asset)->GetActorNameOrLabel() : Asset->GetName();

		const TSharedPtr<FQuickCommandEntry> Edit = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().EditAsset.ToSharedRef(), LevelEditorCommands);
		Edit->Title = FText::Format(NSLOCTEXT("LevelViewportContextMenu", "EditAssociatedAsset", "Edit {0}"), FText::FromString(AssetLabel));

		OutCommands.Add(Edit);
	}
	else if (ReferencedAssets.Num() > 1)
	{

		const TSharedPtr<FQuickCommandEntry> Edit = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().EditAssetNoConfirmMultiple.ToSharedRef(), LevelEditorCommands);
		Edit->Title = NSLOCTEXT("LevelViewportContextMenu", "EditAssociatedAssetsMultiple", "Edit Multiple Assets");

		OutCommands.Add(Edit);
	}

	const TSharedPtr<FQuickCommandEntry> CopyPath = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().CopyActorFilePathtoClipboard.ToSharedRef(), LevelEditorCommands);
	CopyPath->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "GenericCommands.Copy");
	OutCommands.Add(CopyPath);

	const TSharedPtr<FQuickCommandEntry> SaveActor = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().SaveActor.ToSharedRef(), LevelEditorCommands);
	SaveActor->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Save");
	OutCommands.Add(SaveActor);

	return OutCommands;
}