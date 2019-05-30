// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	WT_Rifle UMETA(DisplayName = "Rifle"),
	WT_Pistol UMETA(DisplayName = "Pistol")
};



UCLASS()
class TWINSTICKTEST_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PrimaryFirePressed();

	virtual void PrimaryFireReleased();

	virtual void SecondaryButtonPressed();

	virtual void SecondaryButtonReleased();

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Weapon")
	virtual float GetMoveSpeedModifier();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void DrawWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void SheatheWeapon();

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectileBase> projectileClass;

	UFUNCTION()
	EWeaponType GetWeaponType();

	UFUNCTION()
	virtual void WeaponCooldownFinished();
		
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* projectileOrigin;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* weaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	float weaponMoveSpeedModifier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	float weaponDamage;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon", meta = (DisplayName = "Is Weapon Drawn?"))
	bool isWeaponDrawn;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon", meta = (DisplayName = "Is Weapon Attacking"))
	bool isWeaponAttacking;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon", meta = (DisplayName = "Maybe Reload Size"))
	int weaponClipSize;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (DisplayName = "Weapon Default Cooldown"))
	float fireCooldown;

	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (DisplayName = "Weapon Fire Anim"))
	class UAnimationAsset* weaponFireAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (DisplayName = "Weapon Type"))
	EWeaponType weaponType;

	virtual void FireWeapon();

	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* characterFireAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* weaponEquipAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShake> shotCameraShake;

	class ATwinStickPC* characterRef;

	bool weaponCanFire;

};
