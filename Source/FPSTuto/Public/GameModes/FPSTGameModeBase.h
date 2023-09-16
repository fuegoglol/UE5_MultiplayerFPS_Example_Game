// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "FPSTGameModeBase.generated.h"

UCLASS()
class FPSTUTO_API AFPSTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSTGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
