// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inputs/FPSTInputConfig.h"
#include "InputMappingContext.h"
#include "FPSTPlayerControllerBase.generated.h"

UCLASS()
class FPSTUTO_API AFPSTPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

	// ---------------------------------------------------------------------
	// Base Func and Vars
	// ---------------------------------------------------------------------
	
public:
	// Sets default values for this actor's properties
	AFPSTPlayerControllerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ---------------------------------------------------------------------
	// Inputs Func and Vars
	// ---------------------------------------------------------------------

public:

	UFUNCTION(BlueprintCallable)
	UFPSTInputConfig* GetInputConfig() const;

	UFUNCTION(BlueprintCallable)
	UFPSTTaggedInputComponent* GetPLayerInputComponent() const;
	
protected:

	/**
	 * @brief Link Gameplay Tags and Inputs to Functions
	 */
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> IMC;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UFPSTInputConfig> InputConfig;

	/**
	 * @brief Move
	 * @param InputActionValue : Value of the input
	 */
	void InputMove(const FInputActionValue& InputActionValue);

	/**
	 * @brief Look
	 * @param InputActionValue : Value of the input
	 */
	void InputLook(const FInputActionValue& InputActionValue);

	/**
	 * @brief Jump
	 * @param InputActionValue : Value of the input
	 */
	void InputJump(const FInputActionValue& InputActionValue);
};
