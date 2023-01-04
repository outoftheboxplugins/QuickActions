// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuBuildLevelExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuBuildLevelExtension::GetCommands(const FToolMenuContext& Context)
{
	return Super::GetCommands(Context);
}