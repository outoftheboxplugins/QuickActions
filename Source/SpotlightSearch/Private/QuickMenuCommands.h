// Copyright Out-of-the-Box Plugins 2018-2022. All Rights Reserved.

#pragma once

class FQuickMenuCommands : public TCommands<FQuickMenuCommands>
{
public:
	FQuickMenuCommands();

	// Begin TCommands interface
	virtual void RegisterCommands() override;
	// End TCommands interface

	TSharedPtr<FUICommandInfo> SummonQuickCommands;
};
