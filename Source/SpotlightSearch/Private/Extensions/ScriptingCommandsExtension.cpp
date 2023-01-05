// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ScriptingCommandsExtension.h"

#include <UICommandsScriptingSubsystem.h>

TArray<TSharedPtr<FQuickCommandEntry>> UScriptingCommandsExtension::GetCommands(const FToolMenuContext& Context)
{
	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	const UUICommandsScriptingSubsystem* CommandsScriptingSubsystem = GEngine->GetEngineSubsystem<UUICommandsScriptingSubsystem>();
	for (const FScriptingCommandInfo& Command : CommandsScriptingSubsystem->GetRegisteredCommands())
	{
		const TSharedPtr<FQuickCommandEntry> CommandEntry = MakeShared<FQuickCommandEntry>();
		CommandEntry->Title = Command.Label;
		CommandEntry->Tooltip = Command.Description;
		CommandEntry->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "FullBlueprintEditor.SwitchToScriptingMode");
		CommandEntry->ExecuteCallback = FSimpleDelegate::CreateLambda([]() {});

		FInputBindingManager& BindingManager = FInputBindingManager::Get();
		const TSharedPtr<FUICommandInfo> UICommand = BindingManager.FindCommandInContext(Command.ContextName, Command.GetFullName());
		const FUIAction* FoundAction = Context.GetActionForCommand(UICommand);
		CommandEntry->ExecuteCallback = FoundAction->ExecuteAction;
		CommandEntry->CanExecuteCallback = FoundAction->CanExecuteAction;
	}


	return OutCommands;
}