// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ToolbarMenuWindowLogExtension.h"

TArray<FQuickCommandEntry> UToolbarMenuWindowLogExtension::GetCommands()
{
	TArray<FQuickCommandEntry> OutCommands;

	FQuickCommandEntry DeviceOutputLog;
	DeviceOutputLog.Title = NSLOCTEXT("OutputLog", "DeviceOutputLogTab", "Device Output Log");
	DeviceOutputLog.Tooltip = NSLOCTEXT("OutputLog", "DeviceOutputLogTooltipText", "Open the Device Output Log tab.");
	DeviceOutputLog.Icon = FSlateIcon(FName("OutputLogStyle"), "Log.TabIcon");
	DeviceOutputLog.ExecuteCallback = FSimpleDelegate::CreateLambda(
		[]()
		{
			FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("DeviceOutputLog")));
		}
	);
	OutCommands.Add(DeviceOutputLog);

	FQuickCommandEntry InterchangeResultsBrowser;

	OutCommands.Add(InterchangeResultsBrowser);

	return OutCommands;
}