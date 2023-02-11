#pragma once

#include "Modules/ModuleManager.h"

class FPackagingCommandModule : public IModuleInterface
{
private:
	// Begin IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End IModuleInterface interface
};
