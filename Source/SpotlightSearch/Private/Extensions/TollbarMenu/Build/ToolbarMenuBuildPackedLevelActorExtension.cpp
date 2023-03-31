// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildPackedLevelActorExtension.h"

#include <LevelEditor.h>
#include <LevelEditorActions.h>

#include "LevelInstance/LevelInstanceSubsystem.h"
#include "Settings/EditorExperimentalSettings.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildPackedLevelActorExtension::GetCommands(const FToolMenuContext& Context)
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
			if (const UWorld* World = GEditor->GetEditorWorldContext().World())
			{
				if (ULevelInstanceSubsystem* LevelInstanceSubsystem = World->GetSubsystem<ULevelInstanceSubsystem>())
				{
					LevelInstanceSubsystem->PackAllLoadedActors();
				}
			}
		}
	);
	PackActors->CanExecuteCallback = FCanExecuteCommandDelegate::CreateLambda(
		[]()
		{
			if (const UWorld* World = GEditor->GetEditorWorldContext().World())
			{
				if (const ULevelInstanceSubsystem* LevelInstanceSubsystem = World->GetSubsystem<ULevelInstanceSubsystem>())
				{
					return LevelInstanceSubsystem->CanPackAllLoadedActors();
				}
			}
			return false;
		}
	);
	OutCommands.Emplace(PackActors);

	return OutCommands;
}

bool UToolbarMenuBuildPackedLevelActorExtension::ShouldShow() const
{
	return GetDefault<UEditorExperimentalSettings>()->bPackedLevelActor;
}