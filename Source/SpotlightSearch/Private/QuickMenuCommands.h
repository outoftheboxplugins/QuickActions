// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

/**
 * @brief Class that holds all quick menu commands.
 */
class FQuickMenuCommands : public TCommands<FQuickMenuCommands>
{
public:
	FQuickMenuCommands();

	// Begin TCommands interface
	virtual void RegisterCommands() override;
	// End TCommands interface

	/**
	 * @brief Spawns the spotlight search (Quick Menu) window.
	 */
	TSharedPtr<FUICommandInfo> SummonQuickCommands;
};
