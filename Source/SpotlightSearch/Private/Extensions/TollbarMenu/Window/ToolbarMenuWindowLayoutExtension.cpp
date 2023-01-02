// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuWindowLayoutExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UToolbarMenuWindowLayoutExtension::GetCommands(const FToolMenuContext& Context)
{
	return Super::GetCommands(Context);
}