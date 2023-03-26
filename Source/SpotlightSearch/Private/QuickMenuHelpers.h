// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

namespace QuickMenuHelpers
{
	bool IsAbbreviation(const FString& Candidate, const FString& Search);
	bool IsStartingWith(const FString& Candidate, const FString& Search);
	bool IsCloseTo(const FString& Candidate, const FString& Search);
}; // namespace QuickMenuHelpers
