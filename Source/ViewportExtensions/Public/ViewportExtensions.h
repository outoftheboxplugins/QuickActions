#pragma once

#include "Modules/ModuleManager.h"

class FViewportExtensionsModule : public IModuleInterface
{
private:
	// Begin IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End IModuleInterface interface

	void RegisterViewportContextMenu();
	void UnregisterViewportContextMenu();

	TSharedRef<FExtender> ExtendLevelViewportContextMenu(
		const TSharedRef<FUICommandList> InCommandList, const TArray<AActor*> SelectedActors);

	FDelegateHandle LevelViewportContextMenuExtender;
};
