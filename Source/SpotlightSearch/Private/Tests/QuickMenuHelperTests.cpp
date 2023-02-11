#include "Misc/AutomationTest.h"
#include "QuickMenuHelpers.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(QuickMenuHelperTests, "QuickActions.QuickMenuHelperTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool QuickMenuHelperTests::RunTest(const FString& Parameters)
{
	auto TestPatternAndString = [this](const FString& Pattern, const FString& String, bool bExpectedResult)
	{
		FString TextName = FString::Printf(TEXT("{ %s, %s } -> %s"), *Pattern, *String, *LexToString(bExpectedResult));
		TestTrue(*TextName, QuickMenuHelpers::StringHasPatternInside(Pattern, String) == bExpectedResult);
	};

	TestPatternAndString("WR", "Widget Reflector", true);
	TestPatternAndString("wr", "Widget Reflector", true);
	TestPatternAndString("wtr", "Widget Reflector", true);
	TestPatternAndString("wtrx", "Widget Reflector", false);

	return true;
}
