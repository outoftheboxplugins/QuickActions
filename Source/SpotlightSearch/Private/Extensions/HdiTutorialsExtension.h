// Copyright Out-of-the-Box Plugins 2018-2021. All Rights Reserved.

#pragma once

#include "QuickMenuExtension.h"

#include "HdiTutorialsExtension.generated.h"

/**
 * @brief Holds information about a YouTube tutorial
 */
USTRUCT()
struct FTutorialInfo
{
	GENERATED_BODY()

	/**
	 * @brief Title of the video
	 */
	UPROPERTY()
	FString Title;
	/**
	 * @brief Description of the video
	 */
	UPROPERTY()
	FString Description;
	/**
	 * @brief YouTube URL
	 */
	UPROPERTY()
	FString Url;
};

/**
 * Quick Menu extensions adding video tutorials for the "How the fuck do I" and "What the fuck is" YouTube series from Mathew Wadstein
 * @see https://www.youtube.com/c/MathewWadsteinTutorials
 */
UCLASS(Config = QuickActions)
class UHdiTutorialsExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<FQuickCommandEntry> GetCommands() override;
	virtual int32 GetPriority() const override;

	UPROPERTY(Config)
	TArray<FTutorialInfo> Tutorials;
};