// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Engine/DeveloperSettings.h>

#include "WtfHdiTutorialSettings.generated.h"

USTRUCT(BlueprintType)
struct FTutorialInfo
{
	GENERATED_BODY()

	/**
	 * @brief Title of the video
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Title;
	/**
	 * @brief Description of the video
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;
	/**
	 * @brief YouTube URL
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Url;
};

/**
 * Contains all the Tutorials from the What the fuck How do I from Mathew Wadstein
 */
UCLASS(config = Editor, defaultconfig)
class SPOTLIGHTSEARCH_API UWtfHdiTutorialSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Customization, config)
	TArray<FTutorialInfo> Tutorials;

	UPROPERTY(EditAnywhere, Category = Customization, config)
	bool bIncludeTutorials = true;

	void ToggleIncludeTutorials();
};