#include "QuickMenu.h"

#include <EditorViewportCommands.h>
#include <Interfaces/IMainFrameModule.h>

#include "QuickMenuCommands.h"
#include "QuickMenuStyle.h"
#include "SQuickCommandsMenu.h"

#define LOCTEXT_NAMESPACE "FQuickMenuModule"

namespace
{
	void SpawnMenu()
	{
		TSharedRef<SQuickCommandsMenu> ClassPickerDialog = SNew(SQuickCommandsMenu);

		FSlateApplication::Get().AddWindow(ClassPickerDialog);
	}
} // namespace
void FQuickMenuModule::StartupModule()
{
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
	IMainFrameModule& MainFrame = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	FUICommandList& ActionList = *MainFrame.GetMainFrameCommandBindings();

	ActionList.MapAction(
		FQuickMenuCommands::Get().SummonQuickCommands,
		FExecuteAction::CreateLambda(
			[this]
			{
				SpawnMenu();
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
