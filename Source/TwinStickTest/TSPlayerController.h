// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKTEST_API ATSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ATSPlayerController();

protected:

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual bool InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad) override;
	virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad) override;

	void PrimaryFirePressed();
	void PrimaryFireReleased();

	void SecondaryFirePressed();
	void SecondaryFireReleased();

	void NextWeaponPressed();

	void ShiftLeftPressed();
	void ShiftLeftReleased();

	void ShiftRightPressed();
	void ShiftRightReleased();

	UFUNCTION()
	void RotateToMousePosition();

	UPROPERTY()
	bool bIsGamepadInput;
	
	class ATwinStickPC* currentPC;

};
