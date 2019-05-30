// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TwinStickPC.generated.h"

UCLASS()
class TWINSTICKTEST_API ATwinStickPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATwinStickPC();

protected:

	UPROPERTY()
	bool isAiming;

	UPROPERTY(EditDefaultsOnly)
	float baseMoveSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* characterMeleeAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* characterDeflectAnim;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AMeleeBase> startingMelee;

	UPROPERTY(EditDefaultsOnly)
	float hpRegenPercent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ADeflectResponseActor> normalAttackResponseClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADeflectResponseActor> altAttackResponseClass;

	UPROPERTY(BlueprintReadOnly)
	ADeflectResponseActor* normalAttackResponse;

	UPROPERTY(BlueprintReadOnly)
	ADeflectResponseActor* altAttackReponse;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<class AWeaponBase>> startingWeapons;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 1, UIMin = 1))
	float maxHP;

	UPROPERTY()
	TArray<AWeaponBase*> currentWeapons;

	UPROPERTY()
	AMeleeBase* equipedMelee;

	UPROPERTY(EditDefaultsOnly)
	bool IsMelee;

	UPROPERTY()
	AWeaponBase* equipedWeapon;

	UFUNCTION()
	void EquipWeapon(AWeaponBase* weaponToEquip);

	UPROPERTY()
	int currentWeaponIndex;

	UPROPERTY()
	bool canFire;

	UFUNCTION()
	void ModifyHP(float amountToChange);

	UPROPERTY() 
	float currentHP;

	UPROPERTY(EditDefaultsOnly)
	float shifAmountModifier;


	UPROPERTY()
	bool isShiftingAttack;

	UPROPERTY()
	bool isShiftingDefence;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void SetShiftAttack(bool newState);



	UFUNCTION()
	void SetShiftDefense(bool newState);

	UFUNCTION()
	void PrimaryAction(bool isPressed);

	UFUNCTION()
	void SecondaryAction(bool isPressed);

	UFUNCTION()
	void ChangeWeapon(bool isNext);

	UFUNCTION()
	void SetIsAiming(bool newState);

	UFUNCTION()
	void PlayFireAnimMontage(UAnimMontage* animToPlay);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Weapon")
	EWeaponType GetEquipedWeaponType();

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Weapon")
	bool GetIsAiming();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetCanFire(bool newState);

	UFUNCTION()
	FVector GetWeaponLocation();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	AMeleeBase* GetMeleeWeapon();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetCurrentHealth();

	UFUNCTION()
	void Die();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float totalEnergy;

	UPROPERTY(BlueprintReadWrite)
	float attackEnergy;

	UPROPERTY(BlueprintReadWrite)
	float defenseEnergy;

};
