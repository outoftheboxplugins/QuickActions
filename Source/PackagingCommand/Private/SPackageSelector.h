// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


struct FTargetInfo;
enum class EProjectPackagingBuildConfigurations : uint8;

/**
 *
 */
class SPackageSelector : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPackageSelector) {}
	SLATE_END_ARGS()
	/**
	 * @brief Constructs this widget with InArgs
	 */
	void Construct(const FArguments& InArgs);

	/**
	 * @brief Start the packaging process with the currently selected configuration
	 */
	void StartPackage();

private:
	/**
	 * @brief Gather the data of the available platforms, binaries and target configurations for the packaging command.
	 */
	void InitPackagingData();
	/**
	 * @brief Generate a radio button list with the options provided
	 * @param Category Name displayed before the radio buttons
	 * @param Options Entries for radio buttons
	 * @param CategoryIndex Variable which keeps track of the currently selected index for the category
	 * @return Widget containing the title and generated radio buttons.
	 */
	TSharedRef<SWidget> GenerateOptionsWidget(const FText& Category, const TArray<FString>& Options, int32& CategoryIndex) const;
	/**
	 * @brief All the possible platforms we can package for
	 */
	TArray<FName> PlatformSuggestions;
	/**
	 * @brief Index of the currently selected platform
	 */
	int32 PlatformIndex = 0;
	/**
	 * @brief All the possible binary configurations we can package for
	 */
	TArray<EProjectPackagingBuildConfigurations> BinarySuggestions;
	/**
	 * @brief Index of the currently selected binary configuration
	 */
	int32 BinaryIndex = 0;
	/**
	 * @brief All the possible target configurations (Client/Server/Custom) we can package for
	 */
	TArray<FTargetInfo> TargetSuggestions;
	/**
	 * @brief Index of the currently selected target configuration
	 */
	int32 TargetIndex = 0;
};