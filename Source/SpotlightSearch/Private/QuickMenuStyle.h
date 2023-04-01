// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "Styling/SlateStyle.h"

/**
 * The style class that contains UI elements specific to the Quick Menu.
 */
class FQuickMenuStyle : public FSlateStyleSet
{
public:
	/**
	 * @brief Access the singleton instance for this SlateStyle
	 */
	static const FQuickMenuStyle& Get();
	/**
	 * @brief Creates and Registers the plugin SlateStyle
	 */
	static void Initialize();
	/**
	 * @brief Unregisters the plugin SlateStyle
	 */
	static void Shutdown();

private:
	FQuickMenuStyle();

	// Begin FSlateStyleSet Interface
	virtual const FName& GetStyleSetName() const override;
	// End FSlateStyleSet Interface

	/**
	 * @brief Unique name for this SlateStyle
	 */
	static FName StyleName;
	/**
	 * @brief Singleton instances of this SlateStyle.
	 */
	static TUniquePtr<FQuickMenuStyle> Inst;
};
