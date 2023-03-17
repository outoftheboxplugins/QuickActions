// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "ReflectionFunctionsExtension.h"

TArray<TSharedPtr<FQuickCommandEntry>> UReflectionFunctionsExtension::GetCommands(const FToolMenuContext& Context)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UReflectionFunctionsExtension::GetCommands);

	TArray<TSharedPtr<FQuickCommandEntry>> OutCommands;

	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		const UClass* CurrentClass = *ClassIt;
		for (TFieldIterator<UFunction> FunctionIt(CurrentClass); FunctionIt; ++FunctionIt)
		{
			UFunction* Function = *FunctionIt;
			if (Function->HasMetaData(TEXT("QuickActionEntry")))
			{
				const TSharedPtr<FQuickCommandEntry> FunctionEntry = MakeShared<FQuickCommandEntry>();
				FunctionEntry->Title = FText::FromString(Function->GetName());
				FunctionEntry->Tooltip = FText::FromString(Function->GetDesc());
				FunctionEntry->Icon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Kismet.AllClasses.FunctionIcon");
				FunctionEntry->ExecuteCallback = FSimpleDelegate::CreateLambda(
					[=]()
					{
						ProcessEvent(Function, nullptr);
					}
				);

				OutCommands.Add(FunctionEntry);
			}
		}
	}

	return OutCommands;
}

void UReflectionFunctionsExtension::ExampleFunction()
{
	UE_LOG(LogTemp, Log, TEXT("Example function executed"));
}