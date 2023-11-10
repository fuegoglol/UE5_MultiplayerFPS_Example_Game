// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FPSTDamageBoneRepartitionDataAsset.generated.h"

UENUM()
enum EDamageBodyCategory
{
	Body,
	Head,
	Arms,
	Legs
};

/**
 * 
 */
UCLASS()
class FPSTUTO_API UFPSTDamageBoneRepartitionDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TMap<FName,TEnumAsByte<EDamageBodyCategory>> BonesBodyCategory;
};
