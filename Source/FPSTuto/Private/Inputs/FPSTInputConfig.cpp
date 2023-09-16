// Fill out your copyright notice in the Description page of Project Settings.


#include "Inputs/FPSTInputConfig.h"

const UInputAction* UFPSTInputConfig::FindInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FFPSTaggedInputAction& TaggedInputAction : TaggedInputActions)
	{
		if (TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag)
		{
			return TaggedInputAction.InputAction;
		}
	}

	return nullptr;
}
