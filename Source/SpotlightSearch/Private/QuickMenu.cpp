// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "QuickMenu.h"

#include <Interfaces/IMainFrameModule.h>

#include "QuickMenuCommands.h"
#include "QuickMenuStyle.h"
#include "SQuickMenuWindow.h"

#define LOCTEXT_NAMESPACE "QuickMenuModule"

void FQuickMenuModule::StartupModule()
{
	FQuickMenuStyle::Initialize();
	
	RegisterQuickCommands();
}

void FQuickMenuModule::ShutdownModule()
{
	UnregisterQuickCommands();

	FQuickMenuStyle::Shutdown();
}

void FQuickMenuModule::RegisterQuickCommands()
{
	FQuickMenuCommands::Register();

	//TODO: Investigate if the MainFrame is the best place to bind this action or we should have a more low level one.
	IMainFrameModule& MainFrame = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	FUICommandList& ActionList = *MainFrame.GetMainFrameCommandBindings();

	ActionList.MapAction(
		FQuickMenuCommands::Get().SummonQuickCommands,
		FExecuteAction::CreateLambda(
			[this]
			{
				const TSharedRef<SQuickMenuWindow> ClassPickerDialog = SNew(SQuickMenuWindow);
				FSlateApplication::Get().AddWindow(ClassPickerDialog);
			}
		)
	);
}

void FQuickMenuModule::UnregisterQuickCommands()
{
	FQuickMenuCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FQuickMenuModule, QuickMenu)
