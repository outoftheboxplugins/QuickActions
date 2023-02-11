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