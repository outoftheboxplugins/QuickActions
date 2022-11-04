#include "ViewportExtensions.h"

#include <AssetSelection.h>
#include <EditorViewportCommands.h>
#include <Framework/Commands/GenericCommands.h>
#include <GeometryCollection/GeometryCollectionSelectionCommands.h>
#include <LevelEditor.h>
#include <LevelEditorActions.h>

#define LOCTEXT_NAMESPACE "FViewportExtensionsModule"

void FViewportExtensionsModule::StartupModule()
{
	RegisterViewportContextMenu();
}

void FViewportExtensionsModule::ShutdownModule()
{
	UnregisterViewportContextMenu();
}

void FViewportExtensionsModule::RegisterViewportContextMenu()
{
	FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors LevelEditorMenuExtenderDelegate =
		FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateRaw(
			this, &FViewportExtensionsModule::ExtendLevelViewportContextMenu);
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	auto& MenuExtenders = LevelEditorModule.GetAllLevelViewportContextMenuExtenders();
	MenuExtenders.Add(LevelEditorMenuExtenderDelegate);
	LevelViewportContextMenuExtender = MenuExtenders.Last().GetHandle();
}

void FViewportExtensionsModule::UnregisterViewportContextMenu()
{
	if (FModuleManager::Get().IsModuleLoaded(TEXT("LevelEditor")))
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
		LevelEditorModule.GetAllLevelViewportContextMenuExtenders().RemoveAll(
			[&](const FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors& Delegate)
			{ return Delegate.GetHandle() == LevelViewportContextMenuExtender; });
	}
}

TSharedRef<FExtender> FViewportExtensionsModule::ExtendLevelViewportContextMenu(
	const TSharedRef<FUICommandList> InCommandList, const TArray<AActor*> SelectedActors)
{
	TSharedRef<FExtender> Extender = MakeShared<FExtender>();

	Extender->AddMenuExtension("ActorTypeTools", EExtensionHook::After, nullptr,
		FMenuExtensionDelegate::CreateLambda(
			[SelectedActors](FMenuBuilder& MenuBuilder)
			{
				MenuBuilder.BeginSection("SelectOptions", LOCTEXT("SelectOptions", "Select Options"));

				MenuBuilder.AddSubMenu(LOCTEXT("GeneralCategory", "General"), FText(),
					FNewMenuDelegate::CreateLambda(
						[=](FMenuBuilder& SubMenuBuilder)
						{
							SubMenuBuilder.AddMenuEntry(FGenericCommands::Get().SelectAll);
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectNone);
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().InvertSelection);
							{
								FSelectedActorInfo SelectionInfo = AssetSelectionUtils::GetSelectedActorInfo();
								TAttribute<FText> SelectAllActorsText;
								if (SelectionInfo.bAllSelectedActorsOfSameType && !SelectionInfo.SelectionStr.IsEmpty())
								{
									SelectAllActorsText = FText::Format(
										NSLOCTEXT("LevelViewportContextMenu", "SelectActorsOfSameClass", "Select All {0}(s)"),
										FText::FromString(SelectionInfo.SelectionStr));
								}
								SubMenuBuilder.AddMenuEntry(
									FLevelEditorCommands::Get().SelectAllActorsOfSameClass, NAME_None, SelectAllActorsText);
							}
							SubMenuBuilder.AddMenuEntry(FEditorViewportCommands::Get().FocusViewportToSelection);
						}));

				MenuBuilder.AddSubMenu(LOCTEXT("HierarchyCategory", "Hierarchy"), FText(),
					FNewMenuDelegate::CreateLambda(
						[=](FMenuBuilder& SubMenuBuilder)
						{
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectImmediateChildren);
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectAllDescendants);
						}));

				MenuBuilder.AddSubMenu(LOCTEXT("BSPCategory", "BSP"), FText(),
					FNewMenuDelegate::CreateLambda(
						[=](FMenuBuilder& SubMenuBuilder)
						{
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectAllAddditiveBrushes);
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectAllSubtractiveBrushes);
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectAllSurfaces);
						}));

				MenuBuilder.AddSubMenu(LOCTEXT("LightsCategory", "Lights"), FText(),
					FNewMenuDelegate::CreateLambda(
						[=](FMenuBuilder& SubMenuBuilder)
						{
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectRelevantLights);
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectAllLights);
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectStationaryLightsExceedingOverlap);
						}));

				MenuBuilder.AddSubMenu(LOCTEXT("StaticMeshesCategory", "Static Meshes"), FText(),
					FNewMenuDelegate::CreateLambda(
						[=](FMenuBuilder& SubMenuBuilder)
						{
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectStaticMeshesOfSameClass);
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectStaticMeshesAllClasses);
						}));

				MenuBuilder.AddSubMenu(LOCTEXT("HierachicalLODsCategory", "Hierachical LODs"), FText(),
					FNewMenuDelegate::CreateLambda([=](FMenuBuilder& SubMenuBuilder)
						{ SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectOwningHierarchicalLODCluster); }));

				MenuBuilder.AddSubMenu(LOCTEXT("SkeletalMeshesCategory", "Skeletal Meshes"), FText(),
					FNewMenuDelegate::CreateLambda(
						[=](FMenuBuilder& SubMenuBuilder)
						{
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectSkeletalMeshesOfSameClass);
							SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectSkeletalMeshesAllClasses);
						}));

				MenuBuilder.AddSubMenu(LOCTEXT("EmittersCategory", "Emitters"), FText(),
					FNewMenuDelegate::CreateLambda([=](FMenuBuilder& SubMenuBuilder)
						{ SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectMatchingEmitter); }));

				MenuBuilder.AddSubMenu(LOCTEXT("MaterialsCategory", "Materials"), FText(),
					FNewMenuDelegate::CreateLambda([=](FMenuBuilder& SubMenuBuilder)
						{ SubMenuBuilder.AddMenuEntry(FLevelEditorCommands::Get().SelectAllWithSameMaterial); }));

				MenuBuilder.AddSubMenu(LOCTEXT("GeometryCollection", "Geometry Collection"), FText(),
					FNewMenuDelegate::CreateLambda(
						[=](FMenuBuilder& SubMenuBuilder)
						{
							SubMenuBuilder.AddMenuEntry(FGeometryCollectionSelectionCommands::Get().SelectAllGeometry);
							SubMenuBuilder.AddMenuEntry(FGeometryCollectionSelectionCommands::Get().SelectNone);
							SubMenuBuilder.AddMenuEntry(FGeometryCollectionSelectionCommands::Get().SelectInverseGeometry);
						}));
				MenuBuilder.EndSection();
			}));

	return Extender;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FViewportExtensionsModule, ViewportExtensions)
