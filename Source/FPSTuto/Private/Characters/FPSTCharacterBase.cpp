// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FPSTCharacterBase.h"

// Sets default values
AFPSTCharacterBase::AFPSTCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AFPSTCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

USpringArmComponent* AFPSTCharacterBase::GetSpringArm()
{
	return SpringArm;
}

UCameraComponent* AFPSTCharacterBase::GetCamera()
{
	return Camera;
}

