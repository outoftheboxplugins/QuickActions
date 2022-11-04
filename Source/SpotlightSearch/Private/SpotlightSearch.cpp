#include "SpotlightSearch.h"

#include "QuickMenuCommands.h"
#include "SQuickCommandsMenu.h"

#include <EditorViewportCommands.h>
#include <Interfaces/IMainFrameModule.h>

#define LOCTEXT_NAMESPACE "FSpotlightSearchModule"

namespace
{
void SpawnMenu()
{
	TSharedRef<SQuickCommandsMenu> ClassPickerDialog = SNew(SQuickCommandsMenu);

	FSlateApplication::Get().AddWindow(ClassPickerDialog);
}
}	 // namespace
void FSpotlightSearchModule::StartupModule()
{
	RegisterQuickCommands();
}

void FSpotlightSearchModule::ShutdownModule()
{
	UnregisterQuickCommands();
}

void FSpotlightSearchModule::RegisterQuickCommands()
{
	FQuickMenuCommands::Register();
	IMainFrameModule& MainFrame = FModuleManager::Get().LoadModuleChecked<IMainFrameModule>("MainFrame");
	FUICommandList& ActionList = *MainFrame.GetMainFrameCommandBindings();

	ActionList.MapAction(FQuickMenuCommands::Get().SummonQuickCommands, FExecuteAction::CreateLambda([this] { SpawnMenu(); }));
}

void FSpotlightSearchModule::UnregisterQuickCommands()
{
	FQuickMenuCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSpotlightSearchModule, SpotlightSearch)
