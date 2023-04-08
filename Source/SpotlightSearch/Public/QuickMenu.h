// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

/**
 * @brief Quick Menu module responsible for registering the menu spawning and custom styling
 */
class FQuickMenuModule : public IModuleInterface
{
	// Begin IModuleInterface interface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End IModuleInterface interface
	
	/**
	 * @brief Registers the menu spawning actions
	 */
	void RegisterQuickCommands();
	/**
	 * @brief Unregisters the menu spawning actions
	 */
	void UnregisterQuickCommands();
};
