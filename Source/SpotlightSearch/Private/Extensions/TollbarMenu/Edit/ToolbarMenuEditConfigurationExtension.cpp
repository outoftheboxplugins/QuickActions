// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuEditConfigurationExtension.h"

#include "ISettingsModule.h"

#define LOCTEXT_NAMESPACE "QuickActions"

TArray<FQuickCommandEntry> UToolbarMenuEditConfigurationExtension::GetCommands()
{
	TArray<FQuickCommandEntry> OutCommands;

	FQuickCommandEntry OpenEditorPreferences;
	OpenEditorPreferences.Title = LOCTEXT("OpenEditorPreferences", "Open Editor Preferences");
	OpenEditorPreferences.Tooltip = LOCTEXT("OpenEditorPreferencesTip", "Configure the behavior and features of the Unreal Editor.");
	OpenEditorPreferences.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "EditorPreferences.TabIcon");
	OpenEditorPreferences.ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FModuleManager::LoadModuleChecked<ISettingsModule>("Settings").ShowViewer(FName("Editor"), FName("General"), FName("Appearance"));
		}
	);
	OutCommands.Add(OpenEditorPreferences);

	FQuickCommandEntry OpenProjectSettings;
	OpenProjectSettings.Title = LOCTEXT("OpenProjectSettings", "Open Project Settings");
	OpenProjectSettings.Tooltip = LOCTEXT("OpenProjectSettingsTip", "Change the settings of the currently loaded project.");
	OpenProjectSettings.Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "ProjectSettings.TabIcon");
	OpenProjectSettings.ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FModuleManager::LoadModuleChecked<ISettingsModule>("Settings").ShowViewer(FName("Project"), FName("Project"), FName("General"));
		}
	);
	OutCommands.Add(OpenProjectSettings);

	FQuickCommandEntry Plugins;
	Plugins.Title = LOCTEXT("PluginsEditor", "Plugins");
	Plugins.Tooltip = LOCTEXT("PluginsEditorTip", "Open the Plugins Browser tab.");
	Plugins.Icon = FSlateIcon("PluginStyle", "Plugins.TabIcon");
	Plugins.ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("PluginsEditor")));
		}
	);
	OutCommands.Emplace(Plugins);

	return OutCommands;
}


#undef LOCTEXT_NAMESPACE