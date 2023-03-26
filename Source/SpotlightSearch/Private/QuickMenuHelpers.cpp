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

bool QuickMenuHelpers::IsStartingWith(const FString& Candidate, const FString& Search)
{
	return Candidate.StartsWith(Search, ESearchCase::IgnoreCase);
}

bool QuickMenuHelpers::IsCloseTo(const FString& Candidate, const FString& Search)
{
	return Candidate.Contains(Search, ESearchCase::IgnoreCase);
}

bool QuickMenuHelpers::StringHasPatternInside(const FString& Pattern, const FString& String)
{
	TArray<TCHAR> PatternElements = Pattern.GetCharArray();
	for (const TCHAR& Element : PatternElements)
	{
		TCHAR LowerChar = FChar::ToLower(Element);
		TCHAR UpperChar = FChar::ToUpper(Element);

		if (!FindCharInString(LowerChar, String) && !FindCharInString(UpperChar, String))
		{
			return false;
		}
	}

	return true;
}