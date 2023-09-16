// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "FPSTInputConfig.h"
#include "FPSTTaggedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPSTUTO_API UFPSTTaggedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass, typename FuncType>
	void BindActionByTag(const UFPSTInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);
};

template <class UserClass, typename FuncType>
void UFPSTTaggedInputComponent::BindActionByTag(const UFPSTInputConfig* InputConfig, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}