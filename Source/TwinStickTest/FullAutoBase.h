// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "FullAutoBase.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKTEST_API AFullAutoBase : public AWeaponBase
{
	GENERATED_BODY()
	
protected:

	virtual void PrimaryFirePressed() override;

	virtual void PrimaryFireReleased() override;

	virtual void SecondaryButtonPressed() override;

	virtual void SecondaryButtonReleased() override;

	virtual void WeaponCooldownFinished() override;

	virtual void FireWeapon() override;

	virtual void SheatheWeapon() override;

	FTimerHandle TimerHandle_CooldownFinished;
};
