// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "UObject/Object.h"
#include "FPSTInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FFPSTaggedInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 * 
 */
UCLASS()
class FPSTUTO_API UFPSTInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindInputActionForTag(const FGameplayTag& InputTag) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FFPSTaggedInputAction> TaggedInputActions;
};
