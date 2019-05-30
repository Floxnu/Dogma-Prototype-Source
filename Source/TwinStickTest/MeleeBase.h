// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeleeBase.generated.h"


UCLASS()
class TWINSTICKTEST_API AMeleeBase : public AActor
{
	GENERATED_BODY()


	
public:	
	// Sets default values for this actor's properties
	AMeleeBase();

	UFUNCTION()
	void SetProjectileResponse(ADeflectResponseActor* newDeflectionResponse);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	class ADeflectResponseActor* deflectionResponse;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* weaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* weaponCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	float weaponMoveSpeedModifier;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	TSubclassOf<AActor> hitBoxClass;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon", meta = (DisplayName = "Is Weapon Drawn?"))
	bool isWeaponDrawn;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon", meta = (DisplayName = "Is Weapon Attacking"))
	bool isWeaponAttacking;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (DisplayName = "Weapon Default Cooldown"))
	float fireCooldown;

	UPROPERTY()
	bool weaponCanAttack;

	UPROPERTY()
	bool isAttacking;

	UFUNCTION()
	void WeaponCollisionTrace();

	UPROPERTY()
	TArray<AActor*> hitActors; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnWeaponOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(bool newState);

	UPROPERTY(BlueprintReadWrite)
	AActor* currentHitbox;

	UPROPERTY(EditDefaultsOnly)
	float weaponDamage;

};
