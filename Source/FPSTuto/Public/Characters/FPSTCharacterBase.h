// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "FPSTCharacterBase.generated.h"

UCLASS()
class FPSTUTO_API AFPSTCharacterBase : public ACharacter
{
	GENERATED_BODY()

	// ---------------------------------------------------------------------
	// Base Func and Vars
	// ---------------------------------------------------------------------

public:
	// Sets default values for this character's properties
	AFPSTCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// ---------------------------------------------------------------------
	// Camera
	// ---------------------------------------------------------------------

public:

	UFUNCTION(BlueprintCallable)
	USpringArmComponent* GetSpringArm();

	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetCamera();

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Camera")
	TObjectPtr<UCameraComponent> Camera;
private:
	


};
