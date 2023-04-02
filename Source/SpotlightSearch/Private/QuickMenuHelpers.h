// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

namespace QuickMenuHelpers
{
	/**
	 * @brief Checks if the string we searched for is an abbreviation of the candidate
	 * Example 1: { Candidate: "Widget Reflector" Search: "WR" }       -> TRUE
	 * Example 2: { Candidate: "Widget Reflector" Search: "wr" }       -> TRUE
	 * Example 3: { Candidate: "Widget Reflector" Search: "widget r" } -> FALSE
	 */
	bool IsAbbreviation(const FString& Candidate, const FString& Search);
	/**
	 * @brief Checks if the string we searched for is a potential match of the candidate
	 * Example 1: { Candidate: "Widget Reflector" Search: "Widget" }    -> TRUE
	 * Example 2: { Candidate: "Widget Reflector" Search: "Reflector" } -> TRUE
	 * Example 3: { Candidate: "Widget Reflector" Search: "wid ref" }   -> FALSE
	 */
	bool IsPotentialMatchTo(const FString& Candidate, const FString& Search);
	/**
	 * @brief Uses Levenshtein Distance to determine the matching percentage of the search string to the candidate
	 */
	float GetMatchPercentage(const FString& Candidate, const FString& Search);
}; // namespace QuickMenuHelpers
