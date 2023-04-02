// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#include "QuickMenuHelpers.h"

namespace
{
	bool FindCharInString(const TCHAR& InChar, const FString& String)
	{
		int32 FoundIndex;
		String.FindChar(InChar, FoundIndex);
		return FoundIndex != INDEX_NONE;
	}
} // namespace

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

bool QuickMenuHelpers::IsMatchTo(const FString& Candidate, const FString& Search)
{
	return Candidate.Contains(Search, ESearchCase::IgnoreCase);
}

bool QuickMenuHelpers::IsCloseTo(const FString& Candidate, const FString& Search)
{
	// TODO: Implement fuzzy search algo
	return Candidate.Contains(Search, ESearchCase::IgnoreCase);
}
