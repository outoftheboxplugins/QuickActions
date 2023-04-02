#include "Misc/AutomationTest.h"
#include "QuickMenuHelpers.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(QuickMenuHelperAbbreviationTests, "QuickActions.QuickMenuHelper.AbbreviationTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool QuickMenuHelperAbbreviationTests::RunTest(const FString& Parameters)
{
	auto TestPattern = [this](const FString& Candidate, const FString& Search, bool bExpectedResult)
	{
		const FString TextName = FString::Printf(TEXT("{ %s, %s } -> %s"), *Candidate, *Search, *LexToString(bExpectedResult));
		TestTrue(*TextName, QuickMenuHelpers::IsAbbreviation(Candidate, Search) == bExpectedResult);
	};

	TestPattern("Widget Reflector", "WR", true);
	TestPattern("Widget Reflector", "wr", true);
	TestPattern("Widget Reflector", "wR", true);
	TestPattern("Widget Reflector", "wtr", false);
	TestPattern("Widget Reflector", "Widget", false);
	TestPattern("Widget Reflector", "Reflector", false);
	TestPattern("Widget Reflector", "Widget Reflector", false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(QuickMenuHelperMatchTests, "QuickActions.QuickMenuHelper.MatchTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool QuickMenuHelperMatchTests::RunTest(const FString& Parameters)
{
	auto TestPattern = [this](const FString& Candidate, const FString& Search, bool bExpectedResult)
	{
		const FString TextName = FString::Printf(TEXT("{ %s, %s } -> %s"), *Candidate, *Search, *LexToString(bExpectedResult));
		TestTrue(*TextName, QuickMenuHelpers::IsMatchTo(Candidate, Search) == bExpectedResult);
	};

	TestPattern("Widget Reflector", "WR", false);
	TestPattern("Widget Reflector", "wr", false);
	TestPattern("Widget Reflector", "wR", false);
	TestPattern("Widget Reflector", "wtr", false);
	TestPattern("Widget Reflector", "Widget", true);
	TestPattern("Widget Reflector", "Reflector", true);
	TestPattern("Widget Reflector", "Widget Reflector", true);

	return true;
}