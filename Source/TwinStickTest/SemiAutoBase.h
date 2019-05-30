// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "SemiAutoBase.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKTEST_API ASemiAutoBase : public AWeaponBase
{
	GENERATED_BODY()

protected:

	virtual void PrimaryFirePressed() override;

	virtual void SecondaryButtonPressed() override;

	virtual void SecondaryButtonReleased() override;

	virtual void BeginPlay() override;

	virtual void FireWeapon() override;

	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* aimFireMontage;

	
};
