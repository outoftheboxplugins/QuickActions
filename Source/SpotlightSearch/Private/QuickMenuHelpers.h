#pragma once

namespace QuickMenuHelpers
{
	bool IsAbbreviation(const FString& Candidate, const FString& Search);
	bool IsStartingWith(const FString& Candidate, const FString& Search);
	bool IsCloseTo(const FString& Candidate, const FString& Search);
	
	bool StringHasPatternInside(const FString& Pattern, const FString& String);
};
