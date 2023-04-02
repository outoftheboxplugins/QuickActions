// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

namespace QuickMenuHelpers
{
	bool IsAbbreviation(const FString& Candidate, const FString& Search);
	bool IsMatchTo(const FString& Candidate, const FString& Search);
	float GetMatchPercentage(const FString& Candidate, const FString& Search);
}; // namespace QuickMenuHelpers
