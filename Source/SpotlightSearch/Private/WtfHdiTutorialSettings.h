// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Engine/DeveloperSettings.h>

#include "WtfHdiTutorialSettings.generated.h"


/**
 * Contains all the Tutorials from the What the fuck How do I from Mathew Wadstein
 */
UCLASS(config = Editor, defaultconfig)
class SPOTLIGHTSEARCH_API UWtfHdiTutorialSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Customization, config)
	bool bIncludeTutorials = true;

	void ToggleIncludeTutorials();
};