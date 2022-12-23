// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "QuickMenuExtension.h"

#include "HdiTutorialsExtension.generated.h"

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
 *
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