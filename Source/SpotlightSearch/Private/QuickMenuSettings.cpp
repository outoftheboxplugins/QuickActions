// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "QuickMenuSettings.h"

void UQuickMenuSettings::ToggleIncludeTutorials()
{
	bIncludeTutorials = !bIncludeTutorials;

	SaveConfig(CPF_Config, *GetDefaultConfigFilename());
}