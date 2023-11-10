// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Damages/FPSTDamageBoneRepartitionDataAsset.h"
#include "GameFramework/Actor.h"
#include "FPSTWeaponBase.generated.h"

UCLASS()
class FPSTUTO_API AFPSTWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSTWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// ---------------------------------------------------------------------
// Cosmetic Func and Vars
// ---------------------------------------------------------------------

public:

	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetWeaponSkMesh();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> WeaponSkMesh;

// ---------------------------------------------------------------------
// Ammo Func and Vars
// ---------------------------------------------------------------------

public:
	
	UFUNCTION(BlueprintCallable)
	virtual void Reload();

	UFUNCTION(BlueprintCallable)
	int GetCurrentAmmoCount() const;

protected:
	
	UFUNCTION(BlueprintCallable)
	int DecreaseAmmo(int ByAmount = 1);

	UFUNCTION(BlueprintCallable)
	void SetAmmoCount(int NewAmount);

private:
	
	int AmmoCount = 0;

// ---------------------------------------------------------------------
// Fire Func and Vars
// ---------------------------------------------------------------------

public:
	
	UFUNCTION(BlueprintCallable)
	virtual void PrimaryFire();

	UFUNCTION(BlueprintCallable)
	virtual void SecondaryFire();

protected:

	UFUNCTION(BlueprintCallable)
	TArray<FHitResult> TraceLineShotByChannel(ECollisionChannel CollisionChannel = ECollisionChannel::ECC_Visibility);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Fire")
	int MaxAmmo = 30;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Fire")
	float FireRate = 0.1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Fire")
	float FireRange = 10000;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Fire")
	TEnumAsByte<ECollisionChannel> FireCollisionChannel = ECollisionChannel::ECC_Visibility;

// ---------------------------------------------------------------------
// Damages Func and Vars
// ---------------------------------------------------------------------
	
public:

	/**
	 * @brief Compute damages depending of the hit bone
	 * @param HitBoneName : Bone hit by the shot
	 * @return Damages to deal
	 */
	UFUNCTION(BlueprintCallable)
	float ComputeDamages(FName HitBoneName);

	UFUNCTION(Server,Reliable)
	void Server_NotifyHit(FHitResult HitResult, float DealDamages);
	
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Damages")
	float BaseDamages = 10;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Damages")
	float HeadDamageFactor = 10;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Damages")
	float ArmsDamageFactor = .5;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Damages")
	float LegsDamageFactor = .5;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Damages")
	TSubclassOf<UDamageType> DamageType;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Damages")
	TObjectPtr<UFPSTDamageBoneRepartitionDataAsset> DamagesRepartition;

// ---------------------------------------------------------------------
// Other
// ---------------------------------------------------------------------
public:

	UFUNCTION(BlueprintCallable)
	void SetWeaponOwner(AController* NewOwner);

	UFUNCTION(BlueprintCallable)
	void ClearWeaponOwner();
	
protected:

	UPROPERTY()
	TObjectPtr<AController> WeaponOwner;
};
