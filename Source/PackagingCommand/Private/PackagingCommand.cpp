#include "PackagingCommand.h"

#include <AssetSelection.h>
#include <EditorViewportCommands.h>
#include <Framework/Commands/GenericCommands.h>
#include <GeometryCollection/GeometryCollectionSelectionCommands.h>
#include <LevelEditor.h>
#include <LevelEditorActions.h>

#define LOCTEXT_NAMESPACE "FPackagingCommandModule"

void FPackagingCommandModule::StartupModule()
{
}

void FPackagingCommandModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPackagingCommandModule, PackagingCommand)
