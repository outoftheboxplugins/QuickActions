// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuFileImportExportExtension.generated.h"

/**
 * Add entries from the main frame toolbar -> File menu -> Import/Export section
 */
UCLASS()
class UToolbarMenuFileImportExportExtension : public UQuickMenuExtension
{
	GENERATED_BODY()
	
	virtual TArray<TSharedPtr<FQuickCommandEntry>> GetCommands(const FToolMenuContext& Context) override;
};