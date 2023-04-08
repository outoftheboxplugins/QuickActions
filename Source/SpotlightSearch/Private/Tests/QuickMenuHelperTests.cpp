// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

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
	TestPattern("Widget Reflector", "Wwidget rrflector", false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(QuickMenuHelperMatchTests, "QuickActions.QuickMenuHelper.MatchTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool QuickMenuHelperMatchTests::RunTest(const FString& Parameters)
{
	auto TestPattern = [this](const FString& Candidate, const FString& Search, bool bExpectedResult)
	{
		const FString TextName = FString::Printf(TEXT("{ %s, %s } -> %s"), *Candidate, *Search, *LexToString(bExpectedResult));
		TestTrue(*TextName, QuickMenuHelpers::IsPotentialMatchTo(Candidate, Search) == bExpectedResult);
	};

	TestPattern("Widget Reflector", "WR", false);
	TestPattern("Widget Reflector", "wr", false);
	TestPattern("Widget Reflector", "wR", false);
	TestPattern("Widget Reflector", "wtr", false);
	TestPattern("Widget Reflector", "Widget", true);
	TestPattern("Widget Reflector", "Reflector", true);
	TestPattern("Widget Reflector", "Widget Reflector", true);
	TestPattern("Widget Reflector", "Wwidget rrflector", false);

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(QuickMenuHelperFuzzyTests, "QuickActions.QuickMenuHelper.FuzzyTests", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool QuickMenuHelperFuzzyTests::RunTest(const FString& Parameters)
{
	auto TestPattern = [this](const FString& Candidate, const FString& Search, float ExpectedResult)
	{
		const FString TextName = FString::Printf(TEXT("{ %s, %s } -> %s"), *Candidate, *Search, *LexToString(ExpectedResult));
		const float MatchPercentage = QuickMenuHelpers::GetMatchPercentage(Candidate, Search);
		TestTrue(*TextName, FMath::IsNearlyEqual(MatchPercentage, ExpectedResult, 0.01));
	};

	// Calculated with: https://awsm-tools.com/levenshtein-distance
	TestPattern("Widget Reflector", "wwidget rreflector", 88.89f);
	TestPattern("Widget Reflector", "Wwidget Rreflector", 88.89f);
	TestPattern("Widget Reflector", "wwidget rrflector", 88.24f);
	TestPattern("Widget Reflector", "Wwidget Rrflector", 88.24f);
	TestPattern("Widget Reflector", "widget reflector", 100.0f);
	TestPattern("Widget Reflector", "Widget Reflector", 100.0f);

	return true;
}