// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/FPSTGameModeBase.h"


// Sets default values
AFPSTGameModeBase::AFPSTGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFPSTGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
}


