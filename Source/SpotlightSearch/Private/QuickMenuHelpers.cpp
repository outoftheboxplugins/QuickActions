// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "QuickMenuHelpers.h"

#include "Algo/LevenshteinDistance.h"

bool QuickMenuHelpers::IsAbbreviation(const FString& Candidate, const FString& Search)
{
	TArray<FString> Words;
	Candidate.ParseIntoArray(Words, TEXT(" "), true);

	FString Abbreviation;
	for (const FString& Word : Words)
	{
		Abbreviation.AppendChar(Word[0]);
	}

	return Abbreviation.Equals(Search, ESearchCase::IgnoreCase);
}

bool QuickMenuHelpers::IsPotentialMatchTo(const FString& Candidate, const FString& Search)
{
	return Candidate.Contains(Search, ESearchCase::IgnoreCase);
}

float QuickMenuHelpers::GetMatchPercentage(const FString& Candidate, const FString& Search)
{
	const float WorstCase = FMath::Max3(Candidate.Len(), Search.Len(), 1);
	const float Score = 1.0f - (Algo::LevenshteinDistance(Search.ToLower(), Candidate.ToLower()) / WorstCase);

	return Score * 100.0f;
}
