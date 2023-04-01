// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "Styling/SlateStyle.h"

class FQuickMenuStyle : public FSlateStyleSet
{
public:
	virtual const FName& GetStyleSetName() const override;

	static const FQuickMenuStyle& Get();
	static void Initialize();
	static void Shutdown();

	virtual ~FQuickMenuStyle() override;

private:
	FQuickMenuStyle();

	static FName StyleName;
	static TUniquePtr<FQuickMenuStyle> Inst;
};
