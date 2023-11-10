// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PlayerControllers/FPSTPlayerControllerBase.h"

#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTags/GameplayTags.h"
#include "Inputs/FPSTTaggedInputComponent.h"


// Sets default values
AFPSTPlayerControllerBase::AFPSTPlayerControllerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFPSTPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	// set the mapping context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		// Subsystem is valid : this is the local player
		Subsystem->AddMappingContext(IMC, 0);
	}
}

// Called every frame
void AFPSTPlayerControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UFPSTInputConfig* AFPSTPlayerControllerBase::GetInputConfig() const
{
	return InputConfig;
}

UFPSTTaggedInputComponent* AFPSTPlayerControllerBase::GetPLayerInputComponent() const
{
	return Cast<UFPSTTaggedInputComponent>(InputComponent);
}

void AFPSTPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Check if we are using the right InputComponent
	auto* TaggedInputComponent = CastChecked<UFPSTTaggedInputComponent>(InputComponent);

	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Move, ETriggerEvent::Triggered, this, &AFPSTPlayerControllerBase::InputMove);
	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Look, ETriggerEvent::Triggered, this, &AFPSTPlayerControllerBase::InputLook);
	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Jump, ETriggerEvent::Triggered, this, &AFPSTPlayerControllerBase::InputJump);
}

void AFPSTPlayerControllerBase::InputMove(const FInputActionValue& InputActionValue)
{

	const FVector2d MoveVector = InputActionValue.Get<FVector2d>();
	
	const FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	const FVector ForwardDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
	const FVector RightDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));

	if(APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MoveVector.X);
		ControlledPawn->AddMovementInput(RightDirection, MoveVector.Y);
	}
	
}

void AFPSTPlayerControllerBase::InputLook(const FInputActionValue& InputActionValue)
{
	const auto LookVector = InputActionValue.Get<FVector2d>();
	
	AddPitchInput(LookVector.X);
	AddYawInput(LookVector.Y);
}

void AFPSTPlayerControllerBase::InputJump(const FInputActionValue& InputActionValue)
{
	if(ACharacter* ControlledCharacter = GetCharacter())
	{
		ControlledCharacter->Jump();
	}
}

