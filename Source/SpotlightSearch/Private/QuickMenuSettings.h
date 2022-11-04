// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include <Engine/DeveloperSettings.h>

#include "QuickMenuSettings.generated.h"

/**
 *
 */
UCLASS(config = Editor, defaultconfig)
class SPOTLIGHTSEARCH_API UQuickMenuSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * @brief Maximum number of entries we will display under the search bar
	 */
	UPROPERTY(EditAnywhere, Category = Customization, config)
	int32 MaxEntriesToShow = 10;
};
