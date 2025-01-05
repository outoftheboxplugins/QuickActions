// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildPackedLevelActorExtension.h"

#include <LevelEditor.h>
#include <PackedLevelActorUtils.h>
#include <Settings/EditorExperimentalSettings.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildPackedLevelActorExtension::GetCommands(const FQuickCommandContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> PackActors = MakeShared<FQuickCommandEntry>();
	PackActors->Title = NSLOCTEXT("LevelInstanceEditor", "PackLevelActorsTitle", "Pack Level Actors");
	PackActors->Tooltip = NSLOCTEXT("LevelInstanceEditor", "PackLevelActorsTooltip", "Update packed level actor blueprints");
	PackActors->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.PackedLevelActor");
	PackActors->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			UE_LOG(LogTemp, Warning, TEXT("FPackedLevelActorUtils::PackAllLoadedActors is not DLL exported."))
			//FPackedLevelActorUtils::PackAllLoadedActors();
		}
	);
	PackActors->CanExecuteCallback = FCanExecuteCommandDelegate::CreateLambda(
		[]()
		{
			UE_LOG(LogTemp, Warning, TEXT("FPackedLevelActorUtils::CanPack is not DLL exported."))
			//return FPackedLevelActorUtils::CanPack();
			return true;
		}
	);
	OutCommands.Emplace(PackActors);

	return OutCommands;
}