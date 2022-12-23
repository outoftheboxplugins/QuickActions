// Copyright Out-of-the-Box Plugins 2018-2022. All Rights Reserved.

#include "QuickMenuCommands.h"

#include <EditorStyleSet.h>

#define LOCTEXT_NAMESPACE "FSpotlightSearchModule"

FQuickMenuCommands::FQuickMenuCommands() : TCommands<FQuickMenuCommands>(TEXT("SpotlightSearch"), LOCTEXT("QuickCommands", "Quick Commands"), NAME_None, FAppStyle::GetAppStyleSetName())
{
}

void FQuickMenuCommands::RegisterCommands()
{
	UI_COMMAND(SummonQuickCommands, "Quick Menu", "Summons quick commands menu", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Q));
}

#undef LOCTEXT_NAMESPACE
