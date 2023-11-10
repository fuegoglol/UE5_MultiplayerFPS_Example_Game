// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/Pistols/FPSTWeaponDefaultPistol.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AFPSTWeaponDefaultPistol::AFPSTWeaponDefaultPistol()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AFPSTWeaponDefaultPistol::PrimaryFire()
{
	Super::PrimaryFire();

	if(GetCurrentAmmoCount() <= 0) return;

	const TArray<FHitResult> HitResults = TraceLineShotByChannel(FireCollisionChannel);

	for(const auto &HitResult : HitResults)
	{
		const float DamagesToDeal = ComputeDamages(HitResult.BoneName);
		Server_NotifyHit(HitResult,DamagesToDeal);
	}

	if(DecreaseAmmo() <= 0)
		Reload();
}

void AFPSTWeaponDefaultPistol::Reload()
{
	Super::Reload();
	SetAmmoCount(MaxAmmo);
}

// Called when the game starts or when spawned
void AFPSTWeaponDefaultPistol::BeginPlay()
{
	Super::BeginPlay();
	SetAmmoCount(MaxAmmo);
}

