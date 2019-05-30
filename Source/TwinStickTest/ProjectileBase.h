// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	PT_Deflectable UMETA(DisplayName = "Deflectable"),
	PT_Destructable UMETA(DisplayName = "Destructable"),
	PT_Indestructable UMETA(DisplayName = "Indestructable")
};



UCLASS()
class TWINSTICKTEST_API AProjectileBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* ProjectileCollision;
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	void SetDamageType(TSubclassOf<UDamageType> projectileDamageType);

	void SetprojectileDamage(float damageToDeal);

	UFUNCTION(BlueprintCallable)
	EProjectileType GetProjectileType();

	UPROPERTY(BlueprintReadWrite)
	bool isDeflected;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly)
	EProjectileType projectileType;

	UPROPERTY()
	TSubclassOf<UDamageType> damageType;

	UPROPERTY()
	float projectileDamage;


	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
