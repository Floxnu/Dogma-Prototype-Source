// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class TWINSTICKTEST_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float maxHP;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float currentHP;

	UFUNCTION()
	void OnPointDamageTaken(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser);

	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* attackAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMeleeBase> meleeWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeaponBase> rangedWeapon;

	UPROPERTY()
	AMeleeBase* equipedMeleeWeapon;

	UPROPERTY()
	AWeaponBase* equipRangedWeapon;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ModifyHealth(float changeValue);

	UPROPERTY(BlueprintReadOnly)
	bool hasTakenPlayerDamage;

	UFUNCTION(BlueprintCallable)
	float MeleeAttack();

	UFUNCTION(BlueprintCallable)
	float RangedAttack();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	AMeleeBase* GetMeleeWeapon();

	UFUNCTION(BlueprintPure, BlueprintCallable)
	AWeaponBase* GetRangedWeapon();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

};
