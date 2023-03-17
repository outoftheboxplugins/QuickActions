// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildLandscapeExtension.h"

#include <LandscapeSubsystem.h>
#include <LevelEditor.h>
#include <LevelEditorActions.h>

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildLandscapeExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	const TSharedRef<FUICommandList> LevelEditorCommands = LevelEditorModule.GetGlobalLevelEditorActions();

	const TSharedPtr<FQuickCommandEntry> BuildAllLandscape = MakeShared<FQuickCommandEntry>(FLevelEditorCommands::Get().BuildAllLandscape.ToSharedRef(), LevelEditorCommands);
	BuildAllLandscape->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.LandscapeMode", "LevelEditor.LandscapeMode.Small");
	OutCommands.Emplace(BuildAllLandscape);

	const TSharedPtr<FQuickCommandEntry> BuildGITextures = MakeShared<FQuickCommandEntry>();
	BuildGITextures->Title = NSLOCTEXT("LandscapeEditor", "BuildGITexturesOnly", "Build GI Textures Only");
	BuildGITextures->Tooltip = NSLOCTEXT("LandscapeEditor", "BuildGIBakedTextures ", "Build GI baked base color textures");
	BuildGITextures->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "PlacementBrowser.Icons.Lights");
	BuildGITextures->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			if (const UWorld* World = GEditor->GetEditorWorldContext().World())
			{
				if (ULandscapeSubsystem* LandscapeSubsystem = World->GetSubsystem<ULandscapeSubsystem>())
				{
					LandscapeSubsystem->BuildGIBakedTextures();
				}
			}
		}
	);
	OutCommands.Emplace(BuildGITextures);

	const TSharedPtr<FQuickCommandEntry> BuildGrassMaps = MakeShared<FQuickCommandEntry>();
	BuildGrassMaps->Title = NSLOCTEXT("LandscapeEditor", "BuildGrassMapsOnly", "Build Grass Maps Only");
	BuildGrassMaps->Tooltip = NSLOCTEXT("LandscapeEditor", "BuildLandscapeGrassMaps", "Build landscape grass maps");
	BuildGrassMaps->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.FoliageMode");
	BuildGrassMaps->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			if (const UWorld* World = GEditor->GetEditorWorldContext().World())
			{
				if (ULandscapeSubsystem* LandscapeSubsystem = World->GetSubsystem<ULandscapeSubsystem>())
				{
					LandscapeSubsystem->BuildGrassMaps();
				}
			}
		}
	);
	OutCommands.Emplace(BuildGrassMaps);

	const TSharedPtr<FQuickCommandEntry> BuildPhysicalMaterial = MakeShared<FQuickCommandEntry>();
	BuildPhysicalMaterial->Title = NSLOCTEXT("LandscapeEditor", "BuildPhysicalMaterialOnly", "Build Physical Material Only");
	BuildPhysicalMaterial->Tooltip = NSLOCTEXT("LandscapeEditor", "BuildLandscapePhysicalMaterial", "Build landscape physical material");
	BuildPhysicalMaterial->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "CollisionAnalyzer.TabIcon");
	BuildPhysicalMaterial->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			if (const UWorld* World = GEditor->GetEditorWorldContext().World())
			{
				if (ULandscapeSubsystem* LandscapeSubsystem = World->GetSubsystem<ULandscapeSubsystem>())
				{
					LandscapeSubsystem->BuildPhysicalMaterial();
				}
			}
		}
	);
	OutCommands.Emplace(BuildPhysicalMaterial);

	const TSharedPtr<FQuickCommandEntry> BuildNanite = MakeShared<FQuickCommandEntry>();
	BuildNanite->Title = NSLOCTEXT("LandscapeEditor", "BuildNaniteOnly", "Build Nanite Only");
	BuildNanite->Tooltip = NSLOCTEXT("LandscapeEditor", "BuildLandscapeNanite", "Build Nanite representation");
	BuildNanite->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "EditorViewport.VisualizeNaniteMode");
	BuildNanite->ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			if (const UWorld* World = GEditor->GetEditorWorldContext().World())
			{
				if (ULandscapeSubsystem* LandscapeSubsystem = World->GetSubsystem<ULandscapeSubsystem>())
				{
					LandscapeSubsystem->BuildNanite();
				}
			}
		}
	);
	OutCommands.Emplace(BuildNanite);

	return OutCommands;
}