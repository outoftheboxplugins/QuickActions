// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "QuickMenuExtension.h"

#include "HdiTutorialsExtensions.generated.h"

/**
 *
 */
UCLASS()
class UHdiTutorialsExtensions : public UQuickMenuExtension
{
	GENERATED_BODY()

	virtual TArray<FQuickCommandEntry> GetCommands() override;
	virtual int32 GetPriority() const override;
};
