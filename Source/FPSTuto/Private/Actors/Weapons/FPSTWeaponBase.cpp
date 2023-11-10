// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/FPSTWeaponBase.h"

#include "Camera/CameraComponent.h"
#include "Controllers/PlayerControllers/FPSTPlayerControllerBase.h"
#include "GameplayTags/GameplayTags.h"
#include "Inputs/FPSTTaggedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AFPSTWeaponBase::AFPSTWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponSkMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponSkMesh->SetupAttachment(RootComponent);

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AFPSTWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

USkeletalMeshComponent* AFPSTWeaponBase::GetWeaponSkMesh()
{
	return WeaponSkMesh;
}

void AFPSTWeaponBase::PrimaryFire()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Primary Fire"));
}

void AFPSTWeaponBase::SecondaryFire()
{
}

TArray<FHitResult> AFPSTWeaponBase::TraceLineShotByChannel(ECollisionChannel CollisionChannel)
{
	TArray<FHitResult> Results;

	const AActor* ActorOwner = WeaponOwner->GetPawn();

	UCameraComponent* OwnersCamera = nullptr;

	// Setup Shot Start Vector
	
	FVector Start = FVector::ZeroVector;

	if(auto* UnCastedOwnerCameraComp = ActorOwner->GetComponentByClass(UCameraComponent::StaticClass()))
	{
		OwnersCamera = Cast<UCameraComponent>(UnCastedOwnerCameraComp);
		if(OwnersCamera)
		{
			Start = OwnersCamera->GetComponentLocation();
		}
	}
	else
	{
		Start = ActorOwner->GetActorLocation();
	}

	// Setup Shot End Vector

	FVector End = OwnersCamera?
		Start+OwnersCamera->GetForwardVector()*FireRange :
		Start+ActorOwner->GetActorForwardVector()*FireRange;

	// Setup Query Params

	FCollisionQueryParams ColQueryParams;
	ColQueryParams.bTraceComplex = true;
	ColQueryParams.AddIgnoredActor(ActorOwner);

	GetWorld()->LineTraceMultiByChannel(Results,Start,End,CollisionChannel,ColQueryParams);

	return Results;
}

float AFPSTWeaponBase::ComputeDamages(FName HitBoneName)
{
	EDamageBodyCategory HitCategory = Body;

	if(const auto NewHitCategory = DamagesRepartition->BonesBodyCategory.Find(HitBoneName))
		HitCategory = *NewHitCategory;

	float FinalDamages = BaseDamages;
	
	switch (HitCategory)
	{
	case Head : FinalDamages*=HeadDamageFactor; break;
	case Arms : FinalDamages*=ArmsDamageFactor; break;
	case Legs : FinalDamages*=LegsDamageFactor; break;
	case Body : break;
	}

	return FinalDamages;
}

void AFPSTWeaponBase::Server_NotifyHit_Implementation(FHitResult HitResult, float DealDamages)
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("%s Touched by %s"), *HitResult.GetActor()->GetName(), *WeaponOwner->GetName()));
	UGameplayStatics::ApplyPointDamage(HitResult.GetActor(),DealDamages,HitResult.TraceStart,HitResult,WeaponOwner,this,DamageType);
}

int AFPSTWeaponBase::GetCurrentAmmoCount() const
{
	return AmmoCount;
}

void AFPSTWeaponBase::SetWeaponOwner(AController* NewOwner)
{
	WeaponOwner = NewOwner;

	if(const auto* FPSTController = Cast<AFPSTPlayerControllerBase>(WeaponOwner))
	{
		if(auto* TaggedInputComponent = FPSTController->GetPLayerInputComponent())
		{
			TaggedInputComponent->BindActionByTag(FPSTController->GetInputConfig(),TAG_Input_Primary,ETriggerEvent::Triggered,this,&ThisClass::PrimaryFire);
			TaggedInputComponent->BindActionByTag(FPSTController->GetInputConfig(),TAG_Input_Secondary,ETriggerEvent::Triggered,this,&ThisClass::SecondaryFire);
			TaggedInputComponent->BindActionByTag(FPSTController->GetInputConfig(),TAG_Input_Special,ETriggerEvent::Triggered,this,&ThisClass::Reload);
		}
	}
}

void AFPSTWeaponBase::ClearWeaponOwner()
{
	if(const auto* FPSTController = Cast<AFPSTPlayerControllerBase>(WeaponOwner))
	{
		if(auto* TaggedInputComponent = FPSTController->GetPLayerInputComponent())
			TaggedInputComponent->ClearBindingsForObject(this);
	}
	WeaponOwner = nullptr;
}

void AFPSTWeaponBase::Reload()
{
}

int AFPSTWeaponBase::DecreaseAmmo(int ByAmount)
{
	AmmoCount -= ByAmount;
	return AmmoCount;
}

void AFPSTWeaponBase::SetAmmoCount(int NewAmount)
{
	AmmoCount = UKismetMathLibrary::Clamp(NewAmount,0,MaxAmmo);
}


