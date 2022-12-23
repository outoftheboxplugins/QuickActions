// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "QuickMenuExtension.h"

#include "ToolbarMenuFileExtension.generated.h"

/**
 *
 */
UCLASS()
class SPOTLIGHTSEARCH_API UToolbarMenuFileExtension : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<FQuickCommandEntry> GetCommands() override;
};