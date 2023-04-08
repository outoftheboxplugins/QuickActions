// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "QuickMenuCommands.h"

#include <EditorStyleSet.h>

#define LOCTEXT_NAMESPACE "FQuickMenuModule"

FQuickMenuCommands::FQuickMenuCommands() : TCommands<FQuickMenuCommands>(TEXT("QuickMenu"), LOCTEXT("QuickCommands", "Quick Commands"), NAME_None, FAppStyle::GetAppStyleSetName())
{
}

void FQuickMenuCommands::RegisterCommands()
{
	UI_COMMAND(SummonQuickCommands, "Quick Menu", "Summons quick commands menu", EUserInterfaceActionType::Button, FInputChord(EModifierKey::Control, EKeys::Q));
}

#undef LOCTEXT_NAMESPACE
