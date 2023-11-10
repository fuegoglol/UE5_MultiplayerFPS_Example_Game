// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapons/FPSTWeaponBase.h"
#include "FPSTWeaponDefaultPistol.generated.h"

UCLASS()
class FPSTUTO_API AFPSTWeaponDefaultPistol : public AFPSTWeaponBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSTWeaponDefaultPistol();

	virtual void PrimaryFire() override;

	virtual void Reload() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
