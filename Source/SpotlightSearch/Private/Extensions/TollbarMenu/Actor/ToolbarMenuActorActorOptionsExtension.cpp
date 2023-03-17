// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuActorActorOptionsExtension.h"

namespace
{
	void Test()
	{
		// Options for editing, transforming, and manipulating this actor
		// In most cases, you DO NOT want to extend this section; look at ActorUETools or ActorTypeTools below
		FToolMenuSection& Section = InMenu->AddSection("ActorOptions", LOCTEXT("ActorOptionsHeading", "Actor Options"));

		FLevelEditorContextMenuImpl::AddSelectChildrenEntry(Section, SelectedActors, LevelEditorContext);

		Section.AddSubMenu(
			"EditSubMenu",
			LOCTEXT("EditSubMenu", "Edit"),
			FText::GetEmpty(),
			FNewToolMenuDelegate::CreateStatic(&FLevelEditorContextMenuImpl::FillEditMenu),
			false, // default value
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Edit")
		);

		Section.AddSubMenu(
			"VisibilitySubMenu",
			LOCTEXT("VisibilitySubMenu", "Visibility"),
			LOCTEXT("VisibilitySubMenu_ToolTip", "Selected actor visibility options"),
			FNewToolMenuDelegate::CreateStatic(&FLevelEditorContextMenuImpl::FillActorVisibilityMenu),
			false, // default value
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Visibility")
		);

		Section.AddSubMenu(
			"TransformSubMenu",
			LOCTEXT("TransformSubMenu", "Transform"),
			LOCTEXT("TransformSubMenu_ToolTip", "Actor transform utils"),
			FNewToolMenuDelegate::CreateStatic(&FLevelEditorContextMenuImpl::FillTransformMenu),
			false, // default value
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Transform")
		);

		Section.AddSubMenu(
			"SnapAlignSubMenu",
			LOCTEXT("SnapAlignSubMenu", "Snapping"),
			LOCTEXT("SnapAlignSubMenu_ToolTip", "Actor snap/align utils"),
			FNewToolMenuDelegate::CreateStatic(&FLevelEditorContextMenuImpl::FillSnapAlignMenu),
			false, // default value
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Snap")
		);

		Section.AddSubMenu(
			"PivotSubMenu",
			LOCTEXT("PivotSubMenu", "Pivot"),
			LOCTEXT("PivotSubMenu_ToolTip", "Actor pivoting utils"),
			FNewToolMenuDelegate::CreateStatic(&FLevelEditorContextMenuImpl::FillPivotMenu),
			false, // default value
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.SetShowPivot")
		);

		// Build the menu for grouping actors - this is either the Group item or Groups submenu
		BuildGroupMenu(Section, SelectionInfo);

		// Attach and detach
		Section.AddSubMenu(
			"ActorAttachToSubMenu",
			LOCTEXT("ActorAttachToSubMenu", "Attach To"),
			LOCTEXT("ActorAttachToSubMenu_ToolTip", "Attach Actor as child"),
			FNewToolMenuDelegate::CreateStatic(&FLevelEditorContextMenuImpl::FillActorMenu),
			false, // default value
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Actors.Attach")
		);

		Section.AddMenuEntry(
			FLevelEditorCommands::Get().DetachFromParent,
			TAttribute<FText>(), // Use command title
			TAttribute<FText>(), // Use command tooltip
			FSlateIcon(FAppStyle::GetAppStyleSetName(), "Actors.Detach")
		);
	}
} // namespace

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuActorActorOptionsExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	return OutCommands;
}