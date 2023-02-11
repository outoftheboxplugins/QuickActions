#pragma once

#include "Styling/SlateStyle.h"

class FQuickMenuStyle : public FSlateStyleSet
{
public:
	virtual const FName& GetStyleSetName() const override;
	static const FQuickMenuStyle& Get();
	static void Shutdown();

	~FQuickMenuStyle();

private:
	FQuickMenuStyle();

	void OnSettingsChanged(FName PropertyName);
	void UpdateLogTextSize();

	static FName StyleName;
	static TUniquePtr<FQuickMenuStyle> Inst;
};
