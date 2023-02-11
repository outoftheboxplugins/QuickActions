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
	if (!Inst.IsValid())
	{
		Inst = TUniquePtr<FQuickMenuStyle>(new FQuickMenuStyle);
	}
	return *(Inst.Get());
}

void FQuickMenuStyle::Shutdown()
{
	Inst.Reset();
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
												 .SetActiveBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::Select, 1.0f))
												 .SetActiveHoveredBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::Select, 1.0f))
												 .SetActiveHighlightedBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::Select, 1.0f))
												 .SetInactiveBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::SelectInactive, 1.0f))
												 .SetInactiveHoveredBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::SelectInactive, 1.0f))
												 .SetSelectorFocusedBrush(FSlateRoundedBoxBrush(FStyleColors::Select, 4.0f, FStyleColors::Select, 1.0f));

		Set("ActionMenuRow", ActionMenuRow);
	}

	FSlateStyleRegistry::RegisterSlateStyle(*this);
}

FQuickMenuStyle::~FQuickMenuStyle()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*this);
}
