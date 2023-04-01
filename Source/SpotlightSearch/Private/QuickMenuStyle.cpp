// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "QuickMenuStyle.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/StyleColors.h"


FName FQuickMenuStyle::StyleName("QuickMenuStyle");
TUniquePtr<FQuickMenuStyle> FQuickMenuStyle::Inst(nullptr);

const FName& FQuickMenuStyle::GetStyleSetName() const
{
	return StyleName;
}

const FQuickMenuStyle& FQuickMenuStyle::Get()
{
	ensure(Inst.IsValid());
	return *(Inst.Get());
}

void FQuickMenuStyle::Initialize()
{
	if (!Inst.IsValid())
	{
		Inst = TUniquePtr<FQuickMenuStyle>(new FQuickMenuStyle);
	}
}

void FQuickMenuStyle::Shutdown()
{
	if (Inst.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*Inst.Get());
		Inst.Reset();
	}
}

FQuickMenuStyle::FQuickMenuStyle() : FSlateStyleSet(StyleName)
{
	SetParentStyleName(FAppStyle::GetAppStyleSetName());

	FSlateStyleSet::SetContentRoot(IPluginManager::Get().FindPlugin(TEXT("QuickActions"))->GetBaseDir() / TEXT("Resources"));

	{
		const FTableRowStyle TableViewRow = FCoreStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row");
		const FTableRowStyle ActionMenuRow = FTableRowStyle(TableViewRow)
												 .SetEvenRowBackgroundHoveredBrush(FSlateRoundedBoxBrush(FStyleColors::Panel, 4.0f))
												 .SetOddRowBackgroundHoveredBrush(FSlateRoundedBoxBrush(FStyleColors::Panel, 4.0f))
												 .SetInactiveBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::SelectInactive, 1.0f))
												 .SetInactiveHoveredBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::SelectInactive, 1.0f))
												 .SetSelectorFocusedBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::Select, 1.0f));
		Set("ActionMenuRow", ActionMenuRow);

		const FEditableTextStyle EditableTextStyle = FCoreStyle::Get().GetWidgetStyle<FEditableTextStyle>("NormalEditableText");
		const FEditableTextStyle ActionMenuSearchTextStyle = FEditableTextStyle(EditableTextStyle).SetFont(FCoreStyle::GetDefaultFontStyle("Bold", 18));
		Set("ActionMenuSearchTextStyle", ActionMenuSearchTextStyle);
	}

	FSlateStyleRegistry::RegisterSlateStyle(*this);
}
