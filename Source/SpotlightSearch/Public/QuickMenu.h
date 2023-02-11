// Copyright Out-of-the-Box Plugins 2018-2022. All Rights Reserved.

#pragma once

#include <LevelEditor.h>
#include <Modules/ModuleManager.h>

class FQuickMenuModule : public IModuleInterface
{
private:
	// Begin IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End IModuleInterface interface

	void RegisterQuickCommands();
	void UnregisterQuickCommands();
};
